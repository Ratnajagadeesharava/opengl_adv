#pragma once
#include "Utils.h"
class VertexBuffer
{
	public :
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetID() const { return m_RendererID; }

	GLuint m_RendererID;
};

