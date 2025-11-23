#pragma once
#include <cstdint>
#include "Categories.hpp"
#include "Types.hpp"

namespace engine::events
{
	// 16 bytes on 64-bit targets.
	struct EventHeader
	{
		std::uint16_t	type;			// EventType
		std::uint16_t	categories;		// Category flags
		std::uint16_t	priority;		// Priority
		std::uint8_t	handled;		// 0/1
		std::uint8_t	flags;			// Reserved/padding
		double			timestamp;		// Monotonic seconds
	};

	static_assert(sizeof(EventHeader) == 16, "EventHeader must be 16 bytes.");

	// Defined in the .cpp to avoid including heavy tables in headers.
	Category defaultCategories(EventType type) noexcept;
	Priority defaultPriority(EventType type) noexcept;
}
