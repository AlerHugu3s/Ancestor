#pragma once
#include "Ancestor/Renderer/Texture.h"

namespace Ancestor {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) override;
	private:
		std::string m_path;
		uint32_t m_RendererId;
		uint32_t m_Width, m_Height;
	};
}