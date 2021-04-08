#include "acpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Ancestor {

	static GLuint ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Ancestor::ShaderDataType::Float:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Float2:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Float3:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Float4:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Mat3:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Mat4:	return GL_FLOAT;
		case Ancestor::ShaderDataType::Int:		return GL_INT;
		case Ancestor::ShaderDataType::Int2:	return GL_INT;
		case Ancestor::ShaderDataType::Int3:	return GL_INT;
		case Ancestor::ShaderDataType::Int4:	return GL_INT;
		case Ancestor::ShaderDataType::Bool:	return GL_BOOL;
		}
		AC_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		AC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),"VertexBufferLayOut is Empty!")
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::AddIndexBuffer(uint32_t* indices, uint32_t size)
	{
		if (!m_IndexBuffer)
			m_IndexBuffer = IndexBuffer::Create(indices, size);
		else
		{
			m_IndexBuffer->AddIndices(indices, size);
		}
		m_IndexBuffer->Bind();
	}

}