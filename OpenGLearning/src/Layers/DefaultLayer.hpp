#pragma once
#include "EngineCore/Core/Layer.hpp"

class DefaultLayer final : public engine::core::Layer
{
public:
	DefaultLayer(const std::string& name);
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnRender() override;
};

