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
		virtual void SetType(const std::string& type) override { m_Type = type; }
		virtual std::string GetType() const override { return m_Type; }
		virtual std::string GetPath() const override { return m_Path; };

		virtual void Active(uint32_t slot) override;
		virtual void Bind(uint32_t slot = 0) override;
	private:
		std::string m_Path, m_Type;;
		uint32_t m_RendererId;
		uint32_t m_Width, m_Height;
	};
}