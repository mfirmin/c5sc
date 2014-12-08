#ifndef ENTITY_H
#define ENTITY_H

#include "../math/VECTOR.h"

class Geometry;

class Entity
{
    public:

        Entity(Geometry*, VECTOR p=VECTOR(0,0,0), VECTOR v=VECTOR(0,0,0), VECTOR r=VECTOR(0,0,0), VECTOR w=VECTOR(0,0,0));

        int init();


        // Physical Properties

        VECTOR getPosition();
        void setPosition(VECTOR);
        VECTOR getVelocity();
        void setVelocity(VECTOR);
        VECTOR getRotation();
        void setRotation(VECTOR);
        VECTOR getOmega();
        void setOmega(VECTOR);
        Geometry* getGeometry();
        void setGeometry(Geometry*);


        // Stylistic Properties 
        //

        VECTOR getColor();
        void setColor(VECTOR);

        float getOpacity();
        void setOpacity(float);


    private:

        struct impl;
        impl* pimpl;
};

#endif // ENTITY_H
