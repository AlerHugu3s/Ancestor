#include "acpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Ancestor {
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND | GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r,color.g,color.b,color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawIndexed(Ref<Model> model, Ref<Shader> shader)
	{
		model->Draw(shader);
	}
}