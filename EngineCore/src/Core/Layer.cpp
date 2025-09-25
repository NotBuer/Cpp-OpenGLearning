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
		std::cout << "Layer: " << m_name << "OnAttach successfully!" << std::endl;
	}

	void Layer::OnDetach()
	{
		std::cout << "Layer: " << m_name << "OnAttach successfully!" << std::endl;
	}

	void Layer::OnUpdate()
	{

	}

	void Layer::OnRender()
	{

	}

	void Layer::OnEvent()
	{

	}
}