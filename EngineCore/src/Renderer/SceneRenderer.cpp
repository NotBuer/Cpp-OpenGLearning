#include "pch.h"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"

namespace engine::renderer
{
	SceneRenderer::SceneRenderer(RenderDevice& device) :
		m_RenderDevice{ device },
		m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice))
	{
		m_RenderDevice.Init();
		m_SpriteBatch->Init();

		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{}));
	}

	void SceneRenderer::beginPass(const engine::renderer::RenderPassDesc& pass)
	{
		m_RenderDevice.BeginPass(pass);
		m_RenderDevice.setCullFace(true);
		m_RenderDevice.setViewPort(pass.viewport);
	}

	void SceneRenderer::render(const engine::renderer::RenderView& renderView)
	{
		m_SpriteBatch->Begin(renderView.camera.view, renderView.camera.proj, m_Textures, false);
		m_SpriteBatch->DrawQuads(renderView.quads, m_Textures);
	}

	void SceneRenderer::endPass()
	{
		m_SpriteBatch->End();
	}
}