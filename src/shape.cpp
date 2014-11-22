
#define dSINGLE

#include "shape.h"
#include "globals.h"
#include <ode/ode.h>
#include <iostream>

void Shape::initialize(dBodyID& body, dGeomID& geom) const
{

	dMatrix3 R;

	dBodySetPosition(body, pos.x, pos.y, pos.z);
	dBodySetLinearVel(body, vel.x, vel.y, vel.z);
	
	dRFromAxisAndAngle(R, rot[0], rot[1], rot[2], rot[3]);
	dBodySetRotation(body, R);



}

void Shape::reset(dBodyID& body)
{

	dBodySetPosition(body, pos.x, pos.y, pos.z);

	dMatrix3 R;
	dRFromAxisAndAngle(R, rot[0], rot[1], rot[2], rot[3]);
	dBodySetRotation(body, R);

	dBodySetLinearVel(body, vel.x, vel.y, vel.z);

	dBodySetAngularVel(body, 0,0,0);

}

Capsule::Capsule(dReal m, VECTOR p, VECTOR v, dReal rotation[4], dReal l, dReal r1, dReal r2)
{
	type = CAPSULE; 
	mass = m;
	pos = p; 
	vel = v; 
	for (int i = 0; i < 4; i++) 
		rot[i] = rotation[i]; 

	length = l;
	rad1 = r1;
	if (r2 == -1)
	{
		rad2 = r1;
	}
	else
	{
       		rad2 = r2; 
	}
}
Box::Box(dReal m, VECTOR p, VECTOR v, dReal* rotation, VECTOR s)
{
	type = BOX; 
	mass = m;
	pos = p; 
	vel = v; 
	for (int i = 0; i < 4; i++) 
		rot[i] = rotation[i]; 
	sides.x = s.x; sides.y = s.y; sides.z = s.z;
}
Sphere::Sphere(dReal m, VECTOR p, VECTOR v, dReal* rotation, dReal rad)
{
	type = SPHERE; 
	mass = m;
	pos = p; 
	vel = v; 
	for (int i = 0; i < 4; i++) 
		rot[i] = rotation[i]; 
	radius = rad; 
}

void Capsule::initialize(dBodyID& body, dGeomID& geom) const
{
	Shape::initialize(body, geom);

	dMatrix3 R;
	dMass m;

	dReal rad_avg = (rad1+rad2)/2.0;

	dMassSetCapsuleTotal(&m, mass, 3, rad_avg, length);
	geom = dCreateCapsule(Space, rad_avg, length);
	dBodySetMass(body, &m);
	dGeomSetBody(geom, body);

}
void Sphere::initialize(dBodyID& body, dGeomID& geom) const
{
	Shape::initialize(body, geom);

	dMatrix3 R;
	dMass m;

	dMassSetSphereTotal(&m, mass, radius);
	geom = dCreateSphere(Space, radius);
	dBodySetMass(body, &m);
	dGeomSetBody(geom, body);

}
void Box::initialize(dBodyID& body, dGeomID& geom) const
{
	Shape::initialize(body, geom);

	dMatrix3 R;
	dMass m;

	dMassSetBoxTotal(&m, mass, sides.x, sides.y, sides.z);
	geom = dCreateBox(Space, sides.x, sides.y, sides.z);
	dBodySetMass(body, &m);
	dGeomSetBody(geom, body);
}
