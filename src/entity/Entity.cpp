
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
    VECTOR color;
    float opacity;

    Geometry* geom;
    
};

Entity::Entity(Geometry* g, VECTOR p, VECTOR v, VECTOR r, VECTOR w) 
{
    pimpl = new impl();
    pimpl->pos = p;
    pimpl->vel = v;
    pimpl->rot = r;
    pimpl->ang_vel= w;

    pimpl->color = VECTOR(.5,.5,.5);
    pimpl->opacity = 1;

    pimpl->geom = g;
}

int Entity::init()
{
    return 0;
}

VECTOR Entity::getColor()
{
    return pimpl->color;
}

void Entity::setColor(VECTOR c)
{
    pimpl->color = c;
}

float Entity::getOpacity()
{
    return pimpl->opacity;
}

void Entity::setOpacity(float o)
{
    pimpl->opacity = o;
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
void Entity::setPosition(VECTOR pos)
{
    pimpl->pos = pos;
}
VECTOR Entity::getVelocity()
{
    return pimpl->vel;

}
void Entity::setVelocity(VECTOR vel)
{
    pimpl->vel = vel;
}
VECTOR Entity::getRotation()
{
    return pimpl->rot;

}
void Entity::setRotation(VECTOR rot)
{
    pimpl->rot = rot;
}
VECTOR Entity::getOmega()
{
    return pimpl->ang_vel;

}
void Entity::setOmega(VECTOR o)
{
    pimpl->ang_vel = o;
}

/*
int main(int argc, char** argv)
{

}
*/
