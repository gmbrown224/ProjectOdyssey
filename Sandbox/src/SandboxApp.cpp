#include <Titus.h>

class Layer : public Titus::Layer
{
public:
	Layer() : Titus::Layer("Example") { }

	void OnUpdate() override { }

	void OnEvent(Titus::Event& event) override 
	{
		if (event.GetEventType() == Titus::EventType::KeyPressed)
		{
			Titus::KeyPressedEvent& e = (Titus::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TE_KEY_TAB)
				APP_TRACE("Tab key is pressed (event)");
		}
	}
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