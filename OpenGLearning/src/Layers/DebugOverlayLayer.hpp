#pragma once
#include "EngineCore/Core/Layer.hpp"
#include "EngineCore/Events/Context.hpp"
#include "Debug/IDebugOverlayDataSource.hpp"

class DebugOverlayLayer final : public engine::core::Layer
{
public:
	DebugOverlayLayer(
		const std::string& name, const engine::platform::Window& window, const IDebugOverlayDataSource& dataSource);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	bool OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx) override;

private:
	const IDebugOverlayDataSource& m_DataSource;
};