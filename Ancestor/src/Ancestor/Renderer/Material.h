#pragma once
#include <glm/glm.hpp>
#include "..\tinyobjloader\tinyobjloader.h"
namespace Ancestor {
	class Material
	{
	public:
		Material(tinyobj::material_t material);
		virtual ~Material() = default;
		static Ref<Material> Create(tinyobj::material_t material);

	private:
		std::string name;
		glm::vec3 ambient, diffuse, specular, transmittance, emission;
		float shininess;
		unsigned int ambientId = -1,diffuseId = -1,specularId = -1,specularHighlightId = -1,bumpTexId = -1,displacementTexId = -1,alphaTexId = -1;
		std::string ambientTexName = "",diffuseTexName = "",specularTexName = "",specularHighlightTexName = "",bumpTexName = "",displacementTexName = "",alphaTexName = "";
	};
}