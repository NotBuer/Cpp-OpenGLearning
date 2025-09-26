#include "iostream"
#include "DefaultLayer.hpp"
#include "EngineCore/Core/Layer.hpp"

DefaultLayer::DefaultLayer(const std::string& name) : engine::core::Layer(name)
{

}

void DefaultLayer::OnAttach()
{
	std::cout << "Layer: " << getName() << " -> overriding OnAttach!" << std::endl;
}

void DefaultLayer::OnDetach()
{

}

void DefaultLayer::OnUpdate()
{
	std::cout << "Layer: " << getName() << "-> overriding OnUpdate!" << std::endl;
}

void DefaultLayer::OnRender()
{
	std::cout << "Layer: " << getName() << "-> overriding OnRender!" << std::endl;
}
