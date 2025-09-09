#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "EngineCore/GlfwCallbacks.hpp"
#include "EngineCore/Window.hpp"

constexpr short window_w_default = 1280;
constexpr short window_h_default = 720;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	engine::Window window(window_w_default, window_h_default, "OpenGLearning");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	};

	while (!window.shouldClose())
	{
		auto input = window.input();
		
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.swapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}