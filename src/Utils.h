#ifndef UTILS_H
#define UTILS_H
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(gl_log_error())


#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
static void inline GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool inline gl_log_error() {
    while (GLenum error = glGetError()) {
        std::cout << "Open GL Error " << error << std::endl;
        return false;
    }
    return true;
}
#endif
