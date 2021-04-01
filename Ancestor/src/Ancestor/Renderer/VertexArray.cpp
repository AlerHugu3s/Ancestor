#include "acpch.h"
#include "VertexArray.h"

#include "Ancestor/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ancestor {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}

