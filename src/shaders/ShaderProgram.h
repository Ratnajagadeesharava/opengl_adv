#pragma once
#include <GL/glew.h>
#include "shader.h"
#include <vector>
class ShaderProgram
{
	public:

		
		ShaderProgram( );

	~ShaderProgram();

	void useProgram() const;

	GLuint programID() const { return m_ProgramID; }

	void deleteProgram() const;
	bool linkAndValidateProgram() const;	

	void bindShader(shader shdr) const;
	void unbindShader(shader shdr) const;
	void unbindShaders() const;

	void deleteShaders() const;
	GLint getUniformLocation(const std::string& name) const;
	static void setUniform1f(GLint location, float Vx,float Vy, float Vz, float Va);
	private:
		std::vector<shader> shaders;
		GLuint m_ProgramID;
};

