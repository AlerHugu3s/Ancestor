#include <Ancestor.h>

class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()
		: Layer("Example"){}
	void OnUpdate() override
	{
		//AC_INFO("ExampleLayer::Update");
		if(Ancestor::Input::IsKeyPressed(AC_KEY_TAB))
			AC_TRACE("TAB Key is pressed (Poll)");
	}
	void OnEvent(Ancestor::Event& event) override
	{
		//AC_TRACE("{0}", event);
		if (event.GetEventType() == Ancestor::EventType::KeyPressed)
		{
		Ancestor::KeyPressedEvent& e = (Ancestor::KeyPressedEvent&)event;
		if(e.GetKeyCode() == AC_KEY_TAB)
			AC_TRACE("TAB Key is pressed (Event)");
		AC_TRACE("{0}",(char)e.GetKeyCode());
		}
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