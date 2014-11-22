/***
 * Objective.h
 * Jul 9, 2014
 * Michael Firmin mfirmin@cs.ubc.ca
 *
 * Description: 
 * In which we define phase-specific objective functions for transition optimization
 *
 * Used by:
 * - optimizer.h
 */


#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <iostream>


class Objective
{

    public:

        virtual void update() = 0;
        virtual float evaluate() = 0;
        virtual void reset() = 0;

        void setStepsize(float s) { stepsize = s; }
        float getStepsize() { return stepsize; }
        float getElapsedTime() { return elapsedTime; }

    protected:
        float elapsedTime;
        float stepsize;
        float weight;

    private:

};


class timeObjective : public Objective
{
    public:

        timeObjective() { stepsize = -1; elapsedTime = 0; weight = 1.; }
        timeObjective(float s, float w) { stepsize = s; elapsedTime = 0; weight = w; }


        void update() { elapsedTime += stepsize; }
        float evaluate() { return weight*elapsedTime; }
        void reset() { elapsedTime = 0; }


    private:

};

class fallenObjective : public Objective
{
    public:

        fallenObjective() { stepsize = -1; elapsedTime = 0; weight = 1.; }
        fallenObjective(float s, float w) { stepsize = s; elapsedTime = 0; weight = w; }

        void setFallen(bool f) { fallen = f; }
        void update() { if (fallen) {fallen = false; elapsedTime += stepsize;}  return; }
        float evaluate() { return weight*elapsedTime; }
        void reset() { elapsedTime = 0; fallen = false; }

        
    private:
        bool fallen;
};

class energyObjective : public Objective
{
    public:
        energyObjective() { stepsize = -1; elapsedTime = 0; weight = 1.; currEnergy = 0; totalEnergy = 0;}
        energyObjective(float s, float w) { stepsize = s; elapsedTime = 0; weight = w; currEnergy = 0; totalEnergy = 0;}

        void setCurrEnergy( float ce) { currEnergy = ce; }
        void update() { totalEnergy += currEnergy; return; }
        float evaluate() { return weight*totalEnergy; }
        void reset() { elapsedTime = 0; totalEnergy = 0; currEnergy = 0; }

    private:
        // energy at step in time (weighted by stepsize)
        float currEnergy;
        float totalEnergy;

};



#endif // OBJECTIVE_H
