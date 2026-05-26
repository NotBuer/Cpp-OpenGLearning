#pragma once
#include "EngineCore/Assets/Handles.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Graphics/Shader.hpp"

namespace engine::assets
{
	class AssetManager
	{
	public:

		void init();
		void shutdown();

		[[nodiscard]] const engine::graphics::Texture2D* tryGetTexture(TextureHandle handle) const;


		[[nodiscard]] const engine::graphics::Texture2D* missingTexture() const;
		static engine::assets::TextureHandle missing();

		[[nodiscard]] const engine::graphics::Texture2D* whiteTexture() const;
		static engine::assets::TextureHandle white();

		static engine::assets::TextureHandle grass(); // TODO: Remove. Only for debug/test purposes.
		static engine::assets::TextureHandle face();  // TODO: Remove. Only for debug/test purposes.

	private:
		std::vector<std::optional<engine::graphics::Texture2D>> m_Textures;
	};
}