#pragma once
#include <cstdint>
#include "Modifiers.hpp"
#include "EngineCore/Platform/GlfwAdpter.hpp"

namespace engine::events
{
	using KeyCode = engine::platform::KeyCode;

	// Window/Application.
	struct WindowClose { /* empty */ };
	struct WindowFocusChanged { bool focused; std::uint8_t _pad[7]{}; };
	struct WindowResized { int fbWidth; int fbHeight; };

	// Keyboard/Text.
	struct KeyPressed { KeyCode key; int scancode; std::uint16_t mods; std::uint8_t repeat; std::uint8_t _pad{}; };
	struct KeyReleased { KeyCode key; int scancode; std::uint16_t mods; std::uint16_t _pad{}; };
	struct TextInput { std::uint32_t codepoint; std::uint32_t _pad{}; };

	// Mouse.
	struct MouseButtonPressed { int button; std::uint16_t mods; std::uint16_t _pad{}; };
	struct MouseButtonReleased { int button; std::uint16_t mods; std::uint16_t _pad{}; };
	struct MouseMoved { double x; double y; };		// logical pixels.
	struct MouseDelta { double dx; double dy; };	// relative (locked).
	struct MouseScrolled { double dx; double dy; }; // high-precision.

	// Size checks: each payload <= 32 bytes.
	static_assert(sizeof(WindowClose)			<= 32);
	static_assert(sizeof(WindowFocusChanged)	<= 32);
	static_assert(sizeof(WindowResized)			<= 32);
	static_assert(sizeof(KeyPressed)			<= 32);
	static_assert(sizeof(KeyReleased)			<= 32);
	static_assert(sizeof(TextInput)				<= 32);
	static_assert(sizeof(MouseButtonPressed)	<= 32);
	static_assert(sizeof(MouseButtonReleased)	<= 32);
	static_assert(sizeof(MouseMoved)			<= 32);
	static_assert(sizeof(MouseDelta)			<= 32);
	static_assert(sizeof(MouseScrolled)			<= 32);
}