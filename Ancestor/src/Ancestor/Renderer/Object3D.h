#pragma once

#include "Model.h"
#include "Material.h"

namespace Ancestor {
	class Object3D
	{
	public:
		static Ref<Object3D> Create(const std::string& objPath, const std::string& materialBasePath, bool triangulate);
		virtual ~Object3D() = default;
		virtual std::vector<Ref<Model>> GetModels() const = 0;
		virtual std::vector<Ref<Material>> GetMaterials() const = 0;
		virtual std::vector<float> GetVertices() const = 0;
	};
}