#include "pch.h"
#include "EngineCore/Platform/Window.hpp"
#include "EngineCore/Events/Slot.hpp"
#include "EngineCore/Platform/Time.hpp"
#include "EngineCore/Platform/GlfwAdpter.hpp"

namespace engine::platform
{
	// TODO: Create a real robust logging system...
	static void logf(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		std::vfprintf(stdout, fmt, args);
		std::fputc('\n', stdout);
		va_end(args);
	}

	struct Window::GlfwCallbackCtx
	{
		engine::platform::Window* window = nullptr;
		engine::events::EventBus* bus = nullptr;
		engine::events::InputState* input = nullptr;
	};

	static void KeyCb(GLFWwindow* w, int key, int sc, int action, int mods);
	static void CharCb(GLFWwindow* w, unsigned int codepoint);
	static void MouseBtnCb(GLFWwindow* w, int button, int action, int mods);
	static void CursorPosCb(GLFWwindow* w, double x, double y);
	static void ScrollCb(GLFWwindow* w, double dx, double dy);
	static void FocusCb(GLFWwindow* w, int focused);
	static void FbSizeCb(GLFWwindow* w, int fbW, int fbH);

	static inline Window::GlfwCallbackCtx* Ctx(GLFWwindow* w)
	{
		return static_cast<Window::GlfwCallbackCtx*>(glfwGetWindowUserPointer(w));
	}

	Window::Window(int width, int height, const char* title, engine::events::EventBus& bus)
	{
		_win = glfwCreateWindow(width, height, title, nullptr, nullptr);
		assert(_win && "Failed to create GLFW window");

		_state = std::make_unique<engine::events::InputState>();

		// Allocate and set the context for callbacks
		_ctx = new GlfwCallbackCtx();
		_ctx->window = this;
		_ctx->bus = &bus;
		_ctx->input = _state.get();

		// TODO:
		// Later on when come the time to implement ImGUI,
		// Move this vsync setting to final user settings, with other things related to settings serialization/deserialization on startup time.
		// For now making it off by default for testing performance.
		glfwSwapInterval(0);

		glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwMakeContextCurrent(_win);
		glfwSetWindowUserPointer(_win, _ctx);

		// Register callbacks
		glfwSetKeyCallback(_win, &KeyCb);
		glfwSetCharCallback(_win, &CharCb);
		glfwSetMouseButtonCallback(_win, &MouseBtnCb);
		glfwSetCursorPosCallback(_win, &CursorPosCb);
		glfwSetScrollCallback(_win, &ScrollCb);
		glfwSetWindowFocusCallback(_win, &FocusCb);
		glfwSetFramebufferSizeCallback(_win, &FbSizeCb);

		onResize(width, height);
	}

	Window::~Window()
	{
		if (_win)
		{
			glfwSetWindowUserPointer(_win, nullptr);
			glfwDestroyWindow(_win);
			_win = nullptr;
		}
		delete _ctx; _ctx = nullptr;
	}

	static inline double Now() { return engine::platform::Time::nowSeconds(); }

	static void KeyCb(GLFWwindow* w, int key, int sc, int action, int mods)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			engine::platform::KeyCode keyCode = engine::platform::key_code(key);

			ctx->input->setKeyDown(keyCode, action != GLFW_RELEASE);

			const bool isRelease = (action == GLFW_RELEASE);
			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(isRelease ? EventType::KeyReleased : EventType::KeyPressed);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(static_cast<EventType>(e.header.type)));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(static_cast<EventType>(e.header.type)));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();

			if (isRelease)
			{
				e.payload.kr.key = keyCode;
				e.payload.kr.scancode = sc;
				e.payload.kr.mods = mods_bits(mods);
			}
			else
			{
				e.payload.kp.key = keyCode;
				e.payload.kp.scancode = sc;
				e.payload.kp.mods = mods_bits(mods);
				e.payload.kp.repeat = (action == GLFW_REPEAT) ? 1u : 0u;
			}
			ctx->bus->pushFrame(e);
		}

		const std::string name = key_name(key, sc);
		const char* act = action_name(action);
		const std::string m = mods_string(mods);

		if (!m.empty())
			logf("[Input] Key '%s' (%s) %s", name.c_str(), m.c_str(), act);
		else
			logf("[Input] Key '%s' %s", name.c_str(), act);
	}

	static void CharCb(GLFWwindow* w, unsigned int codepoint)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(EventType::TextInput);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(EventType::TextInput));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(EventType::TextInput));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			e.payload.ti.codepoint = codepoint;
			ctx->bus->pushFrame(e);
		}
	}

	static void MouseBtnCb(GLFWwindow* w, int button, int action, int mods)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			ctx->input->setMouseDown(button, action == GLFW_PRESS);
			EventSlot e{};
			const bool isRelease = (action == GLFW_RELEASE);
			e.header.type = static_cast<std::uint16_t>(isRelease ? EventType::MouseButtonReleased : EventType::MouseButtonPressed);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(static_cast<EventType>(e.header.type)));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(static_cast<EventType>(e.header.type)));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			if (isRelease)
			{
				e.payload.mbr.button = button;
				e.payload.mbr.mods = mods_bits(mods);
			}
			else
			{
				e.payload.mbp.button = button;
				e.payload.mbp.mods = mods_bits(mods);
			}
			ctx->bus->pushFrame(e);
		}

		const std::string btn = mousebutton_name(button);
		const char* act = action_name(action);
		const std::string m = mods_string(mods);

		if (!m.empty())
			logf("[Input] %s (%s) %s", btn.c_str(), m.c_str(), act);
		else
			logf("[Input] %s %s", btn.c_str(), act);
	}

	static void CursorPosCb(GLFWwindow* w, double x, double y)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			ctx->input->setCursorPos(x, y);
			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(EventType::MouseMoved);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(EventType::MouseMoved));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(EventType::MouseMoved));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			e.payload.mm.x = x;
			e.payload.mm.y = y;
			ctx->bus->pushFrame(e);
		}

		logf("[Input] Cursor %.1f, %.1f", x, y);
	}

	static void ScrollCb(GLFWwindow* w, double dx, double dy)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			ctx->input->addScroll(dx, dy);
			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(EventType::MouseScrolled);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(EventType::MouseScrolled));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(EventType::MouseScrolled));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			e.payload.ms.dx = dx;
			e.payload.ms.dy = dy;
			ctx->bus->pushFrame(e);
		}

		logf("[Input] Scroll dx=%.2f dy=%.2f", dx, dy);
	}

	static void FocusCb(GLFWwindow* w, int focused)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			if (!focused) ctx->input->clearOnFocusLost();

			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(EventType::WindowFocusChanged);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(EventType::WindowFocusChanged));
			e.header.priority = static_cast<std::uint8_t>(defaultPriority(EventType::WindowFocusChanged));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			e.payload.wf.focused = (focused != 0);
			ctx->bus->pushImmediate(e);
		}

		logf("[Window] Focus %s", focused ? "gained" : "lost");
	}
	 
	static void FbSizeCb(GLFWwindow* w, int fbW, int fbH)
	{
		using namespace engine::events;
		if (auto* ctx = Ctx(w))
		{
			EventSlot e{};
			e.header.type = static_cast<std::uint16_t>(EventType::WindowResized);
			e.header.categories = static_cast<std::uint16_t>(defaultCategories(EventType::WindowResized));
			e.header.priority = static_cast<std::uint16_t>(defaultPriority(EventType::WindowResized));
			e.header.handled = 0;
			e.header.flags = 0;
			e.header.timestamp = Now();
			e.payload.wr.fbWidth = fbW;
			e.payload.wr.fbHeight = fbH;
			ctx->bus->pushImmediate(e);
			ctx->window->onResize(fbW, fbH);
		}

		logf("[Window] Framebuffer resized %dx%d", fbW, fbH);
	}
}