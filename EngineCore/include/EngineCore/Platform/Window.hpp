#pragma once
#include <memory>
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

		void onResize(uint16_t width, uint16_t height)
		{
			m_currentFbWidth = width;
			m_currentFbHeight = height;
		}

		uint16_t getFramebufferWidth() const { return m_currentFbWidth == 0 ? 1 : m_currentFbWidth; }
		uint16_t getFramebufferHeight() const { return m_currentFbHeight == 0 ? 1 : m_currentFbHeight; }

		engine::events::InputState& inputState() { return *_state; }
		const engine::events::InputState& inputState() const { return *_state; }

		struct GlfwCallbackCtx;

	private:
		GLFWwindow* _win = nullptr;
		std::unique_ptr<engine::events::InputState> _state;

		// Opaque pointer (GLFW User Pointer)
		GlfwCallbackCtx* _ctx = nullptr;

		uint16_t m_currentFbWidth = 0;
		uint16_t m_currentFbHeight = 0;
	};
}
