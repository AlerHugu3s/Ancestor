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
		
		m_Model = std::make_shared<Ancestor::Model>("assets/shaders/models.obj");
		m_Shader = Ancestor::Shader::Create("assets/shaders/OfficialExample.glsl");

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

		m_Transform = glm::mat4(0);
		//Ancestor::Renderer::Submit(m_Model, m_Shader,m_Transform);

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
	Ancestor::Ref<Ancestor::Model> m_Model;
	Ancestor::Ref<Ancestor::Shader> m_Shader;
	Ancestor::Ref<Ancestor::Texture> m_Texture;
	glm::mat4 m_Transform;

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