#include "pch.h"
#include "EngineCore/Events/Dispatcher.hpp"
#include "EngineCore/Events/CaptureState.hpp"
#include "EngineCore/Core/Layerstack.hpp"
#include "EngineCore/Core/Layer.hpp"

namespace engine::events
{
	static inline bool intersects(std::uint16_t mask, std::uint16_t cats) noexcept
	{
		return (mask & cats) != 0;
	}

	bool Dispatcher::dispatch(const EventSlot& e, engine::core::Layerstack& layers, CaptureState& capture) noexcept
	{
		const std::uint16_t cats = e.header.categories;

		// Capture routing.
		if (capture.owner && intersects(capture.captured, cats))
		{
			auto* target = static_cast<engine::core::Layer const*>(capture.owner);
			auto* mutableTarget = const_cast<engine::core::Layer*>(target);
			const bool handled = mutableTarget->OnEvent(e);
			return handled;
		}

		// Top -> bottom (UI/Overlay first).
		const std::size_t n = layers.size();
		for (std::size_t i = 0; i < n; i++)
		{
			engine::core::Layer* L = layers.at(i);
			if (!L) continue;
			if (L->OnEvent(e)) // Handled
			{
				return true;
			}
		}

		return false;
	}
}