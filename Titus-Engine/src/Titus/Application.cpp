#include "TEpch.h"
#include "Application.h"

namespace Titus
{
	Application::Application() { }

	Application::~Application() { }

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			APP_TRACE("Event category is application");
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			APP_TRACE("Event category is input");
		}

		while (true);
	}
}