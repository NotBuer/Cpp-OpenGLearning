#include "pch.h"
#include "EngineCore/Events/Types.hpp"
#include "EngineCore/Events/Categories.hpp"

namespace engine::events
{
	Category defaultCategories(EventType type) noexcept
	{
		switch (type)
		{
			case EventType::WindowClose:			return Category::Application | Category::Window;
			case EventType::WindowFocusChanged:		return Category::Window;
			case EventType::WindowResized:			return Category::Window;

			case EventType::KeyPressed:
			case EventType::KeyReleased:			return Category::Input | Category::Keyboard;
			case EventType::TextInput:				return Category::Input | Category::Text;

			case EventType::MouseButtonPressed:
			case EventType::MouseButtonReleased:
			case EventType::MouseMoved:
			case EventType::MouseDelta:
			case EventType::MouseScrolled:			return Category::Input | Category::Mouse;

			default:								return Category::None;
		}
	}

	Priority defaultPriority(EventType type) noexcept
	{
		switch (type)
		{
			case EventType::WindowClose:
			case EventType::WindowFocusChanged:
			case EventType::WindowResized:			return Priority::High;

			case EventType::KeyPressed:
			case EventType::KeyReleased:
			case EventType::TextInput:				return Priority::Normal;

			case EventType::MouseButtonPressed:		return Priority::Normal;
			case EventType::MouseButtonReleased:	return Priority::Normal;
			case EventType::MouseMoved:				return Priority::Low;
			case EventType::MouseDelta:				return Priority::Low;
			case EventType::MouseScrolled:			return Priority::Normal;

			default:								return Priority::Normal;
		}
	}
}