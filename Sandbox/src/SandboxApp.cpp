#include <Titus.h>

class Layer : public Titus::Layer
{
public:
	Layer() : Titus::Layer("Example") { }

	void OnUpdate() override { }

	void OnEvent(Titus::Event& event) override { }
};

class Sandbox : public Titus::Application
{
public:
	Sandbox() 
	{
		PushLayer(new Layer());
		PushOverlay(new Titus::ImGuiLayer());
	}

	~Sandbox() { }
};

Titus::Application* Titus::CreateApplication()
{
	return new Sandbox();
}