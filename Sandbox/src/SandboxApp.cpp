#include <Ancestor.h>
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Ancestor::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),m_Camera(-1600.0f, 1600.0f, -900.0f, 900.0f),m_CameraPos(0.0f,0.0f,10.0f)
	{
		m_Shader = Ancestor::Shader::Create("assets/shaders/OfficialExample.glsl");
		//m_Model = std::make_shared<Ancestor::Model>("C:/Users/xiasm/Desktop/Ancestor/Sandbox/assets/models/backpack.obj");
		projPath = std::filesystem::current_path();
		if(m_ObjPath != "none")
			m_Model = std::make_shared<Ancestor::Model>(m_ObjPath);
	}
	void OnUpdate(Ancestor::Timestep ts) override
	{
		if (Ancestor::Input::IsMouseButtonPressed(AC_MOUSE_BUTTON_RIGHT))
		{
			float xPos = Ancestor::Input::GetMouseX();
			float yPos = Ancestor::Input::GetMouseY();
			if (m_IsDrag == false)
			{
				lastX = xPos;
				lastY = yPos;
				m_IsDrag = true;
			}
			
			float xOffset = xPos - lastX;
			float yOffset = lastY - yPos;

			lastX = xPos;
			lastY = yPos;

			m_Camera.ProcessMouseMovement(xOffset, yOffset);
			if (Ancestor::Input::IsKeyPressed(AC_KEY_LEFT) || Ancestor::Input::IsKeyPressed(AC_KEY_A))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::LEFT, ts);
			}
			if (Ancestor::Input::IsKeyPressed(AC_KEY_RIGHT) || Ancestor::Input::IsKeyPressed(AC_KEY_D))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::RIGHT, ts);
			}
			if (Ancestor::Input::IsKeyPressed(AC_KEY_UP) || Ancestor::Input::IsKeyPressed(AC_KEY_W))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::FORWARD, ts);
			}
			if (Ancestor::Input::IsKeyPressed(AC_KEY_DOWN) || Ancestor::Input::IsKeyPressed(AC_KEY_S))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::BACKWARD, ts);
			}
			if (Ancestor::Input::IsKeyPressed(AC_KEY_SPACE))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::UPWARD, ts);
			}
			if (Ancestor::Input::IsKeyPressed(AC_KEY_LEFT_CONTROL))
			{
				m_Camera.ProcessKeyboard(Ancestor::CameraMovement::DOWNWARD, ts);
			}
		}

		

		Ancestor::RenderCommand::SetClearColor({ 0.1f, 0.4f, 0.7f, 1.0f });
		Ancestor::RenderCommand::Clear();

		Ancestor::Renderer::BeginScene(m_Camera);

		m_Transform = glm::mat4(1.0f);
		m_Transform = glm::translate(m_Transform, glm::vec3(0.0f, 0.0f, 0.0f));
		m_Transform = glm::scale(m_Transform, glm::vec3(1.0f, 1.0f, 1.0f));
		
		if (m_ObjPath != "none")
		{
			std::filesystem::current_path(projPath);
			if (m_Model == nullptr)
				m_Model = std::make_shared<Ancestor::Model>(m_ObjPath);
			//m_Texture->Bind(0);
			Ancestor::Renderer::Submit(m_Model, m_Shader,m_Transform);
		}

		Ancestor::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O"))
				{
					m_Model = nullptr;
					m_ObjPath = openfilename();
					replace(m_ObjPath.begin(), m_ObjPath.end(), '\\', '/');
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Camera Setting");
		ImGui::DragFloat3("CameraPos", glm::value_ptr(m_CameraPos), 1.0f ,-1000.0f, 1000.0f);
		ImGui::DragFloat("CamerYAW", &m_CameraYaw, 1.0f  ,-180.0f, 180.0f);
		ImGui::DragFloat("CamerPitch", &m_CameraPitch, 1.0f, -180.0f, 180.0f);
		ImGui::End();
	}

	void OnEvent(Ancestor::Event& event) override
	{
		Ancestor::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Ancestor::MouseButtonPressedEvent>(AC_BIND_EVENT_FN(ExampleLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<Ancestor::MouseButtonReleasedEvent>(AC_BIND_EVENT_FN(ExampleLayer::OnMouseButtonReleasedEvent));
	}
	bool OnMouseButtonPressedEvent(Ancestor::MouseButtonPressedEvent& event)
	{
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

	std::string openfilename(char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
		OPENFILENAME ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = (LPCWSTR)filter;
		ofn.lpstrFile = (LPWSTR)fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = (LPCWSTR)"";

		std::string fileNameStr;
		if (GetOpenFileName(&ofn))
		{
			for (size_t i = 0; i < MAX_PATH - 1; i++)
			{
				if (fileName[i] == '\0' && fileName[i + 1] != '\0')
				{
					for (size_t j = i; j < MAX_PATH - 1; j++)
					{
						fileName[j] = fileName[j + 1];
					}
				}
			}
			fileNameStr = fileName;
		}
			
		return fileNameStr;
	}

private:
	Ancestor::Ref<Ancestor::Model> m_Model = nullptr;
	Ancestor::Ref<Ancestor::Shader> m_Shader;
	Ancestor::Ref<Ancestor::Texture> m_Texture;
	glm::mat4 m_Transform;

	Ancestor::PerspectiveCamera m_Camera;
	glm::vec3 m_CameraPos;
	float m_CameraYaw = -90.0f, m_CameraPitch = 0.0f;
	float m_CameraMoveSpeed = 10.0f,m_CameraRotateSpeed = 30.0f, m_CameraZoom = 45.0f;
	bool m_IsDrag = false;

	float lastX, lastY;

	glm::vec3 m_SqColor = glm::vec3(0.8f,0.2f,0.2f);

	std::string m_ObjPath = "none";
	std::filesystem::path projPath;
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