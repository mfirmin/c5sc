#ifndef FACE_H
#define FACE_H

#include <vector>

struct Face
{
	// list of entries into the vertex palette
	std::vector<int> vertices;
	int name;
};

#endif // FACE_H
