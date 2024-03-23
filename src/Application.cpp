
#include "Utils.h"
#include <cmath>
#define ASSERT(x) if((!x)) __debugbreak()
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "shaders/shader.cpp"
#include "render.h"

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

int  createShaderProgram(unsigned int *program) {
    std::string vertexShader = readShaderFile("triangle\\triangle_vertex.glsl");

    std::string fragmentShader = readShaderFile("triangle\\traingle_fragment.glsl");
     *program = createShader(vertexShader, fragmentShader);

    ASSERT(gl_log_error());
    glUseProgram(*program);
    int location = glGetUniformLocation(*program, "u_Color");
    return location;
}

int main(void)
{
    render renderer(1280, 720);
    renderer.render_init();
    GLFWwindow* window = renderer.window;
    unsigned int bufferId;
    float positions[10] = {
         0.0f,0.5f,
         0.5,0.0f,
        -0.5f,0.0f,
        -0.5f,-0.5f,
        -1.0f,1.0f
    };
    unsigned int indices[6] = {
        0,1,2,
        2,3,4
    };

    //index buffer object
    unsigned int ibo;
    renderer.createQuad(positions, indices, &bufferId, &ibo, sizeof(positions),sizeof(indices));
    unsigned int program;
    int location =  createShaderProgram(&program);
    //clear sreeen color as teal
    glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
    float x = 1;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glUniform4f(location, abs(sin(x * 0.02 / (M_PI))), abs(cos(x * 0.02 / (M_PI))), 0.0, 1.0f);
        x++;
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

