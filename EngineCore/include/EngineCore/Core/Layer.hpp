#pragma once
#include <string>
#include "EngineCore/Platform/Window.hpp"

namespace engine { namespace events { struct EventSlot; } }

namespace engine::core
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name, const engine::platform::Window& window);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnRender();
		virtual bool OnEvent(const engine::events::EventSlot& e);

		const std::string& name() { return m_Name; }
		const engine::platform::Window& window() const { return m_Window; }

	protected:
		std::string m_Name;

	private:
		const engine::platform::Window& m_Window;
	};
}