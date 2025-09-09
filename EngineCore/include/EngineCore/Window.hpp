#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include "EngineCore/Input.hpp"

namespace engine
{

	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* handle() const { return _win; }
		Input input()		 const { return Input(_state.get()); }
		bool shouldClose()	 const { return glfwWindowShouldClose(_win); }
		void swapBuffers()		   { glfwSwapBuffers(_win); }

	private:
		GLFWwindow*						_win = nullptr;
		std::unique_ptr<InputState>		_state;
	};

}