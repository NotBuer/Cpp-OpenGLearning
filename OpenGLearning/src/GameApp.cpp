#include <memory>
#include "GameApp.hpp"
#include "EngineCore/Core/Application.hpp"
#include "Layers/DefaultLayer.hpp"
#include "Layers/HUDLayer.hpp"

GameApp::GameApp(const engine::core::ApplicationSpecs& specs) : engine::core::Application(specs)
{	
	layerstack().PushLayer(std::make_unique<DefaultLayer>("Default Layer"));
	layerstack().PushLayer(std::make_unique<HUDLayer>("HUD Layer"));
}