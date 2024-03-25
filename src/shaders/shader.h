#pragma once
#include "../Utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class shader
{
	public:
	shader(const std::string& filePath,GLuint shaderType);
	~shader();

	GLuint shaderID() const { return m_RendererID; }
	GLuint shaderType() const { return m_shaderType; }
	
	void deleteShader() const;

	private:
		GLuint  m_shaderType;
		unsigned int m_RendererID;
		std::string readShaderFile(const std::string& path);
		unsigned int compileShader(unsigned int type, const std::string source);
};

