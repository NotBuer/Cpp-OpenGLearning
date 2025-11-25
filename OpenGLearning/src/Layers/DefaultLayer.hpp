#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/Renderer/Immediate3D.hpp"
#include "EngineCore/Renderer/Camera.hpp"
#include "EngineCore/Renderer/PerspectiveCamera.hpp"
#include "EngineCore/Renderer/OrthographicCamera.hpp"

class DefaultLayer final : public engine::core::Layer
{
public:
	DefaultLayer(const std::string& name, const engine::platform::Window& window);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnRender() override;
	bool OnEvent(const engine::events::EventSlot& e) override;

private:
	engine::renderer::RenderDevice m_RenderDevice;
	engine::renderer::RenderPassDesc world3D{ true, true, {0.15f,0.15f,0.18f,1.f} };

	//engine::renderer::PerspectiveCamera m_PerspectiveCam;
	//engine::renderer::OrthographicCamera m_OrthographicCam;

	std::unique_ptr<engine::renderer::SpriteBatch> m_SpriteBatch = nullptr;
	std::unique_ptr<engine::renderer::Immediate3D> m_Immediate3D = nullptr;

	std::optional<engine::graphics::Texture2D> m_GrassTex;
	std::optional<engine::graphics::Texture2D> m_FaceTex;
};

