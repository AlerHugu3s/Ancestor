#include <Ancestor.h>
#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Ancestor::Event& event) override
	{
		//AC_TRACE("{0}", event);
	}
};

class Sandbox : public Ancestor::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Ancestor::Application* Ancestor::CreateApplication()
{
	return new Sandbox();
}