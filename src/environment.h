#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>

#include "VECTOR.h"

// class Object;
class Entity;

enum obj_type { BOX_, SPHERE_, CYLINDER_, PLANE_, HEIGHTFIELD_, CUSTOM_ };

struct obj_info
{
    obj_info() { collidable = true; visible = true; }
    obj_info(obj_info* other) 
    { 
        this->type = other->type;
        this->mass = other->mass;
        this->rad = other->rad;
        this->pos = other->pos;
        this->dim = other->dim;
        this->pos2 = other->pos2;
        this->collidable = other->collidable;
        this->visible = other->visible;
        if (type==CUSTOM_)
        {
            this->children = new std::vector<obj_info*>;
            for (int i = 0; i < other->children->size(); i++)
            {
                this->children->push_back(new obj_info(other->children->at(i)));
            }
        }
    }

    obj_type type;
    dReal mass;
    dReal rad;
    VECTOR pos;
    VECTOR dim;
    VECTOR pos2;

    bool collidable;
    bool visible;

    std::string name;
    std::vector<obj_info*>* children;

    void addPos(VECTOR shift)
    {

        pos += shift;
        if (type == CUSTOM_)
        {
            for (int i = 0; i < children->size(); i++)
            {
                children->at(i)->addPos(shift);
            }
        }
    }


};


class Environment
{

	public:

		Environment() {}

		void setFromFile(std::string fname);

//		std::vector<Object*>& getObjects() { return objects; }

//        std::vector<Entity*>& getEntities() { return entities; }
//

        void addEntity(Entity*);
        void deleteEntity(std::string);

        std::map<std::string, Entity*>& getEntities() { return entities; }
	private:

//		std::vector<Entity*> entities;
        std::map<std::string, Entity*> entities;


};

#endif // ENVIRONMENT_H


