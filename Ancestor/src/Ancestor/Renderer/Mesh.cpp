#include "acpch.h"
#include "Mesh.h"
#include "Platform/OpenGL/OpenGLMesh.h"
#include "Renderer.h"

namespace Ancestor {
	Ref<Mesh> Mesh::Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLMesh>(vertices, indices, textures);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}