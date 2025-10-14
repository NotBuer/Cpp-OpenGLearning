#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/Renderer/Immediate3D.hpp"

class DefaultLayer final : public engine::core::Layer
{
public:
	DefaultLayer(const std::string& name);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnRender() override;

private:
	engine::renderer::RenderDevice m_RenderDevice;
	engine::renderer::SpriteBatch* m_SpriteBatch = nullptr;
	engine::renderer::Immediate3D* m_Immediate3D = nullptr;

	std::optional<engine::graphics::Texture2D> m_GrassTex;
	std::optional<engine::graphics::Texture2D> m_FaceTex;
};

