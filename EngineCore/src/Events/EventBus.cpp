#include "pch.h"
#include "EngineCore/Events/EventBus.hpp"
#include "EngineCore/Events/Dispatcher.hpp"
#include "EngineCore/Events/CaptureState.hpp"
#include "EngineCore/Core/Layerstack.hpp"

namespace engine::events
{
	// SPSC (Single-Producer Single-Consumer) ring buffer; fixed-size array of EventSlot.
	struct alignas(64) Ring
	{
		EventSlot* buf = nullptr;
		std::uint32_t cap = 0;	// power of two capacity
		std::uint32_t mask = 0; // cap - 1 
		std::uint32_t head = 0;	// write index (producer)
		std::uint32_t tail = 0;	// read index (consumer)

		/// Bitwise AND '&' operator compares each bit of its two operands. If both are 1, result is 1, otherwise is 0.
		/// Subtracting one from a power-of-two number results in a binary value where:
		/// all bits *below (*to the right) the original set bit are 1, and all bits *above (*to the left) it are 0.
		/// head (decimal) | head (binary) | head + 1 (binary) | mask (binary) (8 - 1) | (head + 1) & mask (binary)	| next (decimal)
		/// 5			   | 00000101	   | 00000110		   | 00000111			   | 00000110					| 6
		/// 6			   | 00000110	   | 00000111		   | 00000111			   | 00000111					| 7
		/// 7			   | 00000111	   | 00001000		   | 00000111			   | 00000000					| 0
		bool push(const EventSlot& e) noexcept
		{
			auto next = (head + 1u) & mask;
			if (next == tail) return false; // full.
			buf[head] = e; // trivially copyable.
			head = next;
			return true;
		}

		/// Bitwise AND '&' operator compares each bit of its two operands. If both are 1, result is 1, otherwise is 0.
		/// tail (decimal) | tail (binary) | tail + 1 (binary) | mask (binary) (8 - 1) | (tail + 1) & mask (binary)	| tail (decimal)
		/// 0			   | 00000000	   | 00000001		   | 00000111			   | 00000001					| 1
		/// 6			   | 00000110	   | 00000111		   | 00000111			   | 00000111					| 7
		/// 7			   | 00000111	   | 00001000		   | 00000111			   | 00000000					| 0
		bool pop(EventSlot& out) noexcept
		{
			if (tail == head) return false;
			out = buf[tail];
			tail = (tail + 1u) & mask;
			return true;
		}

		bool peekTail(EventSlot& out) const noexcept
		{
			if (tail == head) return false;
			out = buf[tail];
			return true;
		}

		bool empty() const noexcept { return tail == head; }
		void clear() noexcept { tail = head = 0; }

		EventSlot* lastPushed() noexcept
		{
			if (head == tail) return nullptr;
			const std::uint32_t last = (head + mask) & mask; // index of last pushed: (head - 1) & mask
			return &buf[last];
		}
	};

	struct EventBus::Impl
	{
		Ring imm;	// Immediate lane (High)
		Ring frame; // Frame lane (Normal/Low)
		std::uint32_t droppedImm = 0;
		std::uint32_t droppedFr = 0;

		Impl();
		~Impl();
	};

	static constexpr std::uint32_t kImmCap = 64;		// Must be power of two.
	static constexpr std::uint32_t kFrameCap = 1024;	// Must be power of two.

	EventBus::EventBus()
		: m_impl(new Impl())
	{
	}

	EventBus::~EventBus()
	{
		delete m_impl;
		m_impl = nullptr;
	}

	EventBus::Impl::Impl()
	{
		imm.cap = kImmCap; frame.cap = kFrameCap;
		imm.mask = imm.cap - 1u; frame.mask = frame.cap - 1u;
		imm.buf = new EventSlot[imm.cap]; frame.buf = new EventSlot[frame.cap];
	}

	EventBus::Impl::~Impl()
	{
		delete[] imm.buf; delete[] frame.buf;
	}

	// Immediate is for high-priority events (resize, focus, close).
	void EventBus::pushImmediate(const EventSlot& e) noexcept
	{
		const EventType t = static_cast<EventType>(e.header.type);

		if (t == EventType::WindowResized || t == EventType::WindowFocusChanged)
		{
			if (EventSlot* last = m_impl->imm.lastPushed())
			{
				if (last->header.type == e.header.type)
				{
					*last = e; // overwrite previous same-type event
					return;
				}
			}
		}

		if (!m_impl->imm.push(e))
		{
			++m_droppedImmediate;
			++m_impl->droppedImm;

			if (EventSlot* last = m_impl->imm.lastPushed())
			{
				if (static_cast<EventType>(last->header.type) == t) *last = e;
			}
		}
	}

	// Frame is for normal/low-priority events (input).
	void EventBus::pushFrame(const EventSlot& e) noexcept
	{
		const EventType t = static_cast<EventType>(e.header.type);

		if (!m_impl->frame.push(e))
		{
			// Drop policy: MouseMoved/MouseDelta are lossy.
			if (t == EventType::MouseMoved || t == EventType::MouseDelta)
			{
				++m_droppedFrame; ++m_impl->droppedFr;
			}

			// If full for a more important event, drop the last MouseMoved if present.
			bool droppedLow = false;
			EventSlot tmp{};
			std::uint32_t i = m_impl->frame.tail;
			while (i != m_impl->frame.head)
			{
				const EventType ti = static_cast<EventType>(m_impl->frame.buf[i].header.type);
				if (ti == EventType::MouseMoved || ti == EventType::MouseDelta)
				{
					if (i == m_impl->frame.tail) 
					{
						m_impl->frame.pop(tmp); // drop the tail
					}
					else
					{
						m_impl->frame.buf[i].header.type = static_cast<std::uint16_t>(EventType::MouseDelta);
						m_impl->frame.buf[i].payload.md.dx = 0.0;
						m_impl->frame.buf[i].payload.md.dy = 0.0;
					}
					droppedLow = true;
					break;
				}
				i = (i + 1u) & m_impl->frame.mask;
			}
			if (!droppedLow) { ++m_droppedFrame; ++m_impl->droppedFr; return; }
			(void)m_impl->frame.push(e);
		}
	}

	void EventBus::drainImmediate(Dispatcher& d, engine::core::Layerstack& layers, CaptureState& cap) noexcept
	{
		if (!m_impl) return;
		EventSlot e{};
		while (m_impl->imm.pop(e))
		{
			d.dispatch(e, layers, cap);
		}
	}

	void EventBus::drainFrame(Dispatcher& d, engine::core::Layerstack& layers, CaptureState& cap) noexcept
	{
		if (!m_impl) return;
		EventSlot e{};
		while (m_impl->frame.pop(e))
		{
			d.dispatch(e, layers, cap);
		}
	}
}
