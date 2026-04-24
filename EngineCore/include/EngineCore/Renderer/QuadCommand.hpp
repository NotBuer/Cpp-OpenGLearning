#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>

namespace engine::renderer
{
	struct QuadCommand
	{
		glm::vec2 min;
		glm::vec2 size;
		glm::vec4 color;
	};
}