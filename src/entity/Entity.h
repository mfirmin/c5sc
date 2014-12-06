#ifndef ENTITY_H
#define ENTITY_H

#include "../math/VECTOR.h"

class Geometry;

class Entity
{
    public:

        Entity(Geometry*, VECTOR p=VECTOR(0,0,0), VECTOR v=VECTOR(0,0,0), VECTOR r=VECTOR(0,0,0), VECTOR w=VECTOR(0,0,0));

        int init();

        VECTOR getPosition();
        VECTOR getVelocity();
        VECTOR getRotation();
        VECTOR getOmega();
        Geometry* getGeometry();
        void setGeometry(Geometry*);

    private:

        struct impl;
        impl* pimpl;
};

#endif // ENTITY_H
