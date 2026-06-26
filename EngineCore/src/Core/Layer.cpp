#include "pch.h"
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Events/Context.hpp"

namespace engine::core
{
	Layer::Layer(const std::string& name, const engine::platform::Window& window) : 
		m_Name(name), 
		m_Window(window)
	{

	}

	Layer::~Layer() noexcept = default;

	void Layer::OnAttach()
	{
		std::cout << "Layer: " << m_Name << " -> default OnAttach!" << std::endl;
	}

	void Layer::OnDetach()
	{
		std::cout << "Layer: " << m_Name << "-> default OnDetach" << std::endl;
	}

	void Layer::OnUpdate(float dt)
	{
		std::cout << "Layer: " << m_Name << "-> default" << std::endl;
	}

	void Layer::OnRender()
	{
		std::cout << "Layer: " << m_Name << "-> default" << std::endl;
	}

	bool Layer::OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx)
	{
		std::cout << "Layer: " << m_Name << "-> default" << std::endl;

		//(void)e;
		//(void)ctx;
		return false;
	}
}
