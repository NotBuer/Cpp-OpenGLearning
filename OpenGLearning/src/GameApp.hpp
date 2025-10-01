#pragma once
#include "EngineCore/Core/Application.hpp"

class GameApp final : public engine::core::Application
{
public:
	explicit GameApp(const engine::core::ApplicationSpecs& specs);
	~GameApp() override = default;
};