
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
#include "../entity/Box.h"
#include "../entity/Geometry.h"

struct Renderer::impl
{

    int initGL();
    int initGLFW();

    float zoom;

    GLFWwindow* window;

    void renderBox(Entity*);

    void setCamera();

};

Renderer::Renderer() 
{
    pimpl = new impl();
    pimpl->zoom = 1;
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

int Renderer::addPointLight(VECTOR pos)
{
	GLfloat light_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat light_diffuse[] = { .7, .7, .7, 1.0 };
	GLfloat light_specular[] = { 0, 0, 0, 1.0 };
	GLfloat light_position[] = { pos.x, pos.y, pos.z, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    return 0;
}

// GL Helper fn
GLvoid setMaterialProperties( GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	GLfloat mat_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient_and_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[1] = {0.0};
	
	mat_specular[0] = mat_ambient_and_diffuse[0] = r;
	mat_specular[1] = mat_ambient_and_diffuse[1] = g;
	mat_specular[2] = mat_ambient_and_diffuse[2] = b;
	mat_specular[3] = mat_ambient_and_diffuse[3] = alpha;

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
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

void Renderer::impl::setCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2-zoom, 2+zoom, -0.5-.75*zoom, 2.5+.75*zoom, 3, 20);

}

void Renderer::impl::renderBox(Entity* e)
{

    glPushMatrix();
    VECTOR pos = e->getPosition();
    VECTOR color = e->getColor();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    glTranslatef(0,0,-10);

    VECTOR sides = dynamic_cast<Box*>(e->getGeometry())->getSides();

    glBegin(GL_QUADS);

    {
        // Front Face
        glNormal3f(0.0,0.0,-1.0);

        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);

        // Back Face
        glNormal3f(0.0,0.0,1.0);

        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);

        glNormal3f(1.0,0.0,0.0);

        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);

        glNormal3f(-1.0,0.0,0.0);

        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);

        glNormal3f(0.0,1.0,0.0);

        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);

        glNormal3f(0.0,-1.0,0.0);

        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);

    }


    glEnd();


    glPopMatrix();


}

int Renderer::render(const std::vector<Entity*>& e)
{


    pimpl->setCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (auto it=e.begin(); it != e.end(); it++)
    {

        switch ((*it)->getGeometry()->getType())
        {
            case Geometry::Type::BOX:
                pimpl->renderBox(*it);
                break;
            default:
                break;
        }

    }

    glFlush();

    glfwSwapBuffers(pimpl->window);

    return 0;
}
