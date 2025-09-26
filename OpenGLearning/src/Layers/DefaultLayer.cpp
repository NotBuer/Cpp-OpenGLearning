#include "iostream"
#include "DefaultLayer.hpp"
#include "EngineCore/Core/Layer.hpp"

DefaultLayer::DefaultLayer(const std::string& name) : engine::core::Layer(name.c_str())
{

}

void DefaultLayer::OnAttach()
{
	Layer::OnAttach();
	std::cout << "Layer: " << getName() << " -> overriding OnAttach!" << std::endl;
}

void DefaultLayer::OnDetach()
{

}

void DefaultLayer::OnUpdate()
{

}

void DefaultLayer::OnRender()
{

}
