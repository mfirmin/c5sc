#ifndef COMPONENT_H
#define COMPONENT_H

#define dSingle

#include <vector>
#include <ode/ode.h>
#include <utility>
#include "face.h"

struct Component
{
	// list of faces that make up this component

	char name[8];
	bool flags;
	int priority;
	unsigned int transparency;
	int significance;

	float matrix[16];

	std::vector<Face*> faces;
	std::vector<std::pair<dReal, dReal> > hull;
};


#endif // COMPONENT_H
