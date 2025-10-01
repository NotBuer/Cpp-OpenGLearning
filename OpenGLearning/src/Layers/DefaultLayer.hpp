#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"

class DefaultLayer final : public engine::core::Layer
{
public:
	DefaultLayer(const std::string& name);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnRender() override;

private:
	engine::graphics::Shader m_Shader{};
	std::optional<engine::graphics::Texture2D> m_GrassTex;
	std::optional<engine::graphics::Texture2D> m_FaceTex;
};

