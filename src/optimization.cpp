

#define dSINGLE

#include <ode/ode.h>
#include <iostream>
#include "optimization.h"
#include "human.h"
#include "joint.h"


dReal COMFB::optimize()
{

	dReal d, v;

	if (joint_based)
	{
		dVector3 joint_anchor;
		dJointGetHingeAnchor(joint->getJointID(), joint_anchor);
		d = dBodyGetPosition(com)[0] - joint_anchor[0];
	}
	else
	{
		d = dBodyGetPosition(com)[0] - dBodyGetPosition(part)[0];
	}

	v = dBodyGetLinearVel(com)[0];

	return cd->getdReal() * d + cv->getdReal() * v;

}

dReal COMFB2::optimize()
{

	dReal d, v;


	if (basis == JOINT)
	{
		dVector3 joint_anchor;
		dJointGetHingeAnchor(joint->getJointID(), joint_anchor);
		d = human->getCoM().x - joint_anchor[0];
	}
	else if (basis == PART)
	{
		d = human->getCoM().x - dBodyGetPosition(part)[0];

	}
	else if (basis == COP)
	{
		dReal cop = (dBodyGetPosition(human->parts[L_FOOT]->Body)[0] + dBodyGetPosition(human->parts[R_FOOT]->Body)[0])/2.0;
		d = human->getCoM().x - cop;
	}

	v = human->CoM_vel.x;


    dReal ret = cd->getdReal() * d + cv->getdReal() * v;

	return ret;

}

bool COMFB2::writeToFile(std::ofstream& ofs)
{

    ofs << "COMFB2 " << cd->getdReal() << " " << cv->getdReal() << " ";
    switch (basis)
    {
        case JOINT:
            ofs << "j " << joint->getNameStr() << std::endl;
            break;
        case PART:
            ofs << "p " << "COMFB2 PART-BASED NOT YET SUPPORTED" << std::endl;
            break;
        case COP:
            ofs << "c" << std::endl;
            break;
    }
    std::cout << "returning true..." << std::endl;
    return true;
}
