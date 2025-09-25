#pragma once
#include <GLFW/glfw3.h>
#include "EngineCore/Core/Input.hpp"

namespace engine::platform
{

	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* handle()         const { return _win; }
		engine::core::Input input()	 const { return engine::core::Input::Input(_state.get()); }
		bool shouldClose()	         const { return glfwWindowShouldClose(_win); }
		void swapBuffers()		           { glfwSwapBuffers(_win); }

	private:
		GLFWwindow*	_win = nullptr;
		std::unique_ptr<engine::core::InputState> _state;
	};

}