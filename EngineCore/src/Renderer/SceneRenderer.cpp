#include "pch.h"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"

namespace engine::renderer
{
	SceneRenderer::SceneRenderer(RenderDevice& device) :
		m_RenderDevice{ device }
	{
		m_RenderDevice.Init();
	}

	void SceneRenderer::beginPass(const engine::renderer::RenderPassDesc& pass)
	{
		m_RenderDevice.BeginPass(pass);
		m_RenderDevice.setCullFace(true);
		m_RenderDevice.setViewPort(pass.viewport);
	}

	void SceneRenderer::render(const engine::renderer::RenderView& view)
	{

	}

	void SceneRenderer::endPass()
	{

	}
}