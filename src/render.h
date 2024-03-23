#pragma once
#include "defs.h"
class render
{
	public:
		render(int w,int h);
		 bool render_init();
		 void createQuad(float vertices[],unsigned int indices[], unsigned int* bufferId, unsigned int* ibo,int vertices_size,int indices_size);

		 void render_begin();
		 void render_end();

		 GLFWwindow* window;
private :
	int width;
	int height;
};

