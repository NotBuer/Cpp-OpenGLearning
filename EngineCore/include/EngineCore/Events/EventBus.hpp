#pragma once
#include <cstdint>
#include "Slot.hpp"

namespace engine
{
	namespace core { class Layerstack; }
}

namespace engine::events
{
	class Dispatcher;
	struct CaptureState;

	// Two fixed-capacity SPSC rings: Immediate (High), Frame (Normal/Low).
	class EventBus
	{
	public:
		EventBus();
		~EventBus();

		EventBus(const EventBus&) = delete;				// Copy constructor.
		EventBus& operator=(const EventBus&) = delete;  // Copy assignment constructor.
		EventBus(EventBus&&) = delete;					// Move constructor.
		EventBus& operator=(EventBus&&) = delete;		// Move assignment constructor.

		// Producers (GLFW callbacks)
		void pushImmediate(const EventSlot& e) noexcept; 
		void pushFrame(const EventSlot& e) noexcept;

		// Consumers (Application::Run)
		void drainImmediate(Dispatcher& d, engine::core::Layerstack& layers, CaptureState& cap) noexcept;
		void drainFrame(Dispatcher& d, engine::core::Layerstack& layers, CaptureState& cap) noexcept;

		std::uint32_t droppedImmediate() const noexcept { return m_droppedImmediate; }
		std::uint32_t droppedFrame() const noexcept { return m_droppedFrame; }

	private:
		struct Impl;
		Impl* m_impl{ nullptr };

		std::uint32_t m_droppedImmediate{ 0 };
		std::uint32_t m_droppedFrame{ 0 };
	};
}
