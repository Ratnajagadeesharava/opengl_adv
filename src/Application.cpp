
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../shader.cpp"
#include <cmath>
#define ASSERT(x) if((!x)) __debugbreak()
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static bool gl_log_error() {
    while (GLenum error = glGetError()) {
        std::cout << "Open GL Error " << error << std::endl;
        return false;
    }
    return true;
}

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //error handeling
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in Intialising glew" << std::endl;
    }
    //id of the buffer 
    unsigned int bufferId;
    GLuint bufferIds[3];
    float positions[10] = {
         0.5f,0.5f,
         0.5,-0.5f,
        -0.5f,0.5f,
        -0.5f,-0.5f,
        -1.0f,1.0f
    };
    //generate buffers and give it to buffer Id
    //generates buffer object name(Id)
    glGenBuffers(1,&bufferId);
    glGenBuffers(3, bufferIds);
    
    std::cout<<"Buffer Names" << bufferId << std::endl;
    std::cout << "Generated Buffer names  -->" << bufferIds[0]<<"   "<< bufferIds[1]<<"  "<< bufferIds[2] << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    //the data in the buffer object bound to GL_ARRAY_BUFFER (identified by bufferId) should be filled with the contents of the positions array.
    //there can be multiple buffer objects created and used as GL_ARRAY_BUFFER, you can only bind one of them at a time. When you call glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);
    unsigned int indices[6] = {
        0,1,2,
        2,3,4
    };

    //index buffer object
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0) enables the vertex attribute array at index 0. This indicates to OpenGL that the vertex shader will use data from the buffer bound to vertex attribute index 0.
    glEnableVertexAttribArray(0);
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
    //glVertexAttribPointer function in OpenGL is used to specify the layout and format of vertex attribute data in a vertex attribute array. It tells OpenGL how to interpret the data stored in a buffer object when rendering geometry
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 2 * sizeof(float),0);
    std::string vertexShader = readShaderFile("src\\shaders\\triangle\\triangle_vertex.glsl");

    std::string fragmentShader = readShaderFile("src\\shaders\\triangle\\traingle_fragment.glsl");
     unsigned int program =    createShader(vertexShader, fragmentShader);
     
     ASSERT(gl_log_error());
     glUseProgram(program);
     int location = glGetUniformLocation(program, "u_Color");
     

     glBindBuffer(GL_ARRAY_BUFFER, 0);
     float x = 1;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glUniform4f(location, abs(sin(x * 0.02 / (M_PI))), abs(cos(x * 0.02 / (M_PI))), 0.0, 1.0f);
        x++;
        //clearing the color buffer before rendering each frame
        glClear(GL_COLOR_BUFFER_BIT);
        /*glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 1, 3);
        glDrawArrays(GL_TRIANGLES, 2, 3);*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
        
        glfwSwapBuffers(window);

        /* Poll for and process events */
        //glfwPollEvents function in GLFW is used to process all pending events, such as window events (like resizing or closing the window), keyboard and mouse events, and input events. It checks the event queue and dispatches any pending events to their respective event callbacks.
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

