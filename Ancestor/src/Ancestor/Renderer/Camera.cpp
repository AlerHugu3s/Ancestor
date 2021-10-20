#include "acpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ancestor
{
	//PerspectiveCamera
	PerspectiveCamera::PerspectiveCamera(float left, float right, float bottom, float top)
		:m_ProjectionMartix(glm::perspective(glm::radians(zoom), (std::abs(right) + std::abs(left)) / (std::abs(top) + std::abs(bottom)), 0.1f, 100.0f)), m_ViewMartix(1.0f), m_ViewProjectionMartix(1.0f), m_Position(glm::vec3(0.0f, 0.0f, 5.0f)),
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f))
	{
		m_WorldUp = m_Up;
		RecalculateViewMartix();
	}

	void PerspectiveCamera::RecalculateViewMartix()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_ViewMartix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		m_ViewProjectionMartix = m_ProjectionMartix * m_ViewMartix;
	}

	void PerspectiveCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		if (direction == FORWARD)
			m_Position += m_Front * velocity;
		if (direction == BACKWARD)
			m_Position -= m_Front * velocity;
		if (direction == LEFT)
			m_Position -= m_Right * velocity;
		if (direction == RIGHT)
			m_Position += m_Right * velocity;
		if (direction == UPWARD)
			m_Position += m_Up * velocity;
		if (direction == DOWNWARD)
			m_Position -= m_Up * velocity;
		RecalculateViewMartix();
	}

	void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		RecalculateViewMartix();
	}

	//OrthographicCamera
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
