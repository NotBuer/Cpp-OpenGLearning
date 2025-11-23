#pragma once
#include <cstdint>

namespace engine::events
{
	enum class Priority : std::uint8_t { Low = 0, Normal = 1, High = 2 };

	enum class EventType : std::uint16_t
	{
		// Window/Application.
		WindowClose = 0,
		WindowFocusChanged,
		WindowResized,

		// Keyboard/Text.
		KeyPressed,
		KeyReleased,
		TextInput,

		// Mouse.
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseDelta,
		MouseScrolled
	};
}
