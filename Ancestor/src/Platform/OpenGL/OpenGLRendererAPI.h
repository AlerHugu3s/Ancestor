#pragma once
#include "Ancestor/Renderer/RendererAPI.h"

namespace Ancestor {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(Ref<Model> model, Ref<Shader> shader) override;
	};
}