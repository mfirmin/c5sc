

#include "hierarchy.h"

#include <iostream>

void Hierarchy::print()
{

    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

}

bool Hierarchy::isEqual(Hierarchy* other)
{

    if (data.size() != other->data.size())
    {
        return false;
    }

    auto itThis = data.begin();
    for (auto itOther = other->data.begin(); itOther != other->data.end(); itOther++)
    {
        if (itThis->first.compare(itOther->first) != 0 || itThis->second != itOther->second)
        {
            return false;
        }
        itThis++;
    }
    


    
    /*
    std::cout << "this: " << std::endl;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << (*it).first << ": " << (*it).second << std::endl;
    }

    std::cout << "\n---\nother-> " << std::endl;
    for (auto it = other->data.begin(); it != other->data.end(); it++)
    {
        std::cout << (*it).first << ": " << (*it).second << std::endl;
    }
    */
    return true;
}
