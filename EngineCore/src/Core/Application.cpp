#include "pch.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineCore/Core/Application.hpp"
#include "EngineCore/Platform/Window.hpp"

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
		m_layerstack->PushLayer(new Layer("Default Layer"));

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
		std::cout << "Application working, thanks God!" << std::endl;
		m_running = true;
	}

	void Application::Close()
	{
		glfwTerminate();
		m_running = false;
	}
}