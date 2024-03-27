#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "shaders/ShaderProgram.h"



Renderer::Renderer(int w,int h):width(w),height(h)
{
}

bool Renderer::renderer_init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	GLFWwindow* window_t = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (!window_t)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_t);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	window = window_t;
	return true;
}

void Renderer::createQuad(float vertices[],
	unsigned int indices[],
	unsigned int *bufferId,
	unsigned int *ibo,int vertices_size,int indices_size)
{
	
	VertexBuffer vb(vertices, vertices_size);
    IndexBuffer ib(indices, indices_size);
	*bufferId = vb.GetID();

}

void Renderer::clearScreen(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


