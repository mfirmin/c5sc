#ifndef WORLD_H
#define WORLD_H

#include "../math/VECTOR.h"

class Entity;

class World
{
    public:

        World();

        int init();
        int addEntity(Entity* e);
        int addPointLight(VECTOR pos);
        void go(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
