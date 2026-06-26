#include <cassert>
#include "DebugOverlayLayer.hpp"
#include "EngineCore/Core/Layer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace
{
	struct HudOverlayState
	{
		float frameTimeMs = 0.0f;
		float fps = 0.0f;
	};

	HudOverlayState g_HudState;
}

DebugOverlayLayer::DebugOverlayLayer(const std::string& name, const engine::platform::Window& window) : 
	engine::core::Layer(name, window)
{

}

void DebugOverlayLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	assert(ImGui_ImplGlfw_InitForOpenGL(window().handle(), true));
	assert(ImGui_ImplOpenGL3_Init("#version 330"));
}

void DebugOverlayLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void DebugOverlayLayer::OnUpdate(float dt)
{
	g_HudState.frameTimeMs = dt * 1000.0f;
	g_HudState.fps = (dt > 0.0f) ? (1.0f / dt) : 0.0f;
}

void DebugOverlayLayer::OnRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::SetNextWindowPos(ImVec2(12.0f, 12.0f), ImGuiCond_Always);

	const ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav;

	if (ImGui::Begin("HUD", nullptr, flags))
	{
		ImGui::Text("Frame: %.2f ms (%.1f FPS)", g_HudState.frameTimeMs, g_HudState.fps);
		ImGui::Text("Framebuffer: %ux%u", window().getFramebufferWidth(), window().getFramebufferHeight());

		const ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Mouse capture: %s", io.WantCaptureMouse ? "yes" : "no");
		ImGui::Text("Keyboard capture: %s", io.WantCaptureKeyboard ? "yes" : "no");
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool DebugOverlayLayer::OnEvent(const engine::events::EventSlot& e, engine::events::EventContext& ctx)
{
	//std::printf("DebugOverlayLayer received event of type: %d\n", e.header.type);

	(void)e;
	(void)ctx;
	return false;
}
