#include <Ancestor.h>
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPos(0.0f)
	{
		m_VertexArray = Ancestor::VertexArray::Create();

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		Ancestor::Ref<Ancestor::VertexBuffer> vertexBuffer;
		vertexBuffer = Ancestor::VertexBuffer::Create(vertices, sizeof(vertices));

		Ancestor::BufferLayout layout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" },
			{Ancestor::ShaderDataType::Float4 ,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		Ancestor::Ref<Ancestor::IndexBuffer> indexBuffer;
		indexBuffer = Ancestor::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
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

		m_Shader = Ancestor::Shader::Create(vertexSrc, fragmentSrc);

		squareVA = Ancestor::VertexArray::Create();
		float sqVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5F,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ancestor::Ref<Ancestor::VertexBuffer> squareVB;
		squareVB = Ancestor::VertexBuffer::Create(sqVertices, sizeof(sqVertices));
		Ancestor::BufferLayout sqLayout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" },
			{Ancestor::ShaderDataType::Float2 ,"a_TexCoord" }
		};
		squareVB->SetLayout(sqLayout);
		squareVA->AddVertexBuffer(squareVB);
		unsigned int sqIndices[6] = { 0,1,2,2,3,0 };
		Ancestor::Ref<Ancestor::IndexBuffer> squareIB;
		squareIB = Ancestor::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t));
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

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		squareShader = Ancestor::Shader::Create(sqVertexSrc, sqFragmentSrc);

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";
		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			uniform sampler2D u_Texure;

			in vec2 v_TexCoord;

			void main()
			{
				color = texture(u_Texure,v_TexCoord);
			}
		)";
		m_Texture = Ancestor::Texture2D::Create("assets/textures/BlueNoise.png");
		textureShader = Ancestor::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc);
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

		std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->Bind();
		std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", m_SqColor);

		glm::vec4 redColor = glm::vec4(0.8, 0.2, 0.2, 1.0);
		glm::vec4 blueColor = glm::vec4(0.2, 0.2, 0.8, 1.0);
		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				/*if((x+y)%2 == 0)
					squareShader->UploadUniformFloat4("u_Color", redColor);
				else
					squareShader->UploadUniformFloat4("u_Color", blueColor);*/

				Ancestor::Renderer::Submit(squareVA, squareShader,transform);
			}
		}
		m_Texture->Bind(0);
		Ancestor::Renderer::Submit(squareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Ancestor::Renderer::Submit(m_VertexArray, m_Shader);

		Ancestor::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Color Setting");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SqColor));
		ImGui::End();
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
	Ancestor::Ref<Ancestor::Shader> m_Shader;
	Ancestor::Ref<Ancestor::VertexArray> m_VertexArray;

	Ancestor::Ref<Ancestor::Shader> squareShader;
	Ancestor::Ref<Ancestor::VertexArray> squareVA;

	Ancestor::Ref<Ancestor::Texture> m_Texture;
	Ancestor::Ref<Ancestor::Shader> textureShader;

	Ancestor::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPos;
	float m_CameraSpeed = -3.0f;
	bool m_IsDrag = false;
	glm::vec3 m_SqColor = glm::vec3(0.8f,0.2f,0.2f);
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