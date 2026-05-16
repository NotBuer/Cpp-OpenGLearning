#include "pch.h"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"
#include "EngineCore/Assets/AssetManager.hpp"

namespace engine::renderer
{
	SceneRenderer::SceneRenderer(RenderDevice& device, engine::assets::AssetManager& assetManager) :
		m_RenderDevice{ device },
		m_Assets{ assetManager },
		m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice))
	{ 
		
	}

	void SceneRenderer::init()
	{
		m_RenderDevice.init();
		m_SpriteBatch->init();
	}

	void SceneRenderer::shutdown()
	{
		m_SpriteBatch->shutdown();
	}

	void SceneRenderer::beginPass(const engine::renderer::RenderPassDesc& pass)
	{
		m_RenderDevice.BeginPass(pass);
		m_RenderDevice.setCullFace(true);
		m_RenderDevice.setViewPort(pass.viewport);
	}

	void SceneRenderer::render(const engine::renderer::RenderView& renderView)
	{
		// Update the vector capacity to always match when renderView size exceeds.
		if (m_CommandOut.size() < renderView.quads.size())
			m_CommandOut.reserve(renderView.quads.size());

		m_SpriteBatch->Begin(renderView.camera.view, renderView.camera.proj, false);
		m_SpriteBatch->DrawQuads(quadCommandResolver(renderView.quads));
	}

	void SceneRenderer::endPass()
	{
		m_CommandOut.clear();
		m_SpriteBatch->End(); 
	}

	const std::span<const engine::renderer::ResolvedQuadCommand> SceneRenderer::quadCommandResolver(
		const std::span<const engine::renderer::QuadCommand> quadCommands)
	{
		// TODO:
		// Later add sorting taking advantage of the iteration.
		// It will reduce draw calls.
		// I need to keep in mind the correctness:
		// Layer, order and Z first, then so optimize texture... 
		// (grouping by texture only inside the same render-order bucket).

		for (auto& quadCommand : quadCommands)
		{
			m_CommandOut.emplace_back(
					quadCommand.min,
					quadCommand.size,
					*m_Assets.tryGetTexture(quadCommand.textureHandle),
					quadCommand.color
				);
		}
		return m_CommandOut;
	}
}