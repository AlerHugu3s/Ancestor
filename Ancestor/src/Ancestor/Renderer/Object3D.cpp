#include"acpch.h"
#include"Object3D.h"
#include"Renderer.h"
#include"Platform/OpenGL/OpenGLObject3D.h"

namespace Ancestor {
	Ref<Object3D> Object3D::Create(const std::string& objPath, const std::string& materialBasePath, bool triangulate)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLObject3D>(objPath, materialBasePath, triangulate);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}