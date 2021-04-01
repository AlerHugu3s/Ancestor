#include "acpch.h"
#include "OpenGLTexture3D.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace Ancestor {
	OpenGLTexture3D::OpenGLTexture3D(const std::string& path)
	{
		int width, height,channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		AC_CORE_ASSERT(data, "Failed to load Image!");
		m_Width = width;
		m_Height = height;
		m_Depth = 0;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage3D(m_RendererId, 1, internalFormat, m_Width, m_Height, m_Depth);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage3D(m_RendererId, 0, 0, 0, 0, m_Width, m_Height, m_Depth, dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	OpenGLTexture3D::~OpenGLTexture3D()
	{
		glDeleteTextures(1, &m_RendererId);
	}
	void OpenGLTexture3D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_RendererId);
	}
}