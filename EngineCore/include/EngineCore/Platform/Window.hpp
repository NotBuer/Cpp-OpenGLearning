#pragma once
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Events/InputState.hpp"
#include "EngineCore/Events/EventBus.hpp"

namespace engine::platform
{
	class Window
	{
	public:
		Window(int width, int height, const char* title, engine::events::EventBus& bus);
		~Window();

		GLFWwindow* handle()	 const { return _win; }
		bool shouldClose()		 const { return glfwWindowShouldClose(_win); }
		void swapBuffers()			   { glfwSwapBuffers(_win); }

		engine::events::InputState& inputState();

		struct GlfwCallbackCtx;

	private:
		GLFWwindow* _win = nullptr;
		std::unique_ptr<engine::events::InputState> _state;

		// Opaque pointer (GLFW User Pointer)
		GlfwCallbackCtx* _ctx = nullptr;
	};
}