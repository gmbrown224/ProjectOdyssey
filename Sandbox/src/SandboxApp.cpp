#include <Titus.h>

class Sandbox : public Titus::Application
{
public:
	Sandbox() { }

	~Sandbox() { }
};

Titus::Application* Titus::CreateApplication()
{
	return new Sandbox();
}