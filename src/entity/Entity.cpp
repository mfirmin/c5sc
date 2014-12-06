
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity.h"
#include "../math/VECTOR.h"

struct Entity::impl
{

    VECTOR pos;
    VECTOR vel;
    VECTOR rot;
    VECTOR ang_vel;

    Geometry* geom;
    
};

Entity::Entity(Geometry* g, VECTOR p, VECTOR v, VECTOR r, VECTOR w) 
{
    pimpl = new impl();
    pimpl->pos = p;
    pimpl->vel = v;
    pimpl->rot = r;
    pimpl->ang_vel= w;

    pimpl->geom = g;
}

int Entity::init()
{
    return 0;
}

Geometry* Entity::getGeometry()
{
    return pimpl->geom;
}

void Entity::setGeometry(Geometry* g)
{
    pimpl->geom = g;
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
