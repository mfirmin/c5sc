#ifndef PHASE_H
#define PHASE_H

#define dSINGLE

#include "human.h"
#include "action.h"
#include "transition.h"
#include <vector>
#include "value.h"
#include <string>

#include <ode/ode.h>

class Controller;
struct StateInfo;


struct Phase
{

    Phase() {};
    Phase(StateInfo*, Human*);
		int phase_num;
        int switchPhase;
		
		std::vector<Transition*> transitions;

		// dt used for TIME based transitions, contact for CONTACT based.


        bool writeToFile(std::ofstream&,std::map<std::string, Controller>&);

		bool isSwitch;

        void setSwitchPhase(int p) { switchPhase = p; }
        int getSwitchPhase() { return switchPhase; }

		std::string newControllerName;
		std::vector<Value*> newControllerParams;

		std::vector<Action*> actions;


        void setOptimizable(std::vector<Value*>&);


};

#endif // PHASE_H
