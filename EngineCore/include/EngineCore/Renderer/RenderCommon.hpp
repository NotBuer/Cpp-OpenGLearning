#pragma once
#include <vec4.hpp>

namespace engine::renderer
{
	struct Viewport
	{
		int32_t x = 0;
		int32_t y = 0;
		int32_t width = 0;
		int32_t height = 0;
	};

	struct RenderPassDesc
	{
		bool clearColor = true;
		bool clearDepth = false;
		bool useBlend = false;
		glm::vec4 clearValue{ 0, 0, 0, 1 };
		Viewport viewport{ 0, 0, 0, 0 };
		// TODO: framebuffer...
	};
}