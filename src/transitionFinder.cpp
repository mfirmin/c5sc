
#include "transitionFinder.h"

#include "hierarchy.h"
#include <algorithm>

// TODO: create this function
//Status* TransitionFinder::search(const Status&)
//{

//	return statusList.front();

	//return new Status();

//}
//
//

TransitionFinder::TransitionFinder()
{
    fromHierarchy = new Hierarchy;
    toHierarchy = new Hierarchy;
}
void TransitionFinder::findTransitions()
{

    StateListIterator* to_iter = new StateListIterator(&to);
    StateListIterator* from_iter;

    bool foundTransition = false;

    while(to_iter->getNext() != NULL)
    {

        StateInfo to_data = to_iter->getCurrent()->getBegin();

        from_iter = new StateListIterator(&from);

        while (from_iter->getNext() != NULL)
        {

            StateInfo from_data = from_iter->getCurrent()->getEnd();

            dReal distance = from_data.distance(to_data);

            if ( distance < .035 )

            {
                std::cout << "Transition found with value: " << distance << std::endl;
                foundTransition = true;
                toState = (StateInfo*)(&(to_iter->getCurrent()->getBegin()));
                break;
            }

        }

        if (foundTransition)
            break;
    }

    if (!foundTransition)
    {
        std::cout << "No suitable Transition" << std::endl;
        return;
    } 


    std::cout << "Creating the hierarchy for the 'from' transition..." << std::endl;
    while (from_iter->stackSize() > 0)
    {
        std::pair<StateList*, std::vector<State*>::iterator>* name_phase_pair = from_iter->popStack();
        fromHierarchy->push(name_phase_pair->first->getName(),
                    (*(name_phase_pair->second))->getPhase());
        std::reverse(fromHierarchy->begin(), fromHierarchy->end());
    }
    while (to_iter->stackSize() > 0)
    {
        std::pair<StateList*, std::vector<State*>::iterator>* name_phase_pair = to_iter->popStack();
        toHierarchy->push(name_phase_pair->first->getName(),
                    (*(name_phase_pair->second))->getPhase());
        std::reverse(toHierarchy->begin(), toHierarchy->end());
    }

    
    /*
    std::cout << "from: " << std::endl;
    while (from_iter->stackSize() > 0)
    {
        std::pair<StateList*, std::vector<State*>::iterator>* name_phase_pair =   from_iter->popStack();
        std::cout << name_phase_pair->first->getName() << ", phase: " << (*(name_phase_pair->second))->getPhase() << std::endl;
    }
    std::cout << "to: " << std::endl;
    while (to_iter->stackSize() > 0)
    {
        std::pair<StateList*, std::vector<State*>::iterator>* name_phase_pair =   to_iter->popStack();
        std::cout << name_phase_pair->first->getName() << ", phase: " << (*(name_phase_pair->second))->getPhase() << std::endl;
    }
    */
    

}

