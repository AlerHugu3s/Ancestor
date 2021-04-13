#pragma once

#include "Ancestor/Renderer/Texture.h"
#include "Ancestor/Renderer/Shader.h"
#include "Ancestor/Renderer/Buffer.h"

namespace Ancestor {
	class Mesh
	{
	public:
		static Ref<Mesh> Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures);
		virtual void Draw(Ref<Shader> shader) = 0;
	};
}