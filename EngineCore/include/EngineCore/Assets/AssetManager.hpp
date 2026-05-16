#pragma once
#include "EngineCore/Assets/Handles.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Graphics/Shader.hpp"

namespace engine::assets
{
	using TextureHandle = engine::assets::TextureHandle;

	class AssetManager
	{
	public:

		void init();
		void shutdown();

		[[nodiscard]] const engine::graphics::Texture2D* tryGetTexture(TextureHandle handle) const;
		[[nodiscard]] const engine::graphics::Texture2D* missingTexture() const;
		[[nodiscard]] const engine::graphics::Texture2D* whiteTexture() const;

	private:
		std::vector<std::optional<engine::graphics::Texture2D>> m_Textures;
	};
}