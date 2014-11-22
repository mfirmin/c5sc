#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "controller.h"

#include <map>
#include <vector>
#include <utility>
#include <string>
#include <eigen3/Eigen/Dense>

class Value;
class Phase;
class Hierarchy;
class Trajectory;
class Objective;


double randN();

class Optimizer
{

    public:

        Optimizer();


        bool readFile(char*, std::map<std::string, Controller> &scripts, float stepsize);

        void setUnknowns();

        void initCMA();


        void CMAStep();
        void updateStep();

        Phase* getFirstOptPhase() { return optimization_phases.front(); }
        Phase* getLastOptPhase() { return optimization_phases.back(); }

        Hierarchy* getFirstOptimizationHierarchy() { return fromHierarchies.front().first; }
        Hierarchy* getFromTransitionHierarchy() { return fromHierarchies.back().first; }
        Hierarchy* getToTransitionHierarchy() { return toHierarchy; }
        Hierarchy* getToEndHierarchy() { return toEndHierarchy; }

        void startOptimizing() { optimizing = true; }
        bool isOptimizing() { return optimizing; }
        bool isFirstRun() { return firstRun; }

        void readGoalTrajectory(char*);
        void setGoalTrajectory(Trajectory* t) { goal_trajectory = t; }
        void setParentTrajectory(Trajectory* t) { parent_trajectory = t; }
        void setChildTrajectory(Trajectory* t) { child_trajectory = t; }
        Trajectory* getGoalTrajectory() { return goal_trajectory; }

        void incrementGenerationTime(float stepsize) { generationTime += stepsize; }
        void resetGenerationTime() { generationTime = 0; }
        float getGenerationTime() { return generationTime; }

        float getFitnessParent();
        float getFitnessChild();

        void updateFitnessChild();
        void updateFitnessParent();

        void setFitnessParent(double f) { fitness_parent = f; }
        void setFitnessChild(double f) { fitness_child = f; }
        void setIsFirstRun(bool f) { firstRun = f; }

        void updateControllerValues();
        void setCValsToMinimum();
        int getGenerationNum() { return generationNum; }
        void incrementGenerationNum() { generationNum++; }

        void updateObjectives(Hierarchy*);
        void updateToObjectives();
        void updateFromObjectives();


        bool fallen;
        float energy;

    private:

        int generationNum;
        bool firstRun;
        // just during from phase? TODO: Check this...
        bool optimizing;
        float generationTime;

        Trajectory* goal_trajectory;
        Trajectory* parent_trajectory;
        Trajectory* child_trajectory;

        std::vector<Value*> unknowns;
        std::vector<Phase*> optimization_phases; // list of phases of controller 'from' which we are optimizing.

        // list of phases we optimize. Last one is where we transition from.
//        std::vector<Hierarchy*> fromHierarchies;
        // Pair of Hierarchies and corresponding phase-specific objectives
        std::vector<std::pair<Hierarchy*, std::vector<Objective*> > > fromHierarchies; 
        Hierarchy* toHierarchy; // hierarchy we transition to .

        // last phase of the transitioned controller (ie, when we stop recording the trajectory.
        Hierarchy* toEndHierarchy; 

        // objective functions during the transitioned ctrlr
        std::vector<Objective*> toObjectives;
        // objective fns during the 'from' transitioning controller
        std::vector<Objective*> fromObjectives;

        double fitness_parent;
        double fitness_child;


        /* ---------- CMA DECLARATIONS ----------- */

        Eigen::VectorXd x_parent;
        Eigen::VectorXd x_child;
        Eigen::VectorXd z;
        Eigen::MatrixXd A;
        Eigen::MatrixXd C;
        double sigma; // Step Size
        double p_succ;
        Eigen::VectorXd pc;

        /* ----------- STEP SIZE CONTROL ---------- */

        double d;
        double p_succ_target = 2./11.;
        double cp = 1./12.;

        /* ----------- CMA PARAMS ----------------- */

        double cc;
        double ccov;
        double p_thresh = 0.44;


        int dimension;

        


        // ---- CMA Values ---- //

};

#endif // OPTIMIZER_H
