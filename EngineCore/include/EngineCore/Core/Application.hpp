#pragma once
#include <string>
#include <memory>
#include "EngineCore/Platform/Window.hpp"
#include "EngineCore/Core/Layerstack.hpp"

namespace engine::core
{
	struct ApplicationSpecs
	{
		int width = 1280;
		int height = 720;
		std::string title = "Default title";
	};

	class Application
	{
	public:
		explicit Application(ApplicationSpecs s);
		virtual ~Application();

		void Run();
		void Close();

		const ApplicationSpecs& getSpecs() const { return m_specs; }

	protected:
		engine::platform::Window& window() { return *m_window; }
		Layerstack& layerstack() { return *m_layerstack; }

	private:
		ApplicationSpecs m_specs;
		std::unique_ptr<engine::platform::Window> m_window = nullptr;
		std::unique_ptr<Layerstack> m_layerstack = nullptr;
	};
}