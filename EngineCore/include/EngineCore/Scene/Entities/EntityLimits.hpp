#pragma once
#include <cstdint>
#include <limits>

namespace engine::scene::entities
{ 
	inline constexpr const std::uint16_t kMaxEntities = std::numeric_limits<std::uint16_t>::max();
	inline constexpr const std::uint16_t kInvalidEntityIndex = std::numeric_limits<std::uint16_t>::max();
}