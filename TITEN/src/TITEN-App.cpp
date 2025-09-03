#include <Titus.h>

class Layer : public Titus::Layer
{
public:
	Layer() : Titus::Layer("Example") { }

	void OnUpdate() override { }

	void OnImGuiRender() override
	{
		//ImGui::Begin("Hello, ImGui!");

		//if (ImGui::Button("Press me"))
		//	APP_TRACE("Button pressed (ImGui)");

		//ImGui::End();
	}

	void OnEvent(Titus::Event& event) override
	{
		if (event.GetEventType() == Titus::EventType::KeyPressed)
		{
			//Titus::KeyPressedEvent& e = (Titus::KeyPressedEvent&)event;
			//if (e.GetKeyCode() == TE_TAB)
			//	APP_TRACE("Tab key is pressed (event)");
		}
	}
};

class TITEN : public Titus::Application
{
public:
	TITEN()
	{
		PushLayer(new Layer());
	}

	~TITEN() { }
};

Titus::Application* Titus::CreateApplication()
{
	return new TITEN();
}