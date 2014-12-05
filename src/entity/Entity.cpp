
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity.h"
#include "../math/VECTOR.h"

class Geometry;

struct Entity::impl
{

    VECTOR pos;
    VECTOR vel;
    VECTOR rot;
    VECTOR ang_vel;

    Geometry* geom;
    
};

Entity::Entity(VECTOR p, VECTOR v, VECTOR r, VECTOR w) 
{
    pimpl = new impl();
    pimpl->pos = p;
    pimpl->vel = v;
    pimpl->rot = r;
    pimpl->ang_vel= w;
}

int Entity::init()
{
    return 0;
}

VECTOR Entity::getPosition()
{
    return pimpl->pos;

}
VECTOR Entity::getVelocity()
{
    return pimpl->vel;

}
VECTOR Entity::getRotation()
{
    return pimpl->rot;

}
VECTOR Entity::getOmega()
{
    return pimpl->ang_vel;

}

/*
int main(int argc, char** argv)
{

}
*/
