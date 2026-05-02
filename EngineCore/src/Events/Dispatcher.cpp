#include "pch.h"
#include "EngineCore/Events/Dispatcher.hpp"
#include "EngineCore/Events/CaptureState.hpp"
#include "EngineCore/Core/Layerstack.hpp"
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Events/Context.hpp"

namespace engine::events
{
	static inline bool intersects(std::uint16_t mask, std::uint16_t cats) noexcept
	{
		return (mask & cats) != 0;
	}

	bool Dispatcher::dispatch(const EventSlot& e, engine::core::Layerstack& layers, CaptureState& capture) noexcept
	{
		EventContext ctx{ capture };

		const std::uint16_t cats = e.header.categories;

		// Capture routing.
		if (capture.owner && capture.isCaptured(cats))
		{
			engine::core::Layer* target = capture.owner;
			return target->OnEvent(e, ctx);
		}

		// Top -> bottom (UI/Overlay first).
		const std::size_t n = layers.size();
		for (std::size_t i = n; i > 0; --i)
		{
			engine::core::Layer* L = layers.at(i - 1);

			if (!L) continue;

			if (L->OnEvent(e, ctx)) 
			{
				return true; // Handled
			}
		}

		return false; // Unhandled
	}
}
