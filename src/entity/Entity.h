#ifndef ENTITY_H
#define ENTITY_H

#include "../math/VECTOR.h"

class Entity
{
    public:

        Entity(VECTOR p=VECTOR(0,0,0), VECTOR v=VECTOR(0,0,0), VECTOR r=VECTOR(0,0,0), VECTOR w=VECTOR(0,0,0));

        int init();

        VECTOR getPosition();
        VECTOR getVelocity();
        VECTOR getRotation();
        VECTOR getOmega();

    private:

        struct impl;
        impl* pimpl;
};

#endif // ENTITY_H
