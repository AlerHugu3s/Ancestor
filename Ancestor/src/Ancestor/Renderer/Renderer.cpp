#include "acpch.h"
#include "Renderer.h"

#include "RenderCommand.h"


namespace Ancestor {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectMatrix = camera.GetViewPorjectionMartix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}