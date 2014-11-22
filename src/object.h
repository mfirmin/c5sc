#ifndef OBJECT_H
#define OBJECT_H

#define dSINGLE


#include <ode/ode.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "VECTOR.h"
#include "shape.h"
#include "globals.h"
#include "joint.h"

#define GEOMSPERBODY 1

class Object
{
    public:

        Object() { visible = true; collidable = true; }
        Object_Type getType() { return type; }

        Shape_Type shape_type;
        Part name;
        Shape* shape;
        dBodyID Body;
        dGeomID Geom[GEOMSPERBODY];
        Object* parent;
        Joint* joint2Parent;
        std::vector<Joint*> joints;
        dJointID virtualMotor;
        int meshLocation;

//        VECTOR currentTorque;

        bool groundContact();
        bool human_part;

        void reset();
        void load(std::ifstream&);
        bool save(std::ofstream&);

        void setFriction(dReal f) { friction = f; }

        dReal getFriction() { return friction; }

        bool isVisible() { return visible; }
        bool isCollidable() { return collidable; }

        void setVisible(bool v) { visible = v; }
        void setCollidable(bool c) { collidable = c; }

        ~Object();

    protected:
        Object_Type type;
        bool visible;
        bool collidable;
        dReal friction;


};


class Plane : public Object
{
    public:
        Plane(dReal x1_in, dReal y1_in, dReal x2_in, dReal y2_in);

        dReal getX1() { return x1; }
        dReal getX2() { return x2; }
        dReal getY1() { return y1; }
        dReal getY2() { return y2; }

    private:
        dReal x1, x2, y1, y2;

};


/*
Object createCapsule(dReal, dReal, dReal, 
			const VECTOR, 
			const VECTOR,
		       	const dReal*);

Object createSphere(dReal, dReal,
			const VECTOR,
			const VECTOR,
			const dReal*);

Object createBox(const VECTOR, dReal, 
			const VECTOR, 
			const VECTOR, 
			const dReal*);
*/
dJointID createHingeJoint(dBodyID, dBodyID, VECTOR, int);

dJointID createHingeMotor(dBodyID, dBodyID, int, dReal, dReal);

dJointID createBallMotor(dBodyID, dBodyID, const VECTOR, const VECTOR);

dJointID createLMotor(dBodyID, dBodyID, const VECTOR, const VECTOR);

dJointID createVirtualAMotor(dBodyID);

#endif // OBJECT_H
