#pragma once
#include <cstdint>

namespace engine::assets
{
	// Here 0 means invalid id.

	struct TextureHandle
	{
		std::uint16_t id = 0;
	};

	struct ShaderHandle
	{
		std::uint16_t id = 0;
	};
}
