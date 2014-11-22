#define dSINGLE

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ode/ode.h>
#include <assert.h>

#include <string.h>

#include "fltReader.h"
#include "mesh.h"
#include "vertex.h"

void fltReader::printTopMtx()
{

	float* mtx = mesh.components.back()->matrix;

	std::cout << mtx[0] << " " << mtx[4] << " " << mtx[8] << " " << mtx[12] << std::endl
		<< mtx[1] << " " << mtx[5] << " " << mtx[9] << " " << mtx[13] << std::endl
		<< mtx[2] << " " << mtx[6] << " " << mtx[10] << " " << mtx[14] << std::endl
		<< mtx[3] << " " << mtx[7] << " " << mtx[11] << " " << mtx[15] << std::endl << std::endl;

	mtx = NULL;


}

void fltReader::reverseChar(char*& a, int size)
{
	char* a_rev = new char[size];

	for (int i = 0; i < size; i++)
	{
		a_rev[i] = a[(size-1) -i];
	}
	
	a_rev[size] = '\0';

	a = a_rev;

	a_rev = NULL;

	return;
}


int fltReader::a2i(char* a, int size)
{

	int ret;

	reverseChar(a, size);

	if (size == 1)
		ret = *(std::int8_t *)a;
	else if (size == 2)
		ret = *(std::int16_t *)a;
        else if (size == 4)
		ret = *(std::int32_t *)a;

	delete [] a;

	return ret;
	
}

unsigned int fltReader::a2ui(char* a, int size)
{
	unsigned int ret;
	reverseChar(a, size);
	if (size == 1)
		ret = *(std::uint8_t *)a;
	else if (size == 2)
		ret = *(std::uint16_t *)a;
	else if (size == 4)
		ret = *(std::uint32_t *)a;

	delete [] a;

	return ret;
}

float fltReader::a2f(char* a, int size)
{
	reverseChar(a, size);
	float ret = *(float *)a;
	delete [] a;
	return ret;
}

double fltReader::a2d(char* a, int size)
{
	reverseChar(a, size);
	double ret = *(double *)a;
	delete [] a;
	return ret;
}

void fltReader::a2a(char* a, char* b, int size)
{

	for (int i = 0; i < size; i++)
	{
		b[i] = a[i];
	}

	b[size] = '\0';

}

bool fltReader::a2b(char* a, int size)
{
	reverseChar(a, size);
	bool ret = *(bool *)a;
	delete [] a;
	return ret;
}

int fltReader::open(char* ifname, Human* h)
{

	ifs.open(ifname, std::ios_base::binary);

	if (!ifs.is_open())
	{
		std::cerr << "Couldn't open file: " << ifname << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Successfully opened flt file: " << ifname << std::endl;
	}

	human = h;

	return 0;
	
}

fltReader::fltReader(char* ifname, Human* h)
{

	
	if (open(ifname, h) != 0)
	{
		std::cerr << "Couldn't create fltReader object, bad file name" << std::endl;
	}


}

int fltReader::parseHeader(unsigned int length)
{

	//std::cout << "Header Record Found" << std::endl;
	ifs.ignore(length-4);

	return 0;

}

int fltReader::parseColorPalette(unsigned int length)
{

	//std::cout << "Color Palette Record Found" << std::endl;
	ifs.ignore(length-4);

	return 0;

}

int fltReader::parseMaterial(unsigned int length)
{
	//std::cout << "Material Record Found" << std::endl;
	ifs.ignore(length-4);

	return 0;
}


int fltReader::parseLightSourcePalette(unsigned int length)
{
	//std::cout << "Light Source Palette Record Found" << std::endl;
	ifs.ignore(length-4);

	return 0;
}

int fltReader::parseViewpoint(unsigned int length)
{
	//std::cout << "Viewpoint Record Found" << std::endl;
	ifs.ignore(length-4);

	return 0;
}

// 67
int fltReader::parseVertexPaletteHeader(unsigned int length)
{
	//std::cout << "Vertex Palette Header Record Found" << std::endl;
	//std::cout << "... Skipping Vertex Palette (for now) ..." << std::endl;

	char buff[128];

	ifs.read(buff, 4); // read length of vertex palette header
	//ifs.ignore(a2i(buff, 4) - 8); // skip vertex palette (-8 is the header, ie this)
	

	return 0;
}

int fltReader::parseVertexNormalTexture(unsigned int length)
{
	//std::cout << "Vertex Record with Normal and Texture Format Found" << std::endl;

	char buff[128];

	//std::cout << length << std::endl;

	Vertex* temp = new Vertex;
	
	ifs.read(buff, 2);
	temp->color_index = a2ui(buff, 2);
	ifs.read(buff, 2);
	temp->flags = a2b(buff, 2);
	ifs.read(buff, 8);
	temp->pos.x = (dReal)a2d(buff, 8);
	ifs.read(buff, 8);
	temp->pos.y = (dReal)a2d(buff, 8);
	ifs.read(buff, 8);
	temp->pos.z = (dReal)a2d(buff, 8);

	ifs.read(buff, 4);
	temp->norm.x = (dReal)a2f(buff, 4);
	ifs.read(buff, 4);
	temp->norm.y = (dReal)a2f(buff, 4);
	ifs.read(buff, 4);
	temp->norm.z = (dReal)a2f(buff, 4);

	ifs.read(buff, 4);
	temp->texture_u = a2f(buff, 4);
	ifs.read(buff, 4);
	temp->texture_v = a2f(buff, 4);

	ifs.read(buff, 4);
	temp->packed_color = a2i(buff, 4);

	ifs.read(buff, 4);
	temp->vertex_color_index = a2ui(buff, 4);


	mesh.vertexPalette.push_back(temp);

	//std::cout << "pos: " << temp.pos.x << "," << temp.pos.y << "," << temp.pos.z << std::endl;
	//std::cout << "norm: " << temp.norm.x << "," << temp.norm.y << "," << temp.norm.z << std::endl;



	return 0;
}

int fltReader::parsePushLevelControl(unsigned int length)
{
	//std::cout << "V ";
	ifs.ignore(length-4);

	level++;


	if (currMatrix.size() == 0)
	{
		float temp[16] =  { 1, 0, 0, 0,
				   0, 1, 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1 };
		currMatrix.push(temp);
	}
	else
	{
		float* temp = new float[16];
		for (int i = 0; i < 16; i++)
		{
			temp[i] = currMatrix.top()[i];
		}
		currMatrix.push(temp);
	}

	return 0;
}

int fltReader::parseObject(unsigned int length)
{
	//std::cout << "Object Record Found " << level << std::endl;


	char buff[128];

	Component* temp = new Component;
	
	ifs.read(buff, 8);

	Object* const o = human->getObjectFromString(std::string(buff));

	if (o != NULL)
	{
		o->meshLocation = mesh.components.size();
	//	std::cout << mesh.components.size() << ", " << buff << std::endl;
	}
	

	ifs.read(buff, 4);
	temp->flags = a2b(buff, 4);
	ifs.read(buff, 2);
	temp->priority = a2i(buff, 2);
	ifs.read(buff, 2);
	temp->transparency = a2ui(buff, 2);
	ifs.ignore(4);
	ifs.read(buff, 2);
	temp->significance = a2i(buff, 2);
	ifs.ignore(2);


	for (int i = 0; i < 16; i++)
	{
		temp->matrix[i] = currMatrix.top()[i];
	}

	mesh.components.push_back(temp);

	//printTopMtx();

	return 0;
}

int fltReader::parseLongID(unsigned int length)
{

	//std::cout << "Long ID Record Found: ";

	char buff[128];
	ifs.read(buff, length-4);



	//std::cout << buff << std::endl;


	return 0;
}

void fltReader::multCurrMatrix(float* a)
{

	float b[16];

	if (currMatrix.size() > 1)
		currMatrix.pop(); //pop last element. b/c the new matrix depends on the old element.

	for (int i = 0; i < 16; i++)
	{
		b[i] = currMatrix.top()[i];
	}

	float* c = new float[16];

	for (int i = 0; i < 4; i++) // col
	{
		for (int j = 0; j < 4; j++) // row
		{
			c[j + i*4] = a[j]*b[i*4] + a[j+4]*b[i*4+1] + 
				a[j+8]*b[i*4+2] + a[j+12]*b[i*4+3];
		}
	}

	currMatrix.push(c); //push this new one.

	for (int i = 0; i < 16; i++)
	{
		mesh.components.back()->matrix[i] = currMatrix.top()[i];
	}

}

int fltReader::parseMatrix(unsigned int length)
{
	//std::cout << "Matrix Record Found " << level << std::endl;

	char buff[4];

	float temp[16];

	for (int i = 0; i < 16; i++)
	{
		ifs.read(buff,4);
		temp[i] = a2f(buff, 4);
	}

	multCurrMatrix(temp);

	//printTopMtx();

	return 0;
}

int fltReader::parseFace(unsigned int length)
{
	//std::cout << "Face Record Found" << std::endl;
	ifs.ignore(length-4);

	mesh.components.back()->faces.push_back(new Face);

	return 0;
}

//VertexList is a list of references into the vertex palette, defining a 
// face given by the preceeding Face Record
int fltReader::parseVertexList(unsigned int length)
{
	//std::cout << "Vertex List Record Found" << std::endl;

	char buff[4];

	int num_verts = (length-4)/4;

	for (int i = 0; i < num_verts; i++)
	{

		ifs.read(buff, 4);
		mesh.components.back()->faces.back()->vertices.push_back(a2i(buff,4)/60);

	}

	return 0;
}

int fltReader::parsePopLevelControl(unsigned int length)
{
	//std::cout << "^ ";
	ifs.ignore(length-4);

	level--;

	if (currMatrix.size() > 0)
	{
		currMatrix.pop();
	}
	else
	{
		std::cerr << "===Reached pop level control, but matrix stack is empty===" << std::endl;
	}

	return 0;
}

int fltReader::parseUnknown(int Opcode, unsigned int length)
{

	//std::cout << "Unknown Record Found with Opcode: " << Opcode << std::endl;
	//std::cout << length << std::endl;
	ifs.ignore(length-4);

	return 0;

}

int fltReader::parse()
{


	char buff[128];

	float fdata;
	char cdata;
	long ldata;
	int idata;
	unsigned int uidata;



while (ifs)
{
	

	ifs.read(buff, 2);
	int Opcode = a2i(buff, 2);

	

	ifs.read(buff, 2);
	unsigned int length = a2ui(buff, 2);




	switch (Opcode)
	{
		case 1:
			parseHeader(length);
			continue;
			break;
		case 32:
			parseColorPalette(length);
			continue;
			break;
		case 113:
			parseMaterial(length);
			continue;
			break;
		case 102:
			parseLightSourcePalette(length);
			continue;
			break;
		case 83:
			parseViewpoint(length);
			continue;
			break;
		case 67:
			parseVertexPaletteHeader(length);
			continue;
			break;
		case 70:
			parseVertexNormalTexture(length);
			continue;
			break;
		case 10:
			parsePushLevelControl(length);
			continue;
			break;
		case 4:
			parseObject(length);
			objectCount++;
			continue;
			break;
		case 33:
			parseLongID(length);
			continue;
			break;
		case 49:
			parseMatrix(length);
			continue;
			break;
		case 5:
			parseFace(length);
			continue;
			break;
		case 72:
			parseVertexList(length);
			continue;
			break;
		case 11:
			parsePopLevelControl(length);
			continue;
			break;
		default:

			parseUnknown(Opcode, length);

			if(ifs.eof())
			{
				return 0;
			}
			else
			{
				continue;
			}
			break;
	}

} // end while

	return 0;

}
