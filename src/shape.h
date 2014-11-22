#ifndef SHAPE_H
#define SHAPE_H

#define dSINGLE

#include <ode/ode.h>
#include "VECTOR.h"

enum Shape_Type { CAPSULE, SPHERE, BOX };

class Shape
{

	public:

		virtual void initialize(dBodyID&, dGeomID&) const;

		Shape_Type getType() const {return type;}

		void reset(dBodyID&);

		dReal getMass() { return mass; }
		VECTOR getPos() { return pos; }
		VECTOR getVel() { return vel; }
		dReal* getRot() { return rot; }

	protected:
		Shape_Type type;
		// initial conditions.
		dReal mass;
		VECTOR pos, vel;
		dReal rot[4];
		dQuaternion quat;

		

};

class Capsule : public Shape
{
	public:
		Capsule () {}
		Capsule(dReal m, VECTOR p, VECTOR v, dReal* rotation, dReal l, dReal r1, dReal r2=-1);
		void initialize(dBodyID&, dGeomID&) const;
		dReal getRadius1() const {return rad1;}
		dReal getRadius2() const {return rad2;}
		dReal getLength() const {return length;}
	private:
		dReal rad1, rad2;
		dReal length;
};

class Sphere : public Shape
{
	public:
		Sphere(dReal m, VECTOR p, VECTOR v, dReal* rotation, dReal rad);
		void initialize(dBodyID&, dGeomID&) const;
		dReal getRadius() {return radius;}
	private:
		dReal radius;

};

class Box : public Shape
{
	public:
		Box(dReal m, VECTOR p, VECTOR v, dReal* rotation, VECTOR s);
		void initialize(dBodyID&, dGeomID&) const;
		VECTOR getSides() {return sides;}
	private:
		VECTOR sides;

};

#endif // SHAPE_H

