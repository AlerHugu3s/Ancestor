#pragma once

#include "Core.h"
#include "Window.h"

#include "Ancestor/Events/ApplicationEvent.h"
#include "Ancestor/Events/MouseEvent.h"
#include "Ancestor/LayerStack.h"
#include "Ancestor/Events/Event.h"

#include "ImGui/ImGuiLayer.h"

#include "Ancestor/Renderer/Shader.h"
#include "Ancestor/Renderer/Buffer.h"
#include "Ancestor/Renderer/VertexArray.h"
#include "Ancestor/Renderer/Camera.h"


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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> squareShader;
		std::shared_ptr<VertexArray> squareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in the Client
	Application* CreateApplication();
}


