#pragma once
#include <cstdint>

namespace engine::events
{
	// 16-bit category mask.
	enum class Category : std::uint16_t
	{
		None		= 0,		// 00000000 00000000
		Application = 1u << 0,  // ...00000001 (decimal 1)
		Window		= 1u << 1,  // ...00000010 (decimal 2)
		Input		= 1u << 2,  // ...00000100 (decimal 4)
		Keyboard	= 1u << 3,  // ...00001000 (decimal 8)
		Mouse		= 1u << 4,  // ...00010000 (decimal 16)
		Text		= 1u << 5,  // ...00100000 (decimal 32)
		Gamepad		= 1u << 6,  // ...01000000 (decimal 64)
		UI			= 1u << 7   // ...10000000 (decimal 128)
	};

	[[nodiscard]] constexpr Category operator|(Category a, Category b)
	{
		return static_cast<Category>(static_cast<std::uint16_t>(a) | static_cast<std::uint16_t>(b));
	}

	[[nodiscard]] constexpr Category operator&(Category a, Category b)
	{
		return static_cast<Category>(static_cast<std::uint16_t>(a) & static_cast<std::uint16_t>(b));
	}

	constexpr Category& operator|=(Category& a, Category b) { a = a | b; return a; }
	constexpr Category& operator&=(Category& a, Category b) { a = a & b; return a; }

	[[nodiscard]] constexpr bool any(Category c) { return static_cast<std::uint16_t>(c) != 0; }
}
