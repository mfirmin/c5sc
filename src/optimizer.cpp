
#include "optimizer.h"
#include "hierarchy.h"
#include "phase.h"
#include "trajectory.h"
#include "objective.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <typeinfo>
#define TWO_PI 6.2831853071795864769252866


double randN()
{

    double rand1, rand2;

    rand1 = rand()/ ((double) RAND_MAX);

    if (rand1 < 1e-100) rand1 = 1e-100;
    rand1 = -2*log(rand1);
    rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;

    return sqrt(rand1) * cos(rand2);

}

void Optimizer::updateStep()
{
    // 5. --- Update Step Size.
    //
    int lambda_succ; 

    fitness_child <= fitness_parent ? lambda_succ = 1 : lambda_succ = 0;

    p_succ = (1-cp)*p_succ + cp*lambda_succ;
    sigma = sigma * exp( (1./d) * ( p_succ - (p_succ_target / (1. - p_succ_target)) * (1 - p_succ)));

    // 6. --- Update x_parent, Cov, if child is better.
    //
    if (lambda_succ == 1)
    {
        x_parent = x_child;
        fitness_parent = fitness_child;

        if (p_succ < p_thresh)
        {
            pc = pc*(1-cc) + (A*z)*sqrt(cc*(2-cc));
            C = C*(1-ccov) + pc * pc.transpose()*ccov;
        }
        else
        {
            pc = pc*(1-cc);
            C = C*(1-ccov) + (pc*pc.transpose() + C*cc*(2-cc))*ccov;
        }


    }

}

void Optimizer::CMAStep()
{

    /* ------------------ CMA STEP -------------------
     * 1. Determine A st C = AA^T
     */
    Eigen::LLT<Eigen::MatrixXd> lltofC(C);

    A = lltofC.matrixL();

    // 2. z ~ normal_distribution(0,I);

    for (int i = 0; i < dimension; i++)
    {
        z(i) = randN();
    }

    // 3. x_child <- x_parent + sigma*A*z

    x_child = x_parent + A*z*sigma;


    // 4. Test Fitness with x_child (run program...)
}

void Optimizer::initCMA()
{

    fallen = false;

    srand(time(NULL));

    dimension = unknowns.size();

    std::cout << "Problem dimension: " << dimension << std::endl;

    x_parent = Eigen::VectorXd(dimension);

    int i = 0;
    for (auto it = unknowns.begin(); it != unknowns.end(); it++)
    {
        assert(!(*it)->isVariable);
        x_parent(i++) = (*it)->getdReal();
    }

    C = Eigen::MatrixXd::Identity(dimension, dimension);
    z = Eigen::VectorXd(dimension);

    // --- STEP SIZE CONTROL

    d = 1 + (double)dimension/2.;
    
    // --- CMA PARAMS
    
    cc = 2./(double)(dimension+2.);
    ccov = 2./(double)(dimension*dimension+6);

//    sigma = 0.005; // PROBLEM DEPENDENT (TODO: FIGURE ME OUT)

    p_succ = p_succ_target;
    pc = Eigen::VectorXd::Zero(dimension);

}

Optimizer::Optimizer()
{
    toHierarchy = new Hierarchy;
    toEndHierarchy = new Hierarchy;
    optimizing = false;
    firstRun = true;
    goal_trajectory = new Trajectory();
//    readGoalTrajectory(goal_traj);

    generationTime = 0;
    generationNum = 0;

    fallen = false;

}

bool Optimizer::readFile(char* fname, std::map<std::string, Controller> &scripts, float stepsize)
{

    std::ifstream ifs;
    ifs.open(fname);

    if (!ifs)
    {
        std::cerr << "Error opening optimization file " << fname << std::endl;
        return false;
    }

    std::string str;
    int ival;
    float fval;
    char cval = '\0';

    ifs >> str;
    if (str.compare("TRAJECTORY") != 0)
    {
        std::cerr << "Expected 'TRAJECTORY', got: " << str << std::endl;
        return false;
    }

    std::string goal_traj;
    ifs >> goal_traj;

    readGoalTrajectory((char*)goal_traj.c_str());

    ifs >> str;
    if (str.compare("SIGMA") != 0)
    {
        std::cerr << "Expected 'SIGMA', got: " << str << std::endl;
        return false;
    }

    float ss;
    ifs >> sigma;

    ifs >> str; 

    if (str.compare("FROM") != 0)
    {
        std::cerr << "Expected 'FROM', got: " << str << std::endl;
        return false;
    }

    int numPhases;
    ifs >> numPhases;

    for (int i = 0; i < numPhases; i++)
    {
        Hierarchy* temp = new Hierarchy;

        ifs >> cval;
        // read in base script
        if (cval != '-')
        {
            std::cerr << "Expected '-', got: " << cval << std::endl;
            return false;
        }
        // read in subscripts...
        do 
        {
            ifs >> str;
            ifs >> ival;


            temp->push(str, ival);
            ifs >> cval;
        } while (cval == '>');
        // read in additional objectives for this phase (phase-specific).
        std::vector<Objective*>* objs_ptr = new std::vector<Objective*>;
        while (cval == '+')
        {

            std::string str2;
            ifs >> str2;
            if (str2.compare("min") == 0)
            {
                ifs >> str2;
                if (str2.compare("time") == 0)
                {
                    float _float;
                    ifs >> _float;
                    objs_ptr->push_back(new timeObjective(stepsize, _float)); 
                }
            }

            ifs >> cval;
        }
        // read in terminus character.

        assert(cval == ';');

        optimization_phases.push_back(&(scripts.find(str)->second.phases.at(ival)));

        fromHierarchies.push_back(std::pair<Hierarchy*, std::vector<Objective*> >(temp, *objs_ptr ) );


    }

    // read in FROM (spanning) objectives
    ifs >> str;
    if (str.compare("OBJECTIVES") == 0)
    {

        std::cout << "OBJECTIVES FOUND!" << std::endl;
        ifs >> cval;
        while (cval == '+')
        {

            std::string str2;
            ifs >> str2;
            if (str2.compare("min") == 0)
            {
                ifs >> str2;
                if (str2.compare("time") == 0)
                {
                    std::cout << "time obj found FROM" << std::endl;
                    float _float;
                    ifs >> _float;
                    std::cout << _float << std::endl;
                    fromObjectives.push_back(new timeObjective(stepsize, _float)); 
                }
                else if (str2.compare("fallen") == 0)
                {
                    std::cout << "fallen obj found FROM" << std::endl;
                    float _float;
                    ifs >> _float;
                    fromObjectives.push_back(new fallenObjective(stepsize, _float));
                }
                else if (str2.compare("energy") == 0)
                {
                    std::cout << "energy objective found FROM" << std::endl;
                    float _float;
                    ifs >> _float;
                    fromObjectives.push_back(new energyObjective(stepsize, _float));
                }
            }

            ifs >> cval;
        }
    }

    assert(cval == ';');

    ifs >> str;
    if (str.compare("TO") != 0)
    {
        std::cerr << "Expected 'TO', got: " << str << std::endl;
        return false;
    }
    
    ifs >> cval;
    if (cval != '-')
    {
        std::cerr << "Expected '-', got: " << cval << std::endl;
        return false;
    }
    while (cval != ';')
    {
        ifs >> str;
        ifs >> ival;

        

        toHierarchy->push(str, ival);
        ifs >> cval;
    }

    ifs >> cval;
    if (cval != '-')
    {
        std::cerr << "Expected '-', got: " << cval << std::endl;
        return false;
    }
    while (cval != ';')
    {
        ifs >> str;
        ifs >> ival;

        

        toEndHierarchy->push(str, ival);
        ifs >> cval;
    }

    ifs >> str; 

    if (str.compare("OBJECTIVES") == 0)
    {

        std::cout << "OBJECTIVES FOUND!" << std::endl;
        ifs >> cval;
        while (cval == '+')
        {

            std::string str2;
            ifs >> str2;
            if (str2.compare("min") == 0)
            {
                ifs >> str2;
                if (str2.compare("time") == 0)
                {
                    std::cout << "time objective found (TO)" << std::endl;
                    float _float;
                    ifs >> _float;
                    std::cout << _float << std::endl;
                    toObjectives.push_back(new timeObjective(stepsize, _float)); 
                }
                else if (str2.compare("fallen") == 0)
                {
                    std::cout << "fallen objective found (TO)" << std::endl;
                    float _float;
                    ifs >> _float;
                    toObjectives.push_back(new fallenObjective(stepsize, _float));
                }
                else if (str2.compare("energy") == 0)
                {
                    std::cout << "energy objective found (TO)" << std::endl;
                    float _float;
                    ifs >> _float;
                    toObjectives.push_back(new energyObjective(stepsize, _float));
                }
            }

            ifs >> cval;
        }
    }


    return true;


}

void Optimizer::updateObjectives(Hierarchy* currHierarchy)
{
    for (auto it = fromHierarchies.begin(); it != fromHierarchies.end(); it++)
    {
        if (it->first->isEqual(currHierarchy))
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {


                (*it2)->update();
            }
        }
    } 
}
void Optimizer::updateToObjectives()
{
    for (auto it = toObjectives.begin(); it != toObjectives.end(); it++)
    {

        if (fallenObjective* obj = dynamic_cast<fallenObjective*>(*it))
        {
            obj->setFallen(this->fallen);
        }
        else if (energyObjective* obj = dynamic_cast<energyObjective*>(*it))
        {
            obj->setCurrEnergy(this->energy);
        } 
        (*it)->update();

    }

}

void Optimizer::updateFromObjectives()
{
    for (auto it = fromObjectives.begin(); it != fromObjectives.end(); it++)
    {

        if (fallenObjective* obj = dynamic_cast<fallenObjective*>(*it))
        {
            obj->setFallen(this->fallen);
        }
        else if (energyObjective* obj = dynamic_cast<energyObjective*>(*it))
        {
            obj->setCurrEnergy(this->energy);
        } 
        (*it)->update();

    }

}

void Optimizer::readGoalTrajectory(char* fname)
{

    goal_trajectory->readFromFile(fname);

}

void Optimizer::updateFitnessParent()
{
    fitness_parent = parent_trajectory->distance(*goal_trajectory);

    for (auto it = fromHierarchies.begin(); it != fromHierarchies.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            fitness_parent += (*it2)->evaluate();
            std::cout << "Other: (from phase-specific)" << (*it2)->evaluate() << std::endl;
            (*it2)->reset();
        }
    }
    for (auto it = fromObjectives.begin(); it != fromObjectives.end(); it++)
    {
        fitness_parent += (*it)->evaluate();
        std::cout << "Other (from): " << (*it)->evaluate() << std::endl;
        (*it)->reset();
    }
    for (auto it = toObjectives.begin(); it != toObjectives.end(); it++)
    {
        fitness_parent += (*it)->evaluate();
        std::cout << "Other (to): " << (*it)->evaluate() << std::endl;
        (*it)->reset();
    }

}
void Optimizer::updateFitnessChild()
{
    fitness_child = child_trajectory->distance(*goal_trajectory);
    for (auto it = fromHierarchies.begin(); it != fromHierarchies.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            fitness_child += (*it2)->evaluate();
            std::cout << "Other: (from phase-specific)" << (*it2)->evaluate() << std::endl;
            (*it2)->reset();
        }
    }
    for (auto it = fromObjectives.begin(); it != fromObjectives.end(); it++)
    {
        fitness_child += (*it)->evaluate();
        std::cout << "Other (from): " << (*it)->evaluate() << std::endl;
        (*it)->reset();
    }
    for (auto it = toObjectives.begin(); it != toObjectives.end(); it++)
    {
        fitness_child += (*it)->evaluate();
        std::cout << "Other (to): " << (*it)->evaluate() << std::endl;
        (*it)->reset();
    }
    /*
    if (fallen)
    {
        fitness_child = 100000;
        fallen = false;
    }
    */
}

float Optimizer::getFitnessParent()
{
    return fitness_parent;
}
float Optimizer::getFitnessChild()
{
    return fitness_child;
}

void Optimizer::setUnknowns()
{

    for (auto it = optimization_phases.begin(); it != optimization_phases.end(); it++)
    {
        std::cout << *it << std::endl;
        (*it)->setOptimizable(unknowns);
    }

}

void Optimizer::updateControllerValues()
{

    assert(unknowns.size() == x_child.size());

    int i = 0;
    for (auto it = unknowns.begin(); it != unknowns.end(); it++)
    {
        // ones that are variables are never added to the optimization in the first place, so it is okay to say false here.
        (*it)->set(false, x_child(i++));
    }

}

void Optimizer::setCValsToMinimum()
{

    assert(unknowns.size() == x_child.size());

    int i = 0;
    for (auto it = unknowns.begin(); it != unknowns.end(); it++)
    {
        (*it)->set(false, x_parent(i++));
    }

}
