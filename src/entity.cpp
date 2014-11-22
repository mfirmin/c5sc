

#include "entity.h"
#include "object.h"

Entity::~Entity()
{
    for (auto it = bodies.begin(); it != bodies.end(); it++)
    {
        delete (*it);
    }

}

VECTOR Entity::getCenter()
{
    VECTOR ret(0,0,0);

    for (auto it = bodies.begin(); it != bodies.end(); it++)
    {
        ret += VECTOR(dBodyGetPosition((*it)->Body));
    }
    ret /= bodies.size();





    

    return ret;

}
