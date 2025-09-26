#include <iostream>
#include "HUDLayer.hpp"
#include "EngineCore/Core/Layer.hpp"

HUDLayer::HUDLayer(const std::string& name) : engine::core::Layer(name)
{

}

void HUDLayer::OnUpdate()
{
	std::cout << "Layer: " << getName() << "-> overriding OnUpdate!" << std::endl;
}

void HUDLayer::OnRender()
{
	std::cout << "Layer: " << getName() << "-> overriding OnRender!" << std::endl;
}
