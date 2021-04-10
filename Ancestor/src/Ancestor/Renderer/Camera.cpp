#include "acpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Ancestor::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	:m_ProjectionMartix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),m_ViewMartix(1.0f),m_ViewProjectionMartix(1.0f),m_Position(0.0f),m_Rotation(0.0f)
{
	RecalculateViewMartix();
}

void Ancestor::OrthographicCamera::SetDireaction(glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	//m_ViewMartix = glm::lookAt(m_Position, cameraFront, cameraUp);
	m_ProjectionMartix = glm::perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
 	m_ViewMartix = glm::translate(glm::mat4(1.0f), m_Position);
	//m_ViewProjectionMartix = m_ProjectionMartix * m_ViewMartix;
	RecalculateViewMartix();
}

void Ancestor::OrthographicCamera::RecalculateViewMartix()
{
	glm::mat4 transform = 
		glm::translate(glm::mat4(1.0f), m_Position)*
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1))*
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))*
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));

	m_ViewMartix = glm::inverse(transform);
	m_ViewProjectionMartix = m_ProjectionMartix * m_ViewMartix;
}
