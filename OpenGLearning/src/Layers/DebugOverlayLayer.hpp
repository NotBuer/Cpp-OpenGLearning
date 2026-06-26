#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Events/Context.hpp"

class DebugOverlayLayer final : public engine::core::Layer
{
public:
	DebugOverlayLayer(const std::string& name, const engine::platform::Window& window);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	bool OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx) override;
};