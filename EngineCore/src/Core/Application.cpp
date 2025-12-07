#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Core/Application.hpp"
#include "EngineCore/Platform/Window.hpp"
#include "EngineCore/Platform/Time.hpp"

namespace engine::core
{
	Application::Application(const ApplicationSpecs& s)
		: m_specs{s}
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		auto impl = std::make_unique<Impl>();

		m_window = std::make_unique<engine::platform::Window>(m_specs.width, m_specs.height, m_specs.title.c_str(), impl->events);
		m_layerstack = std::make_unique<engine::core::Layerstack>();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			Close();
		};

		m_impl = std::move(impl);
	}

	Application::~Application() = default;

	void Application::Run()
	{
		using engine::platform::Time;
		double lastTime = Time::nowSeconds();

		while (!m_window->shouldClose())
		{
			double now = Time::nowSeconds();
			float deltaTime = static_cast<float>(now - lastTime);
			lastTime = now;

			glfwPollEvents();

			// Drain immediate (resize/focus/close).
			m_impl->events.drainImmediate(m_impl->dispatch, layerstack(), m_impl->capture);

			// Finalize input for this frame.
			m_window->inputState().finalizeFrame();

			// Layers OnUpdate hook.
			for (const auto& l : m_layerstack->getLayers())
				l->OnUpdate(deltaTime);

			// Drain frame (keyboard/mouse/text/scroll).
			m_impl->events.drainFrame(m_impl->dispatch, layerstack(), m_impl->capture);

			// Layers OnRender hook.
			for (const auto& l : m_layerstack->getLayers())
				l->OnRender();

			m_window->swapBuffers();
		}
	}

	void Application::Close()
	{
		glfwTerminate();
	}
}