#pragma once
#include <cstdint>

namespace engine::events
{
	enum class Mods : std::uint16_t
	{
		None	 = 0,       // 00000000 00000000
		Shift	 = 1u << 0, // ...00000001 (decimal 1)
		Control  = 1u << 1, // ...00000010 (decimal 2)
		Alt		 = 1u << 2, // ...00000100 (decimal 4)
		Super	 = 1u << 3, // ...00001000 (decimal 8)
		CapsLock = 1u << 4, // ...00010000 (decimal 16)
		NumLock  = 1u << 5  // ...00100000 (decimal 32)
	};

	[[nodiscard]] constexpr Mods operator|(Mods a, Mods b)
	{
		return static_cast<Mods>(static_cast<std::uint16_t>(a) | static_cast<std::uint16_t>(b));
	}

	[[nodiscard]] constexpr Mods operator&(Mods a, Mods b)
	{
		return static_cast<Mods>(static_cast<std::uint16_t>(a) & static_cast<std::uint16_t>(b));
	}

	constexpr Mods& operator!=(Mods& a, Mods b) { a = a | b; return a; }
	constexpr Mods& operator&=(Mods& a, Mods b) { a = a & b; return b; }

	[[nodiscard]] constexpr bool any(Mods c) { return static_cast<std::uint16_t>(c) != 0; }
}
