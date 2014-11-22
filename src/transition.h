#ifndef TRANSITION_H
#define TRANSITION_H

#define dSINGLE

#include <ode/ode.h>
#include <string>

#include "value.h"
#include "human.h"

class Entity;

enum TransitionType { TIME, CONTACT, NO_CONTACT, STABLE, ITERATIONS, KEYPRESS, KEYRELEASE, COMPLETE, FALLEN, ANGLERANGE, PASS, RANDOM };

class Transition
{

	public:


        void setOptimizable(std::vector<Value*>&);

		TransitionType type;

		Value* dt;
		int to;

		char key;

        void reset() { curr_iterations = 0; }


		Value* stabilityTolerance;
		Human* human;

		int curr_iterations;
		Value* _float;
        Value* _float2;
        Value* _int;

//		dGeomID contact;
        Object* contact;

        // for testPass
        std::string ent_name;
        Entity* pass_entity;
        Value* dx;
        bool inside;

		bool test(dReal t);
		bool testTime(dReal t);
		bool testContact();
        bool testNoContact();
		bool testStable();
		bool testIterations();
		bool testComplete();
		bool testKeypress();
		bool testKeyrelease();
        bool testFallen(); // (uTorso at a given angle)
        bool testAngleRange();
        bool testPass(); // (human has passed a given obj.
        bool testRandom();


        bool writeToFile(std::ofstream&);

};


#endif //TRANSITION_H
