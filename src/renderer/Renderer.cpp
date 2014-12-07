
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>

#include <vector>

#include "Renderer.h"
#include "../math/VECTOR.h"
#include "../entity/Entity.h"
#include "../entity/Geometry.h"

struct Renderer::impl
{

    int initGL();
    int initGLFW();

    GLFWwindow* window;

};

Renderer::Renderer() 
{
    pimpl = new impl();
}

int Renderer::init()
{

    if (pimpl->initGLFW() != 0)
    {
        std::cerr << "Error initializing GLFW (Renderer.cpp)" << std::endl;
        return -2;
    }
    if (pimpl->initGL() != 0)
    {
        std::cerr << "Error initializing openGL (Renderer.cpp)" << std::endl;
        return -1;
    }

    return 0;


}

int Renderer::impl::initGL()
{
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);

    return 0;

}

int Renderer::impl::initGLFW()
{

	if (!glfwInit())
    {
        std::cout << "Error initializing GLFW in initializeGLFW(), Renderer.cpp" << std::endl;
		return -1;
    }

    window = glfwCreateWindow(960,720,"Composability",NULL,NULL);

	if (window == NULL)
    {
        std::cout << "Error creating GLFW window in initializeGLFW(), Renderer.cpp" << std::endl;
		return -2;
    }

    glfwSetWindowPos(window, 400, 100);
    glfwMakeContextCurrent(window);

	return 0;
}

int Renderer::render(const std::vector<Entity*>& e)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto it=e.begin(); it != e.end(); it++)
    {

        if ((*it)->getGeometry()->getType() == Geometry::Type::BOX)
        {
        }

    }

    glFlush();

    glfwSwapBuffers(pimpl->window);

    return 0;
}
