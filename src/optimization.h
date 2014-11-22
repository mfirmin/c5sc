#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

/* This class represents an optimization to an action rule to adjust angle etc etc */

#define dSINGLE

#include <ode/ode.h>
#include "globals.h"
#include "human.h"
#include "joint.h"
#include "value.h"

class Optimization
{

	public:

		virtual dReal optimize() = 0;
        virtual bool writeToFile(std::ofstream&) = 0;

		bool active;


};

// center of mass feedback
class COMFB : public Optimization
{

	public:
		COMFB() { active = false; }
		COMFB(Value* a, Value* b, Joint* j, dBodyID c) {cd = a; cv = b; joint = j; com = c; joint_based = true; active = true;}
		COMFB(Value* a, Value* b, dBodyID p, dBodyID c) {cd = a; cv = b; part = p; com = c; joint_based = false; active = true;}
		dReal optimize();

		dReal getCD() {return cd->getdReal();}
        bool writeToFile(std::ofstream& ofs) { std::cerr << "COMFB shouldn't exist..." << std::endl; return false; }



	private:
		Value* cd;
		Value* cv;
		dBodyID com, part;
		Joint* joint;
		bool joint_based;


};

class COMFB2 : public Optimization
{

	public:
		COMFB2() { active = false; }
		COMFB2(Value* a, Value* b, Joint* j, const Human& h) {cd = a; cv = b; joint = j; human = &h; basis = JOINT; active = true;}
		COMFB2(Value* a, Value* b, dBodyID p, const Human& h) {cd = a; cv = b; part = p; human = &h; basis = PART; active = true;}
		COMFB2(Value* a, Value* b, const Human& h) {cd = a; cv = b; human = &h; basis = COP; active = true; }
		dReal optimize();
        bool writeToFile(std::ofstream&);


		dReal getCD() {return cd->getdReal();}
		dReal getCV() {return cv->getdReal();}
        std::string getCDwrite() { return cd->write(); }
        std::string getCVwrite() { return cv->write(); }
        Joint* getJoint() { return joint; }

        Basis getBasis() { return basis; }

	private:
		Value* cd;
	        Value* cv;
		dBodyID part;
		Joint* joint;
		const Human* human;
		Basis basis;


};

class inactiveOptimization : public Optimization
{

	public:
		inactiveOptimization() { active = false; }
		dReal optimize() {return -1;}
        bool writeToFile(std::ofstream&) { std::cerr << "shouldn't be reaching inactiveOptimization during write..." << std::endl; return false; };

};


#endif // OPTIMIZATION_H
