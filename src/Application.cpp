
#include "Utils.h"
#include <cmath>
#define ASSERT(x) if((!x)) __debugbreak()
#include "shaders/shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "shaders/ShaderProgram.h"
#include "../Texture.h"





int main(void)
{
    Renderer renderer(1280, 720);
    renderer.renderer_init();
    GLFWwindow* window = renderer.window;
    GLuint bufferId;
    float positions[8] = {
         0.5f,0.5f,
         0.5f,-0.5f,
        -0.5f,0.5f,
        -0.5f,-0.5f
    };

    float positions2[8] = {
		 0.5f,1.0f,
		 0.5f,-0.5f,
		-0.5f,0.5f,
		-0.5f,-0.5f
	};
    GLuint indices[6] = {
        0,1,2,
        1,2,3
    };
    GLuint ibo;
    renderer.createQuad(positions, indices, &bufferId, &ibo, sizeof(positions),sizeof(indices));
    VertexBuffer vb(positions, sizeof(positions));
    ShaderProgram* program = new ShaderProgram();
    shader vertexShader("triangle\\triangle_vertex.glsl", GL_VERTEX_SHADER);
    shader fragmentShader("triangle\\traingle_fragment.glsl", GL_FRAGMENT_SHADER);
    Texture tex = Texture("water.jpg");
    program->bindShader(vertexShader);
    program->bindShader(fragmentShader);
    if (!program->linkAndValidateProgram()) {
        		std::cout << "Program failed to link" << std::endl;
                return -1;
    }
    program->useProgram();
    GLint location = program->getUniformLocation("u_Color");
    renderer.clearScreen(0.0f, 0.0f, 0.0f, 1.0f);
    int x = 1;
    while (!glfwWindowShouldClose(window))
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        ShaderProgram::setUniform1f(location, abs(sin(x * 0.02 / (M_PI))), abs(cos(x * 0.02 / (M_PI))), 0.0, 1.0f);
        x++;
        renderer.Draw();
        glfwSwapBuffers(window);
        GLCall(glfwPollEvents());
    }
    program->unbindShaders();
    
    glfwTerminate();
    return 0;
}

