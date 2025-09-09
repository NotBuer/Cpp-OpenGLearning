#pragma once

struct GLFWwindow;

namespace engine
{
	void register_glfw_callbacks(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow*, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}