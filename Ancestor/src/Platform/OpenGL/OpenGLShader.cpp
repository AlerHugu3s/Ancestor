#include "acpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ancestor {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")	return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		AC_CORE_ASSERT(false, "Unknown Shader Type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexSrc,const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}
	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::UploadUniformInt1(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadUniformFloat1(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, values.x, values.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		AC_CORE_ASSERT(shaderSources.size() >= 2, "Not Support so many Shaders!");
		std::array<GLenum,2> glShaderIDs;
		int  glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& shaderSource = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				AC_CORE_ERROR("{0}", infoLog.data());
				AC_CORE_ASSERT(false, "Shader Compilation Failed!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererId = program;
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			AC_CORE_ERROR("{0}", infoLog.data());
			AC_CORE_ASSERT(false, "Shader Link Failed!");
			return;
		}
		for (auto id : glShaderIDs)
		{
			glDetachShader(program,id);
		}
		
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			AC_CORE_ASSERT(eol == std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			AC_CORE_ASSERT((type == "vertex" || type == "fragment" || type == "pixel"), "Invalid Shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}
		return shaderSources;
	}
	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			AC_CORE_ERROR("Could not open file '{0}'!", path);
		}

		return result;
	}
}