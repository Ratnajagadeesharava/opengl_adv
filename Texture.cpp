#include "Texture.h"
#include <GL/glew.h>
#include "stb_image.h"
#include <iostream>
//source :: https://learnopengl.com/Getting-started/Textures

Texture::Texture(const char* path)
{
	loadTexture(path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
	
}

void Texture::loadTexture(const char* path)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);
	if (localBuffer)
	{
		bindTexture();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		stbi_image_free(localBuffer);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void Texture::bindTexture()
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
