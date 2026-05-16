#pragma once
#include <vec2.hpp>
#include <vec4.hpp>
#include "EngineCore/Graphics/Texture2D.hpp"

namespace engine::renderer
{
	struct ResolvedQuadCommand
	{
		glm::vec2 min;
		glm::vec2 size;
		const engine::graphics::Texture2D& texture;
		glm::vec4 color;

		ResolvedQuadCommand(
			glm::vec2 min,
			glm::vec2 size,
			const engine::graphics::Texture2D& texture,
			glm::vec4 color
		): min(min), size(size), texture(texture), color(color) {}
	};
}