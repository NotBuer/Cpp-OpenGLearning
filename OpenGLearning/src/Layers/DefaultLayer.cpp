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
#include "EngineCore/Platform/Time.hpp"
#include "EngineCore/Platform/GlfwAdpter.hpp"
#include "EngineCore/Events/Types.hpp"

DefaultLayer::DefaultLayer(const std::string& name, const engine::platform::Window& window) :
	engine::core::Layer(name, window),
	m_RenderDevice({}),
	m_PerspectiveCam(
		std::make_unique<engine::renderer::PerspectiveCamera>(
			45.0f,
			static_cast<float>(window.getFramebufferWidth()) / static_cast<float>(window.getFramebufferHeight()),
			0.1f,
			100.0f
		)
	),
	m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice)),
	m_Immediate3D(std::make_unique<engine::renderer::Immediate3D>(m_RenderDevice))
{

}

void DefaultLayer::OnAttach()
{
	m_RenderDevice.Init();

	m_SpriteBatch->Init();
	m_Immediate3D->Init();

	glm::mat4 proj = glm::perspective(
		glm::radians(50.0f),
		static_cast<float>(window().getFramebufferWidth() / window().getFramebufferHeight()),
		0.1f, 100.0f);

	m_SpriteBatch->SetProjection(proj);
	m_Immediate3D->SetProjection(proj);

	m_PerspectiveCam->SetPosition({ 0.0f, 0.0f, 5.0f });

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

void DefaultLayer::OnUpdate(float dt)
{
	using KeyCode = engine::platform::KeyCode;
	const auto& input = window().inputState();

	glm::vec3 dir{ 0.0f };

	if (input.isKeyDown(KeyCode::W)) dir.z += 1.0f;
	if (input.isKeyDown(KeyCode::S)) dir.z -= 1.0f;
	if (input.isKeyDown(KeyCode::A)) dir.x -= 1.0f;
	if (input.isKeyDown(KeyCode::D)) dir.x += 1.0f;

	if (dir != glm::vec3{ 0.0f })
	{
		dir = glm::normalize(dir);
		m_PerspectiveCam->MoveLocal(dir * 10.0f * dt);
	}

	if (input.cursorX() == input.deltaX() && input.cursorY() == input.deltaY()) return;

	float sensitivity = 1.0f;
	m_PerspectiveCam->AddYawPitch(
		(static_cast<float>(input.deltaX()) * sensitivity * dt), 
		(static_cast<float>(input.deltaY()) * sensitivity * dt)
	);
}

void DefaultLayer::OnRender()
{
	uint16_t width = (window().getFramebufferWidth());
	uint16_t height = (window().getFramebufferHeight());
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

#pragma region 3D_PASS
	engine::renderer::RenderPassDesc world3D{
		.clearColor = true, .clearDepth = true,
		.clearValue = {0.15f, 0.15f, 0.18f, 1.f},
		.viewport = {0, 0, width, height}};
	m_RenderDevice.BeginPass(world3D);
	m_RenderDevice.SetCullFace(true);
	m_RenderDevice.setViewPort(world3D.viewport);

	glm::mat4 proj = m_PerspectiveCam->proj();

	m_Immediate3D->shader().Bind();
	m_GrassTex->bind(0);
	m_FaceTex->bind(1);
	m_Immediate3D->shader().setInt("u_tex", 0);
	m_Immediate3D->shader().setInt("u_tex2", 1);

	glm::mat4 model = 
		glm::rotate(glm::mat4(1.0f), static_cast<float>(engine::platform::Time::nowSeconds()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view = m_PerspectiveCam->view();

	m_Immediate3D->SetProjection(proj);
	m_Immediate3D->Begin(view, proj);
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	m_Immediate3D->DrawCube({ -0.5f, -0.5f, -0.5f }, { 1, 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });
	m_Immediate3D->End();



	model = glm::translate(
		glm::rotate(glm::mat4(1.0f), (static_cast<float>(engine::platform::Time::nowSeconds()) / 2) * glm::radians(-75.0f), glm::vec3(0.0f, 1.3f, 0.25f)),
		glm::vec3(0.0f, 0.0f, -5.0f));
	view = m_PerspectiveCam->view();
	m_Immediate3D->Begin(view, proj);;
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	m_Immediate3D->DrawCube({ -0.5f, -0.5f, -0.5f }, { 1, 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });
	m_Immediate3D->End();



	model = glm::translate(
		glm::rotate(glm::mat4(1.0f), (static_cast<float>(-engine::platform::Time::nowSeconds()) / 2) * glm::radians(-75.0f), glm::vec3(0.0f, 1.3f, 0.25f)),
		glm::vec3(0.0f, 0.0f, -5.0f));
	view = m_PerspectiveCam->view();
	m_Immediate3D->Begin(view, proj);
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_Immediate3D->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	m_Immediate3D->DrawCube({ -0.5f, -0.5f, -0.5f }, { 1, 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });
	m_Immediate3D->End();
#pragma endregion

#pragma region 2D_PASS
	//engine::renderer::RenderPassDesc world2D{ 
	//	.clearColor = true, .clearDepth = true, 
	//	.clearValue = {0.2f, 0.3f, 0.3f, 1.0f}, 
	//	.viewport = {0, 0, width, height}
	//};
	//m_RenderDevice.BeginPass(world2D);
	//m_RenderDevice.SetCullFace(false);
	//m_RenderDevice.setViewPort(world2D.viewport);

	//m_SpriteBatch->Begin();

	//m_SpriteBatch->shader().Bind();

	//m_GrassTex->bind(0);
	//m_FaceTex->bind(1);

	//m_SpriteBatch->shader().setInt("u_tex", 0);
	//m_SpriteBatch->shader().setInt("u_tex2", 1);

	//glm::mat4 model = glm::rotate(
	//	glm::mat4(1.0f), static_cast<float>(engine::platform::Time::nowSeconds()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

	//model = glm::rotate(
	//	glm::mat4(1.0f), static_cast<float>(engine::platform::Time::nowSeconds()) * glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(m_SpriteBatch->proj()));

	//m_SpriteBatch->DrawQuad({ -0.5f, -0.5f }, { 1, 1 }, { 0.0f, 0.0f, 0.0f, 1.0f });

	//m_SpriteBatch->End();
#pragma endregion
}

bool DefaultLayer::OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx)
{
	//using EventType = engine::events::EventType;
	//using KeyCode = engine::platform::KeyCode;

	//EventType eventType = static_cast<EventType>(e.header.type);

	//if (eventType == EventType::KeyPressed)
	//{
	//	const auto& keyData = e.payload.kp;
	//	// Do stuff...
	//	return true;
	//}

	//if (eventType == EventType::KeyReleased)
	//{
	//	const auto& keyData = e.payload.kr;
	//	// Do stuff...
	//	return true;
	//}

	(void)ctx;
	return true;
}