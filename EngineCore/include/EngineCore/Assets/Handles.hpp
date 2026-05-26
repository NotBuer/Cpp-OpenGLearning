#pragma once
#include <cstdint>

namespace engine::assets
{
	// Default initialize as white-blank.
	struct TextureHandle
	{
		std::uint16_t id = 1;
	};

	struct ShaderHandle
	{
		std::uint16_t id = 0;
	};
}
