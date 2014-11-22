#ifndef VERTEX_H
#define VERTEX_H

#include "VECTOR.h"

struct Vertex
{
	VECTOR pos;
	VECTOR norm;
	float texture_u, texture_v;
	unsigned int color_index;
	bool flags;
	int packed_color;
	unsigned int vertex_color_index;
};

#endif // VERTEX_H
