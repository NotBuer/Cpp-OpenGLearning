#pragma once
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
		~Application();

		void Run();
		void Close();

		const ApplicationSpecs& getSpecs() const { return m_specs; }
		const bool isRunning() const { return m_running;}

	private:
		ApplicationSpecs m_specs;
		std::unique_ptr<engine::platform::Window> m_window = nullptr;
		std::unique_ptr<Layerstack> m_layerstack = nullptr;
		bool m_running = false;
	};

}