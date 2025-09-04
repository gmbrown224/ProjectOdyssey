#include "TEpch.h"

#include "ImGuiLayer.h"
#include "Titus/Application.h"

#include "imgui.h"
#include "imgui_internal.h"
//#include "backends/imgui_impl_vulkan.h"
#include "backends/imgui_impl_sdl3.h"

namespace Titus
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") { }

	ImGuiLayer::~ImGuiLayer() { }

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcon;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		SDL_Window* window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplSDL3_InitForVulkan(window);

		//ImGui_ImplVulkan_InitInfo init_info = {};
		//ImGui_ImplVulkan_Init(&init_info);
	}

	void ImGuiLayer::OnDetach() 
	{
		//ImGui_ImplVulkan_Shutdown();
		//ImGui_ImplSDL3_Shutdown();

		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() 
	{
		//ImGui_ImplVulkan_NewFrame();
		//ImGui_ImplSDL3_NewFrame();

		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		ImDrawData* draw_data = ImGui::GetDrawData();

		//ImGui_ImplVulkan_RenderDrawData(draw_data, nullptr);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void ImGuiLayer::OnImGuiRender() 
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}