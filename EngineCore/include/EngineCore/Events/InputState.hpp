#pragma once
#include <cstdint>
#include <array>

namespace engine::events
{
	// Polled input snapshot for a frame.
	class InputState
	{
	public:
		static constexpr int MaxKeys = 512;
		static constexpr int MaxMouse = 8;

		// Update from callbacks.
		void setKeyDown(int key, bool down) noexcept;
		void setMouseDown(int button, bool down) noexcept;
		void setCursorPos(double x, double y) noexcept;
		void addScroll(double dx, double dy) noexcept;

		// Finalize at frame start (compute deltas, reset accumulators...).
		void finalizeFrame() noexcept;

		// Queries used by gameplay systems.
		[[nodiscard]] bool isKeyDown(int key) const noexcept;
		[[nodiscard]] bool wasKeyPressed(int key) const noexcept;
		[[nodiscard]] bool wasKeyReleased(int key) const noexcept;
		[[nodiscard]] bool isMouseDown(int btn) const noexcept;

		[[nodiscard]] double cursorX() const noexcept { return m_cursorX; }
		[[nodiscard]] double cursorY() const noexcept { return m_cursorY; }
		[[nodiscard]] double deltaX() const noexcept { return m_deltaX; }
		[[nodiscard]] double deltaY() const noexcept { return m_deltaY; }
		[[nodiscard]] double wheelX() const noexcept { return m_wheelX; }
		[[nodiscard]] double wheelY() const noexcept { return m_wheelY; }

		void clearOnFocusLost() noexcept; // Reset pressed states/deltas.

	private:
		std::array<std::uint8_t, MaxKeys> m_keys{}; // 1 = down, 0 = up.
		std::array<std::uint8_t, MaxKeys> m_prevKeys{}; // previous frame snapshot.
		std::array<std::uint8_t, MaxMouse> m_mouse{}; // 1 = down, 0 = up.
		std::array<std::uint8_t, MaxMouse> m_prevMouse{}; // previous frame snapshot.

		double m_cursorX{ 0.0 }, m_cursorY{ 0.0 };
		double m_prevX{ 0.0 }, m_prevY{ 0.0 };
		double m_deltaX{ 0.0 }, m_deltaY{ 0.0 };
		double m_wheelX{ 0.0 }, m_wheelY{ 0.0 };
	};
}
