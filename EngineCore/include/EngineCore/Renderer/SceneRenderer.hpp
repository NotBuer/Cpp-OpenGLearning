#pragma once
#include "EngineCore/Renderer/RenderCommon.hpp"
#include "EngineCore/Renderer/RenderView.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Assets/AssetManager.hpp"
#include "EngineCore/Renderer/ResolvedQuadCommand.hpp"

namespace engine::renderer { class RenderDevice; }

namespace engine::renderer
{
	class SceneRenderer
	{
	public:
		explicit SceneRenderer(RenderDevice& device, engine::assets::AssetManager& assetManager);

		void init();
		void shutdown();

		void beginPass(const engine::renderer::RenderPassDesc& pass);
		void render(const engine::renderer::RenderView& renderView);
		void endPass();

		const std::span<const engine::renderer::ResolvedQuadCommand>
			quadCommandResolver(const std::span<const engine::renderer::QuadCommand> quadCommands);

	private:
		RenderDevice& m_RenderDevice;
		engine::assets::AssetManager& m_Assets;

		std::vector<engine::renderer::ResolvedQuadCommand> m_CommandOut;

		std::unique_ptr<engine::renderer::SpriteBatch> m_SpriteBatch = nullptr;
	};
}