#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include "EngineCore/Assets/Handles.hpp"

namespace engine::renderer
{
	struct QuadCommand
	{
		glm::vec2 min;
		glm::vec2 size;
		engine::assets::TextureHandle textureHandle;
		glm::vec4 color;
	};
}