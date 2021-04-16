#pragma once

#include <glm/glm.hpp>

namespace Ancestor {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const {}
		virtual void UnBind() const {}

		static Ref<Shader> Create(const std::string& vertexSrc,const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& path);
	};
}