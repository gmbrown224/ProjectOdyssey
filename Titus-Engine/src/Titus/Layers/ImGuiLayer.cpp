#include "TEpch.h"

#include "ImGuiLayer.h"
#include "Titus/Application.h"

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Titus
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") { }

	ImGuiLayer::~ImGuiLayer() { }

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() { }

	void ImGuiLayer::OnUpdate() 
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeyCtrl = ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl);
		io.KeyShift = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
		io.KeyAlt = ImGui::IsKeyDown(ImGuiKey_LeftAlt) || ImGui::IsKeyDown(ImGuiKey_RightAlt);
		io.KeySuper = ImGui::IsKeyDown(ImGuiKey_LeftSuper) || ImGui::IsKeyDown(ImGuiKey_RightSuper);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeyCtrl = ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl);
		io.KeyShift = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
		io.KeyAlt = ImGui::IsKeyDown(ImGuiKey_LeftAlt) || ImGui::IsKeyDown(ImGuiKey_RightAlt);
		io.KeySuper = ImGui::IsKeyDown(ImGuiKey_LeftSuper) || ImGui::IsKeyDown(ImGuiKey_RightSuper);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();

		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}