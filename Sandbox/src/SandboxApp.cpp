#include <Ancestor.h>
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()                                                                                                                                                                                                                                      
		: Layer("Example"),m_Camera(-1600.0f, 1600.0f, -900.0f, 900.0f),m_CameraPos(0.0f,0.0f,-10.0f),m_CameraRot(0.0f)
	{
		//3D Model Show
		m_VertexArray = Ancestor::VertexArray::Create();

		Ancestor::Ref<Ancestor::Object3D> obj = Ancestor::Object3D::Create("assets/models/FinalBaseMesh.obj", "assets/materials", true);
		std::vector<Ancestor::Ref<Ancestor::Model>> models = obj->GetModels();
		std::vector<float> m_3DVertices = obj->GetVertices();

		Ancestor::Ref<Ancestor::VertexBuffer> vertexBuffer;
		AC_CORE_ASSERT(!m_3DVertices.empty(), "Vertices is NULL!");
		vertexBuffer = Ancestor::VertexBuffer::Create(m_3DVertices.data(), m_3DVertices.size());

		Ancestor::BufferLayout layout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Ancestor::Ref<Ancestor::IndexBuffer> indexBuffer;
		uint32_t* modelIndices = (uint32_t*)malloc(1 * sizeof(uint32_t));
		size_t size = 0;
		for (size_t i = 0; i < models.size(); i++)
		{
			modelIndices = (uint32_t *)realloc(modelIndices,models[i]->GetVertexIndices().size() * sizeof(uint32_t));
			std::vector<uint32_t> data = models[i]->GetVertexIndices();
			for (size_t i = size; i < size + data.size(); i++)
			{
				*(modelIndices + i) = data[i];
			}
			size += models[i]->GetVertexIndices().size();
		}
		indexBuffer = Ancestor::IndexBuffer::Create(modelIndices, size);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		cubeVA = Ancestor::VertexArray::Create();
		float cubeVertices[5*3] = {
			-0.5f, -0.5f, -1.0f,
			-0.5f,  0.5f, -1.0f,
			 0.5f,  0.5f, -1.0f,
			 0.5f, -0.5f, -1.0f,
			 0.0f,  0.0f,  0.0f
		};
		Ancestor::Ref<Ancestor::VertexBuffer> cubeVB;
		cubeVB = Ancestor::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));

		Ancestor::BufferLayout cubeLayout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Position" }
		};
		cubeVB->SetLayout(layout);
		cubeVA->AddVertexBuffer(cubeVB);
		Ancestor::Ref<Ancestor::IndexBuffer> cubeIB;
		unsigned int cubeIndices[18] = {
			0, 4, 1,
			1, 4, 2,
			2, 4, 3,
			3, 4, 0,
			0, 1, 3,
			1, 3, 2 };
		cubeIB = Ancestor::IndexBuffer::Create(cubeIndices, 18);
		cubeVA->SetIndexBuffer(cubeIB);

		m_Shader = Ancestor::Shader::Create("assets/shaders/3DModel.glsl");

		m_Texture = Ancestor::Texture2D::Create("assets/textures/BlueNoise.png");
		m_BlendingTestTexture = Ancestor::Texture2D::Create("assets/textures/twiceLogo.png");
		textureShader = Ancestor::Shader::Create("assets/shaders/Texture.glsl");

		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		// world space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		Test3DVA = Ancestor::VertexArray::Create();
		Ancestor::Ref<Ancestor::VertexBuffer> Test3DVB = Ancestor::VertexBuffer::Create(vertices, sizeof(vertices));
		Ancestor::BufferLayout test3DLayout = {
			{Ancestor::ShaderDataType::Float3 ,"a_Pos" },
			{Ancestor::ShaderDataType::Float2 ,"a_aTexCoord" }
		};
		Test3DVB->SetLayout(test3DLayout);
		Test3DVA->AddVertexBuffer(Test3DVB);

		Test3DTexture = Ancestor::Texture2D::Create("assets/textures/BlueNoise.png");
		Test3DShader = Ancestor::Shader::Create("assets/shaders/3DTest.glsl");
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
			m_CameraPos.x -= m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_RIGHT))
		{
			m_CameraPos.x += m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_UP))
		{
			m_CameraPos.y += m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_DOWN))
		{
			m_CameraPos.y -= m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_I))
		{
			m_CameraPos.z += m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_K))
		{
			m_CameraPos.z -= m_CameraMoveSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_Q))
		{
			m_CameraRot.z += m_CameraRotateSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_E))
		{
			m_CameraRot.z -= m_CameraRotateSpeed * ts;
		}if (Ancestor::Input::IsKeyPressed(AC_KEY_W))
		{
			m_CameraRot.x += m_CameraRotateSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_S))
		{
			m_CameraRot.x -= m_CameraRotateSpeed * ts;
		}if (Ancestor::Input::IsKeyPressed(AC_KEY_A))
		{
			m_CameraRot.y += m_CameraRotateSpeed * ts;
		}
		if (Ancestor::Input::IsKeyPressed(AC_KEY_D))
		{
			m_CameraRot.y -= m_CameraRotateSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPos);
		m_Camera.SetRotation(m_CameraRot);
		m_Camera.SetDireaction(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		Ancestor::RenderCommand::SetClearColor({ 0.1f, 0.4f, 0.7f, 1.0f });
		Ancestor::RenderCommand::Clear();

		Ancestor::Renderer::BeginScene(m_Camera);
		//static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->Bind();
		//std::dynamic_pointer_cast<Ancestor::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", m_SqColor);
		//m_Texture->Bind(0);
		//Ancestor::Renderer::Submit(squareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//m_BlendingTestTexture->Bind(0);
		//Ancestor::Renderer::Submit(squareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Ancestor::Renderer::Submit(m_VertexArray, m_Shader);

		//Ancestor::Renderer::Submit(cubeVA, m_Shader);

		//Test3DTexture->Bind(0);
		//Test3DTexture->Bind(1);
		//Ancestor::Renderer::Submit(Test3DVA, Test3DShader);

		Ancestor::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Camera Setting");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SqColor));
		ImGui::DragFloat3("CameraPos", glm::value_ptr(m_CameraPos), 1.0f ,-1000.0f, 1000.0f);
		ImGui::DragFloat3("CameraRot", glm::value_ptr(m_CameraRot), 1.0f  ,-180.0f, 180.0f);
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

	Ancestor::Ref<Ancestor::Shader> cubeShader;
	Ancestor::Ref<Ancestor::VertexArray> cubeVA;

	Ancestor::Ref<Ancestor::Shader> Test3DShader;
	Ancestor::Ref<Ancestor::VertexArray> Test3DVA;
	Ancestor::Ref<Ancestor::Texture> Test3DTexture;

	//Ancestor::Ref<Ancestor::Shader> squareShader;
	//Ancestor::Ref<Ancestor::VertexArray> squareVA;

	Ancestor::Ref<Ancestor::Texture> m_Texture;
	Ancestor::Ref<Ancestor::Texture> m_BlendingTestTexture;
	Ancestor::Ref<Ancestor::Shader> textureShader;

	Ancestor::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPos, m_CameraRot;
	float m_CameraMoveSpeed = 10.0f,m_CameraRotateSpeed = 30.0f;
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