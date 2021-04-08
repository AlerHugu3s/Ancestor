#pragma once
#include <glm/glm.hpp>
#include "..\tinyobjloader\tinyobjloader.h"
namespace Ancestor {
	struct Mesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<int> indices;
		std::vector<glm::vec3> normals;
		glm::vec2 texCoord;
		glm::vec4 color;

		Mesh()
			: vertices(0),texCoord(0),normals(0),color(0)
		{}
	};

	class Model
	{
	public:
		Model(tinyobj::attrib_t attrib,tinyobj::shape_t shape);
		virtual ~Model();

		std::vector<Mesh> GetMesh() { return meshData; }
		std::vector<unsigned int> GetVertexIndices() { return m_VertexIndices; }
		std::vector<unsigned int> GetNormalIndices() { return m_NormalIndices; }
		std::vector<unsigned int> GetTexCoordIndices() { return m_TexCoordIndices; }

		static Ref<Model> Create(tinyobj::attrib_t attrib,tinyobj::shape_t shape);
	private:
		std::vector<Mesh> meshData;
		int meshNum;
		std::vector<unsigned int> m_VertexIndices;
		std::vector<unsigned int> m_NormalIndices;
		std::vector<unsigned int> m_TexCoordIndices;
	};
}