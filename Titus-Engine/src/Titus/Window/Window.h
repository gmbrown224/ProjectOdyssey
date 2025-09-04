#pragma once

#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "Titus/Logging/Log.h"

namespace Titus {

	class TITUS_API Window
	{
	public:
		Window(int width, int height, const std::string& title, Uint32 flags) : m_Width(width), m_Height(height)
		{
			m_Window = SDL_CreateWindow(title.c_str(), m_Width, m_Height, flags);

			if (!m_Window) {
				TE_CORE_ERROR("SDL_CreateWindow Error: {0}", SDL_GetError());
			}

			SDL_SetWindowTitle(m_Window, title.c_str());
		}

		virtual ~Window() 
		{
			if (m_Window) {
				SDL_DestroyWindow(m_Window);
				m_Window = nullptr;
			}
		}

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		// Accessors
		SDL_Window* GetNativeWindow() const { return m_Window; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		// Vulkan
		bool CreateVulkanSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const
		{
			if (!m_Window) return false;

			return SDL_Vulkan_CreateSurface(m_Window, instance, allocator, surface);
		}

		// Utilities
		void SetSize(int width, int height) 
		{ 
			m_Width = width;
			m_Height = height;

			if (m_Window) {
				SDL_SetWindowSize(m_Window, width, height);
			}
		}

		void Show() { if (m_Window) SDL_ShowWindow(m_Window); }
		void Hide() { if (m_Window) SDL_HideWindow(m_Window); }

	private: 
		SDL_Window* m_Window = nullptr;
		int m_Width = 0;
		int m_Height = 0;
	};

}