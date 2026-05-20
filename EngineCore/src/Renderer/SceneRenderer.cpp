#include "pch.h"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"
#include "EngineCore/Assets/AssetManager.hpp"
#include "EngineCore/Core/Assert.hpp"

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
		if (m_CommandOut.capacity() < renderView.quads.capacity())
			m_CommandOut.reserve(renderView.quads.capacity());

		m_SpriteBatch->Begin(renderView.camera.view, renderView.camera.proj, false);

		m_SpriteBatch->DrawQuads(quadCommandResolver(renderView.quads));
	}

	void SceneRenderer::endPass()
	{
		m_SpriteBatch->End();

		m_CommandOut.clear();
	}

	const std::span<const engine::renderer::ResolvedQuadCommand> SceneRenderer::quadCommandResolver(
		const std::span<const engine::renderer::QuadCommand> quadCommands)
	{
		for (std::size_t i = 0; i < quadCommands.size(); ++i)
		{
			auto* texture =  m_Assets.tryGetTexture(quadCommands[i].textureHandle);
			ENGINE_ASSERT_MSG(texture != nullptr, "tryGetTexture must never return nullptr!");

			m_CommandOut.emplace_back(
				quadCommands[i].min,
				quadCommands[i].size,
				quadCommands[i].textureHandle.id,
				texture,
				quadCommands[i].color
			);
		}

		// TODO:
		// Later add more complex sorting, it will reduce draw calls.
		// I need to keep in mind the correctness:
		// Layer, order and Z first, then so optimize texture... 
		// (grouping by texture only inside the same render-order bucket).
		std::sort(m_CommandOut.begin(), m_CommandOut.end(), [](const auto& a, const auto& b)
			{
				// Ascending order.
				return a.textureSortKey < b.textureSortKey;
			});

		return m_CommandOut;
	}
}
