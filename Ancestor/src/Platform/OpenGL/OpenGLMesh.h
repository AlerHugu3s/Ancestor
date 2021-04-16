#pragma once
#include "Ancestor/Renderer/Mesh.h"

namespace Ancestor {
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures);
		virtual void Draw(Ref<Shader> shader) override;

	public:
		Ref<VertexArray> VAO;

	private:
		void setupMesh();

	private:
		// render data 
		Ref<VertexBuffer> VBO;
		Ref<IndexBuffer> IBO;
		std::vector<Ref<Texture>> m_Textures;
		std::vector<unsigned int> m_Indices;
		std::vector<Vertex> m_vertices;
	};
}