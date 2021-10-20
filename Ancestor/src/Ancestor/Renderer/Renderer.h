#pragma once

#include "Ancestor/Renderer/RendererAPI.h"
#include "Ancestor/Renderer/Camera.h"
#include "Ancestor/Renderer/Shader.h"

namespace Ancestor {



	class Renderer 
	{
	public:
		static void Init();

		static void BeginScene(PerspectiveCamera& camera);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(Ref<Model> model, Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectMatrix;
		};
		static SceneData* m_SceneData;
	};
}