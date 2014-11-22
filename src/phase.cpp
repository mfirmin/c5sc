

#include "phase.h"
#include "status.h"
#include "controller.h"


Phase::Phase(StateInfo* s, Human* h)
{

    for (int i = 0; i < JOINT_COUNT; i++)
    {
		actions.push_back(new LIPose(h->joints[i], new Value(false, s->angles[i]), new Value(false, 100), new Value(false, 10), new Value(false, 0.01)));

        std::cout << h->joints[i]->getNameStr() << ": " << s->angles[i] << std::endl;

    }

    Transition* trans = new Transition;

    trans->type = TIME;
    trans->dt = new Value(false, 0.01);
    trans->to = -1;


    transitions.push_back(trans);

    phase_num = 0;
    isSwitch = false;

}


void Phase::setOptimizable(std::vector<Value*>& unknowns)
{

    for (auto it = newControllerParams.begin(); it != newControllerParams.end(); it++)
    {
           if (!(*it)->isVariable) unknowns.push_back(*it);
    }
    for (auto it = transitions.begin(); it != transitions.end(); it++)
    {
        (*it)->setOptimizable(unknowns);
    }
    for (auto it = actions.begin(); it != actions.end(); it++)
    {
        (*it)->setOptimizable(unknowns);
    }

}

bool Phase::writeToFile(std::ofstream& ofs, std::map<std::string, Controller>& scripts)
{
    ofs << "PHASE " << phase_num << std::endl;
    if (this->isSwitch)
    {
        ofs << "> " << newControllerName << "(";
        if (newControllerParams.size() == 0)
            ofs << "void";
        else
        {
            for (auto it = newControllerParams.begin(); it != newControllerParams.end(); it++)
            {
                ofs << (*it)->write();
                if (it != newControllerParams.end()-1)
                {
                    ofs << ", ";
                }
            }
        }
        ofs << ");\n";
    }

    
    if (actions.size() != 0)
    {
        ofs << "ACTIONS\n";
        for (auto it = actions.begin(); it != actions.end(); it++)
        {
            ofs << "\t";
            (*it)->writeToFile(ofs);
        }
        ofs << "ENDACTIONS\n";
    }
    if (transitions.size() != 0)
    {
        for (auto it = transitions.begin(); it != transitions.end(); it++)
        {
            (*it)->writeToFile(ofs);
        }
    }

    ofs << "ENDPHASE\n";

    if (this->isSwitch)
    {
        // load Parameters.
        Controller* toController = &(scripts.find(newControllerName)->second);
        toController->setParams(this->newControllerParams);
        ofs << "\n\n>>>>>>>>>>>\n\n";
        toController->writeToFile(ofs, scripts);
        ofs << "\n\n<<<<<<<<<<<\n\n";
        // pop Parameters
        lookupTable.pop();
    }


    return true;
}
