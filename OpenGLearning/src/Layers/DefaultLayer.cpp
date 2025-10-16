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

DefaultLayer::DefaultLayer(const std::string& name) : 
	engine::core::Layer(name),
	m_RenderDevice({}),
	m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice)),
	m_Immediate3D(std::make_unique<engine::renderer::Immediate3D>(m_RenderDevice))
{

}

void DefaultLayer::OnAttach()
{
	m_RenderDevice.Init();

	m_SpriteBatch->Init();
	m_Immediate3D->Init();

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	m_SpriteBatch->SetProjection(proj);
	m_Immediate3D->SetProjection(proj);

	m_GrassTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{});
	m_FaceTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{});
}

void DefaultLayer::OnDetach()
{
	m_SpriteBatch->Shutdown();
	m_Immediate3D->ShutDown();

	m_SpriteBatch = nullptr;
	m_Immediate3D = nullptr;
}

void DefaultLayer::OnUpdate()
{

}

void DefaultLayer::OnRender()
{
	// 3D world pass.
	//engine::renderer::RenderPassDesc world3D{ true, true, {0.15f,0.15f,0.18f,1.f} };
	m_RenderDevice.BeginPass(world3D);
	m_RenderDevice.SetCullFace(true);

	m_Immediate3D->shader().Bind();
	m_GrassTex->bind(0);
	m_FaceTex->bind(1);
	m_Immediate3D->shader().setInt("u_tex", 0);
	m_Immediate3D->shader().setInt("u_tex2", 1);

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	m_Immediate3D->Begin(view, proj);

	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	m_Immediate3D->DrawCube({ -0.5f, -0.5f, -0.5f }, {1, 1, 1}, { 0.0f, 0.0f, 0.0f, 1.0f });

	m_Immediate3D->End();

	model = glm::rotate(glm::mat4(1.0f), ((float)glfwGetTime() / 2) * glm::radians(-75.0f), glm::vec3(0.0f, 1.3f, 0.25f));
	view = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 1.0f, -10.0f));

	m_Immediate3D->Begin(view, proj);;

	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	m_Immediate3D->DrawCube({ -0.25f, -0.25f, -0.25f }, { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f, 1.0f });

	m_Immediate3D->End();

	// 2D pass.
	//engine::renderer::RenderPassDesc world2D{ .clearColor = true, .clearDepth = true, .clearValue = {0.2f, 0.3f, 0.3f, 1.0f} };
	//m_RenderDevice.BeginPass(world2D);
	//m_RenderDevice.SetCullFace(false);

	//m_SpriteBatch->Begin();

	//m_SpriteBatch->shader().Bind();

	//m_GrassTex->bind(0);
	//m_FaceTex->bind(1);
	//
	//m_SpriteBatch->shader().setInt("u_tex", 0);
	//m_SpriteBatch->shader().setInt("u_tex2", 1);

	//model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	//
	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(m_SpriteBatch->proj()));

	//m_SpriteBatch->DrawQuad({ -0.5f, -0.5f }, { 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });

	//m_SpriteBatch->End();
}
