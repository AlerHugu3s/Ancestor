#include "acpch.h"
#include "Application.h"

#include "Ancestor/Log.h"
#include "Ancestor/Input.h"
#include "Ancestor/Renderer/Renderer.h"
#include "Ancestor/Renderer/RenderCommand.h"

#include <glad/glad.h>
namespace Ancestor {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AC_CORE_ASSERT(!s_Instance,"Application already Exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(AC_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3 ,"a_Position" },
			{ShaderDataType::Float4 ,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Position,1.0);
				v_Color = a_Color;
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));

		squareVA.reset(VertexArray::Create());
		float sqVertices[4 * 3] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75F,  0.75f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		BufferLayout sqLayout = {
			{ShaderDataType::Float3 ,"a_Position" }
		};
		squareVB->SetLayout(sqLayout);
		squareVA->AddVertexBuffer(squareVB);
		unsigned int sqIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squareIB);

		std::string sqVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position,1.0);
			}
		)";
		std::string sqFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2,0.2,0.8,1.0);
			}
		)";

		squareShader.reset(new Shader(sqVertexSrc, sqFragmentSrc));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			squareShader->Bind();
			Renderer::Submit(squareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AC_BIND_EVENT_FN(Application::OnWindowClose));

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
}