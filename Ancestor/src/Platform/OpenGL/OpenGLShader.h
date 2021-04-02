#pragma once

#include "Ancestor/Renderer/Shader.h"
#include <glm/glm.hpp>

//TODO Remove!
typedef unsigned int GLenum;

namespace Ancestor {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc,const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt1(const std::string& name, int value);
		void UploadUniformFloat1(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		std::string ReadFile(const std::string& path);
	private:
		uint32_t m_RendererId;
	};
}