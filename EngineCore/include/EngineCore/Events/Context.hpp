#pragma once
#include "EngineCore/Events/CaptureState.hpp"

namespace engine::events
{
	struct EventContext
	{
		CaptureState& capture;
	};
}
