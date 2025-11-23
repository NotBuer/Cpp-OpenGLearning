#pragma once
#include <cstdint>

namespace engine::core { class Layer; }

namespace engine::events
{
	// Routes certain categories exclusively to one consumer (e.g., a layer).
	struct CaptureState
	{
		// Bitmask of captured categories (e.g., Keyboard | Mouse).
		std::uint16_t captured{ 0 };

		// Owner pointer.
		engine::core::Layer* owner{ nullptr };

		void capture(std::uint16_t cats, engine::core::Layer* who) noexcept
		{
			captured |= cats;
			owner = who;
		}

		void release(std::uint16_t cats) noexcept
		{
			captured &= ~cats;
			if (captured == 0) owner = nullptr;
		}

		void releaseAll() noexcept { captured = 0; owner = nullptr; }

		[[nodiscard]] bool isCaptured(std::uint16_t mask) const noexcept
		{
			return (captured & mask) != 0;
		}
	};
}
