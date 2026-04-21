#include "pch.h"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"

namespace engine::renderer
{
	SceneRenderer::SceneRenderer(RenderDevice& device) :
		m_RenderDevice{ device },
		m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice))
	{
		m_RenderDevice.Init();
		m_SpriteBatch->Init(false);
	}

	void SceneRenderer::beginPass(const engine::renderer::RenderPassDesc& pass)
	{
		m_RenderDevice.BeginPass(pass);
		m_RenderDevice.setCullFace(true);
		m_RenderDevice.setViewPort(pass.viewport);
	}

	void SceneRenderer::render(const engine::renderer::RenderView& renderView)
	{
		m_SpriteBatch->SetProjection(renderView.camera.proj);

		m_SpriteBatch->DrawQuads(renderView.quads);
	}

	void SceneRenderer::endPass()
	{
		m_SpriteBatch->End();
	}
}