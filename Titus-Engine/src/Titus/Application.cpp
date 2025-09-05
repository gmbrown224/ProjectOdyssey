#include "TEpch.h"

#include "Application.h"
#include "Titus/Logging/Log.h"
#include "SDL3/SDL_vulkan.h"

namespace Titus
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			TE_CORE_CRITICAL("Failed to initialize SDL: {0}", SDL_GetError());
			m_Running = false;
			return;
		}

		m_Window = std::make_unique<Window>(1280, 720, "TITEN", SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);

		if (!m_Window || !m_Window->GetNativeWindow()) {
			TE_CORE_CRITICAL("SDL_CreateWindow failed: {}", SDL_GetError());
			m_Running = false;
			return;
		}

		// m_Window->SetEventCallback(TE_BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		SDL_Quit();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		/*EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));*/

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		if (!m_Running || !m_Window || !m_Window->GetNativeWindow()) {
			TE_CORE_CRITICAL("App not initialized; aborting Run()");
			return;
		}

		m_Window->Show();

		while (m_Running)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_QUIT) {
					m_Running = false;
				}
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			//m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}