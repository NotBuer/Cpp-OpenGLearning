#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Core/Application.hpp"
#include "EngineCore/Platform/Window.hpp"
#include "EngineCore/Renderer/Renderer2D.hpp"

namespace engine::core
{
	Application::Application(ApplicationSpecs s)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_specs = std::move(s);
		m_window = std::make_unique<engine::platform::Window>(m_specs.width, m_specs.height, m_specs.title.c_str());
		m_layerstack = std::make_unique<engine::core::Layerstack>();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			Close();
		};
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (!m_window->shouldClose())
		{
			for (const auto& l : m_layerstack->getLayers())
				l->OnUpdate();

			engine::renderer::Renderer2D::ClearFrame({ 0.25f, 0.25f, 0.25f, 1.0f });
			engine::renderer::Renderer2D::BeginFrame();

			for (const auto& l : m_layerstack->getLayers())
				l->OnRender();

			engine::renderer::Renderer2D::EndFrame();

			m_window->swapBuffers();
			glfwPollEvents(); // TODO: Remove directly glfw call on site.
		}
	}

	void Application::Close()
	{
		glfwTerminate();
	}
}