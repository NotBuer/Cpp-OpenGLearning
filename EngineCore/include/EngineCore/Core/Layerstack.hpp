#pragma once
#include <vector>
#include <memory>
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

		Layer* at(std::size_t index) const { return m_layers.at(index).get(); }

		const std::vector<std::unique_ptr<Layer>>& getLayers() const { return m_layers; }
		const std::size_t size() const { return m_layers.size(); }

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_layers.end(); }

	private:
		std::vector<std::unique_ptr<Layer>> m_layers;
	};
}
