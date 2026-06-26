#include <memory>
#include "GameApp.hpp"
#include "EngineCore/Core/Application.hpp"
#include "Layers/DefaultLayer.hpp"
#include "Layers/DebugOverlayLayer.hpp"

GameApp::GameApp(const engine::core::ApplicationSpecs& specs) : engine::core::Application(specs)
{	
	layerstack().PushLayer(std::make_unique<DefaultLayer>("Default Layer", window()));
	layerstack().PushLayer(std::make_unique<DebugOverlayLayer>("Debug Overlay Layer", window()));
}