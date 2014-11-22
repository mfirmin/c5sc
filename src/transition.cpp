#include <GLFW/glfw3.h>
#include <assert.h>
#include <time.h>

#include "transition.h"
#include "globals.h"
#include "environment.h"
#include "entity.h"

void Transition::setOptimizable(std::vector<Value*>& unknowns)
{
    switch(type)
    {
        case TIME:
           if (!dt->isVariable) unknowns.push_back(dt);
           break;
        case ANGLERANGE: // no break is intentional.
           if (!_float2->isVariable) unknowns.push_back(_float2);
        case FALLEN:
           if (!_float->isVariable) unknowns.push_back(_float);
           break;
        case CONTACT:
           break;
        case NO_CONTACT:
           break;
        case ITERATIONS:
           break;
        case STABLE:
           if (!stabilityTolerance->isVariable) unknowns.push_back(stabilityTolerance);
           break;
        case KEYPRESS:
           break;
        case KEYRELEASE:
           break;
        case PASS:
           break;
        default:
           break;

    }

}

bool Transition::test(dReal t)
{

	switch(type)
	{
		case TIME:
			return testTime(t);
		case CONTACT:
			return testContact();
        case NO_CONTACT:
            return testNoContact();
		case STABLE:
			return testStable();
		case ITERATIONS:
			return testIterations();
		case COMPLETE:
			return testComplete();
		case KEYPRESS:
			return testKeypress();
		case KEYRELEASE:
			return testKeyrelease();
        case FALLEN:
            return testFallen();
        case ANGLERANGE:
            return testAngleRange();
        case PASS:
            return testPass();
        case RANDOM:
            return testRandom();
		default:
			std::cerr << "Unknown transition type" << std::endl;
			break;
	}
	return false;
}

bool Transition::testTime(dReal t)
{

	assert(type == TIME);

	if (t > dt->getdReal())
		return true;

	return false;

}

bool Transition::testContact()
{

	dContact temp;
	
    std::map<std::string, Entity*> env_ents = env->getEntities();
/*
	if (dCollide(plane, contact, 1, &temp.geom, sizeof(dContact)) > 0)
	{
		return true;
	}
*/
	for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
    {
        for (auto  objIter = iter->second->getBodies().begin(); objIter != iter->second->getBodies().end(); objIter++)
        {

            if (dCollide((*objIter)->Geom[0], contact->Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
            {
                return true;
            }
        }
    }

	return false;

}

bool Transition::testNoContact()
{

	dContact temp;
	
    std::map<std::string, Entity*> env_ents = env->getEntities();
/*
	if (dCollide(plane, contact, 1, &temp.geom, sizeof(dContact)) > 0)
	{
		return true;
	}
*/
	for (auto iter = env_ents.begin(); iter != env_ents.end(); iter++)
    {
        for (auto  objIter = iter->second->getBodies().begin(); objIter != iter->second->getBodies().end(); objIter++)
        {

            if (dCollide((*objIter)->Geom[0], contact->Geom[0], 1, &temp.geom, sizeof(dContact)) > 0)
            {
                return false;
            }
        }
    }

	return true;

}

bool Transition::testIterations()
{



	if (curr_iterations >= _float->getdReal())
	{
		curr_iterations = 0;
		return true;
	}
	else
	{
		curr_iterations++;
	}
	return false;

}

bool Transition::testStable()
{

	if (human->isStable(stabilityTolerance->getdReal()))
	{	
		return true;
	}

	return false;

}

bool Transition::testComplete()
{
	return true;
}

bool Transition::testKeypress()
{

	glfwPollEvents();
	if (glfwGetKey(window, key) == GLFW_PRESS)
	{
		std::cout << key << std::endl;
		return true;
	}

	return false;

}

bool Transition::testKeyrelease()
{

	glfwPollEvents();
	if (glfwGetKey(window, key) == GLFW_RELEASE)
	{
		return true;
	}
	return false;

}

bool Transition::testFallen()
{
    dReal ang = -dJointGetAMotorAngle(human->uTorso2world_M,2);

    // _int = -1 implies fallen backward, +1 forward.
    if (_int->getInt() == -1 && ang < _float->getdReal())
    {
        return true;
    }
    else if (_int->getInt() == 1 && ang > _float->getdReal())
    {
        return true;
    }
    else if (_int->getInt() == 0 && (ang > _float->getdReal() || ang < -_float->getdReal()))
    {
        return true;
    }

    return false;
   /* 
    if (ang < -_float->getdReal() || ang > _float->getdReal())
    {
        return true;
    }

    return false;
    */

}

bool Transition::testAngleRange()
{
    dReal ang = -dJointGetAMotorAngle(human->uTorso2world_M,2);

    if (_float->getdReal() < _float2->getdReal())
    {
        return (ang > _float->getdReal() && ang < _float2->getdReal());
    }
    else
    {
        return !(ang > _float2->getdReal() && ang < _float->getdReal());

    }

}

bool Transition::testPass()
{

    pass_entity = env->getEntities().find(ent_name)->second;

    dReal min_dist = 10000;

    for (int i = 0; i < PART_COUNT; i++)
    {
        dReal dist_to_ent = std::abs(dBodyGetPosition(human->parts[i]->Body)[0] - pass_entity->getCenter().x  );
        if ( dist_to_ent < min_dist )
        {
            min_dist = dist_to_ent;
        }

    }
    // case entered the BB
    if (min_dist < dx->getdReal())
    {
        inside = true;
        return false;
    }
    // case passed the BB
    if (inside && min_dist > dx->getdReal())
    {
        inside = false;
        return true;
    }

    // case has not yet entered the BB
    return false;

}

bool Transition::testRandom()
{

    float i = rand()/(double)RAND_MAX;

    std::cout << i << std::endl;
    std::cout << "of " << _float->getdReal() << std::endl;

    if (i < _float->getdReal())
    {
        return true;
    }
    return false;

}

bool Transition::writeToFile(std::ofstream& ofs)
{

    ofs << "TRANSITION to(" << to << ").after(";

	switch(type)
	{
		case TIME:
            ofs << "time " << dt->write();
			break;
		case CONTACT:
            ofs << "contact " << getPartNameFromEnum(contact->name); 
			break;
        case NO_CONTACT:
            ofs << "nocontact " << getPartNameFromEnum(contact->name); 
            break;
		case STABLE:
            ofs << "stable " << stabilityTolerance->write();
			break;
		case ITERATIONS:
            ofs << "iterations " << _float->write();
			break;
		case COMPLETE:
            ofs << "complete";
			break;
		case KEYPRESS:
            ofs << "press " << key;
			break;
		case KEYRELEASE:
            ofs << "release " << key;
			break;
        case FALLEN:
            ofs << "fallen ";
            if (_int->getdReal() == 1) ofs << "> ";
            else if (_int->getdReal() == -1) ofs << "< ";
            else if (_int->getdReal() == 0) ofs << "x ";
            ofs << _float->getdReal();
            break;
        case ANGLERANGE:
            ofs << "anglerange " << _float->write() << " " << _float2->write();
            break;
        case PASS:
            ofs << "pass " << ent_name << " " << dx->write();
            break;
		default:
			std::cerr << "Unknown transition type" << std::endl;
			break;
	}
    ofs << ");\n";

    return true;
}
