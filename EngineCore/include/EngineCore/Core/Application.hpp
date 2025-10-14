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
		explicit Application(const ApplicationSpecs& s);
		virtual ~Application();

		// Non-copyable/non-movable
		Application(const Application&) = delete;				// Copy constructor.
		Application& operator=(const Application&) = delete;	// Copy assignment operator.
		Application(Application&&) = delete;					// Move constructor.
		Application& operator=(Application&&) = delete;			// Move assignment operator.

		void Run();
		void Close();

		const ApplicationSpecs& getSpecs() const { return m_specs; }

	protected:
		engine::platform::Window& window()	{ return *m_window; }
		Layerstack& layerstack()			{ return *m_layerstack; }

	private:
		ApplicationSpecs m_specs;
		std::unique_ptr<engine::platform::Window> m_window = nullptr;
		std::unique_ptr<Layerstack> m_layerstack = nullptr;
	};
}