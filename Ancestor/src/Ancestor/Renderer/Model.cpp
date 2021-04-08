#include "acpch.h"
#include "Model.h"
namespace Ancestor {
	Model::Model(tinyobj::attrib_t attrib, tinyobj::shape_t shape)
		: meshNum(shape.mesh.num_face_vertices.size())
	{
		meshData.resize(meshNum);
		size_t index_offset = 0;

		m_VertexIndices.resize(shape.mesh.indices.size());
		m_NormalIndices.resize(shape.mesh.indices.size());
		m_TexCoordIndices.resize(shape.mesh.indices.size());
		for (size_t i = 0; i < shape.mesh.indices.size(); i++)
		{
			m_VertexIndices[i] = shape.mesh.indices[i].vertex_index;
			m_NormalIndices[i] = shape.mesh.indices[i].normal_index;
			m_TexCoordIndices[i] = shape.mesh.indices[i].texcoord_index;
		}

		// For each face
		for (size_t f = 0; f < meshNum; f++)
		{
			size_t fv = size_t(shape.mesh.num_face_vertices[f]);
			meshData[f].vertices.resize(fv);
			meshData[f].normals.resize(fv);
			// 获得所索引下标
			tinyobj::index_t idx;
			for (size_t v = 0; v < fv; v++) 
			{
				idx = shape.mesh.indices[index_offset + v];

				// v
				meshData[f].vertices[v].x = attrib.vertices[size_t(idx.vertex_index) * 3 + 0];
				meshData[f].vertices[v].y = attrib.vertices[size_t(idx.vertex_index) * 3 + 1];
				meshData[f].vertices[v].z = attrib.vertices[size_t(idx.vertex_index) * 3 + 2];

				// vt
				if (idx.texcoord_index >= 0)
				{
					meshData[f].texCoord.x = attrib.texcoords[size_t(idx.texcoord_index) * 2 + 0];
					meshData[f].texCoord.y = attrib.texcoords[size_t(idx.texcoord_index) * 2 + 1];
				}

				// vn
				if (idx.normal_index >= 0)
				{
					meshData[f].normals[v].x = attrib.normals[size_t(idx.normal_index) * 3 + 0];
					meshData[f].normals[v].y = attrib.normals[size_t(idx.normal_index) * 3 + 1];
					meshData[f].normals[v].z = attrib.normals[size_t(idx.normal_index) * 3 + 2];
				}
			}

			// 偏移
			index_offset += fv;
		}
	}
	Model::~Model()
	{
	}
	Ref<Model> Model::Create(tinyobj::attrib_t attrib, tinyobj::shape_t shape)
	{
		return std::make_shared<Model>(attrib,shape);
	}
}