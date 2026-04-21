#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/Renderer/Immediate3D.hpp"
#include "EngineCore/Renderer/Camera.hpp"
#include "EngineCore/Renderer/PerspectiveCamera.hpp"
#include "EngineCore/Renderer/OrthographicCamera.hpp"
#include "EngineCore/Events/Context.hpp"
#include "EngineCore/Scene/Scene.hpp"
#include "EngineCore/Renderer/RenderView.hpp"
#include "EngineCore/Renderer/SceneRenderer.hpp"

class DefaultLayer final : public engine::core::Layer
{
public:
	DefaultLayer(const std::string& name, const engine::platform::Window& window);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	bool OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx) override;

private:
	std::unique_ptr<engine::scene::Scene> m_Scene = nullptr;
	engine::renderer::RenderView m_RenderView;

	engine::renderer::RenderDevice m_RenderDevice;
	engine::renderer::SceneRenderer m_SceneRenderer{ m_RenderDevice };

	engine::renderer::RenderPassDesc world3D{ true, true, {0.15f,0.15f,0.18f,1.f} };

	std::unique_ptr<engine::renderer::PerspectiveCamera> m_PerspectiveCam = nullptr;
	std::unique_ptr<engine::renderer::OrthographicCamera> m_OrthographicCam = nullptr;

	//std::unique_ptr<engine::renderer::SpriteBatch> m_SpriteBatch = nullptr;
	std::unique_ptr<engine::renderer::Immediate3D> m_Immediate3D = nullptr;

	std::optional<engine::graphics::Texture2D> m_GrassTex;
	std::optional<engine::graphics::Texture2D> m_FaceTex;
};

