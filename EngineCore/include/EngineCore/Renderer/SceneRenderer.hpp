#pragma once
#include "EngineCore/Renderer/RenderCommon.hpp"
#include "EngineCore/Renderer/RenderView.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"

namespace engine::renderer { class RenderDevice; }

namespace engine::renderer
{
	class SceneRenderer
	{
	public:
		explicit SceneRenderer(RenderDevice& device);

		void beginPass(const engine::renderer::RenderPassDesc& pass);
		void render(const engine::renderer::RenderView& renderView);
		void endPass();

	private:
		RenderDevice& m_RenderDevice;

		std::unique_ptr<engine::renderer::SpriteBatch> m_SpriteBatch = nullptr;
	};
}