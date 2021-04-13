#pragma once
#include "Ancestor/Renderer/Mesh.h"


namespace Ancestor {
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures);
		virtual void Draw(Ref<Shader> shader) override;

	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Ref<Texture>> textures;
		Ref<VertexArray> VAO;

	private:
		void setupMesh();

	private:
		// render data 
		Ref<VertexBuffer> VBO;
		Ref<IndexBuffer> IBO;
	};
}