#ifndef JOINT_H
#define JOINT_H

#define dSINGLE

#include "VECTOR.h"
#include "globals.h"
#include <ode/ode.h>
#include <iostream>
#include <string>
#include <cmath>

class Optimization;
struct Object;

class Joint
{


	public:
		void initialize(Joint_Type t, Joint_Enum e) {type = t; name = e; currentTorque = VECTOR(0,0,0);}

		virtual void create(const dBodyID& parent, const dBodyID& child) = 0;
		virtual void create_pose() = 0;
		virtual void pose() = 0;
		virtual void setHingePose(dReal, dReal, dReal, dReal) = 0;
		virtual void setPoseOptimization(Optimization* o) = 0;
		virtual dReal getRate() { return 0; }

		virtual void update() { return; }
		virtual bool isStable(dReal tol) { return false; }

        virtual void reset() { currentTorque = VECTOR(0,0,0); }

        virtual bool save(std::ofstream &out) = 0;
        virtual bool load(std::ifstream &in) = 0;

		Joint_Type getType() { return type; }
		dJointID getJointID() { return jointID; }

		Joint_Enum getName() const { return name; }

		std::string getNameStr() const;

		void setParent(Object* p) { parent = p; }
		Object* getParent() { return parent; }
		void setChild(Object* c) { child = c; }
		Object* getChild() { return child; }

		bool isPoseActive() { return poseActive; }
		void setPoseActive(bool a) { poseActive = a; }

        void addCurrentTorque(VECTOR t) { currentTorque += t; }
        VECTOR getCurrentTorque() { return currentTorque; }
        void setCurrentTorque(VECTOR t) { currentTorque = t; }

		

	protected:
		bool poseActive;
		dJointID jointID;
		Joint_Enum name;
		Joint_Type type;
		VECTOR currentTorque;
		Object* parent;
		Object* child;

};

class Hinge : public Joint
{

	public:
		Hinge(Joint_Enum e, VECTOR a, int b, dReal min, dReal max) { Joint::initialize(HINGE, e); anchor = a; axis = b; hi = max; lo = min; prev_rate = 0; curr_rate = 0;}


		void create(const dBodyID& parent, const dBodyID& child);

		void create_pose();
		void setHingePose( dReal optA = 0, dReal KP = 300, dReal KD = 30, dReal optR = 0) { optAngle = optA; kp = KP; kd = KD; optRate = optR; }
		void setPoseOptimization(Optimization* o);

		virtual dReal getRate() { return (curr_rate + prev_rate)/2.0; }

		virtual void update() { prev_rate = curr_rate; curr_rate = dJointGetHingeAngleRate(jointID); }

		virtual bool isStable(dReal tol);

        bool save(std::ofstream &out);
        bool load(std::ifstream &in);


        dReal getOptAngle() { return optAngle; }
	

		void pose();

	private:

		// for 'posing'
		dReal kp, kd;
		dReal optAngle, optRate;
		Optimization* opt;
		dReal prev_rate;
		dReal curr_rate;


		dReal hi, lo;
		VECTOR anchor;
		int axis;
};

class Fixed : public Joint
{

	public:
		Fixed(Joint_Enum e) { Joint::initialize(FIXED, e); }
		void create(const dBodyID& parent, const dBodyID& child);
		void create_pose() {};
		void pose() {};
		void setHingePose(dReal a, dReal b, dReal c, dReal d) {  }
		void setPoseOptimization(Optimization* o) {}
        bool save(std::ofstream &out) { return false; };
        bool load(std::ifstream &in) { return false; };

};

#endif // JOINT_H
