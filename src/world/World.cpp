
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>

#include <vector>

#include <time.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif

#include "world.h"
#include "../entity/Geometry.h"
#include "../entity/Box.h"

#include "../math/VECTOR.h"
#include "../physics/ODEWrapper.h"
#include "../entity/Entity.h"
#include "../renderer/Renderer.h"


#ifdef __APPLE__
typedef timeval _timeval;
#endif
#ifndef __APPLE__
typedef timespec _timeval;
#endif

struct World::impl
{

    // Entity objects.
    std::vector<Entity*> entities;
    // references to simulation IDs.
    std::vector<int> simIDs;

    ODEWrapper simulator;

    Renderer renderer;

    void updateEntities();

    void waitForRender(_timeval&);

    float frameTime;

    const float framerate = 1./30.;

    // Last render;

};

World::World() 
{
    pimpl = new impl();
}

int World::init()
{

    pimpl->simulator = ODEWrapper();
    pimpl->simulator.init();
    pimpl->renderer = Renderer();
    pimpl->frameTime = 0;

    pimpl->renderer.init();

    return 0;


}

int World::addPointLight(VECTOR pos)
{
    if (pimpl->renderer.addPointLight(pos) != 0)
    {
        std::cerr << "Error adding point light (world.cpp)" << std::endl;
        return -1;
    }
    return 0;

}

int World::addEntity(Entity* e)
{

    int ent = -1;
    if (e->getGeometry()->getType() == Geometry::Type::BOX) 
        ent = pimpl->simulator.addBox(e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotation(), e->getOmega(), 10);

    if (ent < 0)
    { 
        std::cerr << "Error encountered trying to add entity to simulator (World.addEntity)" << std::endl;
        return -1;
    }

    pimpl->entities.push_back(e);
    pimpl->simIDs.push_back(ent);;

    return 0;
}

void World::impl::updateEntities()
{

    auto IDit = simIDs.begin();
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->setPosition(simulator.getBodyPositionFromID(*IDit));
        IDit++;
    }

}

void World::impl::waitForRender(_timeval& last)
{
	long frame = (framerate * 1E9);
    int i = 0;
    _timeval now;
#ifndef __APPLE__
    clock_gettime(CLOCK_REALTIME, &now);
    while ( (now.tv_sec * 1E9 + now.tv_nsec) - (last.tv_sec * 1E9 + last.tv_nsec) < frame)
    {
        clock_gettime(CLOCK_REALTIME, &now);
    }

    clock_gettime(CLOCK_REALTIME, &last);
#endif
    
#ifdef __APPLE__
    gettimeofday(&now, NULL);
    while ( (now.tv_sec * 1E9 + now.tv_usec * 1E3) - (last.tv_sec * 1E9 + last.tv_usec * 1E3) < frame)
    {
        gettimeofday(&now, NULL);
        i++;
    }

    gettimeofday(&last, NULL);
#endif

}

void World::go(float stepsize)
{
#ifndef __APPLE__
	timespec last;
    clock_gettime(CLOCK_REALTIME, &last);
#endif

#ifdef __APPLE__
    timeval last;
    gettimeofday(&last, NULL);
#endif
    while (true)
    {
        pimpl->simulator.step(stepsize);

        pimpl->updateEntities();
        pimpl->frameTime+= stepsize;

        if (pimpl->frameTime > pimpl->framerate)
        {
            pimpl->waitForRender(last);
            pimpl->renderer.render(pimpl->entities);
            pimpl->frameTime = 0;
        }
        
            

    }
}

int main(int argc, char** argv)
{

    float STEPSIZE = 0.0001;

    World* world = new World();

    world->init();

    world->addPointLight(VECTOR(10,10,10));

    Geometry* g = new Box(VECTOR(1,1,1));

    Entity* e = new Entity(g, VECTOR(0,10,0));
    e->setColor(VECTOR(1,.3,.3));

    Entity* e2 = new Entity(new Box(VECTOR(2,1,1)), VECTOR(0,15,0));
    e2->setColor(VECTOR(0,.4,.7));

    world->addEntity(e);
    world->addEntity(e2);

    world->go(STEPSIZE);

    std::cout << "yay2" << std::endl;
}
