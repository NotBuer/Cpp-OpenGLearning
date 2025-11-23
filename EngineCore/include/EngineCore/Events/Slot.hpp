#pragma once
#include "Header.hpp"
#include "Payloads.hpp"

namespace engine::events
{
	// 32-byte fixed slot: header (16 Bytes) + union payload (16 Bytes). 
	struct alignas(8) EventSlot
	{
		EventHeader header;

		union Payload
		{
			WindowClose			wc;
			WindowFocusChanged	wf;
			WindowResized		wr;

			KeyPressed			kp;
			KeyReleased			kr;
			TextInput			ti;

			MouseButtonPressed	mbp;
			MouseButtonReleased mbr;
			MouseMoved			mm;
			MouseDelta			md;
			MouseScrolled		ms;

			Payload() {}
		} payload;
	};

	static_assert(sizeof(EventSlot) == 32, "EventSlot must be 32 bytes.");
}