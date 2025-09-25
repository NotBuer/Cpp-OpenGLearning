#pragma once
#include <vector>
#include "EngineCore/Core/Layer.hpp"

namespace engine::core
{
	class Layerstack
	{
	public:
		Layerstack();
		~Layerstack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
	};
}
