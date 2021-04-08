#pragma once
#include "Ancestor/Renderer/Object3D.h"

namespace Ancestor {
	class OpenGLObject3D : public Object3D
	{
	public:
		OpenGLObject3D(const std::string& objPath, const std::string& materialBasePath, bool triangulate);

		virtual ~OpenGLObject3D();
		virtual std::vector<Ref<Model>> GetModels() const override { return m_Models; }
		virtual std::vector<Ref<Material>> GetMaterials() const override { return m_Materials; }
		virtual std::vector<float> GetVertices() const override { return vertices; }
	private:
		std::vector<Ref<Model>> m_Models;
		std::vector<Ref<Material>> m_Materials;
		std::vector<float> vertices;
	};
}