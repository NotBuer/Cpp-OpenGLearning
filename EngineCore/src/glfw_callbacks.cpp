#include "glfw_callbacks.hpp";

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout 
		<< "Resizing window callback registered" << "\n" << "dimensions: " << width << " / " << height <<
	std::endl;
}