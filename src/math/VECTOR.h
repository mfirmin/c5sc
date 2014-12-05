#ifndef VECTOR_H
#define VECTOR_H

#define dSINGLE

#include <math.h>

class VECTOR
{

	public:

		VECTOR() { x = 0; y = 0; z = 0; }
		VECTOR(float a, float b, float c) {x = a; y = b; z = c; }
		VECTOR(const float* v) { x = v[0]; y = v[1]; z = v[2]; }

		const VECTOR operator+(const VECTOR& other) const { return VECTOR(this->x+other.x, this->y+other.y, this->z+other.z); }
		const VECTOR operator-(const VECTOR& other) const { return VECTOR(this->x-other.x, this->y-other.y, this->z-other.z); }
		const VECTOR operator*(const float& other) const { return VECTOR(this->x*other, this->y*other, this->z*other); }
		const VECTOR operator/(const float& other) const { return VECTOR(this->x/other, this->y/other, this->z/other); }
		VECTOR& operator=(const VECTOR& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
		VECTOR& operator +=(const VECTOR& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
		VECTOR cross(const VECTOR& other) { return VECTOR(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x); }
		bool operator==(const VECTOR& other) { return (this->x == other.x && this->y == other.y && this->z == other.z); }
		bool operator!=(const VECTOR& other) { return (this->x != other.x || this->y != other.y || this->z != other.z); }
        VECTOR& operator /=(const float other) { this->x /= other; this->y /= other; this->z /= other; return *this; }
		float dist(const VECTOR& other) const { return sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2)); }
        float distSq(const VECTOR& other) const { return pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2); }
	
		float x, y, z;


};



#endif // VECTOR_H
