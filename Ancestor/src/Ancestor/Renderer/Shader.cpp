#include "acpch.h"
#include "Shader.h"

#include "Ancestor/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ancestor {
	Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc,fragmentSrc);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}

