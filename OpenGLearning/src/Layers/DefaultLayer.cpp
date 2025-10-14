#include <iostream>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "DefaultLayer.hpp"
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"

DefaultLayer::DefaultLayer(const std::string& name) : engine::core::Layer(name)
{
	m_RenderDevice = {};
}

void DefaultLayer::OnAttach()
{
	m_SpriteBatch = new engine::renderer::SpriteBatch(m_RenderDevice);
	//m_Immediate3D = new engine::renderer::Immediate3D(m_RenderDevice);

	m_RenderDevice.Init();
	m_SpriteBatch->Init();
	//m_Immediate3D->Init();

	//glm::mat4 proj = glm::ortho(0.f, 1280.0f, 720.0f, 0.f, -1.f, 1.f);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	m_SpriteBatch->SetProjection(proj);

	m_GrassTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{});
	m_FaceTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{});
}

void DefaultLayer::OnDetach()
{
	delete m_SpriteBatch; m_SpriteBatch = nullptr;
	//delete m_Immediate3D; m_Immediate3D = nullptr;

	//engine::renderer::SpriteBatch::Shutdown();
}

void DefaultLayer::OnUpdate()
{

}

void DefaultLayer::OnRender()
{
	using namespace engine::renderer;

	// 3D world pass.
	//RenderPassDesc world3D{ true, true, {0.15f,0.15f,0.18f,1.f} };
	//m_RenderDevice.BeginPass(world3D);
	//m_Immediate3D->Begin();
	// TODO: Draw 3D cube here...
	//m_Immediate3D->End();

	// 2D pass.
	RenderPassDesc world2D{ false, false, {} };
	m_RenderDevice.BeginPass(world2D);

	m_SpriteBatch->Begin();
	m_SpriteBatch->shader().Bind();

	m_GrassTex->bind(0);
	m_FaceTex->bind(1);
	
	m_SpriteBatch->shader().setInt("u_tex", 0);
	m_SpriteBatch->shader().setInt("u_tex2", 1);
	
	//m_RenderDevice.BindProgram(m_SpriteBatch->shader().id());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	
	int modelLocation = glGetUniformLocation(m_SpriteBatch->shader().id(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	
	int viewLocation = glGetUniformLocation(m_SpriteBatch->shader().id(), "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	
	int projectionLocation = glGetUniformLocation(m_SpriteBatch->shader().id(), "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(m_SpriteBatch->proj()));
	m_SpriteBatch->DrawQuad({ -0.5f, -0.5f }, { 1, 1 }, { 1.0f, 0.0f, 0.0f, 1.0f });

	m_SpriteBatch->End();
}
