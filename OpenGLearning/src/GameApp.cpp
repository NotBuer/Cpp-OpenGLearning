#include "GameApp.hpp"
#include "EngineCore/Core/Application.hpp"
#include "Layers/DefaultLayer.hpp"

GameApp::GameApp(const engine::core::ApplicationSpecs& specs) : engine::core::Application(specs)
{
	layerstack().PushLayer(new DefaultLayer("Game Default Layer"));
}