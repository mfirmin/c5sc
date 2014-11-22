
#define dSINGLE

#include "VECTOR.h"
#include "globals.h"
#include "joint.h"
#include "optimization.h"
#include "object.h"
#include <iostream>
#include <fstream>

#include <ode/ode.h>

bool Hinge::isStable(dReal tol)
{


//	if (std::abs(getRate()) >= tol)
//		std::cout << "Joint " << getNameStr() << " is not stable: " << getRate() << std::endl; 

	return (std::abs(getRate()) < tol); 
} 

void Hinge::create_pose()
{
	kp = 0; kd = 0; optAngle = 0; optRate = 0;
	opt = new inactiveOptimization();
}

void Hinge::setPoseOptimization(Optimization* o)
{
	opt = o;
}

void Hinge::create(const dBodyID& parent, const dBodyID& child)
{

	jointID = dJointCreateHinge(World, jointgroup);

	dJointAttach(jointID, parent, child);
	dJointSetHingeAnchor(jointID, anchor.x, anchor.y, anchor.z);

	if (axis == 0)
	{
		dJointSetHingeAxis(jointID, 1, 0, 0);
	}
	else if (axis == 1)
	{
		dJointSetHingeAxis(jointID, 0, 1, 0);
	}
	else if (axis == 2)
	{
		dJointSetHingeAxis(jointID, 0, 0, 1);
	}

	dJointSetHingeParam(jointID, dParamLoStop, lo);
	dJointSetHingeParam(jointID, dParamHiStop, hi);

}

void Hinge::pose()
{

	if (!poseActive)
		return;


	dReal currAngle = dJointGetHingeAngle(jointID);
	dReal currRate = dJointGetHingeAngleRate(jointID);
	//dReal currRate = getRate();

	dReal desAngle = optAngle;

	if (opt->active)
	{
		desAngle += opt->optimize();
	}

	VECTOR torque;

	torque.z = kp * (desAngle - currAngle) + kd * (optRate - currRate);
/*
	if (torque.z > TORQUE_LIMIT)
	{
		torque.z = TORQUE_LIMIT;
	}
	if (torque.z < -TORQUE_LIMIT)
	{
		torque.z = -TORQUE_LIMIT;
	}
*/
    currentTorque += VECTOR(0,0,torque.z);
/*
	{
		parent->currentTorque = parent->currentTorque + torque;
		child->currentTorque = child->currentTorque + torque*-1;
	}
*/
}

bool Hinge::save(std::ofstream &out)
{

	if (!out)
	{
		return false;
	}

    int pA; 
    poseActive ? pA = 1 : pA = 0;
    out << pA << " " << optAngle << " " << optRate << std::endl << kp << " " <<  kd << std::endl << prev_rate << std::endl;



    return true;

}

bool Hinge::load(std::ifstream &in)
{
    int pA;
    in >> pA; pA ? poseActive = true : poseActive = false;
    in >> optAngle >> optRate >> kp >> kd >> prev_rate;

    return true;

}

void Fixed::create(const dBodyID& parent, const dBodyID& child)
{

	jointID = dJointCreateFixed(World, jointgroup);
	dJointAttach(jointID, parent, child);
	dJointSetFixed(jointID);

}


// used when outputting a controller file (from stored data)
std::string Joint::getNameStr() const
{

    switch (name)
    {
        case NECK2HEAD:
            return "neck2head";
		case U_TORSO2NECK:
			return "uTorso2neck";
		case L_SHOULDER:
			return "lShoulder";
		case R_SHOULDER:
			return "rShoulder";
		case L_ELBOW:
			return "lElbow";
		case R_ELBOW:
			return "rElbow";
		case L_HIP:
			return "lHip";
		case R_HIP:
			return "rHip";
		case L_KNEE:
			return "lKnee";
		case R_KNEE:
			return "rKnee";
		case L_ANKLE:
			return "lAnkle";
		case R_ANKLE:
			return "rAnkle";
		case L_TORSO2U_TORSO:
			return "lTorso2uTorso";
		case WAIST:
			return "waist";
		case L_WRIST:
			return "lWrist";
		case R_WRIST:
			return "rWrist";
	    default:
            return "FAIL";
    }
    /*
    switch (name)
    {
        case NECK2HEAD:
            return "NECK2HEAD";

		case U_TORSO2NECK:
			return "U_TORSO2NECK";
		case L_SHOULDER:
			return "L_SHOULDER";
		case R_SHOULDER:
			return "R_SHOULDER";
		case L_ELBOW:
			return "L_ELBOW";
		case R_ELBOW:
			return "R_ELBOW";
		case L_HIP:
			return "L_HIP";
		case R_HIP:
			return "R_HIP";
		case L_KNEE:
			return "L_KNEE";
		case R_KNEE:
			return "R_KNEE";
		case L_ANKLE:
			return "L_ANKLE";
		case R_ANKLE:
			return "R_ANKLE";
		case L_TORSO2U_TORSO:
			return "L_TORSO2U_TORSO";
		case WAIST:
			return "WAIST";
		case L_WRIST:
			return "L_WRIST";
		case R_WRIST:
			return "R_WRIST";
	    default:
            return "FAIL";
    }
    */


}
