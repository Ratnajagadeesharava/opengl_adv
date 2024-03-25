#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	m_ProgramID = glCreateProgram();
	
}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
}

void ShaderProgram::useProgram() const
{
	glUseProgram(m_ProgramID);
}

void ShaderProgram::deleteProgram() const
{
		glDeleteProgram(m_ProgramID);
}

bool ShaderProgram::linkAndValidateProgram() const
{
	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);
	GLint m_LinkStatus;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &m_LinkStatus);
	if (m_LinkStatus == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);
		std::cout << "Linking failed" << std::endl;
		std::cout << &infoLog[0] << std::endl;
		glDeleteProgram(m_ProgramID);
		return false;
	}
	else
	{
		return true;
	}

}

void ShaderProgram::bindShader(shader shdr) const
{
	glAttachShader(m_ProgramID, shdr.shaderID());
}

void ShaderProgram::unbindShader(shader shdr) const
{
	glDetachShader(m_ProgramID, shdr.shaderID());
}

void ShaderProgram::unbindShaders() const
{
	for (shader shdr : shaders)
	{
		glDetachShader(m_ProgramID, shdr.shaderID());
	}
}

void ShaderProgram::deleteShaders() const
{
	for (shader shdr : shaders)
	{
		glDeleteShader(shdr.shaderID());
	}
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(m_ProgramID, name.c_str());
}

void ShaderProgram::setUniform1f(GLint location, float Vx, float Vy, float Vz, float Va)
{
		glUniform4f(location, Vx, Vy, Vz, Va);
}
