
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "../math/VECTOR.h"

#include "Geometry.h"

struct Geometry::impl
{

};

Geometry::Geometry() 
{
    pimpl = new impl();
}

int Geometry::init()
{
    return 0;
}

/*
int main(int argc, char** argv)
{

}
*/
