#include "pch.h"
#include "EngineCore/Window.hpp"
#include "EngineCore/GlfwCallbacks.hpp"

namespace engine
{

	Window::Window(int width, int height, const char* title)
		: _state(std::make_unique<InputState>())
	{
		_win = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!_win) throw std::runtime_error("Failed to create GLFW window.");

		glfwMakeContextCurrent(_win);
		glfwSetWindowUserPointer(_win, _state.get());
		register_glfw_callbacks(_win);

		int w, h;
		glfwGetFramebufferSize(_win, &w, &h);
		_state->fbWidth = w; _state->fbHeight = h;
	}

	Window::~Window()
	{
		if (_win)
		{
			glfwSetWindowUserPointer(_win, nullptr);
			glfwDestroyWindow(_win);
			_win = nullptr;
		}
	}

}