#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "Ancestor/Renderer/Mesh.h"

namespace Ancestor {
	class Model
	{
	public:
		Model(const std::string& path, bool gamma = false);
		void Draw(Ref<Shader> shader);
		void AddTexture(Ref<Texture3D> texture);

	public:

		// model data 
		std::vector<Ref<Texture>> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<Ref<Mesh>> meshes;
		std::string directory;
		bool gammaCorrection;

	private:
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Ref<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}