#pragma once

namespace Ancestor {

	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetType(const std::string& type) = 0;
		virtual std::string GetType() const = 0;
		virtual std::string GetPath() const = 0;

		virtual void Active(uint32_t slot) = 0;
		virtual void Bind(uint32_t slot = 0) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

	class Texture3D : public Texture
	{
	public:
		static Ref<Texture3D> Create(const std::string& path);
	};
}