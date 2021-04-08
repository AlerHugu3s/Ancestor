#include"acpch.h"
#include"OpenGLObject3D.h"

namespace Ancestor {
	OpenGLObject3D::OpenGLObject3D(const std::string& objPath, const std::string& materialBasePath, bool triangulate)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objPath.c_str(),materialBasePath.c_str(), triangulate);

		AC_CORE_ASSERT(warn.empty(), "WARN: " + warn);
		AC_CORE_ASSERT(err.empty(), "ERR: " + err);
		AC_CORE_ASSERT(ret, "Failed to load/parse .obj");

		vertices = attrib.vertices;

		for (int i = 0; i < materials.size(); i++) 
		{
			Ref<Material> mat = Material::Create(materials[i]);
			this->m_Materials.push_back(mat);
		}

		for (size_t i = 0; i < shapes.size(); i++) 
		{
			Ref<Model> model = Model::Create(attrib, shapes[i]);
			this->m_Models.push_back(model);
		}
	}
	OpenGLObject3D::~OpenGLObject3D()
	{
		
	}
}