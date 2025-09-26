#pragma once
#include <string>

namespace engine::core
{
	class Layer
	{
	public:
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnRender();
		virtual void OnEvent();

		const std::string& getName() { return m_name; }

	private:
		std::string m_name;
	};
}