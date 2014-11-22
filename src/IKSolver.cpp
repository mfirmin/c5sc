
#define dSINGLE

//#include <eigen3/Eigen/Dense>
// Note that I've added a pseudoinverse function to the Jacobi.h file, pinv()
//#include <eigen3/Eigen/SVD> 
#include <iostream>
#include <ode/ode.h>
#include <vector>
#include <math.h>

#include "IKSolver.h"
#include "joint.h"


struct IKJoint
{

	dReal jointAngle_l; dReal locMAX; dReal locMIN;
	dReal jointAngle_w;
	dReal angle2ee_w;
	dReal angle2goal_w;
	dReal rad2child;
	VECTOR jointPos;

	IKJoint* parent;
	IKJoint* child;
		
};


IKSolver::IKSolver(Joint* b, const Object* part, Value* x, Value* y, Value* z, bool g, Value* tol)
{



	IK_tol = tol;

	base = b;
	toMove = part;
	global = g;

    // Problem, can't use variables since it tries to construct this 
    // during the controller-read-in phase. 123013
    //
    /*
*/
    x_in = x;
    y_in = y;
    z_in = z;
	found = false;
	converged = false;
	retarget();

	//IKPoint.x = x->getdReal();
	//IKPoint.y = y->getdReal();
	//IKPoint.z = z->getdReal();

}

// This should only be necessary if we allow the IK target point to be changed
// in one "Phase"
void IKSolver::retarget()
{

	Object* current = (Object*)toMove;
	bool breaknext = false;

	std::vector<dBodyID> bodyList;
	std::vector<dJointID> motorList;

	// collect the list of joints on the path from toMove -> joint.
	// JointID's, BodyID's, MotorID's.

	do
	{
		if (current->joint2Parent == base)
		{
			breaknext = true;
		}

		jointList.push_back(current->joint2Parent);
		bodyList.push_back(current->Body);
		motorList.push_back(current->virtualMotor);

		current = current->parent;



	} while (!breaknext);

	//calculateThetas();
}

void IKSolver::performAction()
{

	const dReal* pos = dBodyGetPosition(toMove->Body);
	VECTOR eePos; eePos.x = pos[0]; eePos.y = pos[1]; eePos.z = pos[2];
	// if the goal has been moved ...
    
	goal_input = VECTOR(x_in->getdReal(), y_in->getdReal(), z_in->getdReal());


	if (global)
	{
		goal = goal_input;
	}
	else
	{
		dVector3 pos;
		dJointGetHingeAnchor(base->getJointID(), pos);
		goal = VECTOR(pos[0], pos[1], pos[2]) + goal_input;
	}


	if (!global)
	{
		dVector3 pos;
		dJointGetHingeAnchor(base->getJointID(), pos);
		goal = VECTOR(pos[0], pos[1], pos[2]) + goal_input;
	}


	// if the ee is at the goal, mark as much.
	if ( sqrt( pow(goal.x - eePos.x, 2) + pow(goal.y - eePos.y, 2)) < IK_tol->getdReal() )
	{
		found = true;
	}
	else
	{
		calculateThetas();
	}

	// if the ee is supposed to be at the goal, but isn't, retarget.
	if (!controllers.empty())
	{

		dVector3 pos_base; dJointGetHingeAnchor(base->getJointID(), pos_base);
		VECTOR basePos; basePos.x = pos_base[0]; basePos.y = pos_base[1]; basePos.z = pos_base[2];
		// if commented: position as close as possible, no matter if found.
		//if ( converged )
		{
			for (std::vector<PDController*>::iterator it = controllers.begin(); it != controllers.end(); it++)
			{
				(*it)->performAction();
			}
		}
	}
	else
	{
	//	std::cout << "\n\nJoint Angles: " << std::endl;
		for (std::vector<dReal>::iterator it = jointAngles.begin(); it != jointAngles.end(); it++)
		{
	//		std::cout << *it << std::endl;
		}
	}

}

void IKSolver::calculateThetas() // attempt 3. with local angles and joint limits.
{

	converged = true;

	// current position of end effector (part you want to move).
	const dReal* pos = dBodyGetPosition(toMove->Body);
	VECTOR eePos; eePos.x = pos[0]; eePos.y = pos[1]; eePos.z = pos[2];

	int i = 0;

	IKJoint* base;
	IKJoint* curr;

	// start from base, fill in toward ee, values that can be filled w/o knowledge of parent.
	for (std::vector<Joint*>::iterator it = jointList.end()-1; it != jointList.begin()-1; it--)
	{

		IKJoint* prev;
		if (i != 0)
			prev = curr;

		curr = new IKJoint();
		if (i == 0)
			base = curr;


		if (i != 0)
		{
			curr->parent = prev;
			prev->child = curr;
		}
		else
			curr->parent = NULL;


		dVector3 temp;
		dJointGetHingeAnchor((*it)->getJointID(), temp);
		curr->jointPos = VECTOR(temp[0], temp[1], temp[2]);
		// negative as ode has positive clockwise, real math ccw
		curr->jointAngle_l = -dJointGetHingeAngle((*it)->getJointID());
		curr->locMIN = -dJointGetHingeParam((*it)->getJointID(), dParamHiStop);
		curr->locMAX = -dJointGetHingeParam((*it)->getJointID(), dParamLoStop);

		curr->angle2goal_w = atan2( goal.y - curr->jointPos.y, goal.x - curr->jointPos.x);
		curr->angle2ee_w = atan2( eePos.y - curr->jointPos.y, eePos.x - curr->jointPos.x);

		i++;

	//	std::cout << "---(" << curr->jointPos.x << "," << curr->jointPos.y << ")" << ":  " << curr->locMIN << " -> " << curr->locMAX << ", currAngle: " << curr->jointAngle_l << std::endl;

	}

	curr->child = NULL;

	// Now that all values are known, iterate thru, filling in world angles to parent and radii to parent
	curr = base;

	while (curr->child != NULL)
	{
		curr->jointAngle_w = atan2( curr->child->jointPos.y - curr->jointPos.y, curr->child->jointPos.x - curr->jointPos.x);
		curr->rad2child = sqrt( pow(curr->child->jointPos.y - curr->jointPos.y, 2) + pow(curr->child->jointPos.x - curr->jointPos.x, 2));

		curr = curr->child;
	}

	// last one 'points' to the ee

	curr->jointAngle_w = atan2( eePos.y - curr->jointPos.y, eePos.x - curr->jointPos.x);
	curr->rad2child = sqrt( pow(eePos.y - curr->jointPos.y, 2) + pow(eePos.x - curr->jointPos.x, 2));



	// RESET THE JOINT POSiTIONS TO BE ANGLE (min+max)/2
	// This provides a better initial guess so it can actually converge.

	curr = base;
	
	while (curr->child != NULL)
	{
		dReal oldAng = curr->jointAngle_l;
		curr->jointAngle_l = (curr->locMIN + curr->locMAX)/2.0;
		dReal dTheta = curr->jointAngle_l - oldAng;

		curr->jointAngle_w += dTheta;

		IKJoint* updator = curr->child;

		while (updator != NULL)
		{
			
			updator->jointAngle_w += dTheta;

			updator->jointPos.x = updator->parent->jointPos.x + updator->parent->rad2child*cos(updator->parent->jointAngle_w);
			updator->jointPos.y = updator->parent->jointPos.y + updator->parent->rad2child*sin(updator->parent->jointAngle_w);

			if (updator->child == NULL)
				break;
			updator = updator->child;
			

		}
		eePos.x = updator->jointPos.x + updator->rad2child*cos(curr->jointAngle_w);
		eePos.y = updator->jointPos.y + updator->rad2child*sin(curr->jointAngle_w);

		curr = curr->child;

	}

	dReal oldAng = curr->jointAngle_l;
	curr->jointAngle_l = (curr->locMIN + curr->locMAX)/2.0;
	curr->jointAngle_w += (curr->jointAngle_l - oldAng);
	eePos.x = curr->jointPos.x + curr->rad2child*cos(curr->jointAngle_w);
	eePos.y = curr->jointPos.y + curr->rad2child*sin(curr->jointAngle_w);

	// END RESETTING

	// Begin Cyclic descent

	// while we are still further than IKtol from the goal position
	// UNCOMMENT THE FOLLOWING

	int iterations = 0;
	while (sqrt( pow(eePos.y - goal.y, 2) + pow(eePos.x - goal.x, 2)) > IK_tol->getdReal())
	{
		// for each joint in turn
		int j = 0;
		curr = base;
		while (curr != NULL)
		{

	//		std::cout << "-----Part " << j << "-----\n\n";
			
			// convert everything to local coords
			dReal w2l = curr->jointAngle_w - curr->jointAngle_l;

			curr->angle2goal_w = atan2( goal.y - curr->jointPos.y, goal.x - curr->jointPos.x);
			curr->angle2ee_w = atan2( eePos.y - curr->jointPos.y, eePos.x - curr->jointPos.x);
	//		std::cout << "angle2goal_w " << curr->angle2goal_w << "\nangle2ee_w " << curr->angle2ee_w << std::endl;

			dReal goal_l = curr->angle2goal_w - w2l;
			dReal ee_l = curr->angle2ee_w - w2l;

	//		std::cout << "goal_l " << goal_l << "\nee_l " << ee_l << std::endl;

			dReal dTheta = goal_l - ee_l;

			// Now rotate curr by dTheta and update all corresponding angles.

			dReal newJointAngle_l = curr->jointAngle_l + dTheta;

			// constrain between joint limits. LATER UPDATE ME TO CHOOSE THE LESSER OF TWO EVILS (MAX v. MIN)

			if ( newJointAngle_l > curr->locMAX)
			{
				newJointAngle_l = curr->locMAX;
				dTheta = newJointAngle_l - curr->jointAngle_l;
			}
			if ( newJointAngle_l < curr->locMIN)
			{
				newJointAngle_l = curr->locMIN;
				dTheta = newJointAngle_l - curr->jointAngle_l;
			}



			curr->jointAngle_l += dTheta;
			curr->jointAngle_w += dTheta;

	//		std::cout << "\nUpdated angles: " << "\nPart " << j << "\nloc: " << curr->jointAngle_l << "\nworld: " << curr->jointAngle_w << std::endl;

			IKJoint* updator = curr->child;
			if (updator == NULL)
			{
				eePos.x = curr->jointPos.x + curr->rad2child*cos(curr->jointAngle_w);
				eePos.y = curr->jointPos.y + curr->rad2child*sin(curr->jointAngle_w);
	//			std::cout << "EEPos: " << eePos.x << "," << eePos.y << std::endl;
				break;
			}

			int k = j+1;
			while (updator != NULL)
			{
				
	//			updator->jointAngle_l += dTheta;
				updator->jointAngle_w += dTheta;

				updator->jointPos.x = updator->parent->jointPos.x + updator->parent->rad2child*cos(updator->parent->jointAngle_w);
				updator->jointPos.y = updator->parent->jointPos.y + updator->parent->rad2child*sin(updator->parent->jointAngle_w);


	//			std::cout << "\nPart " << k << "\nloc: " << updator->jointAngle_l << "\nworld: " << updator->jointAngle_w << std::endl;
				k++;

				if (updator->child == NULL)
					break;
				updator = updator->child;
				

			}


			eePos.x = updator->jointPos.x + updator->rad2child*cos(curr->jointAngle_w);
			eePos.y = updator->jointPos.y + updator->rad2child*sin(curr->jointAngle_w);
	//		std::cout << " EE Pos (x,y): " << "(" << eePos.x << "," << eePos.y << ")" << std::endl;

			curr = curr->child;
			j++;
	//		std::cout << "\n\n\n\n" << std::endl;
		}

		iterations++;
		if (iterations > 10)
		{
			converged = false;
			//std::cerr << "Couldn't converge in 10 iterations..." << std::endl;
			break;
		}

	}

	curr = base;


	controllers.clear();

	for (std::vector<Joint*>::iterator it = jointList.end()-1; it != jointList.begin()-1; it--)
	{

		// negate jointAngle as ode/math cw/ccw issues.
		PDController* PD = new PDController(new Value(false, KP), new Value(false, KD), (*it), new Value(false, -curr->jointAngle_l), new Value(false, 0.0));

		PD->optimization = new inactiveOptimization();

		controllers.push_back(PD);
		
		curr = curr->child;
	}


	curr = base;
/*
	while (curr != NULL)
	{
		std::cout << curr->jointAngle_l << std::endl;
		curr = curr->child;
	}
	std::cout << "EEPOS: " << eePos.x << "," << eePos.y << std::endl;
*/		

}

bool IKSolver::writeToFile(std::ofstream& ofs)
{
    ofs << "IK "  
        << getPartNameFromEnum(toMove->name) << "."
        << ((global) ? "targetglobal" : "targetlocal") << "("
        << x_in->getdReal() << ", " << y_in->getdReal() << ", " << z_in->getdReal() << ").base("
        << base->getNameStr() << ").tolerance("
        << IK_tol->getdReal() << ");\n";

    return true;

}

void IKSolver::setOptimizable(std::vector<Value*>& unknowns)
{
    if (!IK_tol->isVariable) unknowns.push_back(IK_tol);
}
