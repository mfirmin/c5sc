#ifndef FLTREADER_H
#define FLTREADER_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>

#include "mesh.h"
#include "human.h"

class fltReader
{

	public:
		fltReader() {level=0;};
		fltReader(char* ifname, Human*);
		int open(char* ifname, Human*);
		void reverseChar(char*&, int);
		int a2i(char* a, int size);
		unsigned int a2ui(char* a, int size);
		bool a2b(char* a, int size);
		float a2f(char* a, int size);
		double a2d(char* a, int size);
		void a2a(char* a, char* b, int size);
		void printTopMtx();

		void multCurrMatrix(float* other);

		int parse();
		int parseHeader(unsigned int);
		int parseColorPalette(unsigned int);
		int parseMaterial(unsigned int);
		int parseLightSourcePalette(unsigned int);
		int parseViewpoint(unsigned int);
		int parseVertexPaletteHeader(unsigned int);
		int parseVertexNormalTexture(unsigned int);
		int parsePushLevelControl(unsigned int);
		int parseObject(unsigned int);
		int parseLongID(unsigned int);
		int parseMatrix(unsigned int);
		int parseFace(unsigned int);
		int parseVertexList(unsigned int);
		int parsePopLevelControl(unsigned int);
		int parseUnknown(int, unsigned int);

		int objectCount;

		Mesh mesh;
		std::stack<float*> currMatrix;


		int level;


	private:
		std::ifstream ifs;
		Human* human;


};

#endif // FLTREADER_H
