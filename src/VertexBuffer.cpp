#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, const unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	float* a = (float*)data;
	glBufferData(GL_ARRAY_BUFFER, size,data, GL_STATIC_DRAW);
	
}

VertexBuffer::~VertexBuffer()
{
	
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
