#include "pch.h"
#include "EngineCore/Platform/Time.hpp"
#include "EngineCore/Renderer/detail/GL.hpp"

namespace engine::platform
{
	double Time::nowSeconds() noexcept
	{
		return glfwGetTime();
	}
}