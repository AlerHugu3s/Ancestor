#include "acpch.h"
#include "OpenGLTexture3D.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace Ancestor {
	OpenGLTexture3D::OpenGLTexture3D(const std::string& path)
	{
		int index = path.find_last_of('/');
		if (index == -1) index = 0;
		m_Path = path.substr(index, path.length());
		m_Type = "texture_custom";
		int width, height,channels;
		glGenTextures(1, &m_RendererId);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(("assets/textures/" + m_Path).c_str(), &width, &height, &channels, 0);
		AC_CORE_ASSERT(data, "Failed to load Image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			dataFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else if (channels == 3)
		{
			dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	OpenGLTexture3D::~OpenGLTexture3D()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture3D::Active(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot); 
	}

	void OpenGLTexture3D::Bind(uint32_t slot)
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}
}