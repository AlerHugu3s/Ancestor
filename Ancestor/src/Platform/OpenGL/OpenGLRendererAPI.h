#pragma once
#include "Ancestor/Renderer/RendererAPI.h"

namespace Ancestor {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color);
		virtual void Clear();

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}