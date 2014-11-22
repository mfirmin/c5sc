
#define dSINGLE

#include "action.h"
#include "optimization.h"
#include "globals.h"
#include "VECTOR.h"
#include "environment.h"
#include "entity.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

#include <ode/ode.h>

void LIPose::performAction()
{

	if ( t_elapsed == 0 )
	{
		ang_init = dJointGetHingeAngle(joint->getJointID());
        pose->setAngle(ang_init);
	}

	if (t_elapsed < t_goal->getdReal())
	{
		dReal ang_curr = (t_elapsed/t_goal->getdReal())*(ang_goal->getdReal() - ang_init) + ang_init;

		pose->setAngle(ang_curr);

		t_elapsed += STEPSIZE;
	}

	pose->performAction();

}

bool LIPose::writeToFile(std::ofstream& ofs)
{
    ofs << "LIPOSE " << joint->getNameStr() << "(" << ang_goal->write() << ", " << kp->write() << ", " << kd->write() << ").time(" <<  t_goal->write() << ");\n";

    return true;
}

void Holder::performAction()
{

    if (first)
    {
        dReal ang = dJointGetHingeAngle(joint->getJointID());

        pose->setAngle(ang);
        first = false;
    }

    pose->performAction();

}

bool Holder::writeToFile(std::ofstream& ofs)
{
    
    ofs << "HOLD " << joint->getNameStr() << ";\n";
    return true;

}


void HingePose::performAction()
{


	joint->setHingePose(optAngle->getdReal(), kp->getdReal(), kd->getdReal(), optRate->getdReal());
	joint->setPoseActive(true);
	joint->setPoseOptimization(feedbackLaw);


}

bool HingePose::writeToFile(std::ofstream& ofs)
{
    ofs << "POSE " << joint->getNameStr() << "(" << optAngle->write() << ", " << kp->write() << ", " << kd->write() << ");\n";
    return true;
}

void HingePoseOptSetter::performAction()
{
	joint->setPoseOptimization(opt);
}

bool HingePoseOptSetter::writeToFile(std::ofstream& ofs)
{
    ofs << "POSEFB " << joint->getNameStr() << "(";// << kp->getdReal() << ", " << kd->getdReal() << ").on(";

    COMFB2* comfb_opt = dynamic_cast<COMFB2*>(opt);

    ofs << comfb_opt->getCDwrite() << ", " << comfb_opt->getCVwrite() << ").on(";

    switch (comfb_opt->getBasis())
    {
        case PART:
            ofs << "part " << "FIXMESOON";
            break;
        case JOINT:
            ofs << "joint " << comfb_opt->getJoint()->getNameStr();
            break;
        case COP:
            ofs << "cop";
            break;
    }

    ofs << ");\n";

    return true;
}


void PDController::performAction()
{

	dReal currAngle = dJointGetHingeAngle(joint->getJointID());
	dReal currRate = dJointGetHingeAngleRate(joint->getJointID());

	dReal desAngle = optAngle->getdReal();


	if (optimization->active)
	{
		desAngle += optimization->optimize();
	}


	dReal torque = kp->getdReal() * (desAngle - currAngle) + kd->getdReal() * (optRate->getdReal() - currRate);

	joint->setPoseActive(false);

    joint->addCurrentTorque(VECTOR(0,0,torque));

}

bool PDController::writeToFile(std::ofstream& ofs)
{
    ofs << "PD - I shouldn't exist!";
    return false;
}

void VPDController::performAction()
{


	dReal currAngle = dJointGetAMotorAngle(motor, 2);
	dReal currRate = dBodyGetAngularVel(part->Body)[2];

	dReal desAngle = optAngle->getdReal();

	if (optimization->active)
	{
		desAngle += optimization->optimize();
	}

	desAngle = -desAngle; // required for VPD since angle to world is inverted. 
	// note that this has to be after the optimization because we optimize it first, then negate.
    //

	dReal torque = kp->getdReal() * (desAngle - currAngle) + kd->getdReal() * (optRate->getdReal() - currRate);

/*
	if (torque > TORQUE_LIMIT)
	{
		torque = TORQUE_LIMIT;
	}
	if (torque < -TORQUE_LIMIT)
	{
		torque = -TORQUE_LIMIT;
	}
*/
    joint->setPoseActive(false);
    // TODO: MAKE this whole thing better. this isn't even a hack
    joint->addCurrentTorque(VECTOR(0,0,torque));

    // Hack for Simbicon: so that the -torque is applied to the other hip instead.
    if (simbicon)
    {
        if (part->name == R_THIGH)
        {
            human->joints[L_HIP]->setPoseActive(false);
            human->joints[L_HIP]->addCurrentTorque(VECTOR(0,0,-torque));
        }
        if (part->name == L_THIGH)
        {
            human->joints[R_HIP]->addCurrentTorque(VECTOR(0,0,-torque));
            human->joints[R_HIP]->setPoseActive(false);
        }
    }        
/*
	part->currentTorque = part->currentTorque + VECTOR(0,0,torque);
	parent->currentTorque = parent->currentTorque + VECTOR(0,0,-torque);
*/

	//dBodyAddTorque(part, 0, 0, torque);
//	dBodyAddTorque(part2, 0, 0, -torque);

}

bool VPDController::writeToFile(std::ofstream& ofs)
{
    if (this->optimization->active)
    {
        if (!(this->optimization->writeToFile(ofs)))
        {
            return false;
        }
        ofs << "\t";
    }

    ofs << "VPD " << getPartNameFromEnum(part->name) << "(" << optAngle->write() << ", " << kp->write() << ", " << kd->write() << ").joint("
        << joint->getNameStr() << ")";


    if (simbicon)
        ofs << ".flags(s)";
    ofs << ";\n";

    return true;
}

void ExternalForceController::performAction()
{

	dBodyAddForce(first, force_x->getdReal(), force_y->getdReal(), force_z->getdReal());

}

bool ExternalForceController::writeToFile(std::ofstream& ofs)
{

    ofs << "EF " << " STOP USING BLOODY dBODYID's Everywhere. yeesh\n";

    return false;

}



// TODO: Test and fix me. I haven't been used in awhile.
GravityCompensator::GravityCompensator(const Object* o, Joint* b, const Human &h)
{


	on = o;
	by = b;

	h.findJointPath((Object*)on, (Joint*)by, path);


	Object* prev = (Object*)on;

    // TODO: BAD. get rid of the new statements.
	VirtualForceController* VF = new VirtualForceController(prev, by, new Value(false, 0), new Value(false, prev->shape->getMass()*10.), new Value(false, 0));
	h.findJointPath(prev, by, VF->getPath());
	controllers.push_back(VF);


	for (std::vector<std::pair<Joint*, bool> >::iterator it = path.begin(); it != path.end(); it++)
	{

		if ((*it).first->getChild()->name == prev->name)
		{
			prev = (*it).first->getParent();
		}
		else if ((*it).first->getParent()->name == prev->name)
		{
			prev = (*it).first->getChild();
		}
		else
		{
			std::cerr << "Error creating Gravity Compensator" << std::endl;
			return;
		}

        // Oof.
		VF = new VirtualForceController(prev, by, new Value(false, 0), new Value(false, prev->shape->getMass()*10.), new Value(false, 0));
		h.findJointPath(prev, by, VF->getPath());
		controllers.push_back(VF);
	}
		

}
// TODO: See above.
//
void GravityCompensator::performAction()
{

	for (std::vector<VirtualForceController*>::iterator it = controllers.begin(); it != controllers.end(); it++)
	{
		(*it)->performAction();
	}

}

bool GravityCompensator::writeToFile(std::ofstream& ofs)
{
    ofs << "GC: yeah, not even.\n";
    return false;
}

// TODO: fix for joint-based torque.
void VirtualForceController::performAction()
{



	Object* current = (Object*)on;

	const dReal* pos = dGeomGetPosition(current->Geom[0]);
	VECTOR applyTo;

	if (!com_based)
	{
		applyTo = VECTOR(pos[0], pos[1], pos[2]);
	}
	else
	{
		applyTo = human->getCoM();
	}


	dVector3 anchor;

	bool breaknext = false;

	for (std::vector<std::pair<Joint*, bool> >::iterator it = path.begin(); it != path.end(); it++)
	{

		dJointGetHingeAnchor((*it).first->getJointID(), anchor);

		VECTOR r = applyTo - VECTOR(anchor[0], anchor[1], anchor[2]);

		VECTOR F = VECTOR(Fx->getdReal(), Fy->getdReal(), Fz->getdReal());

		VECTOR torque = r.cross(F);


		short sign = 1;
		if (!(*it).second)
			sign = -1;


/*
		(*it).first->getParent()->currentTorque += VECTOR(0,0,-sign*torque.z);
		(*it).first->getChild()->currentTorque += VECTOR(0,0,sign*torque.z);
*/
        (*it).first->addCurrentTorque(VECTOR(0,0,-sign*torque.z));
		// Does a VF controller overwrite a pose controller, or add to it?
		// Going to go with add to it.....
		//(*it).first->setPoseActive(false);

	}

}

bool VirtualForceController::writeToFile(std::ofstream& ofs)
{
    ofs << "VF " << "(" << Fx->write() << ", " << Fy->write() << ", " << Fz->write() << ").on("
        << getPartNameFromEnum(on->name) << ").by("
        << by->getNameStr() << ");\n";
    return true;
}




// VFFB
void VFFeedback::createVF()
{

    std::cout << "This should never be more than one: " << ++counter  << ", VFFeedback::createVF()" << std::endl;

	dReal cop = (dBodyGetPosition(human->parts[L_FOOT]->Body)[0] + dBodyGetPosition(human->parts[R_FOOT]->Body)[0])/2.0;

	dReal d, v;
	d = human->getCoM().x - cop;
	v = human->CoM_vel.x;

	dReal Fx = cd->getdReal() * d + cv->getdReal() * v;

	VF = new VirtualForceController(on, by, new Value(false, Fx), new Value(false, 0.), new Value(false, 0.));

	VF->makeCOMBased(*human);

	human->findJointPath((Object*)on, by, VF->getPath());

}


void VFFeedback::performAction()
{



	dReal pos = 0;
	int numContacts = 0;
/*
	dContact temp;

	if (lfoot)
	{

		std::map<std::string, Entity*> env_ents = env->getEntities();

		for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
		{
            for (auto  objIter = iter->second->getBodies().begin(); objIter != iter->second->getBodies().end(); objIter++)
            {
                if (dCollide((*objIter)->Geom[0], human->parts[L_FOOT]->Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
                { 
                    pos += dBodyGetPosition(human->parts[L_FOOT]->Body)[0];
                    numContacts++;
                }
            }

		}
	}
	else if (rfoot)
	{
		std::map<std::string, Entity*> env_ents = env->getEntities();

		for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
		{
            for (auto  objIter = iter->second->getBodies().begin(); objIter != iter->second->getBodies().end(); objIter++)
            {
                if (dCollide((*objIter)->Geom[0], human->parts[R_FOOT]->Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
                { 
                    pos += dBodyGetPosition(human->parts[R_FOOT]->Body)[0];
                    numContacts++;
                }
            }
		}
	}
    */

    std::vector<Object*> contacts;
    if (over.compare("cop") == 0)
        contacts = human->getContactPoints();

    else
        contacts.push_back(human->getObjectFromString(over));


    numContacts = contacts.size();




	dReal cop;
	if (numContacts > 0)
	{
        for (auto it = contacts.begin(); it != contacts.end(); it++)
        {
            pos += dBodyGetPosition((*it)->Body)[0];
        }

		cop = pos/numContacts;
	}

	else
	{
		cop = (dBodyGetPosition(human->parts[L_FOOT]->Body)[0] + dBodyGetPosition(human->parts[R_FOOT]->Body)[0])/2.0;
	}




	dReal d, v;
	d = human->getCoM().x - cop;
	v = human->CoM_vel.x;


	dReal Fx = cd->getdReal() * d + cv->getdReal() * v;


	VF->setForce(new Value(false, -Fx), new Value(false, 0.), new Value(false, 0.));

	VF->performAction();

}

bool VFFeedback::writeToFile(std::ofstream& ofs)
{
    ofs << "VFFB "  
        << getPartNameFromEnum(on->name) << "("
        << cd->write() << ", " << cv->write() << ").by("
        << by->getNameStr() << ").over("
        << over << ");\n";

    return true;
}

/*
void VFSpeedFeedback::createVF()
{


	dReal v;
	v = goalSpeed->getdReal() - human->CoM_vel.x;

	dReal Fx = cv->getdReal() * v;

	VF = new VirtualForceController(on, by, new Value(false, Fx), new Value(false, 0.), new Value(false, 0.));

	VF->makeCOMBased(*human);

	human->findJointPath((Object*)on, by, VF->getPath());

}
*/

void VFSpeedFeedback::performAction()
{

	dReal v;
	v = goalSpeed->getdReal() - human->CoM_vel.x;
	dReal Fx = cv->getdReal() * v;

    if (!initialized)
    {
        VF = new VirtualForceController(on, by, new Value(false, Fx), new Value(false, 0.), new Value(false, 0.));
        VF->makeCOMBased(*human);
        human->findJointPath((Object*)on, by, VF->getPath());
        initialized = true;
    }



	VF->setForce(new Value(false, Fx), new Value(false, 0.), new Value(false, 0.));

	VF->performAction();

}
bool VFSpeedFeedback::writeToFile(std::ofstream& ofs)
{
    ofs << "VFSFB "  
        << getPartNameFromEnum(on->name) << "("
        << cv->write() << ").by("
        << by->getNameStr() << ").speed("
        << goalSpeed->write() << ");\n";

    return true;
}
void Matcher::performAction()
{

    if (LI_based && first)
    {
        LI = new LIPose(joint, new Value(false, dJointGetHingeAngle(other->getJointID())), KP, KD, time);
        LI->performAction();
        first = false;
    }
    else if (LI_based && !first)
    {
        LI->performAction();
    }
    else
    {
        joint->setHingePose(dJointGetHingeAngle(other->getJointID()), KP->getdReal(), KD->getdReal(), 0.0);
        joint->setPoseActive(true);
        joint->setPoseOptimization(new inactiveOptimization());
    }
}

bool Matcher::writeToFile(std::ofstream& ofs)
{
    ofs << "MATCH "  
        << joint->getNameStr() << ".to("
        << other->getNameStr() << ", " << KP->write() << ", " << KD->write() << ")";

    if (this->LI_based)
        ofs << ".time(" << time->write() << ")";

    ofs << ";\n";

    return true;
}

void PDController::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!kp->isVariable) unknowns.push_back(kp);
    if (!kd->isVariable) unknowns.push_back(kd);
    if (!optAngle->isVariable) unknowns.push_back(optAngle);
}
void VPDController::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!kp->isVariable) unknowns.push_back(kp);
    if (!kd->isVariable) unknowns.push_back(kd);
    if (!optAngle->isVariable) unknowns.push_back(optAngle);
}
void ExternalForceController::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!force_x->isVariable) unknowns.push_back(force_x);
    if (!force_y->isVariable) unknowns.push_back(force_y);
}
void VirtualForceController::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!Fx->isVariable) unknowns.push_back(Fx);
    if (!Fy->isVariable) unknowns.push_back(Fy);
}
void VFFeedback::setOptimizable(std::vector<Value*>& unknowns)
{

    if (!cd->isVariable) unknowns.push_back(cd);
    if (!cv->isVariable) unknowns.push_back(cv);
}
void VFSpeedFeedback::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!cv->isVariable) unknowns.push_back(cv);
}
void HingePose::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!kp->isVariable) unknowns.push_back(kp);
    if (!kd->isVariable) unknowns.push_back(kd);
    if (!optAngle->isVariable) unknowns.push_back(optAngle);
}
void LIPose::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!kp->isVariable) unknowns.push_back(kp);
    if (!kd->isVariable) unknowns.push_back(kd);
    if (!ang_goal->isVariable) unknowns.push_back(ang_goal);
    if (!t_goal->isVariable) unknowns.push_back(t_goal);
}
void Matcher::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!KP->isVariable) unknowns.push_back(KP);
    if (!KD->isVariable) unknowns.push_back(KD);
    if (!time->isVariable) unknowns.push_back(time);
}
