
#define dSINGLE


#include <stdlib.h>
#include <iostream>

#include <ode/ode.h>


//#include <GL/glew.h>
#ifdef __APPLE__
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>

#include <GL/glc.h>

#include <cmath>

#include <vector>
#include <stack>
#include <map>
#include <utility>
#include <string>
#include <sstream>

#include <time.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif

#include <assert.h>

#include "controller.h"
#include "VECTOR.h"
#include "globals.h"
#include "object.h"
#include "human.h"
#include "controllerReader.h"
#include "characterReader.h"
#include "shape.h"
#include "fltReader.h"
#include "face.h"
#include "main.h"
#include "transition.h"
#include "status.h"
#include "transitionFinder.h"
#include "environment.h"
#include "heightfield.h"
#include "fltk.h"
#include "entity.h"
#include "envAction.h"
#include "visualizer.h"
#include "trajectory.h"
#include "optimizer.h"

using namespace std;

void initODE()
{


	World = dWorldCreate();

	Space = dSimpleSpaceCreate(0);

	contactgroup = dJointGroupCreate(0);

	jointgroup = dJointGroupCreate(0);

	//plane = dCreatePlane(Space, 0, 1, 0, PLANE_HEIGHT);

	dWorldSetGravity(World, 0, -9.81, 0);

	dWorldSetERP(World, 0.5);
	dWorldSetCFM(World, 1e-5);

	dWorldSetContactMaxCorrectingVel(World, 0.3);

	dWorldSetContactSurfaceLayer(World, 0.001);

	dWorldSetAutoDisableFlag(World, 0);

//    dWorldSetAutoDisableTime(World, .01);
}


void initObjects()
{

	human = Human(VECTOR(0.0,.95,-10.0));

	// For constraining to 2D.
	dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
	dJointAttach(lin_motor, human.parts[U_TORSO]->Body, 0);
	dJointSetLMotorNumAxes(lin_motor,1);
	dJointSetLMotorAxis(lin_motor,0,1,0,0,1);


	dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);


	dJointSetLMotorParam(lin_motor,dParamVel, 0);

	dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
	dJointAttach(ang_motor, human.parts[U_TORSO]->Body, 0);
	dJointSetAMotorNumAxes(ang_motor,2);
	dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
	dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);

	dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
	dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);


	dJointSetAMotorParam(ang_motor, dParamVel, 0);
	dJointSetAMotorParam(ang_motor, dParamVel2, 0);

}

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
	int i;
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);


//	if (o1 != plane && o2 != plane)
	
		Object* obj1 = geom2obj.find(o1)->second;
		Object* obj2 = geom2obj.find(o2)->second;

		// THIS PREVENTS ANY INTER-BODY COLLISIONS.
		//if (o1 != plane && o2 != plane)
		if (obj1->human_part && obj2->human_part)
		{
			return;
		}

        if ((obj1->human_part && !(obj2->isCollidable())) || (obj2->human_part && !(obj1->isCollidable())))
        {
            return;
        }

	if ((obj1->getType() != PLANE && obj2->getType() != PLANE && obj1->getType() != HEIGHTFIELD && obj2->getType() != HEIGHTFIELD) && dAreConnected(b1,b2))
	{
		return;
	}
	dContact contact[MAX_CONTACTS];


	for (i = 0; i < MAX_CONTACTS; i++)
	{

		dReal mu = dInfinity;
		if (obj1->getType() != PLANE && obj1->getType() != HEIGHTFIELD)
		{
			//Object* obj1 = geom2obj.find(o1)->second;

			if (obj1->getFriction() != -1)
				mu = obj1->getFriction();
		}
		if (obj2->getType() != PLANE && obj2->getType() != HEIGHTFIELD)
		{
			//Object* obj2 = geom2obj.find(o2)->second;

			if (obj2->getFriction() != -1)
				mu = obj2->getFriction();
		}

		contact[i].surface.mode = dContactBounce;
		contact[i].surface.mu = mu;
		contact[i].surface.bounce = 0.0;
		contact[i].surface.bounce_vel = .000001;
//		contact[i].surface.soft_cfm = 0.00; // Was at 0.01, but weird ground penetration issues.
	}
	if (int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
	{

		for (i = 0; i < numc; i++)
		{
			dJointID c = dJointCreateContact(World, contactgroup, contact + i);
			dJointAttach(c, b1, b2);
		}
	}
}

void closeODE()
{
	dJointGroupDestroy(contactgroup);
	dJointGroupDestroy(jointgroup);

	dSpaceDestroy(Space);
	dWorldDestroy(World);

}


void renderVisGraph(Visualizer& controllerGraph, std::string currController)
{

    glPushMatrix();

//    std::cout << controllerGraph.getCurrController() << std::endl;

    for (auto it = controllerGraph.getNodes().begin(); it != controllerGraph.getNodes().end(); it++)
    {

        // if the current (lowest level) controller name matches a node, update controllerGraph's.
        // color the appropriate node
        if (controllerGraph.getCurrController().compare((*it)->getLabel()) == 0)
        {
            setMaterialProperties(1.,0,0);
        }
        else
        {
            setMaterialProperties(.5,.5,.5);
        }

        glPushMatrix();
            dReal pos_x = (*it)->getPos().x / controllerGraph.getBB().x;
            dReal pos_y = (*it)->getPos().y / controllerGraph.getBB().y;
            glTranslatef(pos_x, pos_y, 0);
            DrawSphere(.03);
        glPopMatrix();

        setMaterialProperties(1,1,1);
        Agedge_t* e;
        for (e = agfstedge(controllerGraph.getGraphPtr(), (*it)->ptr); e; e = agnxtout(controllerGraph.getGraphPtr(), e))
        {

            glBegin(GL_LINE_STRIP);

            for (int i = 0; i < ED_spl(e)->list[0].size; i++)
            {

                dReal e_x = ED_spl(e)->list[0].list[i].x/ controllerGraph.getBB().x;
                dReal e_y = ED_spl(e)->list[0].list[i].y/ controllerGraph.getBB().y;
                glVertex3f(e_x, e_y, 0);

                /*
                glPushMatrix();
                glTranslatef(ED_spl(e)->list[0].list[i].x, ED_spl(e)->list[0].list[i].y, 0);

                setMaterialProperties(0,1,0);
                DrawSphere(.02);

                glPopMatrix();
                */
                
//                std::cout << ED_spl(e)->list[0].list[i].x << ", " << ED_spl(e)->list[0].list[i].y << std::endl;

            }
            glEnd();

 //           std::cout << "endcurve" << std::endl;
        }


    }

    glPopMatrix();




}

void renderMesh(int loc)
{



	for (int i = loc; i < loc+1; i++)
	{


		glPushMatrix();

		dReal P[16];

		for (int j = 0; j < 16; j++)
		{
			P[j] = flt_reader.mesh.components.at(i)->matrix[j];
		}



		//glMultMatrixf(P);
		// Hack to fix rotation differences btwn ode, maya
		if (i == 16 || i == 18 || i == 22 || i == 24 )
		{
			glRotatef(-90,1,0,0);
		}
		else if (i == 0 || i == 2 || i == 4 || i == 8 || i == 10 || i == 12
				|| i == 14 || i == 28 || i == 30)
			glRotatef(-90,1,0,0);


		setMaterialProperties(0.0,0.0,0.0);

		glPushMatrix();
		glTranslatef(0,0,0.01);
		if (i == 16 || i == 18 || i == 20)
			glTranslatef(0,0,0.09); 
		if (i == 22 || i == 24 || i == 26)
			glTranslatef(0,0,0.04);
        if (i == 26)
            glTranslatef(0,0,-.09);
		if ( i == 24)
			glTranslatef(0,0,-.15);

		if (i == 6 || i == 32) // feet
			glTranslatef(.015,0,0);

		glBegin(GL_LINE_STRIP);

	//	cout << flt_reader.mesh.components.at(i)->hull.size() << endl;

		for (int k = 0; k < flt_reader.mesh.components.at(i)->hull.size(); k++)
		{

			glVertex3f(flt_reader.mesh.components.at(i)->hull.at(k).first, flt_reader.mesh.components.at(i)->hull.at(k).second, 0);


		}


		glEnd();
		glPopMatrix();

		// Hack to set up colors. Eventually make it so we don't need all these nubmers.
		if (i == 0 || i == 8 || i == 10) //10 == torso
			setMaterialProperties(0.0, 0.0, 1, 1.0); // ?
		else if ( (i%2) != 0) //joint
			setMaterialProperties(0.0, 0.0, 0.0, 1.0);
		else if (i == 12 || i == 14 || i == 16 || i == 18 || i == 2
				|| i == 4 || i == 6)
			setMaterialProperties(0,.8,1,1.0);
		else if (i == 22 || i == 24) // lArm
			setMaterialProperties(0,.5,.7);
		else if (i == 26) // left hand
			setMaterialProperties(0, .6, .3, 1.0);
		else if (i == 28 || i == 30 || i == 32) // 32 = foot
			setMaterialProperties(0, .5, .7, 1.0);	
		else if (i == 20) // right Hand.
			setMaterialProperties(0,.8,.5,1.0);
		else
			setMaterialProperties(.5,.5,.5,1.0);
		// hack, just because the rendered feet are slightly shorter than the geometry feet.
		if (i == 6 || i == 32) // feet
			glTranslatef(.015,0,0);



		for (std::vector<Face*>::iterator it = flt_reader.mesh.components.at(i)->faces.begin(); it != flt_reader.mesh.components.at(i)->faces.end(); it++)
		{

			if ((*it)->vertices.size() == 4)
			{

				glBegin(GL_QUADS);
					for (int j = 0; j < (*it)->vertices.size(); j++)
					{
						VECTOR temp = flt_reader.mesh.vertexPalette.at( (*it)->vertices.at(j) )->pos;
						VECTOR temp_norm = flt_reader.mesh.vertexPalette.at( (*it)->vertices.at(j) )->norm;
						glNormal3f(temp_norm.x, temp_norm.y, temp_norm.z);
						glVertex3f(temp.x, temp.y, temp.z);
					}
				glEnd();
			}
			else if ((*it)->vertices.size() == 3)
			{
				glBegin(GL_TRIANGLES);
					for (int j = 0; j < (*it)->vertices.size(); j++)
					{
						VECTOR temp = flt_reader.mesh.vertexPalette.at( (*it)->vertices.at(j) )->pos;
						VECTOR temp_norm = flt_reader.mesh.vertexPalette.at( (*it)->vertices.at(j) )->norm;
						glNormal3f(temp_norm.x, temp_norm.y, temp_norm.z);
						glVertex3f(temp.x, temp.y, temp.z);
					}
				glEnd();
			}
			else
			{
				std::cout << "Neither Quad nor Tri" << std::endl;
			}

		}

		glPopMatrix();
	}


}

void simLoop(bool draw, char* phasename, Visualizer& controllerGraph, std::string currController)
{

// ODE step

	dSpaceCollide(Space, 0, &nearCallback);

	dWorldQuickStep(World, STEPSIZE);

	dJointGroupEmpty(contactgroup);

	human.updateCoM();




// OGL stuff

	if (draw)
	{



	    
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		

	//	gluPerspective(15, 1.0, 5, 15);

        zoom = .95;

		// .75 preserves aspect ratio
		glOrtho(-2-zoom, 2+zoom, -0.5-.75*zoom, 2.5+.75*zoom, 3, 20);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		const dReal *pos;

		pos = dGeomGetPosition(human.parts[U_TORSO]->Geom[0]);

		
		glTranslatef(-pos[0],0,0);

		init_lightsource();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setMaterialProperties(0.5, 0.5, 0.5, 1.0);



		for (int i = 0; i < PART_COUNT; i++)
		{
			if (DRAW_CONTACT)
			{
				DrawGeom(human.parts[i]->Geom[0], human.parts[i]->shape, -1);
			}
			else
			{
				DrawGeom(human.parts[i]->Geom[0], human.parts[i]->shape, human.parts[i]->meshLocation);
			}

		}


//		std::vector<Entity*> env_ents = env->getEntities();
        std::map<std::string, Entity*> env_ents = env->getEntities();
		for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
		{
            if (!( (iter->second)->isVisible()))
            {
                continue;
            }
            if (!( (iter->second)->isCollidable()))
            {
                glPushMatrix();
                glTranslatef(0,0,-5);
            }
            
            std::vector<Object*> obj_list = (iter->second)->getBodies();

            for (int j = 0; j < obj_list.size(); j++)
            {
                if (obj_list.at(j)->getType() != PLANE && obj_list.at(j)->getType() != HEIGHTFIELD)
                {
                    if (obj_list.at(j)->isCollidable())
                    {
			            setMaterialProperties(0.0, 0.8, 0, 1.0); // ?
                    }
                    else
                    {
                        setMaterialProperties(0.0, 0.5, 0, 1.0); // ?
                    }
                    DrawGeom(obj_list.at(j)->Geom[0], obj_list.at(j)->shape, -1);
                }
                if (obj_list.at(j)->getType() == PLANE)
                {
                    drawPlane((Plane*)obj_list.at(j));
                }
                if (obj_list.at(j)->getType() == HEIGHTFIELD)
                {
                    drawHF(((Heightfield*)obj_list.at(j))->getData(), ((Heightfield*)obj_list.at(j))->getSize(), ((Heightfield*)obj_list.at(j))->getStart(), ((Heightfield*)obj_list.at(j))->getWidth());
                }
            }
            if (!( (iter->second)->isCollidable()))
            {
                glPopMatrix();
            }

		}
	

		

/*
   		// This code to draw the plane (for 3D)
		glPushMatrix();
		   glLoadIdentity();
		   glBegin(GL_QUADS);
			glNormal3f(0.0,1.0,0.0);=
			glVertex3f(-20.0,PLANE_HEIGHT,0.0);
			glVertex3f(20.0,PLANE_HEIGHT,0.0);
			glVertex3f(20.0,PLANE_HEIGHT,-30.0);
			glVertex3f(-20.0,PLANE_HEIGHT,-30.0);
		   glEnd();
		glPopMatrix();
*/
		// Draw the target ball (used for testing IK)
/*
		glPushMatrix();
			setMaterialProperties(1.0, 0.0, 0.0, 1.0);
			glTranslatef(IKPoint.x, IKPoint.y, IKPoint.z);
			gluSphere(gluNewQuadric(), .05, 16, 16);
		glPopMatrix();
*/
		// Draw the ground line (for 2D)
/*
			setMaterialProperties(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(-15.0+pos[0], PLANE_HEIGHT, -10);
			glVertex3f(15+pos[0], PLANE_HEIGHT, -10);
		glEnd();
*/


		if (draw_com)
		{
			VECTOR com = human.getCoM();

			glPushMatrix();
				setMaterialProperties(1.0, 0.5, 0.0);
				glTranslatef(com.x, com.y, com.z/2.0);
				gluSphere(gluNewQuadric(), .025, 16, 16);
			glPopMatrix();

		}
        
		if (DISPLAY_COMVEL)
		{

			glPushMatrix();
			glColor3f(1.,0.,0.);
			glRasterPos3f( .5+pos[0], -.4, -10);
			char* buffer = new char[32];
			int n = sprintf(buffer,"CoM Vel: %f", human.getCoMVel().x);
			glcRenderString(buffer);
			glPopMatrix();

            //std::cout << pos[0] << endl;

            delete [] buffer;
		}

	
		glPushMatrix();
			glColor3f(0.,1,0);
			glRasterPos3f(-1.5+pos[0], -.4,-10);
			glcRenderString(phasename);
		glPopMatrix();


        if (VISUALIZATION)
        {

            glPushMatrix();
                glTranslatef(pos[0] + .75, 1.25, -10);
                renderVisGraph(controllerGraph, currController);
            glPopMatrix();

            glRasterPos3f(pos[0]+1.1, 1.15, -10);
            glcRenderString(controllerGraph.getCurrController().c_str());


            // Box around vizgraph
            glBegin(GL_LINES);
                glVertex3f(pos[0] + .6, 2.4, -10);
                glVertex3f(pos[0] + .6, 1.1, -10);

                glVertex3f(pos[0] + .6, 1.1, -10);
                glVertex3f(pos[0] + 1.9, 1.1, -10);

                glVertex3f(pos[0] + 1.9, 1.1, -10);
                glVertex3f(pos[0] + 1.9, 2.4, -10);

                glVertex3f(pos[0] + 1.9, 2.4, -10);
                glVertex3f(pos[0] + .6, 2.4, -10);
            glEnd();


        }

        // Current Trajectory
        if (RECORD_TRAJECTORY)
        {

            glLineWidth(5.);
                #ifdef __APPLE__
                    glLineWidth(10.);
                #endif
            setMaterialProperties(0,2,0);
            glBegin(GL_LINE_STRIP);
               for (auto it = traj->getTrajectoryInfo().begin(); it != traj->getTrajectoryInfo().end(); it++)
               {
                   glVertex3f(it->com.x, it->com.y, -10);
               }
            glEnd();
            glLineWidth(1.);

        }
        if (OPTIMIZE && RECORD_TRAJECTORY)
        {
//            glColor3f(1,.6,0);
            if (traj->getTrajectoryInfo().size() > 0)
            {
                glLineWidth(5.);
                #ifdef __APPLE__
                    glLineWidth(10.);
                #endif
                setMaterialProperties(10,0,0);
                glBegin(GL_LINE_STRIP);


                dReal x_adjust = 0;
                
                x_adjust = optimizer.getGoalTrajectory()->getTrajectoryInfo().front().com.x - traj->getTrajectoryInfo().front().com.x;
            

                int i = 0;
                for (auto it = optimizer.getGoalTrajectory()->getTrajectoryInfo().begin(); it != optimizer.getGoalTrajectory()->getTrajectoryInfo().end(); it++)
                {
                    if (i++ > traj->getTrajectoryInfo().size())
                    {
                        setMaterialProperties(.0,0,10);
                    }

//                    glVertex3f(it->com.x - x_adjust, it->com.y-.1, -10);
                    glVertex3f((it->com.x - optimizer.getGoalTrajectory()->getTrajectoryInfo().front().com.x)*1./2. - x_adjust + optimizer.getGoalTrajectory()->getTrajectoryInfo().front().com.x, it->com.y, it->com.z);
                }
                glEnd();
                glLineWidth(1.);
            }
        }
                

        if (PUSH_FORWARD || PUSH_BACKWARD)
        {
        glPushMatrix();
            setMaterialProperties(1, .6, 0);
            glTranslatef(pos[0],pos[1],-9);
            if (PUSH_BACKWARD)
                glRotatef(180,0,1,0);
            drawArrow(.2,.05, .1,.1);
        glPopMatrix();
        }

		glFlush();

		glfwSwapBuffers(window);

	}
}

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

void drawPlane(Plane* plane)
{
    glBegin(GL_LINES);
        glVertex3f(plane->getX1(), plane->getY1(), -10);
        glVertex3f(plane->getX2(), plane->getY2(), -10);
    glEnd();
    setMaterialProperties(0.0,1.0,0.0);
    for (int i = plane->getX1(); i < plane->getX2(); i+=2.5)
    {
        glBegin(GL_LINES);
            float height = (plane->getY2() - plane->getY1()) * (i - plane->getX1())/(plane->getX2() - plane->getX1()) + plane->getY1(); 
            glVertex3f(i, height, -10);
            glVertex3f(i, height-0.2, -10);
        glEnd();
    }
}
void drawHF(dReal* data, int numSamples, dReal start, dReal width)
{

    dReal widthSample = width/(numSamples-1);
    glBegin(GL_LINES);
    for (int i = 1; i < numSamples; i++)
    {
        glVertex3f(start+(i-1)*widthSample, data[i-1], -10);
        glVertex3f(start+(i)*widthSample, data[i], -10);
				glVertex3f(start+(i)*widthSample, data[i], -10);
				glVertex3f(start+(i)*widthSample, data[i]-0.2, -10);
    }

    glEnd();

}

void DrawGeom (dGeomID g, const Shape* const shape, int meshLoc)
{

	const dReal *pos; const dReal *R; int show_aabb;
	if (!g)
		return;

	pos = dGeomGetPosition(g);

	R = dGeomGetRotation(g);

	Draw(g, pos, R, shape, meshLoc);


}

void ODEtoOGL(float* M, const dReal* p, const dReal* R)
{
	
	M[0] = R[0]; M[1] = R[4]; M[2] = R[8]; M[3] = 0;
	M[4] = R[1]; M[5] = R[5]; M[6] = R[9]; M[7] = 0;
	M[8] = R[2]; M[9] = R[6]; M[10] = R[10]; M[11] = 0;
	M[12] = p[0]; M[13] = p[1]; M[14] = p[2]; M[15] = 1;

}


void DrawBox(const dReal* sides)
{

  glBegin(GL_QUADS);

    // Front Face
	  glNormal3f(0.0,0.0,-1.0);

	  glVertex3f(sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);

	 // Back Face
	  glNormal3f(0.0,0.0,1.0);

	  glVertex3f(sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);

	  glNormal3f(1.0,0.0,0.0);

	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);

	  glNormal3f(-1.0,0.0,0.0);

	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  
	  glNormal3f(0.0,1.0,0.0);

	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,sides[1]/2.0,-sides[2]/2.0);

	  glNormal3f(0.0,-1.0,0.0);

	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,-sides[2]/2.0);
	  glVertex3f(sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);
	  glVertex3f(-sides[0]/2.0,-sides[1]/2.0,sides[2]/2.0);


  glEnd();

}
void DrawSphere(const dReal rad)
{

	gluSphere(gluNewQuadric(), rad, 16, 16);

}

void drawArrow(const dReal lt, const dReal ht, const dReal lh, const dReal hh)
{

    glPushMatrix();
        glRotatef(90,0,1,0);

        
        glPushMatrix();
            glTranslatef(0,0,-lt - lh);
            gluCylinder(gluNewQuadric(), ht/2., ht/2., lt, 16, 16);

        glPopMatrix();

        
        glPushMatrix();
            glTranslatef(0,0,-lh);
            gluCylinder(gluNewQuadric(), hh/2., 0., lh, 16, 16);
        glPopMatrix();
    glPopMatrix();

}

void DrawCapsule(const dReal rad, const dReal length)
{

	glPushMatrix();
		glTranslatef(0,0,length/2.0);

		gluSphere(gluNewQuadric(), rad, 16, 16);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,-length/2.0);
		gluCylinder(gluNewQuadric(), rad, rad, length, 16, 16);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,-length/2.0);
		gluSphere(gluNewQuadric(), rad, 16, 16);
	glPopMatrix();

}

void DrawCapsule(const dReal rad1, const dReal rad2, const dReal length)
{

	DrawCapsule((rad1+rad2)/2.0, length);


/*
	glPushMatrix();
		glTranslatef(0,0,length/2.0);
		gluSphere(gluNewQuadric(), rad2, 16, 16);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, -length/2.0);
		gluCylinder(gluNewQuadric(), rad1, rad2, length, 16, 16);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,-length/2.0);
		gluSphere(gluNewQuadric(), rad1, 16, 16);
	glPopMatrix();
*/
}

void Draw(dGeomID g, const dReal pos[3], const dReal R[12], const Shape* const shape, int meshLoc = -1)
{

        glPushMatrix();

                float M[16];
                ODEtoOGL(M, pos, R);

 	        glMultMatrixf(M);

		// if render mesh, not contact geom
		if (meshLoc != -1)
		{
			renderMesh(meshLoc);
		}
		else
		{

			int type = dGeomGetClass(g);
			
			if (type == dBoxClass)
			{
				dReal sides[3];
				dGeomBoxGetLengths(g, sides);


				DrawBox(sides);
			}
			if (type == dSphereClass)
			{
				dReal rad;
				rad = dGeomSphereGetRadius(g);

				DrawSphere(rad);
			}
			if (type == dCapsuleClass)
			{
				dReal rad, length;
				dGeomCapsuleGetParams(g, &rad, &length);

				// ODE does not support capsules with different radii.
				// Could probably get of the varied radii capsule entirely, since
				// we are now displaying a different mesh (9/9/13)
				const Capsule* const c = dynamic_cast<const Capsule* const>(shape);

				DrawCapsule(c->getRadius1(), c->getRadius2(), length);
			}
		}

	glPopMatrix();

}




void initializeGL()
{
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);

	glLineWidth(1.0);
}

int initializeGLFW()
{

	if (!glfwInit())
    {
        std::cout << "Error initializing GLFW in initializeGLFW(), main.cpp" << std::endl;
		return -1;
    }

    window = glfwCreateWindow(960,720,"Composability",NULL,NULL);

	if (window == NULL)
    {
        std::cout << "Error creating GLFW window in initializeGLFW(), main.cpp" << std::endl;
		return -2;
    }

    glfwSetWindowPos(window, 400, 100);
    glfwMakeContextCurrent(window);

	return 0;
}

int initQuesoGLC()
{
	GLint ctx, myFont;

	ctx = glcGenContext();
	glcContext(ctx);
	glcAppendCatalog("/etc/X11/fonts/Type1/");
	glcAppendCatalog("/usr/lib/X11/fonts/Type1");

	myFont = glcGenFontID();
	glcNewFontFromFamily(myFont, "Courier");
	glcFontFace(myFont, "Bold");
	glcFont(myFont);

	glcScale(28,28);


    return 0;

}

GLvoid init_lightsource()
{

	GLfloat light_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat light_diffuse[] = { .7, .7, .7, 1.0 };
	GLfloat light_specular[] = { 0, 0, 0, 1.0 };
	GLfloat light_position[] = { 5.0, 3.0, 5.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

char int2char(int i)
{


	switch(i)
	{
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		default:
			return '0';
	}
	
}

void determineTransition(std::stack<Controller> &controllers, int &phase, dReal &time)
{


}


int handleArgs(int argc, char** argv, std::stack<Controller> &controllers, std::map<string, Controller> &scripts, std::vector<std::string>& standaloneScripts)
{

	std::vector<Value*> initParams;

	bool hasScript = false;

	controllerReader reader;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-f") == 0)
		{
            // read in all necessary scripts for given script
			if (reader.readScript(argv[i+1], human, scripts) != 0)
			{
				std::cerr << "Error encountered while reading in controller: " << argv[i+1] << std::endl;
					return -1;
			}
			cout << "Using base script: " << argv[i+1] << endl;
			cout << scripts.find(argv[i+1])->first << endl;
            // find the given script [argv[i+1]] and load that as the initial;
			controllers.push(scripts.find(argv[i+1])->second);
            standaloneScripts.push_back(argv[i+1]);
			i++;
			hasScript = true;
		}
        else if (strcmp(argv[i], "-t") == 0)
        {
            std::string from = argv[i+1];
            std::string to = argv[i+2];
            from.at(from.size()-2) = '_'; 
            from.append(".data");
            to.at(to.size()-2) = '_'; 
            to.append(".data");

            
            tf.setFrom((char*)from.c_str());
            tf.setTo((char*)to.c_str());
            tf.findTransitions();
            FIND_TRANSITIONS = true;


            if (reader.readScript(argv[++i], human, scripts) != 0)
            {
				std::cerr << "Error encountered while reading in controller: " << argv[i+1] << std::endl;
					return -1;
			}
            controllers.push(scripts.find(argv[i])->second);
            standaloneScripts.push_back(argv[i]);


            if (reader.readScript(argv[++i], human, scripts) != 0)
            {
				std::cerr << "Error encountered while reading in controller: " << argv[i+1] << std::endl;
					return -1;
			}
            
            standaloneScripts.push_back(argv[i]);

            hasScript = true;

        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            ifstream ifs(argv[i+1]);
            if (!ifs)
            {
                std::cerr << "Problem opening scriptlist: " << argv[i+1] << std::endl;
                return -1;
            }
            bool first = true;
            while (!(ifs.eof()))
            {
                std::string nextScript;
                ifs >> nextScript;
                if (ifs.eof())
                {
                    break;
                }

                standaloneScripts.push_back(nextScript);

                if (reader.readScript((char*)nextScript.c_str(), human, scripts) != 0)
                {
                    std::cerr << "Error encountered while reading in controller: " << nextScript << std::endl;
                    return -1;
                }
                if (first)
                {
                    controllers.push(scripts.find(nextScript)->second);
                    hasScript = true;
                    first = false;
                }
            }
            i++;
        }

        else if (strcmp(argv[i], "-s") == 0)
        {

			speed = 1./(double)atof(argv[++i]);
            
        }
                
		// parameters for initial script
		else if (strcmp(argv[i], "-p") == 0)
		{


			i++;

			if (strcmp(argv[i], "(") != 0)
			{
				std::cerr << "Expected: '(', got: " << argv[i] << std::endl;
				return -1;
			}

			
			while (strcmp(argv[++i], ")") != 0)
			{
				initParams.push_back(new Value(false, string(argv[i])));
			}



			i++;



		}
		else if (strcmp(argv[i], "-z") == 0)
		{
			norotate = true;
		}
		else if (strcmp(argv[i], "-c") == 0)
		{

			characterReader charReader;

			cout << "Using Character File: " << argv[i+1] << endl;

			if (charReader.read(argv[i+1]) != 0)
			{
				return -1;	
			}

			i++;
			
		}
		// TODO: currently does nothing, should set flt_file name
		else if (strcmp(argv[i], "-o") == 0)
		{
			i++;
		}
		else if (strcmp(argv[i], "-fps") == 0)
		{
			fps = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			WRITE_ON_STABLE = true;
		}
/*		else if (strcmp(argv[i], "-t") == 0)
		{
			WRITE_ON_TRANSITION = true;
		}
        */
        else if (strcmp(argv[i], "-r") == 0)
        {
            RECORD_STATES = true;
        }
		else if (strcmp(argv[i], "-e") == 0)
		{
			FAILURE_DETECTION = true;
		}
        else if (strcmp(argv[i], "-v") == 0)
        {
            VISUALIZATION = true;
        }
        else if (strcmp(argv[i], "-traj") == 0)
        {
            traj = new Trajectory(atof(argv[++i]));
            traj->setWriteName(argv[++i]);

            RECORD_TRAJECTORY = true;
        }
        else if (strcmp(argv[i], "-opt") == 0)
        {
            optimizer.readFile(argv[++i], scripts, STEPSIZE);
            OPTIMIZE = true;
        }
        else if (strcmp(argv[i], "--write") == 0)
        {
            WRITE_CONTROLLER = true;
        }
		else
		{
			cerr << "Usage: ./main -f <input controller> [-o <flt file>]" << endl;
			return -1;
		}

	}



	controllers.top().setParams(initParams);
    controllers.top().setGlobals();

	if (!hasScript)
	{
		cerr << "Usage: ./main -f <input controller> [-o <flt file>]" << endl;
		return -1;
	}

	return 0;

}

int readFLT()
{
	string fltfile = "data/char.flt";

	if (flt_reader.open((char*)fltfile.c_str(), &human) != 0)
	{
		cerr << "Error opening flt file " << fltfile << endl;
		return -1;
	}

	flt_reader.objectCount = 0;
	flt_reader.parse();

	for (int c_num = 0; c_num < flt_reader.mesh.components.size(); c_num++)
	{
		flt_reader.mesh.createHull(c_num);
	}

return 0;
	
}

int nextOptGeneration(std::stack<Controller>& controllers, std::map<string, Controller>& scripts, int& phase, dReal& time, bool switched)
{


                    Hierarchy* fromHierarchy = optimizer.getFirstOptimizationHierarchy();
                    RECORD_TRAJECTORY = false;
                    if (optimizer.isFirstRun())
                    {
                        if (switched)
                        {
                            optimizer.setParentTrajectory(traj);  
                            optimizer.updateFitnessParent();
                        }
                        else
                            optimizer.setFitnessParent(1000000);

                        std::cout << "\n\n-----\nGeneration " << optimizer.getGenerationNum() << std::endl;
                        std::cout << "Curve Fitness (parent) is: " << optimizer.getFitnessParent() << std::endl;

                        optimizer.setIsFirstRun(false);
                        optimizer.CMAStep();
                        optimizer.updateControllerValues();
                    }
                    // AFTER THE FIRST RUN
                    else
                    {
                        if (switched)
                        {
                            optimizer.setChildTrajectory(traj);
                            optimizer.updateFitnessChild();
                        }
                        else
                        {
                            optimizer.setFitnessChild(1000000);
                        }
                        optimizer.incrementGenerationNum();
                        std::cout << "\n\n-----\nGeneration " << optimizer.getGenerationNum() << std::endl;
                        std::cout << "Curve Fitness (child) is: " << optimizer.getFitnessChild() << std::endl;
                        std::cout << "Curve Fitness Best (parent) is: " << optimizer.getFitnessParent() << std::endl;

                        optimizer.updateStep();
                        optimizer.CMAStep();
                        optimizer.updateControllerValues();


                    }
                    delete traj;
                    traj = NULL;

                    for (int i = 0; i < controllers.top().phases.at(phase).actions.size(); i++)
                    {
                        controllers.top().phases.at(phase).actions.at(i)->reset();
                    }


                    while (!controllers.empty())
                    {
                        for (int j = 0; j < controllers.top().phases.size(); j++)
                        {
                            for (int i = 0; i < controllers.top().phases.at(j).transitions.size(); i++)
                            {
                                controllers.top().phases.at(j).transitions.at(i)->reset();
                            }
                        }
                        controllers.pop();
                        lookupTable.pop();
                        currHierarchy.pop();
                    }

                    // replace current controller with the specified controller
                    for (auto it = fromHierarchy->begin(); it != fromHierarchy->end(); it++)
                    {
                        if (it != fromHierarchy->begin())
                        {
                           scripts.find(it->first)->second.setParams(controllers.top().phases.at(phase).newControllerParams);
                        }
                        else
                        {
                            std::vector<Value*> placeHolder;
                            scripts.find(it->first)->second.setParams(placeHolder);
                        }

                        controllers.push(scripts.find(it->first)->second);
                        phase = it->second;
                        controllers.top().setCurrPhase(it->second);

                        currHierarchy.push(it->first, it->second);

                    }


                    human.load("OPTIMIZATION.state");

                    time = 0;
                    optimizer.resetGenerationTime();
                    return 1;
                    // stop looking for transitions.


                    // 1. Stop recording trajectory. 
                    // 2. do CMA optimization things.
                    // 3. RESET.

}

int doTransition(std::stack<Controller>& controllers, std::map<string, Controller>& scripts, int& phase, dReal& time, State*& sta, std::stack<StateList*>& sl, Visualizer& controllerGraph)
{

    int ret = 0;
    // test all possible transitions for this phase
    for (std::vector<Transition*>::iterator iter = controllers.top().phases.at(phase).transitions.begin(); iter != controllers.top().phases.at(phase).transitions.end(); iter++)
    {
        // if we are transitioning...
        if ((*iter)->test(time))
        {

            // IF TRANSITIONING

            // If we are recording states, do so now (end of previous state.)
            if (RECORD_STATES)
            {
                if (sta == NULL)
                { 
                    std::cerr << "State pointer was null on reaching the end of a phase. " << std::endl;
                    return -1;
                }
                // end assumes a beginning existed.
                std::cout << "Recording controller: " << controllers.top().getName() << ", phase: " << phase << "-END" << std::endl;
                sta->setEnd(human);
                
                sl.top()->addState(sta);
                sta = NULL;
            }


            // reset all actions for previous state
            for (int i = 0; i < controllers.top().phases.at(phase).actions.size(); i++)
            {
                controllers.top().phases.at(phase).actions.at(i)->reset();
            }
            for (int i = 0; i < controllers.top().phases.at(phase).transitions.size(); i++)
            {
                controllers.top().phases.at(phase).transitions.at(i)->reset();
            }

            // if we are optimizing
            if (FIND_TRANSITIONS || OPTIMIZE)
            {
                Hierarchy* fromHierarchy;
                Hierarchy* toHierarchy;
                bool atFrom = false;
                bool atToEnd = false;
                // if we've found the state we want to transition from.
                if (FIND_TRANSITIONS && currHierarchy.isEqual(tf.getFromHierarchy()))
                {
                    fromHierarchy = tf.getFromHierarchy();
                    toHierarchy = tf.getToHierarchy();
                    atFrom = true;
                }
                if (OPTIMIZE && currHierarchy.isEqual(optimizer.getFromTransitionHierarchy()))
                {
                    fromHierarchy = optimizer.getFromTransitionHierarchy();
                    toHierarchy = optimizer.getToTransitionHierarchy();
                    atFrom = true;
                } 
                if (OPTIMIZE && currHierarchy.isEqual(optimizer.getToEndHierarchy()))
                {
                //    fromHierarchy = optimizer.getFirstOptimizationHierarchy();
                 //   toHierarchy = optimizer.getToEndHierarchy();
                    atToEnd = true;
                }

                /*
                std::cout << "TO: " << std::endl;
                optimizer.getToEndHierarchy()->print();
                std::cout << "CURR: " << std::endl;
                currHierarchy.print();
                */

                // if we've found the state we want to transition from.
                if (atFrom)
                {

                    // remove all controllers
                    while (!controllers.empty())
                    {
                        controllers.pop();
                        lookupTable.pop();
                        currHierarchy.pop();
                    }

                    // replace current controller with the specified controller
                    for (auto it = toHierarchy->begin(); it != toHierarchy->end(); it++)
                    {
                        if (it != toHierarchy->begin())
                        {
                           scripts.find(it->first)->second.setParams(controllers.top().phases.at(phase).newControllerParams);
                        }
                        else
                        {
                            std::vector<Value*> placeHolder;
                            scripts.find(it->first)->second.setParams(placeHolder);
                        }

                        controllers.push(scripts.find(it->first)->second);
                        phase = it->second;
                        controllers.top().setCurrPhase(it->second);

                        currHierarchy.push(it->first, it->second);


                        RECORD_TRAJECTORY = true;
                        delete traj;
                        traj = new Trajectory(0.01);

                    }

                    //std::cout << controllers.top().phases.at(phase).transitions.at(0)->curr_iterations << std::endl;


                    time = 0;
                    ret = 1;
                    // stop looking for transitions.
                    break;

                }
                if (atToEnd)
                {
                    nextOptGeneration(controllers, scripts, phase, time, true);
                    break;
                }
                
            } // end if optimizing
                // (else if not optimizing or not atFrom) NO ELSE HERE.
            {
                // replace push next phase on.
                controllers.top().setCurrPhase((*iter)->to);
                phase = controllers.top().getCurrPhase();

                currHierarchy.setLastPhase(controllers.top().getCurrPhase());

                if (RECORD_STATES && phase != -1 && !controllers.top().phases.at(phase).isSwitch)
                {
                    std::cout << "Recording controller: " << controllers.top().getName() << ", phase: " << phase << "-BEGIN" << std::endl;
                    sta = new State(phase);
                    sta->setBegin(human);
                }
                // reset phase time
                time = 0;
                ret = 1;
                // stop looking for transitions.
                break;
            }

        }
    }
            // pop if we reach the end of a controller.
    if (phase == -1)
    {

        bool done = false;
        while (phase == -1)
        {
            controllers.pop();
            currHierarchy.pop();
            if (RECORD_STATES)
                    sl.pop();
            // if no more controllers, switch to RAGDOLL
            if (controllers.empty())
            {
                done = true;
                break;
            }
            // otherwise, move to the next phase of parent controller
            else
            {
                lookupTable.pop();
                phase = controllers.top().getCurrPhase();
                controllers.top().setGlobals();

                // transition...
                for (std::vector<Transition*>::iterator iter = controllers.top().phases.at(phase).transitions.begin(); iter != controllers.top().phases.at(phase).transitions.end(); iter++)
                {
                    if ((*iter)->test(time))
                    {

                        time = 0;
                        ret = 1;
                        controllers.top().setCurrPhase((*iter)->to);
                        phase = controllers.top().getCurrPhase();
                        currHierarchy.setLastPhase(phase);
                        break;

                    }
                }
            }
        }
        // case where we are on the last level of a controller (ie, search)
        if (done)
        {

            ret = 3;
            RAGDOLL = true;
//                break;

//					break; // breaks out of the main loop
        }
        // case where we nicely switch back to the next phase of the (a) parent controller.
        else
        {

            if (RECORD_STATES && phase != -1 && !controllers.top().phases.at(phase).isSwitch)
            {
                std::cout << "Recording controller: " << controllers.top().getName() << ", phase: " << phase << "-BEGIN" << std::endl;
//                    sl.pop();
                sta = new State(phase);
                sta->setBegin(human);
        //        sl.top()->addState(sta);
            }

        }
//			cout << controllers.top().getName() << ": Phase: " << phase << endl;

        if (!RAGDOLL)
            controllerGraph.checkCurrController(controllers.top().getDisplayName());

    //    return 1;
        
    }

    return ret;

}


int main(int argc, char** argv)
{
    
	if (argc < 3 || argc > 10)
	{
		cerr << "Usage: ./main -f <input controller> [-o <flt file>]" << endl;
		return -1;
	}


    Visualizer controllerGraph;

    srand(time(NULL));

    speed = 1;
    // number of balls thrown at the character
    addedEntities = 0;

	dInitODE();

	initODE();
	initObjects();

	std::stack<Controller> controllers; // the current controller hierarchy
	
	std::map<string, Controller> scripts; // the map of all available controllers
    std::vector<string> standaloneScripts; // list of standalone scripts (when using a scriptlist

	env = new Environment();

	env->setFromFile("base.env");

	if (handleArgs(argc, argv, controllers, scripts, standaloneScripts) < 0)
		return -1;


    currHierarchy.push(controllers.top().getName(), controllers.top().getCurrPhase());
        //return 2;
    
	int glfw_err = initializeGLFW();
	if (glfw_err != 0)
	{
		std::cerr << "Error initializing GLFW Window: " << glfw_err << std::endl;
		return -1;
	}
    
    int fltk_err = createFLTKWindow((char*)("Scripts"), standaloneScripts, env->getEntities());

    if (fltk_err != 0)
    {
        std::cerr << "Error initializing FLTK Window: " << fltk_err << std::endl;
    }

	initializeGL();
	initQuesoGLC();

	int mousewheel_pos_prev = 0;

	dReal tol = 0.01;


	// Top of the stack is the currently running controller.
	// Note that the current running controller will have to be a **COPY** of the controller stored in map scripts. (So that we don't set the current phase etc etc.)

/*
	{
		// TODO: Temporary for testing transition finder
		Status* s = new Status();

		s->setFromFile("../states/backflip0to1.state");

		transitionFinder.pushStatus(s);

		SEARCH = true;

		// END TEMPORARY
	}
*/

	// read in the maya openFlight file.
	if (readFLT() != 0)
		return -1;

	
	cout << "\n\n  CONTROLS\n" << "  --------\n";
	cout << "Pause: Enter\n" << "Zoom: Scroll Wheel\n" << "Apply Force: Space\n"
		 << "Exit: Escape\n";


//    StateList sl;
    std::stack<StateList*> sl;
    sl.push(new StateList);
    State* sta;
    int phase = 0;
    if (RECORD_STATES)
    {
        std::cout << "Recording states for: " << controllers.top().getName() << std::endl;
        sl.top()->setName(controllers.top().getName());

                if (RECORD_STATES && phase != -1 && !controllers.top().phases.at(phase).isSwitch)
                {
                    std::cout << "Initial State Record: Controller: " << controllers.top().getName() << ", phase: " << phase << "-BEGIN" << std::endl;
                    sta = new State(phase);
                    sta->setBegin(human);
                }
    } 


//    controllerGraph.createGraph(scripts);

    if (controllerGraph.openGraph("visualizer.dot") != 0)
    {
        std::cerr << "Error reading in visusalization graph" << std::endl;
        return -1;
    }
    controllerGraph.createLayout();

   // controllerGraph.printAllNodes();

	dReal time = 0; // counter since last phase change.
	dReal t = 0; // counter till frame render.
    dReal time_tot = 0; // counter since beginning

	long frame = (1.0/fps * 1E9);


    /*
    std::cout << "Controller " << controllers.top().getName() << " calls: " << std::endl;

    for (auto it = controllers.top().getLinks().begin(); it != controllers.top().getLinks().end(); it++)
    {

        std::cout << (*it)->getName() << std::endl;

    }

    return -1;
*/



    /* ------------------------------------------------------ */
    /* ---------------Playing Field-------------------------- */

    
    optimizer.setUnknowns();
    optimizer.initCMA();

   // optimizer.CMAStep();
    


    /*return 4;
    */


#ifndef __APPLE__
	timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
#endif

#ifdef __APPLE__
    timeval start, end;
    gettimeofday(&start, NULL);
#endif

		char* buffer = new char[128];

    // Main loop. TODO: Rework the whole int main to reduce clutter by a factor of 1000
	while (true)
	{


        // checks to see if any updates in fltkWindow
        checkFLTKWindow(); 

        if (checkPause())
        {
            continue;
        }


       
		// if we've done enough simulations for this timestep...
		if (t >= 1.0/fps)
		{

			// wait until we've gone over the necessary amount of real time for a frame
#ifndef __APPLE__
			clock_gettime(CLOCK_REALTIME, &end);
			while ( (end.tv_sec * 1E9 + end.tv_nsec) - (start.tv_sec * 1E9 + start.tv_nsec) < frame*speed )
			{
				clock_gettime(CLOCK_REALTIME, &end);
			}

			clock_gettime(CLOCK_REALTIME, &start);
#endif
			
#ifdef __APPLE__
            gettimeofday(&end, NULL);
            while ( (end.tv_sec * 1E9 + end.tv_usec * 1E3) - (start.tv_sec * 1E9 + start.tv_usec * 1E3) < frame*speed )
            {
                gettimeofday(&end, NULL);
            }

            gettimeofday(&start, NULL);
#endif

            t = 0;
		}

        
		t += STEPSIZE;

        
        phase = -1;
        if (!RAGDOLL)
		    phase = controllers.top().getCurrPhase();


        if (OPTIMIZE && !optimizer.isOptimizing())
        {

            if (optimizer.isFirstRun() && currHierarchy.isEqual(optimizer.getFirstOptimizationHierarchy()))
            {
                optimizer.startOptimizing();
                human.save("OPTIMIZATION.state");
            }
            /* // Note, this will be handled when comparing the trajectories.
            else if (!optimizer.isFirstRun() && currHierarchy.isEqual(optimizer.getFirstOptimizationHierarchy()))
            {

            }
            */

        }

        if (!RAGDOLL)
        {
            
            if (controllers.top().phases.at(phase).isSwitch)
            {

                StateList* temp;

                if (RECORD_STATES)
                {

                    std::cout << "Recording controller: " << controllers.top().getName() << ", phase: " << phase << "-SWITCH" << std::endl;
                    sta = new State(phase);
                    temp = new StateList;

                    sta->setChild(temp);
                    sl.top()->addState(sta);


                }

                int nextPhase = controllers.top().phases.at(phase).getSwitchPhase();

                scripts.find(controllers.top().phases.at(phase).newControllerName)->second.setParams(controllers.top().phases.at(phase).newControllerParams);
                controllers.push(scripts.find(controllers.top().phases.at(phase).newControllerName)->second);
                controllers.top().setCurrPhase(nextPhase);
                phase = controllers.top().getCurrPhase();

                //cout << controllers.top().getName() << ": Phase: " << phase << endl;
                //
                controllers.top().setGlobals();
                
                // push current controller onto transition finder hierarchy.
                currHierarchy.push(controllers.top().getName(), controllers.top().getCurrPhase());

                if (RECORD_STATES)
                {
                    sl.push(temp);
                    sl.top()->setName(controllers.top().getName());

                    if (phase != -1 && !controllers.top().phases.at(phase).isSwitch)
                    {
                        std::cout << "Recording controller: " << controllers.top().getName() << ", phase: " << phase << "-BEGIN" << std::endl;

                        sta = new State(phase);
                        sta->setBegin(human);
                    }
                }

                if (!RAGDOLL)
                    controllerGraph.checkCurrController(controllers.top().getDisplayName());

                continue;
            }
            
        }



		int n;
        std::string dname;
        if (!RAGDOLL)
        {
            n=sprintf(buffer,"%s - Phase: %d", controllers.top().getDisplayName().c_str(), phase);
            dname = controllers.top().getDisplayName();
        }
        else
        {
            n=sprintf(buffer,"RAGDOLL");
            dname = "RAGDOLL";
        }

        if (RECORD_TRAJECTORY && traj->getRecordingTime() > traj->timelength() + traj->getTimestep())
        {
            float* jangles = new float[JOINT_COUNT];
            for (int i = 0; i < JOINT_COUNT; i++)
            {
                jangles[i] = dJointGetHingeAngle(human.joints[i]->getJointID());
            }
            traj->push(human.getCoM(), -dJointGetAMotorAngle(human.uTorso2world_M,2), jangles); 

        }


        bool emptyPhase = true;

        if (!RAGDOLL)
        {


            // Update phase-specific objectives
            if (OPTIMIZE && optimizer.isOptimizing())
            {
                if (-dJointGetAMotorAngle(human.uTorso2world_M,2) > .6 || -dJointGetAMotorAngle(human.uTorso2world_M,2) < -.6)
                {
                    optimizer.fallen = true;
                }
                else
                {
                    optimizer.fallen = false;
                }
                optimizer.energy = human.getEnergy();
                // update phase-specific objectives
                optimizer.updateObjectives(&currHierarchy);
                // update from controller (spanning) objectives
                optimizer.updateFromObjectives();
            }
            if (RECORD_TRAJECTORY && OPTIMIZE) 
            {
                if (-dJointGetAMotorAngle(human.uTorso2world_M,2) > .6 || -dJointGetAMotorAngle(human.uTorso2world_M,2) < -.6)
                {
                    optimizer.fallen = true;
                }
                else
                {
                    optimizer.fallen = false;
                }
                optimizer.energy = human.getEnergy();

                optimizer.updateToObjectives();

            }

            if (controllers.top().phases.at(phase).actions.size() > 0)
                emptyPhase = false;

            // This block sets the joint torques for each joint.
            {
            // Perform all actions for this phase
                for (int i = 0; i < controllers.top().phases.at(phase).actions.size(); i++)
                {
                    controllers.top().phases.at(phase).actions.at(i)->performAction();
                }

                // perform the task for each individual PD Controller
                // Perform pose for all joints.
                for (int i = 0; i < JOINT_COUNT; i++)
                {
                    human.joints[i]->pose();
                }
            }

            VECTOR torque;

            // This block limits the torques. (TODO: This should probably be part of human).
            for (int i = 0; i < JOINT_COUNT; i++)
            {
                torque = human.joints[i]->getCurrentTorque();

                if (torque.z > TORQUE_LIMIT)
                    torque.z = TORQUE_LIMIT;

                if (torque.z < -TORQUE_LIMIT)
                    torque.z = -TORQUE_LIMIT;

                if (torque.z == 0)
                {}

                human.joints[i]->setCurrentTorque(torque);

                dJointAddHingeTorque(human.joints[i]->getJointID(), torque.z);
                
//               std::cout << i << ": " << torque.z << std::endl;
//
            }


            human.updateEnergy(STEPSIZE);
//            std::cout << human.getEnergy() << std::endl;

            // This block zeroes the torques
            for (int i = 0; i < JOINT_COUNT; i++)
            {
                human.joints[i]->setCurrentTorque(VECTOR(0,0,0));
            }
            

        }
        // Still want to simulate during ragdoll, even though there is no 'active' phase
        else
        {
            emptyPhase = false;
        }


        // Wait_var corresponds to the amount of time to wait in a controller before we assume it failed. Higher values for slower controllers.
        // Don't simulate during phases that have no actions. (SAVE, LOAD, etc)
        if (!emptyPhase)
        {
            simLoop(t>=1.0/fps, buffer, controllerGraph, dname);
            time_tot += STEPSIZE;
            time += STEPSIZE;
            if (RECORD_TRAJECTORY)
            {
                traj->incrementRecordingTime(STEPSIZE);
                // 'TO' phase
                // For most controllers, wait_var = 1 is okay. For walking handstand, use 10+ Note this must be lower than the from phase variable.
                dReal wait_var = 2;
                if (OPTIMIZE && traj->timelength() > wait_var*optimizer.getGoalTrajectory()->timelength())
                {
                    if (nextOptGeneration(controllers, scripts, phase, time, true) == 1)
                        continue;
                }
            }
                // 'FROM' phase
            // --- 
            if (OPTIMIZE && optimizer.isOptimizing())
            {
                if (-dJointGetAMotorAngle(human.uTorso2world_M,2) > 1)
                    optimizer.fallen = true;
                optimizer.incrementGenerationTime(STEPSIZE);
                // rough estimate... TODO: Look into a better value for this.
                // For most controllers, wait_var = 2 is okay. For walking handstand, use 20+
                dReal wait_var = 3;
                if (optimizer.getGenerationTime() > wait_var*optimizer.getGoalTrajectory()->timelength())
                {
                    if (nextOptGeneration(controllers, scripts, phase, time, false) == 1)
                        continue;
                }
            }
        }


        if (!RAGDOLL)
        {

        
            /* ----- TRANSITIONING SECTION ----- */

            // Determine whether or not to transition

            int transResult = doTransition(controllers, scripts, phase, time, sta, sl, controllerGraph);
            // Transition found
            if (transResult == 1)
            {
                // test to see if we are at the initial state for the optimization

            }
            // Error
            if (transResult == -1)
            {
                std::cerr << "Error encountered during transitioning" << std::endl;
                return -1;
            }



        } // end if !ragdoll

        /* // exit on ragdoll
        if (RAGDOLL)
        {
            return -1;
        }
        */


		/*  All the keypress events  */

		glfwPollEvents();
		//Exit
		if ( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
		{
            // TODO: FIXME

            if (RECORD_STATES)
            {
            while ( sl.size() > 1)
                sl.pop();

            sl.top()->writeToFile();
            }
            if (RECORD_TRAJECTORY)
            {
                traj->writeToFile();
            }
            if (WRITE_CONTROLLER)
            {
                if (OPTIMIZE) { optimizer.setCValsToMinimum(); }
                while (controllers.size() > 1)
                {
                    controllers.pop();
                }
                while (lookupTable.size() > 0)
                {
                    lookupTable.pop();
                }

                controllers.top().writeToFile("OutputController.s", scripts);
            }
			break;
		}
		//Add force at torso
		if ( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS )
		{
			dBodyAddForce(human.parts[U_TORSO]->Body, 50, 0, 0);
            PUSH_FORWARD = true;
		}
        else
            PUSH_FORWARD = false;
		if ( glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS )
		{
			dBodyAddForce(human.parts[U_TORSO]->Body, -50, 0, 0);
            PUSH_BACKWARD = true;
		}
        else
            PUSH_BACKWARD = false;

		//Pause
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{

			while (glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_RELEASE)
			{
				glfwPollEvents();
			}

			while (glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_PRESS)
			{
				glfwPollEvents();
			}

			while (glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_RELEASE)
			{
				glfwPollEvents();
			}

		}
		if (glfwGetKey(window, 'C') == GLFW_PRESS)
		{
			draw_com = !draw_com;

			while (glfwGetKey(window, 'C') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}
		if (glfwGetKey(window, 'G') == GLFW_PRESS)
		{
			DRAW_CONTACT = !DRAW_CONTACT;
			while (glfwGetKey(window, 'G') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}
		if (glfwGetKey(window, 'V') == GLFW_PRESS)
		{
			DISPLAY_COMVEL = !DISPLAY_COMVEL;
			while (glfwGetKey(window, 'V') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}
		if ( (glfwGetKey(window, 'R') == GLFW_PRESS) || checkReset())
		{
			human.reset();
    		for (int i = 0; i < controllers.top().phases.at(phase).actions.size(); i++)
			{
				controllers.top().phases.at(phase).actions.at(i)->reset();
			}

			while (controllers.size() > 1)
			{
				controllers.pop();
			}
			while (lookupTable.size() > 0)
			{
				lookupTable.pop();
			}

			controllers.top().setCurrPhase(0);
			phase = 0;
			time = 0;
			t = 0;
		}
       
        int resNum = checkLoad();
        if (resNum != -1)
        {
			human.reset();
            if (controllers.size() > 0)
            {
                for (int i = 0; i < controllers.top().phases.at(phase).actions.size(); i++)
                {
                    controllers.top().phases.at(phase).actions.at(i)->reset();
                }
            }

			while (controllers.size() > 0)
			{
				controllers.pop();
			}
			while (lookupTable.size() > 0)
			{
				lookupTable.pop();
			}

            controllers.push(scripts.find(standaloneScripts.at(resNum))->second);

			controllers.top().setCurrPhase(0);
			phase = 0;
			time = 0;
			t = 0;
            RAGDOLL = false;
        }
        std::string toggleVis = checkToggleVis();
        if ( toggleVis.compare("") != 0 )
        {
            Entity* ent = (env->getEntities().find(toggleVis)->second);
            ent->setVisible(!(ent->isVisible()));
            for (std::vector<Object*>::iterator iter = ent->getBodies().begin(); iter != ent->getBodies().end(); iter++)
            {
                (*iter)->setVisible(ent->isVisible());
            }
            resetVis();
        }
        std::string toggleCol = checkToggleCol();
        if ( toggleCol.compare("") != 0 )
        {
            Entity* ent = (env->getEntities().find(toggleCol)->second);
            ent->setCollidable(!(ent->isCollidable()));
            for (std::vector<Object*>::iterator iter = ent->getBodies().begin(); iter != ent->getBodies().end(); iter++)
            {
                (*iter)->setCollidable(ent->isCollidable());
            }
            resetCol();
        }
        

		if (glfwGetKey(window, 'S') == GLFW_PRESS && !S_DOWN)
		{
            S_DOWN = true;
			human.save("manual.state");
            std::cout << "Saving State ... " << std::endl;
		}
        if (S_DOWN && glfwGetKey(window, 'S') == GLFW_RELEASE)
        {
            S_DOWN = false;
        }
		if (glfwGetKey(window, 'L') == GLFW_PRESS && !L_DOWN)
		{
            L_DOWN = true;
			human.load("manual.state");
            std::cout << "Loading State ... " << std::endl;
		}
        if (L_DOWN && glfwGetKey(window, 'L') == GLFW_RELEASE)
        {
            L_DOWN = false;
        }
		if (glfwGetKey(window, 'D') == GLFW_PRESS)
		{
            RAGDOLL = !RAGDOLL;

			while (glfwGetKey(window, 'D') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}
		if (glfwGetKey(window, '1') == GLFW_PRESS)
		{

            if (addedEntities >= 1)
            {
                char buff[16];
                sprintf(buff, "Ball%d", addedEntities);
                env->deleteEntity(std::string(buff));
            }


            Entity* e = new Entity();

            dReal rot[4] = {0,0,0,0};
            
            dReal coin = rand()/(dReal)RAND_MAX;
            dReal e_x, e_vx;

            if (coin < .5)
            {
                e_x = -2; e_vx = 7;
            }
            else
            {
                e_x = 2; e_vx = -7;
            }

            dReal size = rand()/(dReal)RAND_MAX*(1./7.)+.01;

            Shape* shape = new Sphere(size*50, human.getCoM()+VECTOR(e_x,.5,-.010), VECTOR(e_vx,1,0), rot, size);

            Object* o = new Object();
            o->Body = dBodyCreate(World);

            o->parent = NULL;
            o->shape = shape;
            o->setFriction(-1);

            o->human_part = false;
            o->setVisible(true);
            o->setCollidable(true);

            shape->initialize(o->Body, o->Geom[0]);
            geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));
            
            e->getBodies().push_back(o);

            addedEntities++;

            char buff[8];

            sprintf(buff, "Ball%d", addedEntities);

            e->setName(std::string(buff));

            env->addEntity(e);



			while (glfwGetKey(window, '1') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}
		if (glfwGetKey(window, '2') == GLFW_PRESS)
		{



            Entity* e = new Entity();

            dReal rot[4] = {0,0,0,0};
            

            Shape* shape = new Sphere(250, human.getCoM()+VECTOR(-3,.5,-.010), VECTOR(7,1,0), rot, 1);

            Object* o = new Object();
            o->Body = dBodyCreate(World);

            o->parent = NULL;
            o->shape = shape;
            o->setFriction(-1);

            o->human_part = false;
            o->setVisible(true);
            o->setCollidable(true);

            shape->initialize(o->Body, o->Geom[0]);
            geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));
            
            e->getBodies().push_back(o);

            addedEntities++;

            char buff[16];

            sprintf(buff, "BigBall%d", addedEntities);

            e->setName(std::string(buff));

            env->addEntity(e);



			while (glfwGetKey(window, '2') != GLFW_RELEASE)
			{
				glfwPollEvents();
			}
		}

		// IK repositioning
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{

			int x, y;
			//glfwGetMousePos(&x, &y);

			while (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_RELEASE)
			{
				glfwPollEvents();
			}


		}
		
		// for zooming.
		{
			
			//int mousewheel_pos = glfwGetMouseWheel();

	//		zoom -= .2*(mousewheel_pos - mousewheel_pos_prev);

			//mousewheel_pos_prev = mousewheel_pos;
		}



	}

	closeODE();

	return 0;

}
