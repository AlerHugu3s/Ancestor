#pragma once

#include <glm/glm.hpp>

namespace Ancestor {
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UPWARD,
		DOWNWARD
	};

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float left,float right,float bottom,float top);

		void SetPosition(glm::vec3 position) { m_Position = position; RecalculateViewMartix(); }
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetRotation(float yaw, float pitch) { m_Yaw = yaw; m_Pitch = pitch; RecalculateViewMartix(); }

		const glm::mat4& GetViewMartix() const { return m_ViewMartix; }
		const glm::mat4& GetProjectionMartix() const { return m_ProjectionMartix; }
		const glm::mat4& GetViewPorjectionMartix() const { return m_ViewProjectionMartix; }

		void ProcessKeyboard(CameraMovement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		
	private:
		void RecalculateViewMartix();
	private:
		glm::mat4 m_ViewMartix,m_ProjectionMartix,m_ViewProjectionMartix;
		float movementSpeed = 2.5f,mouseSensitivity = 0.1f,zoom = 0.0f;
		float m_Yaw = -90.0f, m_Pitch = 0.0f;
		glm::vec3 m_Position, m_Up, m_Front, m_Right, m_WorldUp;
	};
}