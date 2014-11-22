#ifndef HUMAN_H
#define HUMAN_H

#define dSINGLE

#include "object.h"
#include <string>
#include "VECTOR.h"
#include <ode/ode.h>
#include <vector>
#include "globals.h"
#include "joint.h"
#include "shape.h"
#include "math.h"
#include <utility>


class Human
{

	public: 

		Human();
		Human(VECTOR);


		void reset();
		bool save(std::string) const;
		bool load(std::string);

		VECTOR getCoM() const;
		VECTOR getCoMVel() { return CoM_vel; };
		dReal getCoMVelMagnitude() { return sqrt( CoM_vel.x*CoM_vel.x + CoM_vel.y*CoM_vel.y + CoM_vel.z*CoM_vel.z); }
		dReal getCoMAccMagnitude() { return sqrt( CoM_acc.x*CoM_vel.x + CoM_acc.y*CoM_acc.y + CoM_acc.z*CoM_acc.z); }
		dReal getMass() const;
		void updateCoM();

		bool isStable(dReal);

		void reportState(std::string, std::string, int);
		void compareState(std::string);


		Object* addNewBody(Part, Object* parent, Joint* joint2Parent, const Shape* shape);

		dBodyID getPartFromString(std::string) const;
		dGeomID getGeomFromString(std::string) const;
		Joint* getJointFromString(std::string) const;
		Object* const getObjectFromString(std::string) const;


		void findJointPathHelper(Object* from, Joint const * to, std::vector<std::pair<Joint*, bool> > &path, bool* visited) const;
		void findJointPath(Object* from, Joint const * to, std::vector<std::pair<Joint*, bool> > &path) const;

        std::vector<Object*> getContactPoints() const;

        void updateEnergy(float);
        float getEnergy() { return energy; }


		VECTOR prev_CoM;
		VECTOR prev_prev_CoM;
		VECTOR CoM_acc;
		VECTOR CoM_vel;


		Object* parts[PART_COUNT];
		Joint* joints[JOINT_COUNT];


		// Virtual (connected to world) motors
		dJointID uTorso2world_M, lTorso2world_M, head2world_M, neck2world_M,
			 rThigh2world_M, lThigh2world_M, rShin2world_M, lShin2world_M,
 			 rArm2world_M, lArm2world_M, rForearm2world_M, lForearm2world_M,
		   	 rFoot2world_M, lFoot2world_M, rHand2world_M, lHand2world_M;

		// Between torso part joints/motors
		//dJointID torso2upperTorso;
	
	// Constant Definitions for body parts.

	static constexpr dReal HEAD_UPPER_RADIUS = 0.1;
	static constexpr dReal HEAD_LOWER_RADIUS = 0.08;
	static constexpr dReal HEAD_LENGTH = 0.11;

	static constexpr dReal HEAD_WEIGHT = 4.5;


	static constexpr dReal NECK_UPPER_RADIUS = 0.015;
	static constexpr dReal NECK_LOWER_RADIUS = 0.015;
	static constexpr dReal NECK_LENGTH = 0.04;

	static constexpr dReal NECK_WEIGHT = .5;


	static constexpr dReal U_TORSO_UPPER_RADIUS = 0.1;
	static constexpr dReal U_TORSO_LOWER_RADIUS = 0.07;
	static constexpr dReal U_TORSO_LENGTH = 0.3;

	static constexpr dReal U_TORSO_WEIGHT = 16.0;

	static constexpr dReal L_TORSO_UPPER_RADIUS = 0.12;
	static constexpr dReal L_TORSO_LOWER_RADIUS = 0.10;
	static constexpr dReal L_TORSO_LENGTH = 0.065;

	static constexpr dReal L_TORSO_WEIGHT = 7.0;

	static constexpr dReal PELVIS_UPPER_RADIUS = 0.06;
	static constexpr dReal PELVIS_LOWER_RADIUS = 0.05;
	static constexpr dReal PELVIS_LENGTH = 0.06;

	static constexpr dReal PELVIS_WEIGHT = 6.5;

	static constexpr dReal ARM_UPPER_RADIUS = 0.05;
	static constexpr dReal ARM_LOWER_RADIUS = 0.027;
	static constexpr dReal ARM_LENGTH = 0.303;

	static constexpr dReal ARM_WEIGHT = 2;

	static constexpr dReal FOREARM_UPPER_RADIUS = 0.032;
	static constexpr dReal FOREARM_LOWER_RADIUS = 0.016;
	static constexpr dReal FOREARM_LENGTH = 0.232;

	static constexpr dReal FOREARM_WEIGHT = 1;

	// should be 0.14 and 0.05, but that needs a longer pelvis.
	static constexpr dReal THIGH_UPPER_RADIUS = 0.07; 
	static constexpr dReal THIGH_LOWER_RADIUS = 0.03;
	static constexpr dReal THIGH_LENGTH = 0.4;

	static constexpr dReal THIGH_WEIGHT = 7;

	static constexpr dReal SHIN_UPPER_RADIUS = 0.045;
	static constexpr dReal SHIN_LOWER_RADIUS = 0.022;

	static constexpr dReal SHIN_LENGTH = 0.433;

	static constexpr dReal SHIN_WEIGHT = 3;

	static constexpr dReal FOOT_X = 0.18; // .07
	static constexpr dReal FOOT_Y = 0.05;
	static constexpr dReal FOOT_Z = .07; // .2

	static constexpr dReal FOOT_WEIGHT = 1;

	static constexpr dReal HAND_X = 0.044;
	static constexpr dReal HAND_Y = 0.16;
	static constexpr dReal HAND_Z = 0.10;

	static constexpr dReal HAND_WEIGHT = .5;

    private:
        float energy;

};

#endif // HUMAN_H
