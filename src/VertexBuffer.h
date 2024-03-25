#pragma once
#include "Utils.h"
class VertexBuffer
{
	public :
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	static void BindById(GLuint id);
	GLuint GetID() const { return m_RendererID; }
private:
	GLuint m_RendererID;
};

