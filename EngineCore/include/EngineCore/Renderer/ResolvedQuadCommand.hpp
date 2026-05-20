#pragma once
#include <vec2.hpp>
#include <vec4.hpp>
#include "EngineCore/Graphics/Texture2D.hpp"
#include "EngineCore/Assets/Handles.hpp"

namespace engine::renderer
{
	struct ResolvedQuadCommand
	{
		glm::vec2 min;
		glm::vec2 size;
		std::uint16_t textureSortKey;
		const engine::graphics::Texture2D* texture;
		glm::vec4 color;

		ResolvedQuadCommand(
			glm::vec2 min,
			glm::vec2 size,
			std::uint16_t textureSortKey,
			const engine::graphics::Texture2D* texture,
			glm::vec4 color
		): min(min), size(size), textureSortKey(textureSortKey), texture(texture), color(color) {}
	};
}