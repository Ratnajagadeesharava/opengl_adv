#include "render.h"



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
	
	glGenBuffers(1, bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, *bufferId);

    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);


    glGenBuffers(1, ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

}

void render::render_begin()
{
	
}

void render::render_end()
{
}


