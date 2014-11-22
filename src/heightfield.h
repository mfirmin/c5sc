#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H

#include "object.h" 


class Heightfield : public Object
{

    public:

        Heightfield(char* filename);

        int readFromFile(char* filename);
        dReal* getData() { return data; } 
        int getSize() { return num_samples; } 
        dReal getStart() { return x_start; }
        dReal getWidth() { return width; }

        ~Heightfield();
    private:
        dReal* data;
        dReal width;
        int num_samples;

        dReal x_start;

};

#endif // HEIGHTFIELD_H
