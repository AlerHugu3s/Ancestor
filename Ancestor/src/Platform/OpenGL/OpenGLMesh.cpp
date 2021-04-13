#include "acpch.h"
#include "OpenGLMesh.h"
#include "glad/glad.h"
#include "OpenGLShader.h"

namespace Ancestor {
	// constructor
	OpenGLMesh::OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures)
	{
		VAO = VertexArray::Create();
		VBO = VertexBuffer::Create(vertices);
		IBO = IndexBuffer::Create(indices);
		this->textures = textures;

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
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			// active proper texture unit before binding
			textures[i]->Active(i);
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i]->GetType();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream

			// now set the sampler to the correct texture unit
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformInt1(name + number, i);

			// and finally bind the texture
			textures[i]->Bind();

			// draw mesh
			VAO->Bind();
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			VAO->UnBind();

			// always good practice to set everything back to defaults once configured.
			textures[i]->Active(0);
		}
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