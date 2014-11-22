
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "globals.h"
#include "characterReader.h"

using namespace std;

int characterReader::read(char* filename)
{

	ifstream ifs;
	ifs.open(filename);

	if (!ifs)
	{
		cerr << "Cannot open " << filename << endl;
		return -1;
	}

	istringstream is;
	string str;

	while (getline(ifs, str))
	{
		is.clear();
		is.str(str);

		string action;

		is >> action;

		if (action.compare("T") == 0)
		{
			string type;
			is >> type;
			if (type.compare("global") == 0)
			{
				int torque;
				is >> torque;
				TORQUE_LIMIT = torque;
				cout << "Setting global torque limit to " << TORQUE_LIMIT << endl;
			}
			else
			{
				cerr << "Improper joint specification for setting torque" << endl;
				return -1;
			}
		}
		else
		{
			cerr << "Unexpected action in character file: " << action << endl;
			return -1;
		}
	}

	return 0;

}
