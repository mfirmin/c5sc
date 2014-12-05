
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>

#include <vector>

#include "world.h"
#include "../math/VECTOR.h"
#include "../physics/ODEWrapper.h"
#include "../entity/Entity.h"

struct World::impl
{

    // Pair<Entity, simID>
    std::vector<std::pair<Entity*, int> > entities;
    ODEWrapper simulator;

};

World::World() 
{
    pimpl = new impl();
}

int World::init()
{

    pimpl->simulator = ODEWrapper();
    pimpl->simulator.init();

    return 0;


}

int World::addEntity(Entity* e)
{

    int box1 = pimpl->simulator.addCube(e->getPosition(), 1, e->getVelocity(), e->getRotation(), e->getOmega(), 10);

    pimpl->entities.push_back(std::pair<Entity*, int>(e, box1));

    return 0;

}

void World::go(float stepsize)
{
    while (true)
    {
        pimpl->simulator.step(stepsize);

        /*
        float pos = pimpl->simulator.getBodyPositionFromID(0).y;

        std::cout << pos << std::endl;
        if (pos < -5)
            break;
            */

    }
}

int main(int argc, char** argv)
{

    float STEPSIZE = 0.0001;

    World* world = new World();

    world->init();

    Entity* e = new Entity(VECTOR(0,-2,0));

    world->addEntity(e);

    world->go(STEPSIZE);

    std::cout << "yay2" << std::endl;
}
