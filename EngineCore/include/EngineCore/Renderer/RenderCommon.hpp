#pragma once
#include <vec4.hpp>

namespace engine::renderer
{
	struct RenderPassDesc
	{
		bool clearColor = true;
		bool clearDepth = false;
		glm::vec4 clearValue { 0,0,0,1 };
		// TODO: framebuffer/viewport/...
	};
}