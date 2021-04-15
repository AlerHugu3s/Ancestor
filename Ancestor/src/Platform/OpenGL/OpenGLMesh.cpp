#include "acpch.h"
#include "OpenGLMesh.h"
#include "glad/glad.h"
#include "OpenGLShader.h"

namespace Ancestor {
	// constructor
	OpenGLMesh::OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures)
	{
		m_Indices = indices;
		m_vertices = vertices;
		m_Textures = textures;
		VAO = VertexArray::Create();
		VBO = VertexBuffer::Create(m_vertices);
		IBO = IndexBuffer::Create(m_Indices);

		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void OpenGLMesh::Draw(Ref<Shader> shader)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		unsigned int customNr = 1;
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			// active proper texture unit before binding
			m_Textures[i]->Active(i);
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = m_Textures[i]->GetType();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream
			else
				number = std::to_string(customNr++); // transfer unsigned int to stream
			m_Textures[i]->Bind();
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformInt1(name + number, i);
		}

		// draw mesh
		VAO->Bind();
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		VAO->UnBind();

		// always good practice to set everything back to defaults once configured.
		//glActiveTexture(GL_TEXTURE0);
	}

	// initializes all the buffer objects/arrays
	void OpenGLMesh::setupMesh()
	{
		BufferLayout layout = BufferLayout{
			{Ancestor::ShaderDataType::Float3 ,"a_Pos" },
			{Ancestor::ShaderDataType::Float3 ,"a_Normal" },
			{Ancestor::ShaderDataType::Float2 ,"a_TexCoords" },
			{Ancestor::ShaderDataType::Float3 ,"a_Tangent" },
			{Ancestor::ShaderDataType::Float3 ,"a_Bitangent" }
		};
		VBO->SetLayout(layout);
		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);
	}
}