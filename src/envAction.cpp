

#include "envAction.h"
#include "environment.h"
#include "object.h"
#include "entity.h"

void toggleVisible(std::string s)
{

    Entity* ent = (env->getEntities().find(s)->second);
    ent->setVisible(!(ent->isVisible()));
    for (std::vector<Object*>::iterator iter = ent->getBodies().begin(); iter != ent->getBodies().end(); iter++)
    {
        (*iter)->setVisible(ent->isVisible());
    }

}

void toggleCollidable(std::string s)
{

    Entity* ent = (env->getEntities().find(s)->second);
    ent->setCollidable(!(ent->isCollidable()));
    for (std::vector<Object*>::iterator iter = ent->getBodies().begin(); iter != ent->getBodies().end(); iter++)
    {
        (*iter)->setCollidable(ent->isCollidable());
    }

}

void EnvAction::performAction()
{

    if (!done)
    {
        for (auto it = actions.begin(); it != actions.end(); it++)
        {
            (*it)();
        }
        done = true;
    }

}


