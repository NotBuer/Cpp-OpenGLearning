#include "GameApp.hpp"
#include "EngineCore/Core/Application.hpp"
#include "Layers/DefaultLayer.hpp"
#include "Layers/HUDLayer.hpp"

GameApp::GameApp(const engine::core::ApplicationSpecs& specs) : engine::core::Application(specs)
{
	layerstack().PushLayer(new DefaultLayer("Default Layer"));
	layerstack().PushLayer(new HUDLayer("HUD Layer"));
}