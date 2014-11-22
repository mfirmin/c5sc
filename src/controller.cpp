
#include "controller.h"
#include "phase.h"
#include "globals.h"
#include "value.h"
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <assert.h>


Controller::Controller(StateInfo* s, Human* h)
{

    numParams = 0;
    phases.push_back(Phase(s, h));
    name = "transitioner";
    displayName = "Transitioning";
    currPhase = 0;

    std::vector<Value*> placeHolder;
    setParams(placeHolder);

}
void Controller::setGlobals()
{

    for (auto it = values.begin(); it != values.end(); it++)
    {
        switch ((*it).first)
        {
            case SET_TORQUE_LIMIT:
                TORQUE_LIMIT = (*it).second;
                break;
        }
    }

}

void Controller::setParams(std::vector<Value*> &valuesVec)
{

	// If you are having problems with paramsVec size != valuesVec, you just
	// forgot to add the controller to the SCRIPTS import line.
	// there's nothing wrong here.

	assert(paramNames.size() == valuesVec.size());

	std::map<std::string, std::string>* temp = new std::map<std::string, std::string>();

	for (int i = 0; i < paramNames.size(); i++)
	{

		char buff[32];
		sprintf(buff, "%f", valuesVec.at(i)->getdReal());

		std::pair<std::string, std::string> p(paramNames.at(i), std::string(buff));
		temp->insert(p);
	}

	//lookupTable.pop();
	lookupTable.push(temp);
//	lookupTable = temp;

	temp = NULL;

}

bool Controller::writeToFile(std::string ofname, std::map<std::string, Controller>& scripts)
{
    std::ofstream ofs;
    ofs.open(ofname);
    if (!ofs)
    {
        std::cerr << "Error opening file " << ofname << " for writing." << std::endl;
        return false;
    }

    if (!(this->writeToFile(ofs, scripts)))
    { 
        std::cerr << "Error writing file " << ofname << std::endl;
        return false;
    }

    ofs.close();

    return true;


}


bool Controller::writeToFile(std::ofstream& ofs, std::map<std::string, Controller>& scripts)
{

    /*
    std::ofstream ofs;
    ofs.open(ofname);
    */


    if (dependencies.size() > 0)
    {
        ofs << "SCRIPTS ";
        for (int i = 0; i < dependencies.size()-1; i++)
        {
            ofs << dependencies.at(i) << ", ";
        }
        ofs <<  dependencies.at(dependencies.size()-1) << ";\n\n";
    }

    // output setting global parameters (TORQUE LIMIT etc)
    for (auto it = values.begin(); it != values.end(); it++)
    {
        std::vector<std::pair<GLOBAL_NAME, dReal> > values;
        switch(it->first)
        {
            case SET_TORQUE_LIMIT:
                ofs << "\nSET TORQUELIMIT = " << it->second << "\n\n";
                break;
            case NUM_VALUES:
                ofs << "Error, global value doesn't exist..." << std::endl;
                return false;
                break;
        }
    }



    ofs<< "BEGINSCRIPT " << this->displayName << "(";
    for (int i = 0; i < paramNames.size(); i++)
    {
        ofs << paramNames.at(i);
        if (i != paramNames.size()-1)
            ofs << ", ";
    }
    if (paramNames.size() == 0)
        ofs << "void";

    ofs << ")\n\n";

    for (auto it  = phases.begin(); it != phases.end(); it++)
    {
        if (!(it->writeToFile(ofs, scripts)))
            return false;
        ofs << std::endl; 
    }

    ofs << "ENDSCRIPT";


    return true;

}


