#include "acpch.h"
#include "Application.h"

#include "Ancestor/Log.h"

#include <GLFW/glfw3.h>

namespace Ancestor {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(color.red, color.green, color.blue, color.alpha);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseClick));
		AC_CORE_TRACE("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnMouseClick(MouseButtonPressedEvent& e)
	{
		int button = e.GetButton();
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
			color.red = 0.0f;
			color.green = 1.0f;
			color.blue = 1.0f;
			return true;
		case GLFW_MOUSE_BUTTON_2:
			color.red = 1.0f;
			color.green = 0.0f;
			color.blue = 1.0f;
			return true;
		}
		return false;
	}
}