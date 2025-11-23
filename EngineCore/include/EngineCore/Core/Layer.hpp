#pragma once
#include <string>

namespace engine { namespace events { struct EventSlot; } }

namespace engine::core
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnRender();

		virtual bool OnEvent(const engine::events::EventSlot& e);

		const std::string& getName() { return m_Name; }

	protected:
		std::string m_Name;
	};
}