#include "acpch.h"
#include "Shader.h"

#include "Ancestor/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ancestor {
	Ref<Shader> Shader::Create(const std::string& vertexSrc,const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc,fragmentSrc);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(path);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}

