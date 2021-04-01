#pragma once

#include <glm/glm.hpp>

namespace Ancestor {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const {}
		virtual void UnBind() const {}

		static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);
	private:
		uint32_t m_RendererId;
	};
}