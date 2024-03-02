#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
/// <summary>

//b.
//c.Write shader in string and add it as source
//d.Compile the shader
//e.Attach Shader to program
//f.Attach program
//g.Delete shader

/// </summary>



static unsigned int compileShader(unsigned int type, std::string source) {
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
        std:: cout << message<< std::endl;
        glDeleteShader(shaderId);
        return 0;
    }
    return shaderId;
}
static unsigned int createShader(std::string vertexShader,
    std::string fragmentShader) {
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in Intialising glew" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    //id of the buffer 
    unsigned int bufferId;
    float positions[6] = {
        0.5,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f
    };
    glGenBuffers(1,&bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    // "layout(location=0) in vec4 position\n --> inedx"
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 2 * sizeof(float),0);
    std::string vertexShader = "#version 330 core\n"
        "layout(location=0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = position;\n"
        "}";

    std::string fragmentShader = "#version 330 core\n"
        "layout(location=0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0,0.0,0.0,1.0);\n"
        "}";
     unsigned int program =    createShader(vertexShader, fragmentShader);
     glUseProgram(program);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /*openg GL Legacy
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glEnd();*/
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}