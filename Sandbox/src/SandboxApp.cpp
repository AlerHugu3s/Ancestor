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
		//3D Model Show
		m_VertexArray = Ancestor::VertexArray::Create();

		Ancestor::Ref<Ancestor::Object3D> obj = Ancestor::Object3D::Create("assets/models/test-nan.obj", "assets/materials", true);
		std::vector<Ancestor::Ref<Ancestor::Model>> models = obj->GetModels();
		std::vector<float> m_3DVertices = obj->GetVertices();
		AC_TRACE("Vertices:");
		for (size_t j = 0; j < m_3DVertices.size(); j++)
		{
			AC_TRACE(m_3DVertices[j]);
		}

		Ancestor::Ref<Ancestor::VertexBuffer> vertexBuffer;
		AC_CORE_ASSERT(!m_3DVertices.empty(), "Vertices is NULL!");
		vertexBuffer = Ancestor::VertexBuffer::Create(m_3DVertices.data(), m_3DVertices.size());

		Ancestor::BufferLayout layout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" },
			{Ancestor::ShaderDataType::Float4 ,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Ancestor::Ref<Ancestor::IndexBuffer> indexBuffer;

		for (size_t i = 0; i < models.size(); i++)
		{
			AC_TRACE("modelIndices:");
			std::vector<unsigned int> vec = models[i]->GetVertexIndices();
			for (size_t j = 0; j < vec.size(); j++)
			{
				AC_TRACE(vec[j]);
			}
			m_VertexArray->AddIndexBuffer(vec.data(), vec.size());
		}

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

		m_Texture = Ancestor::Texture2D::Create("assets/textures/BlueNoise.png");
		m_BlendingTestTexture = Ancestor::Texture2D::Create("assets/textures/twiceLogo.png");
		textureShader = Ancestor::Shader::Create("assets/shaders/Texture.glsl");
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
		//static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->Bind();
		//std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", m_SqColor);
		//m_Texture->Bind(0);
		//Ancestor::Renderer::Submit(squareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//m_BlendingTestTexture->Bind(0);
		//Ancestor::Renderer::Submit(squareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Ancestor::Renderer::Submit(m_VertexArray, m_Shader);

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
	Ancestor::Ref<Ancestor::Texture> m_BlendingTestTexture;
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