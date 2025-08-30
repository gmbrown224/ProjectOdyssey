#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern Titus::Application* Titus::CreateApplication();

int main(int argc, char** argv)
{
	Titus::Log::Init();
	TE_CORE_WARN("Initialized Log!");
	int a = 5;
	APP_INFO("Hello World! Var={0}", a);

	auto app = Titus::CreateApplication();

	app->Run();

	delete app;
}

#endif