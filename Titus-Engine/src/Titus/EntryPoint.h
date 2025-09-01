#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern Titus::Application* Titus::CreateApplication();

int main(int argc, char** argv)
{
	Titus::Log::Init();
	auto app = Titus::CreateApplication();

	app->Run();

	delete app;
}

#endif