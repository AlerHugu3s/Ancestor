#include <Ancestor.h>

class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()
		: Layer("Example"){}
	void OnUpdate() override
	{
		AC_INFO("ExampleLayer::Update");
	}
	void OnEvent(Ancestor::Event& event) override
	{
		AC_TRACE("{0}", event);
	}
};

class Sandbox : public Ancestor::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Ancestor::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Ancestor::Application* Ancestor::CreateApplication()
{
	return new Sandbox();
}