#pragma once
#include "defs.h"
class Renderer
{
	public:
		Renderer(int w,int h);
		 bool renderer_init();
		 void createQuad(float vertices[],unsigned int indices[], unsigned int* bufferId, unsigned int* ibo,int vertices_size,int indices_size);

		 void clearScreen(float red,float green,float blue,float alpha);

		 void renderer_begin();
		 void renderer_end();

		 GLFWwindow* window;
private :
	int width;
	int height;
};

