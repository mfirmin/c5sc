#ifndef IKSOLVER_H
#define IKSOLVER_H

#define dSINGLE

#include "action.h"
#include "VECTOR.h"
#include "joint.h"
#include "value.h"
//#include <eigen3/Eigen/Dense>
#include <ode/ode.h>
#include <vector>

class IKSolver : public Action
{

	public:
		IKSolver(Joint* b, const Object* move, Value* x, Value* y, Value* z, bool g, Value* tol=new Value(false,0.05));
		void performAction();
		virtual void reset() { return; }
		void calculateThetas();
		void retarget();

		static constexpr dReal stepsize = 0.0001;
		Value* IK_tol;
		static constexpr int MAX_STEPS = 100;
		static constexpr dReal MAX_RAD = .25;
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

	private:
		Joint* base;
		const Object* toMove;
		VECTOR goal;
		VECTOR goal_input;
        Value* x_in;
        Value* y_in;
        Value* z_in;
		bool global;
		bool found;
		bool converged;
		std::vector<Joint*> jointList;
		std::vector<PDController*> controllers;
		std::vector<dReal> jointAngles;

};


#endif // IKSOLVER_H
