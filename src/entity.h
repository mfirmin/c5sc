#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "VECTOR.h"

class Object;
class Joint;


class Entity
{
    public:

        Entity() { visible = true; collidable = true; }
        Entity(std::string s) { name = s; visible = true; collidable = true; }

        void pushObject(Object* o) { bodies.push_back(o); }

        std::vector<Object*>& getBodies() { return bodies; }
        std::vector<Joint*>& getJoints() { return joints; }

        bool isVisible() { return visible; }
        bool isCollidable() { return collidable; }

        void setVisible(bool v) { visible = v; }
        void setCollidable(bool c) { collidable = c; }

        std::string getName() { return name; }
        void setName(std::string s) { name = s; }

        VECTOR getCenter();

        ~Entity();

    private:
        std::vector<Object*> bodies;
        std::vector<Joint*> joints;

        bool visible, collidable;
        std::string name;


};


#endif // ENTITY_H
