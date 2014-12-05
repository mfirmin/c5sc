#ifndef WORLD_H
#define WORLD_H

class Entity;

class World
{
    public:

        World();

        int init();
        int addEntity(Entity* e);
        void go(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
