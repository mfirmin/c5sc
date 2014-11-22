#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "phase.h"
#include "value.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_set>

struct StateInfo;
class Human;

enum GLOBAL_NAME { SET_TORQUE_LIMIT, NUM_VALUES };

class Controller
{

	public:

        Controller() {};
        Controller(StateInfo*, Human* h);

		int numParams;


        bool writeToFile(std::ofstream&,std::map<std::string, Controller>&);
        bool writeToFile(std::string, std::map<std::string, Controller>&);

        // List of phases
		std::vector<Phase> phases;
		std::vector<std::string> paramNames;

		int getCurrPhase() {return currPhase;}
		void setCurrPhase(int phase) {currPhase = phase;}
		std::string getName() { return name;}
		std::string getDisplayName() { return displayName; }
		void setName(std::string n) { name = n; }
		void setDisplayName(std::string dN) { displayName = dN; }
		void setParams(std::vector<Value*>&);
        void setDependencies(std::vector<std::string> s) { dependencies = s; }

        // On starting this controller, setGlobalValues, if given.
        void setGlobals();

        void addGlobal(std::pair<GLOBAL_NAME, dReal> g) { values.push_back(g); }

        // List of script dependencies for this controller. Solely used for the purpose of outputting scripts (actual necessary info for switching is in Phase.*.

   //     void setLinks(std::unordered_set<Controller*>* l) { links = *l; }

  //      std::unordered_set<Controller*> const & getLinks() { return links; }

	private:
        std::vector<std::string> dependencies; 
		int currPhase; // used to tell which phase this controller is on, in the main loop
		std::string name;
		std::string displayName;

        std::vector<std::pair<GLOBAL_NAME, dReal> > values;

        // Set of all controllers that this one can 'link' to. ie, transition to
        // not 100% sure this is used anywhere
        // 90% sure it's leftover from before I put transitions in the phases
//        std::unordered_set<Controller*> links;


};

#endif // CONTROLLER_H
