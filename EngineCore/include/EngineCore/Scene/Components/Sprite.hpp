#pragma once
#include <vec2.hpp>
#include <vec4.hpp>
#include "EngineCore/Assets/Handles.hpp"

namespace engine::scene::components
{
	struct Sprite
	{
		engine::assets::TextureHandle textureHandle;
		glm::vec4 color;

		Sprite(
			engine::assets::TextureHandle textureHandle = {},
			glm::vec4 color = glm::vec4(1.0f)
		) : textureHandle(textureHandle), color(color) {}
	};
}