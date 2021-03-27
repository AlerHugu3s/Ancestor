#pragma once

#include "Ancestor/Renderer/RendererAPI.h"
#include "Ancestor/Renderer/VertexArray.h"

namespace Ancestor {



	class Renderer 
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}