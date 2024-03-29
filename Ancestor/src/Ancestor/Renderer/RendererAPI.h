#pragma once

#include "glm/glm.hpp"
#include "Ancestor/Renderer/Model.h"

namespace Ancestor {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(Ref<Model> model, Ref<Shader> shader) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};


}