#include "shader.h"
#define SOLUTION_DIR std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/"))




shader::shader(const std::string& filePath, GLuint shaderType)
{
    std::string shader_code =  readShaderFile(filePath);
    m_RendererID = compileShader(shaderType, shader_code);
    m_shaderType = shaderType;
}



shader::~shader()
{
	deleteShader();
}

void shader::deleteShader() const
{
	glDeleteShader(m_RendererID);
}

std::string shader::readShaderFile(const std::string& path)
{
    std::fstream myFile;

    std::string completepath = SOLUTION_DIR + "\\" + path;
    myFile.open(completepath, std::ios::in);
    std::string line;
    std::stringstream stream;

    if (!myFile.is_open()) {
        std::cout << path << "file cannot be opened" << std::endl;
    }
    while (std::getline(myFile, line)) {
        stream << line << std::endl;
    }
    myFile.close();
    return stream.str();
    
}

unsigned int shader::compileShader(unsigned int type, const std::string source)
{
    //Create a shader in the GPU  And get an id for it
    unsigned int shaderId = glCreateShader(type);
    //Write shader in string and add it as source
    const char* src = &source[0];
    glShaderSource(shaderId, 1, &src, NULL);
    //compile the shader
    glCompileShader(shaderId);
    int result;
    //get the status or any compilation issues
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        //alocates string of specified length in stack
        char* message = new char[length];
        glGetShaderInfoLog(shaderId, length, &length, message);
        std::cout << message << std::endl;
        glDeleteShader(shaderId);
        return 0;
    }
    std::cout << "shader compiled Succesfully" << std::endl;
    return shaderId;
}
