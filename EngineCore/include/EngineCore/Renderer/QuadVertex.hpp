#pragma once
#include <vec2.hpp>
#include <vec3.hpp>

namespace engine::renderer
{
	struct QuadVertex
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 uv;
	};
}