#include "pch.h"
#include "EngineCore/Assets/AssetManager.hpp"
#include "EngineCore/Assets/Handles.hpp"
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Assets/Handles.hpp"

namespace engine::assets
{
	inline constexpr const std::uint8_t kMissingId = 0;
	inline constexpr const std::uint8_t kWhiteId = 1;

	void AssetManager::init()
	{
		m_Textures.reserve(0xFF);
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("untextured-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("white-fallback-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("grass-sprite-test.png"), engine::graphics::TextureParams{}));
		m_Textures.push_back(engine::graphics::Texture2D::fromFile(engine::io::sprites("face-sprite-test.png"), engine::graphics::TextureParams{}));
	}

	void AssetManager::shutdown()
	{
		m_Textures.clear();
	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::tryGetTexture(engine::assets::TextureHandle handle) const
	{
		// Fallback to white texture.
		// For now using 1 as white texture intentional.
		if (handle.id == kWhiteId)
			return whiteTexture();

		size_t index = static_cast<size_t>(handle.id);
		if (index >= m_Textures.size() || index >= UINT16_MAX)
			return missingTexture();

		const auto& opt = m_Textures[index];
		if (!opt.has_value())
			return missingTexture();

		return &*opt;
	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::missingTexture() const
	{
		std::uint16_t index = kMissingId;
		if (!m_Textures[index].has_value())
			throw std::runtime_error("The default 'Missing Texture' was not found");

		return &*m_Textures[index];
	}
	engine::assets::TextureHandle AssetManager::missing()
	{
		return engine::assets::TextureHandle{ static_cast<std::uint16_t>(kMissingId) };
	}

	[[nodiscard]] const engine::graphics::Texture2D* AssetManager::whiteTexture() const
	{
		std::uint16_t index = kWhiteId;
		if (!m_Textures[index].has_value())
			throw std::runtime_error("The default 'White Texture' was not found");

		return &*m_Textures[index];
	}
	engine::assets::TextureHandle AssetManager::white()
	{
		return engine::assets::TextureHandle{ static_cast<std::uint16_t>(kWhiteId) };
	}

	// TODO: Remove. Only for debug/test purposes.
	engine::assets::TextureHandle AssetManager::grass()
	{
		return engine::assets::TextureHandle{ 2 };
	}
	// TODO: Remove. Only for debug/test purposes.
	engine::assets::TextureHandle AssetManager::face()
	{
		return engine::assets::TextureHandle{ 3 };
	}
}