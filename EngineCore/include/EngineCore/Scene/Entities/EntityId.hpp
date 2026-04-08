#pragma once
#include <cstdint>

namespace engine::scene::entities
{
	struct EntityId
	{
		std::uint32_t index;

		bool operator==(const EntityId& other) const noexcept { return this->index == other.index; }
		bool operator!=(const EntityId& other) const noexcept { return this->index != other.index; }
	};
}
