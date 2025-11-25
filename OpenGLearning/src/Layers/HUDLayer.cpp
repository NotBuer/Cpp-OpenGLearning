#include <iostream>
#include "HUDLayer.hpp"
#include "EngineCore/Core/Layer.hpp"

HUDLayer::HUDLayer(const std::string& name, const engine::platform::Window& window) : 
	engine::core::Layer(name, window)
{

}

void HUDLayer::OnUpdate()
{

}

void HUDLayer::OnRender()
{

}

bool HUDLayer::OnEvent(const engine::events::EventSlot& e)
{
	std::printf("HUDLayer received event of type: %d\n", e.header.type);
	return true;
}