#pragma once
#include <cstdint>
#include <string>
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Events/Modifiers.hpp"

namespace engine::platform
{
	enum class KeyCode : std::uint16_t
	{
		Unknown = 0,
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		Space = GLFW_KEY_SPACE,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		Tab = GLFW_KEY_TAB,
	};

	/// <summary>
	/// Converts a GLFW key code to engine KeyCode
	/// </summary>
	/// <param name="glfwKey">glfw key code</param>
	/// <returns></returns>
	[[nodiscard]] static inline KeyCode key_code(int glfwKey) noexcept
	{
		if (glfwKey < 0) 
			return KeyCode::Unknown; // GLFW_KEY_UNKNOWN

		return static_cast<KeyCode>(static_cast<std::uint16_t>(glfwKey));
	}

	[[nodiscard]] static inline const char* action_name(int action) noexcept
	{
		switch (action)
		{
			case GLFW_PRESS:		return "PRESSED";
			case GLFW_RELEASE:		return "RELEASED";
			case GLFW_REPEAT:		return "REPEATED";
			default:				return "UNKNOWN";
		}
	}

	[[nodiscard]] static inline std::string key_name(int key, int scancode) noexcept
	{
		if (const char* printable = glfwGetKeyName(key, scancode))
		{
			return std::string(printable);
		}

		switch (key)
		{
			case GLFW_KEY_SPACE:			return "SPACE";
			case GLFW_KEY_ENTER:			return "ENTER";
			case GLFW_KEY_TAB:				return "TAB";
			case GLFW_KEY_BACKSPACE:		return "BACKSPACE";
			case GLFW_KEY_ESCAPE:			return "ESCAPE";
			case GLFW_KEY_LEFT_SHIFT:		return "LEFT SHIFT";
			case GLFW_KEY_RIGHT_SHIFT:		return "RIGHT SHIFT";
			case GLFW_KEY_LEFT_CONTROL:		return "LEFT CONTROL";
			case GLFW_KEY_RIGHT_CONTROL:	return "RIGHT CONTROL";
			case GLFW_KEY_LEFT_ALT:			return "LEFT ALT";
			case GLFW_KEY_RIGHT_ALT:		return "RIGHT ALT";
			case GLFW_KEY_LEFT_SUPER:		return "LEFT SUPER";
			case GLFW_KEY_RIGHT_SUPER:		return "RIGHT SUPER";
			case GLFW_KEY_CAPS_LOCK:		return "CAPS LOCK";
			case GLFW_KEY_UP:				return "UP";
			case GLFW_KEY_DOWN:				return "DOWN";
			case GLFW_KEY_LEFT:				return "LEFT";
			case GLFW_KEY_RIGHT:			return "RIGHT";
			default: {
				char buf[32];
				std::snprintf(buf, sizeof(buf), "KeyCode(%d)", key);
				return std::string(buf);
			}
		}
	}

	[[nodiscard]] static inline std::string mousebutton_name(int button) noexcept
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:		return "MOUSE LEFT BUTTON";
			case GLFW_MOUSE_BUTTON_RIGHT:		return "MOUSE RIGHT BUTTON";
			case GLFW_MOUSE_BUTTON_MIDDLE:		return "MOUSE MIDDLE BUTTON";
			default: {
				char buf[32];
				std::snprintf(buf, sizeof(buf), "MouseButton(%d)", button);
				return std::string(buf);
			}
		}
	}

	[[nodiscard]] static inline std::string mods_string(int glfwMods) noexcept
	{
		std::string s;
		if (glfwMods & GLFW_MOD_SHIFT)		s += "Shift+";
		if (glfwMods & GLFW_MOD_CONTROL)	s += "Ctrl+";
		if (glfwMods & GLFW_MOD_ALT)		s += "Alt+";
		if (glfwMods & GLFW_MOD_SUPER)		s += "Super+";
		if (glfwMods & GLFW_MOD_CAPS_LOCK)	s += "CapsLock+";
		if (glfwMods & GLFW_MOD_NUM_LOCK)	s += "NumLock+";
		if (!s.empty()) s.pop_back();
		return s;
	}

	[[nodiscard]] static inline std::uint16_t mods_bits(int glfwMods) noexcept
	{
		using Mods = engine::events::Mods;
		using U16 = std::uint16_t;
		U16 mods = 0;
		if (glfwMods & GLFW_MOD_SHIFT)		mods |= static_cast<U16>(Mods::Shift);
		if (glfwMods & GLFW_MOD_CONTROL)	mods |= static_cast<U16>(Mods::Control);
		if (glfwMods & GLFW_MOD_ALT)		mods |= static_cast<U16>(Mods::Alt);
		if (glfwMods & GLFW_MOD_SUPER)		mods |= static_cast<U16>(Mods::Super);
		if (glfwMods & GLFW_MOD_CAPS_LOCK)	mods |= static_cast<U16>(Mods::CapsLock);
		if (glfwMods & GLFW_MOD_NUM_LOCK)	mods |= static_cast<U16>(Mods::NumLock);
		return mods;
	}
}