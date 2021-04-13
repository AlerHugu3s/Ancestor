#pragma once

#include "RendererAPI.h"

namespace Ancestor {
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(Ref<Model> model, Ref<Shader> shader)
		{
			s_RendererAPI->DrawIndexed(model,shader);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}