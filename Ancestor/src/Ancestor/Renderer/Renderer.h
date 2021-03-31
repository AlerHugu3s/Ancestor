#pragma once

#include "Ancestor/Renderer/RendererAPI.h"
#include "Ancestor/Renderer/VertexArray.h"
#include "Ancestor/Renderer/Camera.h"
#include "Ancestor/Renderer/Shader.h"

namespace Ancestor {



	class Renderer 
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray,const std::shared_ptr<Shader> shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectMatrix;
		};
		static SceneData* m_SceneData;
	};
}