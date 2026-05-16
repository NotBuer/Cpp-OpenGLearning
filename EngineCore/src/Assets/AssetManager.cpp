#include "pch.h"
#include "EngineCore/Assets/AssetManager.hpp"
#include "EngineCore/Assets/Handles.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/IO/AssetPath.hpp"

namespace engine::assets
{
	void AssetManager::init()
	{
		// The first texture always should be the one that represents a texturing problem.
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("untextured-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("white-fallback-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{}));
	}

	void AssetManager::shutdown()
	{

	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::tryGetTexture(engine::assets::TextureHandle handle) const
	{
		// Fallback to white texture.
		// For now using 0 as white texture intentional.
		if (handle.id == 0)
			return whiteTexture();

		size_t index = static_cast<size_t>(handle.id);
		if (index >= m_Textures.size())
			return missingTexture();

		const auto& opt = m_Textures[index];
		if (!opt.has_value())
			return missingTexture();

		return &*opt;
	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::missingTexture() const
	{
		return &*m_Textures[0];
	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::whiteTexture() const
	{
		return &*m_Textures[1];
	}
}