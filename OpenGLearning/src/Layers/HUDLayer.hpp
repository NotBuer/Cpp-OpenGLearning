#pragma once
#include "EngineCore/Core/Layer.hpp"

class HUDLayer final : public engine::core::Layer
{
public:
	HUDLayer(const std::string& name);

	void OnUpdate() override;
	void OnRender() override;
};

