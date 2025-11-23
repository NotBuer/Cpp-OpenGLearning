#include "pch.h"
#include "EngineCore/Events/InputState.hpp"

namespace engine::events
{ 
	void InputState::setKeyDown(int key, bool down) noexcept
	{
		if (key >= 0 && key < MaxKeys) m_keys[static_cast<std::size_t>(key)] = down ? 1u : 0u;
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
		m_deltaY = m_cursorY - m_prevY;
		m_prevX = m_cursorX; m_prevY = m_cursorY;

		m_prevKeys = m_keys;
		m_prevMouse = m_mouse;
	}

	bool InputState::isKeyDown(int key) const noexcept
	{
		return (key >= 0 && key < MaxKeys) ? m_keys[static_cast<std::size_t>(key)] != 0u : false;
	}

	bool InputState::wasKeyPressed(int key) const noexcept
	{
		if (key < 0 || key > MaxKeys) return false;
		auto i = static_cast<std::size_t>(key);
		return (m_keys[i] != 0u) && (m_prevKeys[i] == 0u);
	}

	bool InputState::wasKeyReleased(int key) const noexcept
	{
		if (key < 0 || key > MaxKeys) return false;
		auto i = static_cast<std::size_t>(key);
		return (m_keys[i] == 0u) && (m_prevKeys[i] != 0u);
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