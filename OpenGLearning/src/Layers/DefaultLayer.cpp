#include <iostream>
#include "DefaultLayer.hpp"
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Renderer/Renderer2D.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"

DefaultLayer::DefaultLayer(const std::string& name) : engine::core::Layer(name)
{

}

void DefaultLayer::OnAttach()
{
	engine::renderer::Renderer2D::Init();

	m_Shader = engine::graphics::Shader{ engine::io::shader("basic.vert").c_str(), engine::io::shader("basic.frag").c_str() };

	m_GrassTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{});
	m_FaceTex = engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{});
}

void DefaultLayer::OnDetach()
{
	engine::renderer::Renderer2D::Shutdown();
}

void DefaultLayer::OnUpdate()
{

}

void DefaultLayer::OnRender()
{
	m_GrassTex->bind(0);
	m_FaceTex->bind(1);

	m_Shader.setInt("u_tex", 0);
	m_Shader.setInt("u_tex2", 1);

	engine::renderer::Renderer2D::BeginPass(m_Shader);

	engine::renderer::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 1, 1 }, { 1.0f, 0.0f, 0.0f, 1.0f });

	engine::renderer::Renderer2D::EndPass();
}
