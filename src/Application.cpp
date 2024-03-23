
#include "Utils.h"
#include <cmath>
#define ASSERT(x) if((!x)) __debugbreak()
#include "shaders/shader.cpp"
#include "render.h"



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
    float positions[8] = {
         0.5f,0.5f,
         0.5f,-0.5f,
        -0.5f,0.5f,
        -0.5f,-0.5f
    };
    unsigned int indices[6] = {
        0,1,2,
        1,2,3
    };
    unsigned int ibo;
    renderer.createQuad(positions, indices, &bufferId, &ibo, sizeof(positions),sizeof(indices));
    unsigned int program;
    int location =  createShaderProgram(&program);
    glClearColor(0.0f, 0.22f, 0.2f, 1.0f);
    float x = 1;
    while (!glfwWindowShouldClose(window))
    {
        ASSERT(gl_log_error());

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glUniform4f(location, abs(sin(x * 0.02 / (M_PI))), abs(cos(x * 0.02 / (M_PI))), 0.0, 1.0f);
        x++;
        (glClear(GL_COLOR_BUFFER_BIT));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(window);
        GLCall(glfwPollEvents());
    }
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

