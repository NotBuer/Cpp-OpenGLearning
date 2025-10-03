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

		void PushLayer(std::unique_ptr<Layer> layer);
		void PopLayer(Layer* layer);

		const std::vector<std::unique_ptr<Layer>>& getLayers() const { return m_layers; }

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_layers.end(); }

	private:
		std::vector<std::unique_ptr<Layer>> m_layers;
	};
}
