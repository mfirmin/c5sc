#ifndef ODEWRAPPER_H
#define ODEWRAPPER_H




#include "VECTOR.h"

class ODEWrapper
{


    public:

        ODEWrapper();


        int init();
        int addCube(VECTOR pos, float sides, VECTOR vel0, float ang0, float ang_vel0, float mass);
        int addBox(VECTOR pos, VECTOR sides, VECTOR vel0, float ang0, float ang_vel0, float mass);
        int addJoint(VECTOR pos, float theta=0, float dTheta=0);
        VECTOR getBodyPositionFromID(int id);

        void step(float);


    private:

        struct impl;
        impl* pimpl;

};

#endif // ODEWRAPPER_H
