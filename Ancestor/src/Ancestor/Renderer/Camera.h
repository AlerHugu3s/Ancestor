#pragma once

#include <glm/glm.hpp>

namespace Ancestor {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left,float right,float bottom,float top);

		void SetPosition(glm::vec3 position) { m_Position = position; RecalculateViewMartix(); }
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMartix(); }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		const glm::mat4& GetViewMartix() const { return m_ViewMartix; }
		const glm::mat4& GetProjectionMartix() const { return m_ProjectionMartix; }
		const glm::mat4& GetViewPorjectionMartix() const { return m_ViewProjectionMartix; }
	private:
		void RecalculateViewMartix();
	private:
		glm::mat4 m_ViewMartix,m_ProjectionMartix,m_ViewProjectionMartix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};
}