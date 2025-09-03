#pragma once

#include "SDL3/SDL.h"

namespace Titus {

	class TITUS_API Window
	{
	public:
		Window(int width, int height, const std::string& title, Uint32 flags = SDL_WINDOW_OPENGL) : m_Width(width), m_Height(height)
		{
			m_Window = SDL_CreateWindow(title.c_str(), width, height, flags);

			if (!m_Window) {
				SDL_Log("SDL_CreateWindow Error: ", SDL_GetError());
			}

			m_GLContext = SDL_GL_CreateContext(m_Window);

			SDL_SetWindowTitle(m_Window, title.c_str());

			/*SDL_Surface* icon = SDLImage_Load("C:\\Users\\gramb\\source\\repos\\Titus-Engine\\Titus-Engine\\src\\Assets\\Logos\\Spartan.png");
			if (!icon) {
				SDL_Log("Failed to load icon PNG: %s", SDLImage_GetError());
				return;
			}

			SDL_SetWindowIcon(m_Window, icon);
			SDL_DestroySurface(icon);*/
		}

		virtual ~Window() 
		{
			if (m_GLContext) {
				SDL_GL_DestroyContext(m_GLContext);
				m_GLContext = nullptr;
			}

			if (m_Window) {
				SDL_DestroyWindow(m_Window);
				m_Window = nullptr;
			}
		}

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		// Accessors
		SDL_Window* GetNativeWindow() const { return m_Window; }
		SDL_GLContext GetGLContext() const { return m_GLContext; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

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
		SDL_GLContext m_GLContext = nullptr;
		int m_Width = 0;
		int m_Height = 0;
	};

}