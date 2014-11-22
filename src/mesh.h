#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vertex.h"
#include "component.h"

class Mesh
{

	public:
		std::vector<Vertex*> vertexPalette;
		// each component has faces, which have references to the vertex palette.
		std::vector<Component*> components;

		void createHull(int c_num);



};

#endif // MESH_H
