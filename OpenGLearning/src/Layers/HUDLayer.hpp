#pragma once
#include "EngineCore/Core/Layer.hpp"

class HUDLayer final : public engine::core::Layer
{
public:
	HUDLayer(const std::string& name, const engine::platform::Window& window);

	void OnUpdate() override;
	void OnRender() override;
	bool OnEvent(const engine::events::EventSlot& e) override;
};