#ifndef BOX_H
#define BOX_H 

#include "../math/VECTOR.h"
#include "Geometry.h"

class Box : public Geometry
{
    public:

        Box(VECTOR sides);

        int init();


        VECTOR getSides();

        void setSides(VECTOR);
        void setWidth(float);
        void setHeight(float);
        void setDepth(float);

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = BOX;
};

#endif // ENTITY_H
