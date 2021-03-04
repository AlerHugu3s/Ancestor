#include <Ancestor.h>

class Sandbox : public Ancestor::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Ancestor::Application* Ancestor::CreateApplication()
{
	return new Sandbox();
}