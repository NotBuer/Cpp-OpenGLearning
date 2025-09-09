#include "pch.h"
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <EngineCore/GlfwCallbacks.hpp>;
#include <EngineCore/Input.hpp>

namespace engine
{

	static inline InputState* stateFrom(GLFWwindow* w)
	{
		return static_cast<InputState*>(glfwGetWindowUserPointer(w));
	}

	void register_glfw_callbacks(GLFWwindow* window)
	{
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetKeyCallback(window, key_callback);
	}

	void framebuffer_size_callback(GLFWwindow* w, int width, int height)
	{
		auto* s = stateFrom(w);
		if (!s) return;

		s->fbWidth = width; s->fbHeight = height; s->resized = true;
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* w, int key, int, int action, int)
	{
		auto* s = stateFrom(w); 
		if (!s) return;

		if (key >= 0 && key < (int)s->keyDown.size())
			s->keyDown[key] = (action != GLFW_RELEASE);

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(w, GLFW_TRUE);
	}

}