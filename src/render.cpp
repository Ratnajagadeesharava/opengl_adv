#include "render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"



render::render(int w,int h):width(w),height(h)
{
}

bool render::render_init()
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

void render::createQuad(float vertices[],
	unsigned int indices[],
	unsigned int *bufferId,
	unsigned int *ibo,int vertices_size,int indices_size)
{
	
	VertexBuffer vb(vertices, vertices_size);
    


    IndexBuffer ib(indices, indices_size);

}

void render::render_begin()
{
	
}

void render::render_end()
{
}


