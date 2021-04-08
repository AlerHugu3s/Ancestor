#include "acpch.h"
#include "OpenGLBuffer.h"

#include <Glad/glad.h>

//////////////////////////////////////////////////////////////////////////
///// VertexBuffer ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
Ancestor::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Ancestor::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Ancestor::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Ancestor::OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//////////////////////////////////////////////////////////////////////////
///// IndexBuffer ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
Ancestor::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
	m_indices = indices;
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Ancestor::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Ancestor::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Ancestor::OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ancestor::OpenGLIndexBuffer::AddIndices(uint32_t* indices, uint32_t size)
{	
	int totalSize = m_Count + size;
	unsigned int* newIndices = (unsigned int*)malloc(sizeof(unsigned int) * totalSize);

	for (size_t i = 0; i < m_Count; i++)
	{
		newIndices[i] = m_indices[i];
	}
	//delete m_indices;
	for (size_t i = m_Count; i < totalSize; i++)
	{
		newIndices[i] = indices[i];
	}
	m_indices = newIndices;
	m_Count = totalSize;
	glBufferData(GL_ARRAY_BUFFER, m_Count, &m_indices[0], GL_STATIC_DRAW);
}
