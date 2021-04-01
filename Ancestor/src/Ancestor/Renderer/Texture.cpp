#include "acpch.h"
#include "Texture.h"

#include "Ancestor/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Platform/OpenGL/OpenGLTexture3D.h"

namespace Ancestor {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
	Ref<Texture3D> Texture3D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AC_CORE_ASSERT(false, "RendererAPI is None! Not Supported");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture3D>(path);
		}
		AC_CORE_ASSERT(false, "RendererAPI is unknown!");
		return nullptr;
	}
}