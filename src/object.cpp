
#define dSINGLE

#include <ode/ode.h>

#include <iostream>
#include <fstream>
#include <assert.h>

#include "globals.h"
#include "VECTOR.h"
#include "object.h"
#include "environment.h"
#include "entity.h"

// TODO: THIS NEEDS TO BE FIXED NOW THAT WE"RE NOT USING PLANE GLOBAL AS GROUND
bool Object::groundContact()
{

    /*
	dContact temp;
//    std::cout << "?" << std::endl;
	if (dCollide(plane, Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
	{
		return true;
	}
	else
		return false;
        */
	dContact temp;
	
    std::map<std::string, Entity*> env_ents = env->getEntities();
	for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
    {
        for (auto  objIter = iter->second->getBodies().begin(); objIter != iter->second->getBodies().end(); objIter++)
        {

            if (dCollide((*objIter)->Geom[0], Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
            {
                return true;
            }
        }
    }

	return false;
}

void Object::reset()
{

	shape->reset(Body);

}

bool Object::save(std::ofstream &out)
{

	if (!out)
	{
		return false;
	}

	out << name << std::endl;

	const dReal* pos = dBodyGetPosition(Body);

	out << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;

	const dReal* R = dBodyGetRotation(Body);

	out << R[0] << " " << R[1] << " " << R[2] << " " << R[3] << std::endl <<
		R[4] << " " << R[5] << " " << R[6] << " " << R[7] << std::endl <<
		R[8] << " " << R[9] << " " << R[10] << " " << R[11] << std::endl;

	const dReal* linVel = dBodyGetLinearVel(Body);

	out << linVel[0] << " " << linVel[1] << " " << linVel[2] << std::endl;

	const dReal* angVel = dBodyGetAngularVel(Body);

	out << angVel[0] << " " << angVel[1] << " " << angVel[2] << std::endl;

	//out << currentTorque.x << " " << currentTorque.y << " " << currentTorque.z << std::endl;


	return true;

}


void Object::load(std::ifstream &in)
{


	dReal check;
	in >> check;
	assert(check == name);


	VECTOR pos;
	in >> pos.x >> pos.y >> pos.z;



	dBodySetPosition(Body, pos.x, pos.y, pos.z);

	dReal R[12];

	for (int i = 0; i < 12; i++)
		in >> R[i];

	dBodySetRotation(Body, R);

	VECTOR linVel;
	in >> linVel.x >> linVel.y >> linVel.z;

	dBodySetLinearVel(Body, linVel.x, linVel.y, linVel.z);

	VECTOR angVel;
	in >> angVel.x >> angVel.y >> angVel.z;

	dBodySetAngularVel(Body, angVel.x, angVel.y, angVel.z);


//	in >> currentTorque.x >> currentTorque.y >> currentTorque.z;

	//currentTorque = VECTOR(0,0,0);

}

Plane::Plane(dReal x1_in, dReal y1_in, dReal x2_in, dReal y2_in)
{ 
            x1 = x1_in; x2 = x2_in; y1 = y1_in; y2 = y2_in; type = PLANE; 
            dReal dx = x2 - x1, dy = y2 - y1; dReal norm = sqrt(dx*dx + dy*dy);
            dReal d = dy/norm * x1 - dx/norm *y1;
        	Geom[0] = dCreatePlane(Space, -dy/norm, dx/norm, 0, -d);
 //           Geom[0] = dCreatePlane(Space, 0, 1, 0, 0);
}

dJointID createHingeMotor(dBodyID first, dBodyID second, int axis, dReal max_force, dReal init_vel = 0)
{

	dJointID ret = dJointCreateAMotor(World, jointgroup);
	dJointAttach(ret, first, second);
	dJointSetAMotorNumAxes(ret,1);


	if (axis == 0)
		dJointSetAMotorAxis(ret,0,1,1,0,0);
	else if (axis == 1)
		dJointSetAMotorAxis(ret,0,1,0,1,0);
	else if (axis == 2)
		dJointSetAMotorAxis(ret,0,1,0,0,1);

	dJointSetAMotorParam(ret,dParamFMax, max_force);

	dJointSetAMotorParam(ret,dParamVel, init_vel);

	return ret;

}

dJointID createBallMotor(dBodyID first, dBodyID second, const VECTOR max_force, const VECTOR init_vel)
{

	dJointID ret = dJointCreateAMotor(World, jointgroup);
	dJointAttach(ret, first, second);
	dJointSetAMotorNumAxes(ret, 3);

	dJointSetAMotorAxis(ret,0,1,1,0,0);
	dJointSetAMotorAxis(ret,1,1,0,1,0);
	dJointSetAMotorAxis(ret,2,1,0,0,1);

	dJointSetAMotorParam(ret,dParamFMax, max_force.x);
	dJointSetAMotorParam(ret,dParamFMax2, max_force.y);
	dJointSetAMotorParam(ret,dParamFMax3, max_force.z);

	dJointSetAMotorParam(ret,dParamVel, init_vel.x);
	dJointSetAMotorParam(ret,dParamVel2, init_vel.y);
	dJointSetAMotorParam(ret,dParamVel3, init_vel.z);

	return ret;
}

dJointID createLMotor(dBodyID first, dBodyID second, const VECTOR max_force, const VECTOR init_vel)
{
	dJointID ret = dJointCreateLMotor(World, jointgroup);
	dJointAttach(ret, first, second);
	dJointSetLMotorNumAxes(ret,3);
	dJointSetLMotorAxis(ret,0,1,1,0,0);
	dJointSetLMotorAxis(ret,1,1,0,1,0);
	dJointSetLMotorAxis(ret,2,1,0,0,1);

	dJointSetLMotorParam(ret,dParamFMax, max_force.x);
	dJointSetLMotorParam(ret,dParamFMax2, max_force.y);
	dJointSetLMotorParam(ret,dParamFMax3, max_force.z);

	dJointSetLMotorParam(ret,dParamVel, init_vel.x);
	dJointSetLMotorParam(ret,dParamVel2, init_vel.y);
	dJointSetLMotorParam(ret,dParamVel3, init_vel.z);

	return ret;

}

dJointID createVirtualAMotor(dBodyID body)
{

	dJointID ret = dJointCreateAMotor(World, jointgroup);
	dJointAttach(ret, body, 0);

	dJointSetAMotorMode(ret, dAMotorEuler);

	dJointSetAMotorAxis(ret,0,1,1,0,0);
	dJointSetAMotorAxis(ret,2,0,0,0,1);

	return ret;
}

dJointID createHingeJoint(dBodyID body1, dBodyID body2, VECTOR pos, int axis)
{
	dJointID ret = dJointCreateHinge(World, jointgroup);
	dJointAttach(ret, body1, body2);
	dJointSetHingeAnchor(ret, pos.x, pos.y, pos.z);
	if (axis == 0)
	{
		dJointSetHingeAxis(ret, 1, 0, 0);
	}
	else if (axis == 1)
	{
		dJointSetHingeAxis(ret, 0, 1, 0);
	}
	else if (axis == 2)
	{
		dJointSetHingeAxis(ret, 0, 0, 1);
	}

	return ret;
}

Object::~Object()
{

    delete shape;
    dBodyDestroy(Body);
    dGeomDestroy(Geom[0]);


}
