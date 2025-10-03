#include "pch.h"
#include "EngineCore/Core/Layerstack.hpp"
#include "EngineCore/Core/Layer.hpp"

namespace engine::core
{
	Layerstack::Layerstack()
	{

	}

	Layerstack::~Layerstack()
	{

	}

	void Layerstack::PushLayer(std::unique_ptr<Layer> layer)
	{
		layer->OnAttach();
		m_layers.emplace_back(std::move(layer));
	}

	void Layerstack::PopLayer(Layer* layer)
	{
		auto it = std::find_if(m_layers.begin(), m_layers.end(),
			[layer](const std::unique_ptr<Layer>& p) { return p.get() == layer; });
		if (it != m_layers.end())
		{
			(*it)->OnDetach();
			m_layers.erase(it);
		}
	}
}