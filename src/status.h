#ifndef STATUS_H
#define STATUS_H

#define dSINGLE

#include <ode/ode.h>

#include <string>
#include <vector>
#include "globals.h"
#include "VECTOR.h"
#include "human.h"
#include <utility>

struct StateInfo
{
		VECTOR CoM_vel;
		dReal angles[JOINT_COUNT];
		dReal ang_vels[JOINT_COUNT];
		bool contacts[PART_COUNT];
        bool setFromFile(std::ifstream&);
        bool setFromHuman(const Human&);
        int writeToFile(std::ofstream&);
        dReal distance(StateInfo const & other);
};

class StateList;

class State
{

	public:

        State() { phase = 0; hasChild = false; }
        State(int p) { phase = p; hasChild = false; }

        void setBegin(const Human& h) { begin.setFromHuman(h); }
        void setEnd(const Human& h) { end.setFromHuman(h); }
        void setBegin(std::ifstream& infile) { begin.setFromFile(infile); }
        void setEnd(std::ifstream& infile) { end.setFromFile(infile); }
            
        void setChild(StateList* c) { hasChild = true; child = c; }
        StateList* getChild() { return child; }

        StateInfo const & getBegin() { return begin; }
        StateInfo const & getEnd() { return end; }

        bool getHasChild() { return hasChild; }

        int getPhase() { return phase; }

        void writeToFile(std::ofstream& o) { begin.writeToFile(o); end.writeToFile(o); }

	private:
        StateInfo begin;
        StateInfo end;

        bool hasChild;

        StateList* child;

        int phase;


};



class StateList
{

    public:
        StateList() {}
        StateList(std::string n) { name = n; }
        void setName(std::string n) { name = n; }
        void addState(State* s) { statusList.push_back(s); }
        int writeToFile();
        int writeToFileHelper(std::ofstream&);
        int readFromFile(std::string);
        std::vector<State*>& getStatusList() { return statusList; }
        std::string getName() { return name; }

    private:
        std::vector<State*> statusList;
        std::string name;


};

class StateListIterator
{
    public:
        StateListIterator(StateList* s) { sl.push(std::pair<StateList*, std::vector<State*>::iterator>(s, s->getStatusList().begin() ) ); first = true; }
        State* getNext();
        State* getNextHelper();
        State* getCurrent() { return current; }
        std::pair<StateList*, std::vector<State*>::iterator>* popStack() { std::pair<StateList*, std::vector<State*>::iterator>* ret = &(sl.top()); sl.pop(); return ret; }
        int stackSize() { return sl.size(); }

    private:
        bool first;
        std::stack<std::pair<StateList*, std::vector<State*>::iterator> > sl;
        State* current;
//        std::vector<State*>::iterator stateIter;

};


#endif // STATUS_H
