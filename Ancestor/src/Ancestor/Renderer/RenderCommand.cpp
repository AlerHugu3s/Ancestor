#include "acpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace  Ancestor {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}