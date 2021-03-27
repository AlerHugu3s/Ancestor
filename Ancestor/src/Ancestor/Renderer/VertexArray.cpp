#include "acpch.h"
#include "VertexArray.h"

#include "Ancestor/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ancestor {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}

