
#include <string>
#include <iostream>

#include "status.h"
#include "globals.h"
#include "human.h"

dReal StateInfo::distance(StateInfo const & other)
{

    dReal weight_com = 1;
    dReal weight_angle = 1;
    dReal weight_angvel = 1;
    dReal weight_contact = 1;

    dReal comvel_termx = CoM_vel.x - other.CoM_vel.x;
    dReal comvel_termy = CoM_vel.y - other.CoM_vel.y;
    dReal comvel_term = weight_com*(comvel_termx*comvel_termx + comvel_termy*comvel_termy);

    dReal angle_term = 0;
    dReal angvel_term = 0;
    dReal contact_term = 0;

    for (int i = 0; i < JOINT_COUNT; i++)
    {
        dReal temp = angles[0] - other.angles[0];
        angle_term += temp*temp;
    }
    angle_term *= weight_angle;

    for (int i = 0; i < JOINT_COUNT; i++)
    {
        dReal temp = ang_vels[0] - other.ang_vels[0];
        angvel_term += temp*temp;
    }
    angvel_term *= weight_angvel;

    for (int i = 0; i < PART_COUNT; i++)
    {
        dReal temp = (contacts[i] ? 1 : 0) - (other.contacts[i] ? 1 : 0);
        contact_term += temp*temp;
    }

    contact_term *= weight_contact;

    return comvel_term + angle_term + angvel_term + contact_term;

}

int StateInfo::writeToFile(std::ofstream& outfile)
{
    if (!outfile)
    {
        return -1;
    }

    outfile << CoM_vel.x << " " <<  CoM_vel.y << " " << CoM_vel.z << std::endl;

    for (int i = 0; i < JOINT_COUNT; i++)
    {
        outfile << angles[i] << " " << ang_vels[i] << std::endl;;
    }
    for (int i = 0; i < PART_COUNT; i++)
    {
        (contacts[i]) ? outfile << 1 << " " : outfile << 0 << " ";
    }
    outfile << std::endl;

    return 0;

} 

bool StateInfo::setFromFile(std::ifstream& infile)
{
	if (!infile)
	{
        std::cerr << "StateInfo Datafile not present" << std::endl;
		return false;
	}


	infile >> CoM_vel.x >> CoM_vel.y >> CoM_vel.z;

	for (int i = 0; i < JOINT_COUNT; i++)
	{
		infile >> angles[i];
		infile >> ang_vels[i];
	}
	dReal temp;
	for (int i = 0; i < PART_COUNT; i++)
	{
		infile >> temp;
		(temp == 1) ? (contacts[i] = (true)) : (contacts[i] = (false));
	}

    return true;

}

bool StateInfo::setFromHuman(const Human& h)
{

    
    CoM_vel = ((Human)h).getCoMVel();

	for (int i = 0; i < JOINT_COUNT; i++)
	{
		angles[i] = dJointGetHingeAngle(h.joints[i]->getJointID());
		ang_vels[i] = h.joints[i]->getRate();
	}
	for (int i = 0; i < PART_COUNT; i++)
	{
		contacts[i] = h.parts[i]->groundContact();
	}

    return true;

}


int StateList::writeToFileHelper(std::ofstream& output)
{
    output << name << std::endl;
    for (auto it = statusList.begin(); it != statusList.end(); it++)
    {
        output << (*it)->getPhase();
        if ((*it)->getHasChild())
        {
            output << "\n>" << std::endl;
            (*it)->getChild()->writeToFileHelper(output);
            output << "-1\n<" << std::endl;
        }
        else
        {
            output << "\nDATA" << std::endl;
            (*it)->writeToFile(output);
        }

    }

    return 0;

}

int StateList::writeToFile()
{

	std::ofstream output;

    // assuming extension is one character.
    std::string ofname = name;
    ofname.at(name.size()-2) = '_';
    ofname.append(".data");
    std::cout << "Writing state data to file " << ofname << std::endl;

	output.open(ofname.c_str());

    writeToFileHelper(output);



	output.close();

	return 0;

}

int StateList::readFromFile(std::string ifname)
{

    std::ifstream input;

    std::cout << "Reading in " << ifname << std::endl;

    input.open(ifname);
    if(!input)
    {
        std::cerr << "StateInfo Data file " << ifname << " not found" << std::endl;
        return -1;
    }

    std::stack<StateList*> sl;

    input >> name;
    sl.push(this);


    std::string temp_str;
    int temp_int;

    State* sta;

    while (input.good())
    {


        input >> temp_int;

        sta = new State(temp_int);

        input >> temp_str;

        if (temp_str.compare(">") == 0)
        {
            input >> temp_str;
            StateList* temp = new StateList(temp_str);
            sta->setChild(temp);
            sl.top()->statusList.push_back(sta);
            sl.push(temp);

        }
        else if (temp_str.compare("<") == 0)
        {
            sl.pop();
        }
        else if (temp_str.compare("DATA") == 0)
        {
            sta->setBegin(input);
            sta->setEnd(input);
            sl.top()->statusList.push_back(sta);
        }
        else
        {
            std::cerr << "Discovered unknown state type " << temp_str << " while reading in file " << name << std::endl;
            return -1;
        }


        

    }

    std::cout << "Done reading" << std::endl;

    return 0;




}

// TODO: bah. Pointers in the stack.
State* StateListIterator::getNextHelper()
{


    if (sl.top().second == sl.top().first->getStatusList().end())
    {
        sl.pop();
        return getNext();
    }


    else if ((*(sl.top().second))->getHasChild())
    {
        StateList* next = (*(sl.top().second))->getChild();
        sl.push(std::pair<StateList*, std::vector<State*>::iterator>(next, next->getStatusList().begin()));
        return getNextHelper();
    }
    else
    {
        return (*(sl.top().second));
    }

}

State* StateListIterator::getNext()
{

    // Unless the is the first time calling, get the next
    if (!first)
    {
        sl.top().second++;
    }
    first = false;

    if (sl.size() == 1 && sl.top().second == sl.top().first->getStatusList().end())
    {
        return NULL;
    }

    current = getNextHelper();
    return current;


}

