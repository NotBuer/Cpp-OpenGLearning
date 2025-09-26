#include "pch.h"
#include "EngineCore/Core/Layer.hpp"

namespace engine::core
{
	Layer::Layer(const std::string& name) : m_name(name)
	{

	}

	Layer::~Layer() = default;

	void Layer::OnAttach()
	{
		std::cout << "Layer: " << m_name << " -> default OnAttach!" << std::endl;
	}

	void Layer::OnDetach()
	{
		std::cout << "Layer: " << m_name << "-> default OnDetach" << std::endl;
	}

	void Layer::OnUpdate()
	{
		std::cout << "Layer: " << m_name << "-> default" << std::endl;
	}

	void Layer::OnRender()
	{
		std::cout << "Layer: " << m_name << "-> default" << std::endl;
	}

	void Layer::OnEvent()
	{
		std::cout << "Layer: " << m_name << "-> default" << std::endl;
	}
}