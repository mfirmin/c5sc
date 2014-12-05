
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>
#include <ode/ode.h>

#include <vector>

#include "ODEWrapper.h"
#include "../math/VECTOR.h"

struct ODEWrapper::impl
{
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    dJointGroupID jointgroup;

    std::vector<dBodyID> bodies;
    std::vector<dJointID> joints;

    dBodyID addBody(ODEWrapper*, dGeomID&, VECTOR, VECTOR, VECTOR, VECTOR);

    dBodyID getBodyIDFromID(int i) { return bodies.at(i); }

    void nearCallback(void*, dGeomID, dGeomID);
};

ODEWrapper::ODEWrapper() 
{
	dInitODE();
    pimpl = new impl();
}


dBodyID ODEWrapper::impl::addBody(ODEWrapper*, dGeomID&, VECTOR pos, VECTOR vel, VECTOR ang, VECTOR w)
{
    dBodyID id = dBodyCreate(world);
    dBodySetPosition(id, pos.x, pos.y, pos.z);

	dMatrix3 R;
	dRFromEulerAngles(R, ang.x, ang.y, ang.z);
	dBodySetRotation(id, R);

	dBodySetLinearVel(id, vel.x, vel.y, vel.z);
	dBodySetAngularVel(id, w.x,w.y, w.z);

    return id;
}

int ODEWrapper::init() 
{

	pimpl->world = dWorldCreate();
	pimpl->space = dSimpleSpaceCreate(0);
	pimpl->contactgroup = dJointGroupCreate(0);
	pimpl->jointgroup = dJointGroupCreate(0);


	dWorldSetGravity(pimpl->world, 0, -9.81, 0);


	dWorldSetERP(pimpl->world, 0.5);
	dWorldSetCFM(pimpl->world, 1e-5);

	dWorldSetContactMaxCorrectingVel(pimpl->world, 0.3);

	dWorldSetContactSurfaceLayer(pimpl->world, 0.001);

	dWorldSetAutoDisableFlag(pimpl->world, 0);

    return 0;

}

int ODEWrapper::addCube(VECTOR pos, float sides, VECTOR vel0, VECTOR ang0, VECTOR ang_vel0, float mass)
{

    return addBox(pos, VECTOR(sides, sides, sides), vel0, ang0, ang_vel0, mass);

}

int ODEWrapper::addBox(VECTOR pos, VECTOR sides, VECTOR vel0, VECTOR ang0, VECTOR ang_vel0, float mass)
{
    dMass m;
	dMassSetBoxTotal(&m, mass, sides.x, sides.y, sides.z);
	dGeomID geom = dCreateBox(pimpl->space, sides.x, sides.y, sides.z);
    dBodyID id   = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);

    pimpl->bodies.push_back(id);
    return pimpl->bodies.size();

}

int addJoint(VECTOR pos, float theta=0, float dTheta=0)
{
    std::cout << "not yet implemented" << std::endl;
    return -1;

}


static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
	int i;
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);



        int MAX_CONTACTS = 5;
	dContact contact[MAX_CONTACTS];


	for (i = 0; i < MAX_CONTACTS; i++)
	{

		dReal mu = dInfinity;

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
            /*
			dJointID c = dJointCreateContact(pimpl->world, pimpl->contactgroup, contact + i);
			dJointAttach(c, b1, b2);
            */
		}
	}
}

VECTOR ODEWrapper::getBodyPositionFromID(int id)
{

    const dReal* pos = dBodyGetPosition(pimpl->getBodyIDFromID(id));
    return VECTOR(pos[0], pos[1], pos[2]);

}

void ODEWrapper::step(float timestep) 
{
    dSpaceCollide(pimpl->space, 0, &nearCallback);
    dWorldQuickStep(pimpl->world, timestep);
    dJointGroupEmpty(pimpl->contactgroup);
}

/*

int main(int argc, char** argv)
{


    ODEWrapper* phys = new ODEWrapper();
    phys->init();

    int box1 = phys->addCube(VECTOR(0,10,0), 1, VECTOR(0,0,0), 0, 0, 10);
    phys->addCube(VECTOR(0,15,0), 1, VECTOR(0,0,0), 0, 0, 10);


    while (true)
    {
        phys->step(0.0001);
        float pos = phys->getBodyPositionFromID(box1).y;

        std::cout << pos << std::endl;
        if (pos < -5)
            break;
    }



    std::cout << "yay" << std::endl;
}
*/
