#include "pch.h"
#include "EngineCore/Events/InputState.hpp"
#include "EngineCore/Platform/GlfwAdpter.hpp"

namespace engine::events
{ 
	using KeyCode = engine::platform::KeyCode;

	[[nodiscard]] static inline std::size_t to_index(KeyCode key) noexcept
	{
		return static_cast<std::size_t>(static_cast<std::uint16_t>(key));
	}

	[[nodiscard]] static inline bool is_valid_key(KeyCode key, std::size_t index) noexcept
	{
		return (key != KeyCode::Unknown) && (index > 0 && index < InputState::MaxKeys);
	}

	void InputState::setKeyDown(KeyCode key, bool down) noexcept
	{
		std::size_t index = to_index(key);
		if (!is_valid_key(key, index)) return;
		m_keys[index] = down ? 1u : 0u;
	}

	void InputState::setMouseDown(int button, bool down) noexcept
	{
		if (button >= 0 && button < MaxMouse) m_mouse[static_cast<std::size_t>(button)] = down ? 1u : 0u;
	}

	void InputState::setCursorPos(double x, double y) noexcept
	{
		m_cursorX = x; m_cursorY = y;
	}

	void InputState::addScroll(double dx, double dy) noexcept
	{
		m_wheelX += dx; m_wheelY += dy;
	}

	void InputState::finalizeFrame() noexcept
	{
		m_deltaX = m_cursorX - m_prevX;
		m_deltaY = m_prevY - m_cursorY; // reversed since y-coordinates go from bottom to top.
		m_prevX = m_cursorX; 
		m_prevY = m_cursorY;

		m_prevKeys = m_keys;
		m_prevMouse = m_mouse;
	}

	bool InputState::isKeyDown(KeyCode key) const noexcept
	{
		std::size_t index = to_index(key);
		if (!is_valid_key(key, index)) return false;
		return m_keys[index] != 0u;
	}

	bool InputState::wasKeyPressed(KeyCode key) const noexcept
	{
		std::size_t index = to_index(key);
		if (!is_valid_key(key, index)) return false;
		return m_keys[index] != 0u && m_prevKeys[index] == 0;
	}

	bool InputState::wasKeyReleased(KeyCode key) const noexcept
	{
		std::size_t index = to_index(key);
		if (!is_valid_key(key, index)) return false;
		return (m_keys[index] == 0u) && (m_prevKeys[index] != 0u);
	}

	bool InputState::isMouseDown(int btn) const noexcept
	{
		return (btn >= 0 && btn < MaxMouse) ? m_mouse[static_cast<std::size_t>(btn)] != 0u : false;
	}

	void InputState::clearOnFocusLost() noexcept
	{
		std::fill(m_keys.begin(), m_keys.end(), 0u);
		std::fill(m_mouse.begin(), m_mouse.end(), 0u);
		std::fill(m_prevKeys.begin(), m_prevKeys.end(), 0u);
		std::fill(m_prevMouse.begin(), m_prevMouse.end(), 0u);
		m_deltaX = m_deltaY = 0.0;
		m_wheelX = m_wheelY = 0.0;
	}
}