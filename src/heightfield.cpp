
#define dSINGLE

#include <ode/ode.h>

#include <iostream>
#include "heightfield.h"
#include "globals.h"

Heightfield::Heightfield(char* filename)
{
    int err = readFromFile(filename);
    if (err != 0)
    {
        std::cerr << "Error reading in file " << filename << ": " << err << std::endl;
        return;
    }

    dHeightfieldDataID d = dGeomHeightfieldDataCreate ();

    dGeomHeightfieldDataBuildSingle (d, data, 0, width, 2, num_samples, 2, 1, 0, 1, 0);
    dGeomHeightfieldDataSetBounds (d, -.5, 4);
    Geom[0] = dCreateHeightfield(Space, d, 1);
    dGeomSetPosition(Geom[0], x_start + width/2.0, 0, -10);
    type = HEIGHTFIELD;

	geom2obj.insert(std::pair<dGeomID, Object*>(Geom[0], this));

}
int Heightfield::readFromFile(char* filename)
{

    std::ifstream ifs(filename);

    if (!ifs)
    {
        std::cerr << "Cannot open heightfield file " << filename << std::endl;
        return -1;
    }

    ifs >> x_start >> width >> num_samples;
    // two rows of data, (z direction) 
    data = new dReal[num_samples*2];
    for (int i = 0; i < num_samples; i++)
    {
        dReal temp;
        ifs >> temp;
        data[i] = data[i+num_samples] = temp;
    }
    
    return 0;


}

Heightfield::~Heightfield()
{
 //    dGeomHeightfieldDataDestroy(d); 
}
