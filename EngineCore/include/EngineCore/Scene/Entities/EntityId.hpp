#pragma once
#include <cstdint>
#include "EngineCore/Scene/Entities/EntityLimits.hpp"

namespace engine::scene::entities
{
	using EntityIndex = std::uint16_t;
	using EntityGeneration = std::uint16_t;

	struct EntityId
	{
		EntityIndex index = kInvalidEntityIndex;
		EntityGeneration generation = 0;

		bool isValid() const noexcept
		{
			return index != kInvalidEntityIndex;
		}

		bool operator==(const EntityId& other) const noexcept = default;
	};
}
