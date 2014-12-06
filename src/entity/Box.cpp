
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "Box.h"

struct Box::impl
{

    VECTOR sides;
    
};

Box::Box(VECTOR s) 
{
    pimpl = new impl();
    pimpl->sides = s;
}

int Box::init()
{
    return 0;
}

VECTOR Box::getSides()
{
    return pimpl->sides;

}

void Box::setSides(VECTOR s)
{
    pimpl->sides = s;
}

void Box::setWidth(float w)
{
    pimpl->sides.x = w;
}
void Box::setHeight(float h)
{
    pimpl->sides.y = h;
}
void Box::setDepth(float d)
{
    pimpl->sides.z = d;
}


/*
int main(int argc, char** argv)
{

}
*/
