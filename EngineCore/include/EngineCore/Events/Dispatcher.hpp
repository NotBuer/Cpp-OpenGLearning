#pragma once
#include "Slot.hpp"

namespace engine
{
	namespace core { class Layerstack; } // Forward declaration.
}

namespace engine::events
{
	struct CaptureState; // Forward declaration.

	class Dispatcher
	{
	public:
		// Deliver to layers top->bottom;
		// Returns true if any layer handled the event.
		bool dispatch(const EventSlot& e, engine::core::Layerstack& layers, CaptureState& capture) noexcept;
	};
}