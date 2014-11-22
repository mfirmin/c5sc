#ifndef TRANSITIONFINDER_H
#define TRANSITIONFINDER_H

#include "status.h"
#include <vector>

class Hierarchy;

class TransitionFinder
{

	public:

        TransitionFinder();

        Hierarchy* getFromHierarchy() { return fromHierarchy; }
        Hierarchy* getToHierarchy() { return toHierarchy; }

        void setTo(char* filename) { to.readFromFile(std::string(filename)); } 
        void setFrom(char* filename) { from.readFromFile(std::string(filename)); }
        void findTransitions();

        StateInfo* getToStateInfo() { return toState; }



	private:

        StateList to;
        StateList from;

        StateInfo* toState;

    // List of the current hierarchy (controller name, phase num). To compare against the 
    // transition finder, for the purpose
    // of telling when to transition to the 'interim' controller.
        Hierarchy* fromHierarchy; 
        Hierarchy* toHierarchy; 

};


#endif // TRANSITIONFINDER_H
