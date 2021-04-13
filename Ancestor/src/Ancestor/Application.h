#pragma once

#include "Window.h"

#include "Ancestor/Events/ApplicationEvent.h"
#include "Ancestor/Events/MouseEvent.h"
#include "Ancestor/LayerStack.h"


#include "ImGui/ImGuiLayer.h"




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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		Color color;

		bool OnWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in the Client
	Application* CreateApplication();
}


