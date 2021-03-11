#pragma once

#include "Core.h"
#include "Window.h"

#include "Ancestor/Events/ApplicationEvent.h"
#include "Ancestor/Events/MouseEvent.h"


namespace Ancestor {
	struct Color
	{
		float red = 1.0f;
		float green = 0.0f;
		float blue = 1.0f;
		float alpha = 1.0f;

		Color(float r = 1.0f, float g = 0.0f, float b = 1.0f, float a = 1.0f)
			:red(r), blue(b), green(g), alpha(a) {}
	};

	class ANCESTOR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		Color color;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnMouseClick(MouseButtonPressedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in the Client
	Application* CreateApplication();
}


