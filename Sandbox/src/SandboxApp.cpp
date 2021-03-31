#include <Ancestor.h>
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPos(0.0f)
	{
		m_VertexArray.reset(Ancestor::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Ancestor::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Ancestor::VertexBuffer::Create(vertices, sizeof(vertices)));

		Ancestor::BufferLayout layout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" },
			{Ancestor::ShaderDataType::Float4 ,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<Ancestor::IndexBuffer> indexBuffer;
		indexBuffer.reset(Ancestor::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
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

		m_Shader.reset(new Ancestor::Shader(vertexSrc, fragmentSrc));

		squareVA.reset(Ancestor::VertexArray::Create());
		float sqVertices[4 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5F,  0.5f, 0.0f
		};
		std::shared_ptr<Ancestor::VertexBuffer> squareVB;
		squareVB.reset(Ancestor::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		Ancestor::BufferLayout sqLayout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" }
		};
		squareVB->SetLayout(sqLayout);
		squareVA->AddVertexBuffer(squareVB);
		unsigned int sqIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Ancestor::IndexBuffer> squareIB;
		squareIB.reset(Ancestor::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squareIB);

		std::string sqVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
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

		squareShader.reset(new Ancestor::Shader(sqVertexSrc, sqFragmentSrc));
	}
	void OnUpdate(Ancestor::Timestep ts) override
	{
		if (Ancestor::Input::IsMouseButtonPressed(AC_MOUSE_BUTTON_RIGHT))
		{
			m_CameraPos.x = (1.6f - Ancestor::Input::GetMouseX() / 1280.0f * 3.2f);
			m_CameraPos.y = -0.9f + Ancestor::Input::GetMouseY() / 720.0f * 1.8f;
		}

		if (Ancestor::Input::IsKeyPressed(AC_KEY_LEFT))
		{
			m_CameraPos.x -= m_CameraSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_RIGHT))
		{
			m_CameraPos.x += m_CameraSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_UP))
		{
			m_CameraPos.y += m_CameraSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_DOWN))
		{
			m_CameraPos.y -= m_CameraSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPos);

		Ancestor::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ancestor::RenderCommand::Clear();

		m_Camera.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

		Ancestor::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Ancestor::Renderer::Submit(squareVA, squareShader,transform);
			}
		}
		Ancestor::Renderer::Submit(m_VertexArray, m_Shader);

		Ancestor::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Ancestor::Event& event) override
	{
		//AC_TRACE("{0}", event);
		Ancestor::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Ancestor::MouseButtonPressedEvent>(AC_BIND_EVENT_FN(ExampleLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<Ancestor::MouseButtonReleasedEvent>(AC_BIND_EVENT_FN(ExampleLayer::OnMouseButtonReleasedEvent));
	}
	bool OnMouseButtonPressedEvent(Ancestor::MouseButtonPressedEvent& event)
	{
		if (event.GetButton() == AC_MOUSE_BUTTON_RIGHT)
		{
			m_IsDrag = true;
		}
		return false;
	}
	bool OnMouseButtonReleasedEvent(Ancestor::MouseButtonReleasedEvent& event)
	{
		if (event.GetButton() == AC_MOUSE_BUTTON_RIGHT)
		{
			m_IsDrag = false;
		}
		return false;
	}

private:
	std::shared_ptr<Ancestor::Shader> m_Shader;
	std::shared_ptr<Ancestor::VertexArray> m_VertexArray;

	std::shared_ptr<Ancestor::Shader> squareShader;
	std::shared_ptr<Ancestor::VertexArray> squareVA;

	Ancestor::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPos;
	float m_CameraSpeed = -3.0f;
	bool m_IsDrag = false;
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