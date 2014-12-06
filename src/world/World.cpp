
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>

#include <vector>

#include "world.h"
#include "../entity/Geometry.h"
#include "../entity/Box.h"

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

    int ent = -1;
    if (e->getGeometry()->getType() == Geometry::Type::BOX) 
        ent = pimpl->simulator.addBox(e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotation(), e->getOmega(), 10);


    pimpl->entities.push_back(std::pair<Entity*, int>(e, ent));

    return 0;

}

void World::go(float stepsize)
{
    while (true)
    {
        pimpl->simulator.step(stepsize);

        
        float pos = pimpl->simulator.getBodyPositionFromID(0).y;

        std::cout << pos << std::endl;
        if (pos < -5)
            break;
            

    }
}

int main(int argc, char** argv)
{

    float STEPSIZE = 0.0001;

    World* world = new World();

    world->init();

    Geometry* g = new Box(VECTOR(5,5,5));

    Entity* e = new Entity(g, VECTOR(0,-2,0));

    world->addEntity(e);

    world->go(STEPSIZE);

    std::cout << "yay2" << std::endl;
}
