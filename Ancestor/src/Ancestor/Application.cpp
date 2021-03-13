#include "acpch.h"
#include "Application.h"

#include "Ancestor/Log.h"

#include <glad/glad.h>

namespace Ancestor {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AC_CORE_ASSERT(!s_Instance,"Application already Exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	}
	 
	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(color.red, color.green, color.blue, color.alpha);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseClick));

		for (auto it = m_LayerStack.end();it!=m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled == true) break;
		}
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
		case 0:
			color.red = 0.0f;
			color.green = 1.0f;
			color.blue = 1.0f;
			return true;
		case 1:
			color.red = 1.0f;
			color.green = 0.0f;
			color.blue = 1.0f;
			return true;
		}
		return false;
	}
}