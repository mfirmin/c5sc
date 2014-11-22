#ifndef CHARACTERREADER_H
#define CHARACTERREADER_H

#define dSINGLE

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class characterReader
{

	public:
		characterReader() {}
		int read(char* filename);

};


#endif // CHARACTERREADER_H
