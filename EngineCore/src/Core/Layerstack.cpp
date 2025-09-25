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
		for (Layer* layer : m_layers)
			delete layer;
	}

	void Layerstack::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_layers.push_back(layer);
	}

	void Layerstack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		
		if (it != end())
		{
			m_layers.erase(it);
		}
	}
}