/* ------------------------
   *
   *  File: human.cpp
   *  Author: Michael Firmin
   *  
   *  Description: Create humanoid character, all ode bodies and joints
   *
   -----------------------*/


#define dSINGLE

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <ode/ode.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>

#include <cmath>
#include <string>

#include "human.h"
#include "shape.h"
#include "globals.h"
#include "VECTOR.h"
#include "optimization.h"
#include "joint.h"
#include "object.h"
#include "environment.h"
#include "entity.h"

// Base Constructor (atm, does nothing)
Human::Human()
{

	//Human(VECTOR(0, 2, -10));


}

// Main constructor
// Creates all human body parts and joints given a root position
// Dimensions of human defined in human.h (as of Jul 4 2013)
Human::Human(VECTOR pelvis_pos)
{



	// Default velocity and rotation
	VECTOR vel; vel.x = 0; vel.y = 0; vel.z = 0;

	dReal rot[4]; rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;

	//Default positions of all body parts.

	//VECTOR upperTorso_pos = uTorso_pos + VECTOR(0, 0.5*TORSO_LENGTH + 0.5*TORSO_UPPER_RADIUS + SHOULDERS_RADIUS, 0);

	VECTOR rHip_pos = pelvis_pos + VECTOR(0,-0.027, THIGH_UPPER_RADIUS);
	VECTOR rThigh_pos = rHip_pos + VECTOR(0.002, -.204, 0.0);
	VECTOR rKnee_pos = rThigh_pos + VECTOR(-0.002, -0.226, 0.01);
	VECTOR rShin_pos = rKnee_pos + VECTOR(0.002, -0.215,0);
	VECTOR rAnkle_pos = rShin_pos + VECTOR(-0.003, -0.236, 0.01);
	VECTOR rFoot_pos = rAnkle_pos + VECTOR(0.065, -0.017, 0);

	VECTOR lHip_pos = pelvis_pos + VECTOR(0,-0.027, -1.*THIGH_UPPER_RADIUS);
	VECTOR lThigh_pos = lHip_pos + VECTOR(0.002, -.204, 0);
	VECTOR lKnee_pos = lThigh_pos + VECTOR(-0.002, -0.226, 0.01);
	VECTOR lShin_pos = lKnee_pos + VECTOR(0.002, -0.215,0);
	VECTOR lAnkle_pos = lShin_pos + VECTOR(-0.003, -0.236, 0.01);
	VECTOR lFoot_pos = lAnkle_pos + VECTOR(0.065, -0.017, 0);

	VECTOR waist_pos = pelvis_pos + VECTOR(0,0.045,0.01);
	VECTOR lTorso_pos = waist_pos + VECTOR(0,0.049,0);
	VECTOR joint_torso_pos = lTorso_pos + VECTOR(0,0.053,0.01);
	VECTOR uTorso_pos = joint_torso_pos + VECTOR(-0.001,0.23,0);
	
	VECTOR uTorso2neck_pos = uTorso_pos + VECTOR(-0.001,0.232,0.01);
	VECTOR neck_pos = uTorso2neck_pos + VECTOR(0,0.015,0);
	VECTOR neck2head_pos = neck_pos + VECTOR(0.001, 0.014, 0.01);
	VECTOR head_pos = neck2head_pos + VECTOR(0.000, 0.14, 0);

	VECTOR rShoulder_pos = uTorso_pos + VECTOR(0.001, 0.148, U_TORSO_UPPER_RADIUS);
	VECTOR rArm_pos = rShoulder_pos + VECTOR(-0.001, -0.128, 0);
	VECTOR rElbow_pos = rArm_pos + VECTOR(0, -.173, 0.05);
	VECTOR rForearm_pos = rElbow_pos + VECTOR(0, -0.116, 0);
	VECTOR rWrist_pos = rForearm_pos + VECTOR(-0.004, -0.134, 0.05);
	VECTOR rHand_pos = rWrist_pos + VECTOR(0.001,-0.061,0);

	VECTOR lShoulder_pos = uTorso_pos + VECTOR(0.001, 0.148, -1.*U_TORSO_UPPER_RADIUS);
	VECTOR lArm_pos = lShoulder_pos + VECTOR(-0.001, -0.128, 0);
	VECTOR lElbow_pos = lArm_pos + VECTOR(0, -.173, 0.005);
	VECTOR lForearm_pos = lElbow_pos + VECTOR(0, -.116, 0);
	VECTOR lWrist_pos = lForearm_pos + VECTOR(-0.004, -0.134, 0.005);
	VECTOR lHand_pos = lWrist_pos + VECTOR(0.001,-0.061,0);



	// Joint Position. (used for hinge anchors (fixed joints do not need this))
	VECTOR pos;

	vel.x = 0; vel.y = 0; vel.z = 0;
	rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;

	parts[PELVIS] = addNewBody(PELVIS, NULL, NULL, new Sphere(PELVIS_WEIGHT, pelvis_pos, vel, rot, PELVIS_LENGTH));


	joints[WAIST] = new Hinge(WAIST, waist_pos, 2, -PI/8.0, PI/8.0);
	joints[WAIST]->setParent(parts[PELVIS]);
	joints[WAIST]->create_pose();

	/* LOWER_TORSO */
	parts[L_TORSO] = addNewBody(L_TORSO, parts[PELVIS], joints[WAIST], new Sphere(L_TORSO_WEIGHT, lTorso_pos, vel, rot, L_TORSO_LENGTH));

	parts[PELVIS]->parent = parts[PELVIS];
	parts[PELVIS]->joint2Parent = joints[WAIST];

	joints[WAIST]->setChild(parts[L_TORSO]);

	/* UPPER TORSO */

	joints[L_TORSO2U_TORSO] = new Hinge(L_TORSO2U_TORSO, joint_torso_pos, 2, -PI/8.0, PI/8.0);
	joints[L_TORSO2U_TORSO]->create_pose();

	parts[U_TORSO] = addNewBody(U_TORSO, parts[L_TORSO], joints[L_TORSO2U_TORSO], new Capsule(U_TORSO_WEIGHT, uTorso_pos, vel, rot, U_TORSO_LENGTH, U_TORSO_UPPER_RADIUS, U_TORSO_LOWER_RADIUS));

	joints[L_TORSO2U_TORSO]->setParent(parts[L_TORSO]);
	joints[L_TORSO2U_TORSO]->setChild(parts[U_TORSO]);


	/* RIGHT ARM */
	rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;

	// +0.001 needed on joint limit because...?
	joints[R_SHOULDER] = new Hinge(R_SHOULDER, rShoulder_pos, 2, -PI+0.001, PI/2.0);
	joints[R_SHOULDER]->create_pose();

	parts[R_ARM] = addNewBody(R_ARM, parts[U_TORSO], joints[R_SHOULDER], new Capsule(ARM_WEIGHT, rArm_pos, vel, rot, ARM_LENGTH, ARM_UPPER_RADIUS, ARM_LOWER_RADIUS));

	joints[R_SHOULDER]->setParent(parts[U_TORSO]);
	joints[R_SHOULDER]->setChild(parts[R_ARM]);
	
	/* RIGHT FOREARM */

	joints[R_ELBOW] = new Hinge(R_ELBOW, rElbow_pos, 2, -7.0*PI/8.0, 0.0);
	joints[R_ELBOW]->create_pose();

	parts[R_FOREARM] = addNewBody(R_FOREARM, parts[R_ARM], joints[R_ELBOW], new Capsule(FOREARM_WEIGHT, rForearm_pos, vel, rot, FOREARM_LENGTH, FOREARM_UPPER_RADIUS, FOREARM_LOWER_RADIUS));

	joints[R_ELBOW]->setParent(parts[R_ARM]);
	joints[R_ELBOW]->setChild(parts[R_FOREARM]);

	/* LEFT ARM */

	joints[L_SHOULDER] = new Hinge(L_SHOULDER, lShoulder_pos, 2, -PI+0.001, PI/2.0);
	joints[L_SHOULDER]->create_pose();

	parts[L_ARM] = addNewBody(L_ARM, parts[U_TORSO], joints[L_SHOULDER], new Capsule(ARM_WEIGHT, lArm_pos, vel, rot, ARM_LENGTH, ARM_UPPER_RADIUS, ARM_LOWER_RADIUS));

	joints[L_SHOULDER]->setParent(parts[U_TORSO]);
	joints[L_SHOULDER]->setChild(parts[L_ARM]);

	/* LEFT FOREARM */
	joints[L_ELBOW] = new Hinge(L_ELBOW, lElbow_pos, 2, -7.0*PI/8.0, 0.0);
	joints[L_ELBOW]->create_pose();

	parts[L_FOREARM] = addNewBody(L_FOREARM, parts[L_ARM], joints[L_ELBOW], new Capsule(FOREARM_WEIGHT, lForearm_pos, vel, rot, FOREARM_LENGTH, FOREARM_UPPER_RADIUS, FOREARM_LOWER_RADIUS));

	joints[L_ELBOW]->setParent(parts[L_ARM]);
	joints[L_ELBOW]->setChild(parts[L_FOREARM]);


	/* NECK */
	rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;
	joints[U_TORSO2NECK] = new Hinge(U_TORSO2NECK, uTorso2neck_pos, 2, 0, 0);
	joints[U_TORSO2NECK]->create_pose();

	parts[NECK] = addNewBody(NECK, parts[U_TORSO], joints[U_TORSO2NECK], new Sphere(NECK_WEIGHT, neck_pos, vel, rot, NECK_LENGTH));

	joints[U_TORSO2NECK]->setParent(parts[U_TORSO]);
	joints[U_TORSO2NECK]->setChild(parts[NECK]);

	rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;
	joints[NECK2HEAD] = new Hinge(NECK2HEAD, neck2head_pos, 2, -PI/4.0, PI/4.0);
	joints[NECK2HEAD]->create_pose();

	parts[HEAD] = addNewBody(HEAD, parts[NECK], joints[NECK2HEAD], new Capsule(HEAD_WEIGHT, head_pos, vel, rot, HEAD_LENGTH, HEAD_UPPER_RADIUS, HEAD_LOWER_RADIUS));

	joints[NECK2HEAD]->setParent(parts[NECK]);
	joints[NECK2HEAD]->setChild(parts[HEAD]);


	/* RIGHT THIGH */
	rot[0] = 1; rot[1] = 0; rot[2] = 0; rot[3] = PI/2.0;
	joints[R_HIP] = new Hinge(R_HIP, rHip_pos, 2, -3.0*PI/4.0, PI/4.0);
	joints[R_HIP]->create_pose();

	parts[R_THIGH] = addNewBody(R_THIGH, parts[PELVIS], joints[R_HIP], new Capsule(THIGH_WEIGHT, rThigh_pos, vel, rot, THIGH_LENGTH, THIGH_UPPER_RADIUS, THIGH_LOWER_RADIUS));

	joints[R_HIP]->setParent(parts[PELVIS]);
	joints[R_HIP]->setChild(parts[R_THIGH]);

	/* LEFT THIGH */
	joints[L_HIP] = new Hinge(L_HIP, lHip_pos, 2, -3.0*PI/4.0, PI/4.0);
	joints[L_HIP]->create_pose();

	parts[L_THIGH] = addNewBody(L_THIGH, parts[PELVIS], joints[L_HIP], new Capsule(THIGH_WEIGHT, lThigh_pos, vel, rot, THIGH_LENGTH, THIGH_UPPER_RADIUS, THIGH_LOWER_RADIUS));

	joints[L_HIP]->setParent(parts[PELVIS]);
	joints[L_HIP]->setChild(parts[L_THIGH]);

	/* RIGHT SHIN */
	joints[R_KNEE] = new Hinge(R_KNEE, rKnee_pos, 2, 0.0, 7.0*PI/8.0);
	joints[R_KNEE]->create_pose();

	parts[R_SHIN] = addNewBody(R_SHIN, parts[R_THIGH], joints[R_KNEE], new Capsule(SHIN_WEIGHT, rShin_pos, vel, rot, SHIN_LENGTH, SHIN_UPPER_RADIUS, SHIN_LOWER_RADIUS));

	joints[R_KNEE]->setParent(parts[R_THIGH]);
	joints[R_KNEE]->setChild(parts[R_SHIN]);

	/* LEFT SHIN */
	joints[L_KNEE] = new Hinge(L_KNEE, lKnee_pos, 2, 0.0, 7.0*PI/8.0);
	joints[L_KNEE]->create_pose();

	parts[L_SHIN] = addNewBody(L_SHIN, parts[L_THIGH], joints[L_KNEE], new Capsule(SHIN_WEIGHT, lShin_pos, vel, rot, SHIN_LENGTH, SHIN_UPPER_RADIUS, SHIN_LOWER_RADIUS));

	joints[L_KNEE]->setParent(parts[L_THIGH]);
	joints[L_KNEE]->setChild(parts[L_SHIN]);

	/* RIGHT FOOT */

	rot[0] = 0; rot[1] = 1; rot[2] = 0; rot[3] = PI/2.0;
	rot[3] = 0;
	VECTOR FOOT_SIDES; 
	FOOT_SIDES.x = FOOT_X; FOOT_SIDES.y = FOOT_Y; FOOT_SIDES.z = FOOT_Z;

	joints[R_ANKLE] = new Hinge(R_ANKLE, rAnkle_pos, 2, -PI/3.0, PI/3.0);
	joints[R_ANKLE]->create_pose();

	parts[R_FOOT] = addNewBody(R_FOOT, parts[R_SHIN], joints[R_ANKLE], new Box(FOOT_WEIGHT, rFoot_pos, vel, rot, FOOT_SIDES));

	joints[R_ANKLE]->setParent(parts[R_SHIN]);
	joints[R_ANKLE]->setChild(parts[R_FOOT]);

	/* LEFT FOOT */
	joints[L_ANKLE] = new Hinge(L_ANKLE, lAnkle_pos, 2, -PI/3.0, PI/3.0);
	joints[L_ANKLE]->create_pose();

	parts[L_FOOT] = addNewBody(L_FOOT, parts[L_SHIN], joints[L_ANKLE], new Box(FOOT_WEIGHT, lFoot_pos, vel, rot, FOOT_SIDES));

	joints[L_ANKLE]->setParent(parts[L_SHIN]);
	joints[L_ANKLE]->setChild(parts[L_FOOT]);


	VECTOR HAND_SIDES; 
	HAND_SIDES.x = HAND_X; HAND_SIDES.y = HAND_Y; HAND_SIDES.z = HAND_Z;
	
	/* LEFT HAND */
	joints[L_WRIST] = new Hinge(L_WRIST, lWrist_pos, 2, -PI/2.0, PI/2.0);
	joints[L_WRIST]->create_pose();

	parts[L_HAND] = addNewBody(L_HAND, parts[L_FOREARM], joints[L_WRIST], new Box(HAND_WEIGHT, lHand_pos, vel, rot, HAND_SIDES));

	joints[L_WRIST]->setParent(parts[L_FOREARM]);
	joints[L_WRIST]->setChild(parts[L_HAND]);

	/* RIGHT HAND */
	joints[R_WRIST] = new Hinge(R_WRIST, rWrist_pos, 2, -PI/2.0, PI/2.0);
	joints[R_WRIST]->create_pose();

	parts[R_HAND] = addNewBody(R_HAND, parts[R_FOREARM], joints[R_WRIST], new Box(HAND_WEIGHT, rHand_pos, vel, rot, HAND_SIDES));

	joints[R_WRIST]->setParent(parts[R_FOREARM]);
	joints[R_WRIST]->setChild(parts[R_HAND]);

	
	/* --- VIRTUAL MOTORS --- */ 


	// Virtual AMotors to world. (used in Virtual PD controllers)

	uTorso2world_M = createVirtualAMotor(parts[U_TORSO]->Body);
	parts[U_TORSO]->virtualMotor = uTorso2world_M;
	lTorso2world_M = createVirtualAMotor(parts[L_TORSO]->Body);
	parts[L_TORSO]->virtualMotor = lTorso2world_M;

	rThigh2world_M = createVirtualAMotor(parts[R_THIGH]->Body);
	parts[R_THIGH]->virtualMotor = rThigh2world_M;
	lThigh2world_M = createVirtualAMotor(parts[L_THIGH]->Body);
	parts[L_THIGH]->virtualMotor = lThigh2world_M;
	
	// For some reason some of these being on causes ground penetration. (esp the feet).
	// doesn't seem to be doing it anymore as of Jul 4 2013

	head2world_M = createVirtualAMotor(parts[HEAD]->Body);
	parts[HEAD]->virtualMotor = head2world_M;
	neck2world_M = createVirtualAMotor(parts[NECK]->Body);
	parts[NECK]->virtualMotor = neck2world_M;

	rArm2world_M = createVirtualAMotor(parts[R_ARM]->Body);
	parts[R_ARM]->virtualMotor = rArm2world_M;
	lArm2world_M = createVirtualAMotor(parts[L_ARM]->Body);
	parts[L_ARM]->virtualMotor = lArm2world_M;
	rForearm2world_M = createVirtualAMotor(parts[R_FOREARM]->Body);
	parts[R_FOREARM]->virtualMotor = rForearm2world_M;
	lForearm2world_M = createVirtualAMotor(parts[L_FOREARM]->Body);
	parts[L_FOREARM]->virtualMotor = lForearm2world_M;
	rShin2world_M = createVirtualAMotor(parts[R_SHIN]->Body);
	parts[R_SHIN]->virtualMotor = rShin2world_M;
	lShin2world_M = createVirtualAMotor(parts[L_SHIN]->Body);
	parts[L_SHIN]->virtualMotor = lShin2world_M;
	rFoot2world_M = createVirtualAMotor(parts[R_FOOT]->Body);
	parts[R_FOOT]->virtualMotor = rFoot2world_M;
	lFoot2world_M = createVirtualAMotor(parts[L_FOOT]->Body);
	parts[L_FOOT]->virtualMotor = lFoot2world_M;
	rHand2world_M = createVirtualAMotor(parts[R_HAND]->Body);
	parts[R_HAND]->virtualMotor = rHand2world_M;
	lHand2world_M = createVirtualAMotor(parts[L_HAND]->Body);
	parts[L_HAND]->virtualMotor = lHand2world_M;

	prev_CoM = getCoM();
	prev_prev_CoM = getCoM();
	CoM_vel = VECTOR(0,0,0);
	CoM_acc = VECTOR(0,0,0);


    energy = 0;

}

void Human::updateEnergy(float s)
{

    energy = 0;

    for (int i = 0; i < JOINT_COUNT; i++)
    {
        energy += joints[i]->getCurrentTorque().z*joints[i]->getCurrentTorque().z;
    }

    energy *= s;

}

void Human::reset()
{

	for (int i = 0; i < PART_COUNT; i++)
	{
		parts[i]->reset();
	}

}

bool Human::save(std::string savename) const
{

	std::ofstream out;
	out.open(savename.c_str());

	if (!out)
		return false;

	out << prev_CoM.x << " " << prev_CoM.y << " " << prev_CoM.z << std::endl; 
	out << prev_prev_CoM.x << " " << prev_prev_CoM.y << " " << prev_prev_CoM.z << std::endl;
	out << CoM_acc.x << " " << CoM_acc.y << " " << CoM_acc.z << std::endl;
	out << CoM_vel.x << " " << CoM_vel.y << " " << CoM_vel.z << std::endl;
	

	for (int i = 0; i < PART_COUNT; i++)
	{
		if (!(parts[i]->save(out)))
			return false;
	}

    // record state of joint PD Controllers.
    for (int i = 0; i < JOINT_COUNT; i++)
    {
        if (!(joints[i]->save(out)))
            return false;
    }

	out.close();

	return true;


}

bool Human::load(std::string loadfile)
{

	std::ifstream in;
	in.open(loadfile.c_str());

	if (!in)
		return false;

	
	in >> prev_CoM.x >> prev_CoM.y >> prev_CoM.z; 
	in >> prev_prev_CoM.x >> prev_prev_CoM.y >> prev_prev_CoM.z;
	in >> CoM_acc.x >> CoM_acc.y >> CoM_acc.z;
	in >> CoM_vel.x >> CoM_vel.y >> CoM_vel.z;


	for (int i = 0; i < PART_COUNT; i++)
	{
		parts[i]->load(in);
	}
    for (int i = 0; i < JOINT_COUNT; i++)
    {
        if (!(joints[i]->load(in)))
            return false;
    }

	in.close();

    /*
	for (int i = 0; i < JOINT_COUNT; i++)
	{
		joints[i]->setPoseActive(false);
	}
    */
	
	//updateCoM();


	return true;

}

void Human::updateCoM()
{

	VECTOR temp = getCoM();

	CoM_vel = (temp-prev_prev_CoM)/(2.*STEPSIZE);
	CoM_acc = (temp - prev_CoM*2.0 + prev_prev_CoM)/(STEPSIZE*STEPSIZE);

	prev_prev_CoM = prev_CoM;
	prev_CoM = temp;


	for (int i = 0; i < JOINT_COUNT; i++)
	{
		joints[i]->update();
	}

}

dReal Human::getMass() const
{
	return HEAD_WEIGHT + NECK_WEIGHT + U_TORSO_WEIGHT + L_TORSO_WEIGHT + PELVIS_WEIGHT+2*ARM_WEIGHT +
		2*FOREARM_WEIGHT + 2*THIGH_WEIGHT + 2*SHIN_WEIGHT + 2*FOOT_WEIGHT + 2*HAND_WEIGHT;
}

VECTOR Human::getCoM() const
{

	VECTOR pos;

	pos = VECTOR(dBodyGetPosition(parts[HEAD]->Body))*(const dReal)HEAD_WEIGHT +
		VECTOR(dBodyGetPosition(parts[NECK]->Body))*(const dReal)NECK_WEIGHT +
		VECTOR(dBodyGetPosition(parts[U_TORSO]->Body))*(const dReal)U_TORSO_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_TORSO]->Body))*(const dReal)L_TORSO_WEIGHT +
		VECTOR(dBodyGetPosition(parts[PELVIS]->Body))*(const dReal)PELVIS_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_ARM]->Body))*(const dReal)ARM_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_ARM]->Body))*(const dReal)ARM_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_FOREARM]->Body))*(const dReal)FOREARM_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_FOREARM]->Body))*(const dReal)FOREARM_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_THIGH]->Body))*(const dReal)THIGH_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_THIGH]->Body))*(const dReal)THIGH_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_SHIN]->Body))*(const dReal)SHIN_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_SHIN]->Body))*(const dReal)SHIN_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_FOOT]->Body))*(const dReal)FOOT_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_FOOT]->Body))*(const dReal)FOOT_WEIGHT +
		VECTOR(dBodyGetPosition(parts[R_HAND]->Body))*(const dReal)HAND_WEIGHT +
		VECTOR(dBodyGetPosition(parts[L_HAND]->Body))*(const dReal)HAND_WEIGHT;

	pos = pos/getMass();
		

	return pos;

}



Object* const Human::getObjectFromString(std::string str) const
{

	int ret = getPartEnumFromString(str);
	if (ret != -1)
		return parts[ret];
	else
	{
	//	std::cerr << "Improper body part specification: " << str << std::endl;
		return NULL;
	}

}

/* -- getPartFromString(std::string) -- */
// Takes in a string and returns the dBodyID corresponding to it.
// Primarily used to convert strings read in by the file reader.
dBodyID Human::getPartFromString(std::string str) const
{

	int ret = getPartEnumFromString(str);
	if (ret != -1)
		return parts[ret]->Body;
	else
	{
		std::cerr << "Improper body part specification" << std::endl;
		return dBodyID();
	}
}

/* -- getPartFromString(std::string) -- */
// Takes in a string and returns the dGeomID corresponding to it.
// Primarily used to convert strings read in by the file reader.
dGeomID Human::getGeomFromString(std::string str) const
{

	int ret = getPartEnumFromString(str);
	if (ret != -1)
		return parts[ret]->Geom[0];
	else
	{
	//	std::cerr << "Improper body part specification" << std::endl;
		return dGeomID();
	}
}

/* -- getPartFromString(std::string) -- */
// Takes in a string and returns the dGeomID corresponding to it.
// Primarily used to convert strings read in by the file reader.
Joint* Human::getJointFromString(std::string str) const
{

	int ret = getJointEnumFromString(str);
	if (ret != -1)
		return joints[ret];
	else
	{
		std::cerr << "Improper joint specification" << std::endl;
		return NULL;
	}
}


/* -- addNewBody(---) -- */
// Used to add a new body to the human.
// Given a pointer to a parent object (NULL for the root), and a pointer to a joint
// And a shape object (basic geometry for the part)
// creates and assigns ode IDs to new object and joint.
// Returns the created object (body part)
Object* Human::addNewBody(Part part_enum, Object* parent, Joint* joint2Parent, const Shape* shape)
{


	Object* ret = new Object();
	ret->Body = dBodyCreate(World);

	ret->name = part_enum;
	ret->parent = parent;
	ret->shape = (Shape*)shape;

	ret->human_part = true;

	ret->setFriction(-1);

	shape->initialize(ret->Body, ret->Geom[0]);
	geom2obj.insert(std::pair<dGeomID, Object*>(ret->Geom[0], ret));

	if (joint2Parent != NULL)
	{
		joint2Parent->create(ret->parent->Body, ret->Body);

		parent->joints.push_back(joint2Parent);
		ret->joints.push_back(joint2Parent);

		ret->joint2Parent = joint2Parent;
	}

	return ret;

}

void Human::compareState(std::string infile)
{

	std::cout << std::endl << "comparing state . . . " << std::endl;


	std::ifstream input;

	input.open(infile.c_str());


	VECTOR vel_expected;

	input >> vel_expected.x >> vel_expected.y >> vel_expected.z;


	if (CoM_vel.dist(vel_expected) > 100)
	{
		std::cout << "CoM Vel very different" << std::endl;
	}


	for (int i = 0; i < 18; i++)
		input.ignore(32,'\n');

	dReal contact;


	for (int i = 0; i < PART_COUNT; i++)
	{
		input >> contact;
		if (!( ( parts[i]->groundContact() && contact == 1) || (!parts[i]->groundContact() && contact == 0)))
		{
			std::cerr << "Contact info doesn't match for part" << i << std::endl;
		}
	}

/*
	parts[HEAD]->groundContact() ? output << "1 " : output << "0 ";
	parts[NECK]->groundContact() ? output << "1 " : output << "0 ";
	parts[U_TORSO]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_TORSO]->groundContact() ? output << "1 " : output << "0 ";
	parts[PELVIS]>groundContact() ? output << "1 " : output << "0 ";
	parts[R_ARM]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_ARM]->groundContact() ? output << "1 " : output << "0 ";
	parts[R_FOREARM]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_FOREARM]->groundContact() ? output << "1 " : output << "0 ";
	parts[R_HAND]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_HAND]->groundContact() ? output << "1 " : output << "0 ";
	parts[R_THIGH]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_THIGH]->groundContact() ? output << "1 " : output << "0 ";
	parts[R_SHIN]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_SHIN]->groundContact() ? output << "1 " : output << "0 ";
	parts[R_FOOT]->groundContact() ? output << "1 " : output << "0 ";
	parts[L_FOOT]->groundContact() ? output << "1 " : output << "0 ";
*/
}

void Human::reportState(std::string outfile, std::string controllerName, int nextPhase)
{

	std::ofstream output;

	output.open(outfile.c_str());


	if (!output)
		return;

	output << controllerName << " " << nextPhase << std::endl;

	output << CoM_vel.x << " " << CoM_vel.y << " " << CoM_vel.z << std::endl;


	for (int i = 0; i < JOINT_COUNT; i++)
	{
		output << dJointGetHingeAngle(joints[i]->getJointID()) << " " << joints[i]->getRate() << std::endl;

	}

	for (int i = 0; i < PART_COUNT; i++)
	{
		parts[i]->groundContact() ? output << "1 " : output << "0 ";
	}



	output.close();

	return;


}

bool Human::isStable(dReal tol)
{
//	if (std::abs(getCoMVelMagnitude()) >= tol)
//		std::cout << "CoM Vel is not stable: " << getCoMVelMagnitude() << std::endl; 


	return ( std::abs(getCoMVelMagnitude()) < tol &&
			joints[WAIST]->isStable(tol) &&
			joints[L_TORSO2U_TORSO]->isStable(tol) &&
			
			joints[NECK2HEAD]->isStable(tol) &&
			joints[U_TORSO2NECK]->isStable(tol) &&

			joints[L_SHOULDER]->isStable(tol) &&
			joints[R_SHOULDER]->isStable(tol) &&

			joints[R_ELBOW]->isStable(tol) &&
			joints[L_ELBOW]->isStable(tol) &&

			joints[R_HIP]->isStable(tol) &&
			joints[L_HIP]->isStable(tol) &&

			joints[R_KNEE]->isStable(tol) &&
			joints[L_KNEE]->isStable(tol) &&

			joints[R_ANKLE]->isStable(tol) &&
			joints[L_ANKLE]->isStable(tol) &&

			joints[R_WRIST]->isStable(tol) &&
			joints[L_WRIST]->isStable(tol) );

}


void Human::findJointPathHelper(Object* from, Joint const * to, std::vector<std::pair<Joint*, bool> > &path, bool* visited) const
{


	for ( std::vector<Joint*>::iterator it = from->joints.begin(); it!= from->joints.end(); it++)
	{

		if (!visited[(*it)->getName()])
		{
			visited[(*it)->getName()] = true;
		

			path.push_back(std::pair<Joint*, bool> (*it, (*it)->getChild()->name == from->name));
			// Case MATCH
			if ( (*it)->getName() == to->getName() )
			{
				return;
			}
			else
			{
				if ( (*it)->getParent()->name == from->name )
					findJointPathHelper((*it)->getChild(), to, path, visited);
				else if ( (*it)->getChild()->name == from->name )
					findJointPathHelper((*it)->getParent(), to, path, visited);
				else
				{
					std::cerr << "Error finding joint path" << std::endl;
					break;
				}

				if ( path.back().first->getName() == to->getName() )
					return;
			}

			path.pop_back();

		}


	}



	return;
}


void Human::findJointPath(Object* from, Joint const * to, std::vector<std::pair<Joint*, bool> > &path) const
{

	bool visited[JOINT_COUNT];

	for (int i = 0; i < JOINT_COUNT; i++)
	{
		visited[i] = false;
	}

	Human::findJointPathHelper(from, to, path, visited);

}

std::vector<Object*> Human::getContactPoints() const
{

    dContact temp;

    std::vector<Object*> ret;

    for (int i = 0; i < PART_COUNT; i++)
    {
        for (auto it = env->getEntities().begin(); it != env->getEntities().end(); it++)
        {
            for (auto  objIter = it->second->getBodies().begin(); objIter != it->second->getBodies().end(); objIter++)
            if (dCollide((*objIter)->Geom[0], parts[i]->Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
            {
                ret.push_back(parts[i]);
            }
        }
    }

    return ret;

} 
