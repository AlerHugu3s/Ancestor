#include"acpch.h"
#include "Material.h"
#include "tinyobjloader.h"
namespace Ancestor{
	Material::Material(tinyobj::material_t material)
		:ambient(material.ambient[0], material.ambient[1], material.ambient[2]),
		diffuse(material.diffuse[0], material.diffuse[1], material.diffuse[2]),
		specular(material.specular[0], material.specular[1], material.specular[2]),
		transmittance(material.transmittance[0], material.transmittance[1], material.transmittance[2]),
		emission(material.emission[0], material.emission[1], material.emission[2]),
		shininess(material.shininess)
	{
		if (material.name.size())
			name = material.name;
	}
	Ref<Material> Material::Create(tinyobj::material_t material)
	{
		return std::make_shared<Material>(material);
	}

}