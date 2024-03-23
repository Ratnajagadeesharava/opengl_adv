#pragma once
#include "Utils.h"
class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetID() const { return m_RendererID; }
private:
	GLuint m_RendererID;
};

