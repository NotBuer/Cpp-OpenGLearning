#pragma once
#include <vec2.hpp>
#include <vec4.hpp>

namespace engine::scene::components
{
	struct Sprite
	{
		std::uint16_t textureId;
		glm::vec4 color;

		Sprite(
			std::uint16_t textureId = 0,
			glm::vec4 color = glm::vec4(1.0f)
		) : textureId(textureId), color(color) {}
	};
}