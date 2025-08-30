#pragma once

#include "Core.h"

namespace Titus
{
	class TITUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client
	Application* CreateApplication();
}