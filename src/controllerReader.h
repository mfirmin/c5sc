#ifndef CONTROLLERREADER_H
#define CONTROLLERREADER_H

#define dSINGLE

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "human.h"
#include "action.h"
#include "value.h"

#include <ode/ode.h>

class controllerReader
{

	public:
		controllerReader() {};
		int readScript(char* filename, const Human&, std::map<std::string, Controller>&);
		PDController* createPDController(const Human&, std::string, Value*, Value*, Value*, Value*);
		VPDController* createVPDController(const Human&, std::string, std::string, Value*, Value*, Value*, Value*, bool);



	private:

};




#endif // CONTROLLERREADER_H
