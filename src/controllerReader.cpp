

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <utility>
#include <unordered_set>
#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/regex_actions.hpp>

#include "globals.h"
#include "controller.h"
#include "controllerReader.h"
#include "phase.h"
#include "human.h"
#include "action.h"
#include "IKSolver.h"
#include "assert.h"
#include "value.h"
#include "transition.h"
#include "envAction.h"

using namespace std;

using namespace boost::xpressive;

Controller* c_ptr;
Phase* phase_ptr;
EnvAction* EA_ptr;
Optimization* opt_ptr;
Transition* trans_ptr;
LInterpValue* LI_ptr;

#include "xpressivefunctions.h"

sregex SCRIPT, PHASELIST, PHASE, COMMANDLIST, COMMAND, ACTIONLIST, ACTIONS, ACTION;

sregex TRANSITION, TIME_TYPE, CONTACT_TYPE, NO_CONTACT_TYPE, COMPLETE_TYPE, ITERATIONS_TYPE, KEYPRESS_TYPE, KEYRELEASE_TYPE, STABLE_TYPE, FALLEN_TYPE, ANGLERANGE_TYPE, PASS_TYPE,
       RAND_TYPE;

sregex INT, VARIABLE, COMMENT, WORD, FLOAT, PARAM, PARAMS, VOID, OUTPARAM, OUTPARAMS, CHAR;

sregex POSE, POSES, POSEFB, POSEFBS, LIPOSE;

sregex VPD, COMFB2, SWITCHSCRIPT, EF, VF, VFFB, GC, IK, VFSFB;

sregex ENVACTIONLIST, ENVACTIONS, ENVACTION;

sregex TOGGLEVISIBLE, TOGGLECOLLIDABLE;

// sregex SVF;

sregex MATCH, HOLD;

sregex JOINT_X, PART_X;

sregex VALUE, LINTERP;

sregex SAVE, LOAD;

sregex ERROR;

//Takes in a reference to a controller, reads in a script and saves it to said reference.
int controllerReader::readScript(char* filename, const Human& human, std::map<std::string, Controller> &scripts)
{

	cout << "Opening . . . " << filename << endl;



	ifstream ifs;
	// first check current directory
	ifs.open(filename);
	if (!ifs)
	{
		//otherwise look in scripts folder
		string fname = "../scripts/";
		fname.append(filename);
		ifs.open(fname.c_str());
		if (!ifs)
		{
			// error if still can't find.
			cerr << "Cannot open controller script: " << filename << endl;
			return -1;
		}
	}

	string input( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));

    WORD = +_w;
	JOINT_X = WORD;
	PART_X = WORD;
	CHAR = _w;

//    std::unordered_set<Controller*>* links = new std::unordered_set<Controller*>;

    std::vector<std::string> scriptnames;
	// read in SCRIPTS section
	{

		sregex SCRIPTNAME = (s1 = (sregex::compile("[^[:space:];,]*")))[ push_back(boost::xpressive::ref(scriptnames), as<string>(s1)) ];
		sregex SCRIPTNAMES = SCRIPTNAME >> *space >> "," >> *space >> by_ref(SCRIPTNAMES)
			| SCRIPTNAME >> *space >> ";";
		sregex SCRIPTS = "SCRIPTS" >> +space >> SCRIPTNAMES;


		smatch what;
		regex_search(input, what, SCRIPTS);

        // if given script has not already been read in.
		for (int i = 0; i < scriptnames.size(); i++)
		{
			if (scripts.find(scriptnames.at(i)) == scripts.end())
			{
				readScript((char*)scriptnames.at(i).c_str(), human, scripts);
			}

            if (scripts.find(scriptnames.at(i)) != scripts.end())
            {
                //links->insert(&(scripts.find(scriptnames.at(i))->second));
            }

		}

	}

	cout << "Reading Script: " << filename << endl;

	c_ptr = new Controller;
	c_ptr->setCurrPhase(0);
	c_ptr->setName(filename);
    c_ptr->setDependencies(scriptnames);
    //c_ptr->setLinks(links);

    // Read in SET_GLOBALS SECTION
    {
       sregex SET = "SET" >> +space >> (s1= WORD) >> *space >> "=" >> *space >> (s2 = sregex::compile("-?\\d*\\.?\\d+")) [ createGlobal( as<std::string>(s1), as<dReal>(s2)) ];

       smatch what;
       regex_search(input, what, SET);
    }

	opt_ptr = new inactiveOptimization();

	std::vector<std::string> paramVec;
	std::vector<std::string> outParams;
	std::stack<std::vector<Value*> > inputs;

	bool errorFlag=false;

	// --- DEFINE GRAMMAR HERE --- //
	{

		/* ----
		   MAJOR ERROR SOURCE: 
		   IF YOU PUT A FUNCTION CALL FOLLOWING A *SPACE, IT WILL NOT EXECUTE
		   IF IT MATCHES zero SPACES
		*/


		// Variable Types
        // VARIABLE must start with an alphabetic character. (should eliminate long waits for ints.)
		VARIABLE = (s1= (alpha >> *_w)) [ pushVar(true, s1, boost::xpressive::ref(inputs)) ];
		INT = (s1= sregex::compile("-?\\d+\\.?")) [ pushVar(false, s1, boost::xpressive::ref(inputs)) ];
		FLOAT = (s1= sregex::compile("-?\\d*\\.\\d+")) [ pushVar(false, s1, boost::xpressive::ref(inputs)) ];
		LINTERP = sregex::compile("linterp") [ pushInputs(boost::xpressive::ref(inputs)) ] >> *space >> "(" >> repeat<4>(*space >> by_ref(VALUE) >> *space >> ",") >> *space >> by_ref(VALUE) >> *space >> sregex::compile("\\)") [ createLInterp(boost::xpressive::ref(inputs)) ];

		VALUE = INT|FLOAT|VARIABLE|LINTERP;


		// Comment Types
		COMMENT = "#" >> *~_n;
	    //COMMENT = "#" >> *~_n >> _n;
		ERROR = (s1= *~_n) [ handleError(as<string>(s1), boost::xpressive::ref(errorFlag)) ];

		// Action Types
		POSE = ((s1= JOINT_X) [ pushInputs(boost::xpressive::ref(inputs)) ] >> 
                "(" >> *space >> (VALUE) >> *space >> 
                    !("," >> *space >> (VALUE) >> *space >> 
                        !("," >> *space >> (VALUE) >> *space)) >> ")")
            [ createPose(  boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		POSES = (POSE >> *space >> "," >> *space >> by_ref(POSES)) | (POSE >> *space >> ";");

		POSEFB = ((s1= JOINT_X) [pushInputs(boost::xpressive::ref(inputs)) ] >> "(" >> *space >> (VALUE) >> *space >> "," >> *space >> ( VALUE) >> *space >> ").on" >> *space >> "(" >> *space >> (s2= WORD) >> *space >> (s3= (PART_X|JOINT_X)) >> ")") [ createPoseFB(  boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2), as<string>(s3)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		POSEFBS = (POSEFB >> *space >> "," >> *space >> by_ref(POSEFBS)) | (POSEFB >> *space >> ";");

		LIPOSE = (s1= JOINT_X) [ pushInputs(boost::xpressive::ref(inputs)) ] >> 
            "(" >> *space >> (VALUE) >> *space >> 
                !("," >> *space >> (VALUE) >> *space >> 
                    !("," >> *space >> (VALUE) >> *space)) >> 
            ").time" >> *space >> 
            "(" >> *space >> (VALUE) >> *space >> ")" >> 
            *space >> sregex::compile(";") 
            [ createLIPose( boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1) ) ] [popInputs(boost::xpressive::ref(inputs)) ];


controllerReader* me = this;

		VPD = ((s1= PART_X) [ pushInputs(boost::xpressive::ref(inputs)) ] >> "(" >> *space >> (VALUE) >> *space >> !("," >> *space >> (VALUE) >> *space >> !("," >> *space >> (VALUE) >> *space)) >> ").joint(" >> *space >> (s2= PART_X) >> *space >> ")" >> *space >> !( ".flags(" >> *space >> (s3= WORD) >> *space >> ")"  ) >> *space >> ";") [ createVPD( boost::xpressive::ref(me), boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2), as<string>(s3)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		COMFB2 = ((VALUE) >> +space >> (VALUE) >> +space >> (s1= _w) >> +space >> (s2= (JOINT_X|PART_X))) [ createCOMFB( boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<char>(s1), as<string>(s2)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		EF = ((s1= PART_X) >> *space >> "(" >> *space >> (s2= FLOAT) >> *space >> "," >> *space >> (s3= FLOAT) >> *space >> "," >> *space >> (s4= FLOAT) >> *space >> ")" >> *space >> ";") [ createEF( boost::xpressive::ref(human), as<string>(s1), as<string>(s2), as<string>(s3), as<string>(s4) ) ];
/*
		SVF = (sregex::compile("\\(") [ pushInputs(boost::xpressive::ref(inputs)) ] >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> ").on(" >> *space >> (s1= PART_X) >> *space >> ").by(" >> *space >> (s2= JOINT_X) >> *space >> ")" >> *space >> ";") [ createSVF( boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2)) ] [ popInputs(boost::xpressive::ref(inputs)) ];
        */
		VF = (sregex::compile("\\(") [ pushInputs(boost::xpressive::ref(inputs)) ] >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> ").on(" >> *space >> (s1= PART_X) >> *space >> ").by(" >> *space >> (s2= JOINT_X) >> *space >> ")" >> *space >> ";") [ createVF( boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2)) ] [ popInputs(boost::xpressive::ref(inputs)) ];


		VFFB = ((s1= PART_X) [pushInputs(boost::xpressive::ref(inputs))] >> *space >> "(" >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> ").by" >> *space >> "(" >> *space >> (s2= JOINT_X) >> *space >> ").over" >> *space >> "(" >> *space >> (s3= WORD) >> *space >> ")" >> *space >> sregex::compile(";")) [createVFFB(boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2), as<string>(s3) ) ] [popInputs(boost::xpressive::ref(inputs))];

		VFSFB = ((s1= PART_X) [pushInputs(boost::xpressive::ref(inputs))] >> *space >> "(" >> *space >> (VALUE) >> *space >> ").by" >> *space >> "(" >> *space >> (s2= JOINT_X) >> *space >> ").speed" >> *space >> "(" >> *space >> (VALUE) >> *space >> ")" >> *space >> sregex::compile(";")) [createVFSFB(boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2)) ] [popInputs(boost::xpressive::ref(inputs))];


		IK = (s1 = PART_X) [ pushInputs(boost::xpressive::ref(inputs)) ] >> ".target" >> (s2= sregex::compile("local")|sregex::compile("global")) >> *space >> "(" >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> "," >> *space >> (VALUE) >> *space >> ").base" >> *space >> "(" >> *space >> (s3 = JOINT_X) >> *space >> ")" >> !( ".tolerance" >> *space >> "(" >> *space >> (VALUE) >> *space >> ")" ) >> *space >> sregex::compile(";") [ createIK(boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2), as<string>(s3)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		GC = (s1 = PART_X) >> ".by" >> *space >> "(" >> *space >> (s2= JOINT_X) >> *space >> ")" >> *space >> sregex::compile(";") [ createGC(boost::xpressive::ref(human), as<string>(s1), as<string>(s2)) ];

		MATCH = (s1 = JOINT_X) [ pushInputs(boost::xpressive::ref(inputs)) ] >> ".to" >> *space >> 
            "(" >> *space >> (s2= JOINT_X) >> *space >> 
            !("," >> *space >> (VALUE) >> *space >> 
                    "," >> *space >> (VALUE) >> *space
            ) >>
            ")" >> *space >> 
            !(".time" >> *space >> "(" >> *space >> (VALUE) >> *space >> ")" ) >> sregex::compile(";") [ createMatch(boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<string>(s1), as<string>(s2)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		HOLD = (s1 = JOINT_X) >> sregex::compile(";") [ createHold(boost::xpressive::ref(human), as<string>(s1) ) ];



		// Command Types
		ACTION = ("POSE" >> +space >> POSES)
			| ("POSEFB" >> +space >> POSEFBS)
			| ("VPD" >> +space >> VPD)
			| ("COMFB2" >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> COMFB2)
			| ("EF" >> +space >> EF)
			| ("VF" >> +space >> VF)
			| ("VFFB" >> +space >> VFFB)
            | ("VFSFB" >> +space >> VFSFB)
//			| ("SVF" >> *space >> SVF)
			| ("IK" >> +space >> IK)
			| ("GC" >> +space >> GC)
			| ("LIPOSE" >> +space >> LIPOSE)
			| ("MATCH" >> +space >> MATCH)
            | ("HOLD" >> +space >> HOLD)
			| COMMENT;
		ACTIONS = (ACTION >> +space >> by_ref(ACTIONS)) | ACTION;
		ACTIONLIST = "ACTIONS" >> +space >> ACTIONS >> +space >> "ENDACTIONS";
        

        TOGGLEVISIBLE = ("toggleVisible" >> *space >> "(" >> *space >> (s1= WORD) >> *space >> ")" >> *space >> ";" ) [ pushToggleVisible( as<std::string>(s1)) ];
        TOGGLECOLLIDABLE = ("toggleCollidable" >> *space >> "(" >> *space >> (s1= WORD) >> *space >> ")" >> *space >> ";" ) [ pushToggleCollidable( as<std::string>(s1)) ];

        ENVACTION = TOGGLEVISIBLE
            | TOGGLECOLLIDABLE
            | COMMENT;

        ENVACTIONS = (ENVACTION >> +space >> by_ref(ENVACTIONS) | ENVACTION);

        ENVACTIONLIST = sregex::compile("ENVACTIONS") [ pushEnvAction() ] >> *space >> ENVACTIONS >> +space >> "ENDACTIONS";

		TIME_TYPE = "time" >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (VALUE) [ setTransTime( boost::xpressive::ref(inputs) ) ] [ popInputs(boost::xpressive::ref(inputs)) ];
		CONTACT_TYPE = "contact" >> +space >> (s1 = PART_X) [ setTransContact( boost::xpressive::ref(human), as<string>(s1)) ];
		NO_CONTACT_TYPE = "nocontact" >> +space >> (s1 = PART_X) [ setTransNoContact( boost::xpressive::ref(human), as<string>(s1)) ];
		COMPLETE_TYPE = sregex::compile("complete") [ setTransComplete() ];

		ITERATIONS_TYPE = "iterations" >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (VALUE) [ setTransIters( boost::xpressive::ref(inputs) ) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		KEYPRESS_TYPE = "press" >> +space >> (s1= CHAR) [ setTransPress( as<char>(s1) ) ];
		KEYRELEASE_TYPE = "release" >> +space >> (s1= CHAR) [ setTransRelease( as<char>(s1) ) ];

		STABLE_TYPE = sregex::compile("stable") >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (VALUE) [ setTransStable(boost::xpressive::ref(human), boost::xpressive::ref(inputs) )] [ popInputs(boost::xpressive::ref(inputs)) ];

        FALLEN_TYPE = sregex::compile("fallen") >> +space >> (s1= (sregex::compile("[><x]"))) >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (VALUE) [ setTransFallen(boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<char>(s1)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

        ANGLERANGE_TYPE = sregex::compile("anglerange") >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (VALUE) >> +space >> (VALUE) [ setTransAngleRange( boost::xpressive::ref(human), boost::xpressive::ref(inputs)) ] [ popInputs(boost::xpressive::ref(inputs)) ];

        PASS_TYPE = sregex::compile("pass") [ pushInputs(boost::xpressive::ref(inputs)) ] >> +space >> (s1= WORD) >> +space >> (VALUE) [ setTransPass( boost::xpressive::ref(human), boost::xpressive::ref(inputs), as<std::string>(s1) ) ] [ popInputs(boost::xpressive::ref(inputs)) ];

        RAND_TYPE = sregex::compile("random") [ pushInputs(boost::xpressive::ref(inputs)) ] >> +space >> (VALUE) [ setTransRand(boost::xpressive::ref(inputs) ) ] [ popInputs(boost::xpressive::ref(inputs)) ];

		TRANSITION = "TRANSITION" >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> "to(" >> *space >> (s1= INT) [ setTransTo( as<int>(s1) ) ] [ popInputs(boost::xpressive::ref(inputs)) ] >> *space >> ").after(" >> *space >> (TIME_TYPE|CONTACT_TYPE|NO_CONTACT_TYPE|COMPLETE_TYPE|STABLE_TYPE|ITERATIONS_TYPE|KEYPRESS_TYPE|KEYRELEASE_TYPE|FALLEN_TYPE|ANGLERANGE_TYPE|PASS_TYPE|RAND_TYPE) >> *space >> ")" >> *space >> ";";

		VOID = (*space >> "void" >> *space) [ voidFound() ];

		PARAM = (s1= WORD) [ createParam(boost::xpressive::ref(c_ptr->paramNames), as<string>(s1)) ];

		PARAMS = (*space >> PARAM >> *space >> "," >> by_ref(PARAMS)) | (*space >> PARAM >> *space);

		OUTPARAM = (VALUE) [ createOutParam(boost::xpressive::ref(inputs)) ] [ popInputs(boost::xpressive::ref(inputs)) ];
		OUTPARAMS = (*space >> OUTPARAM >> *space >> sregex::compile(",") [ pushInputs(boost::xpressive::ref(inputs)) ] >> by_ref(OUTPARAMS) ) | (*space >> OUTPARAM >> *space);


		SWITCHSCRIPT = ">" >> +space [ pushInputs(boost::xpressive::ref(inputs)) ] >> (s1 = (sregex::compile("[^[:space:]\\(]*"))) [ switchController(as<string>(s1)) ] >> *space >> ( sregex::compile("\\(") [pushInputs(boost::xpressive::ref(inputs)) ] >> (VOID|OUTPARAMS) >> ")") >> *space  >> 
            !(".atPhase" >> *space >> sregex::compile("\\(") [pushInputs(boost::xpressive::ref(inputs)) ] >> *space >> (s2= INT)  >> *space >> sregex::compile("\\)") [ setSwitchPhase(as<int>(s2)) ] [popInputs(boost::xpressive::ref(inputs)) ]  ) >> *space
            >> sregex::compile(";") [popInputs(boost::xpressive::ref(inputs)) ];

		SAVE = "SAVE" >> +space >> (s1= sregex::compile("([^;]*)")) [ createSave( boost::xpressive::ref(human), as<string>(s1) ) ] >> ";";

		LOAD = "LOAD" >> +space >> (s1= sregex::compile("([^;]*)")) [ createLoad( boost::xpressive::ref(human), as<string>(s1) ) ] >> ";";



		// Inside Phase
		COMMAND = TRANSITION
			| ACTIONLIST
            | ENVACTIONLIST
			| SWITCHSCRIPT
			| SAVE
			| LOAD
			| COMMENT;
//			| ERROR
		COMMANDLIST = (COMMAND >> +space >> by_ref(COMMANDLIST)) 
			| COMMAND;
		// Phases
		PHASE = (sregex::compile("PHASE") >> +_s [ pushInputs(boost::xpressive::ref(inputs)) ] >> (s1= INT) [ newPhase( as<int>(s1) ) ] [ popInputs(boost::xpressive::ref(inputs)) ]>> +space >> COMMANDLIST >> +space >> "ENDPHASE") [ pushPhase( ) ]
			| COMMENT;
		PHASELIST = PHASE >> +space >> by_ref(PHASELIST)
			| PHASE;


		// Overall
		SCRIPT = "BEGINSCRIPT" >> +_s [ pushInputs(boost::xpressive::ref(inputs)) ] >> (s1= sregex::compile("[^[:space:]\\(]*")) [ setName(s1) ]  >> *space >> ("(" >> (VOID|PARAMS) >> ")") >> +space >> PHASELIST >> +space >> "ENDSCRIPT";
	}

	//input = string("> asdf.t (0, 0, 0, 0, 0)");



	smatch what;
	if (!regex_search(input, what, SCRIPT) || errorFlag)
	{
		cerr << "Encountered syntax error while reading in script " << filename << endl;
		return -1;
	}

	//cout << what[0] << endl;

	scripts.insert(pair<std::string, Controller>(filename, *c_ptr));

	return 0;


}

PDController* controllerReader::createPDController(const Human& human, string joint, Value* optAngle, Value* kp, Value* kd, Value* optRate)
{


	Joint* toSet;

	if (joint.compare("rHip") == 0)
	{
		toSet = human.joints[R_HIP];
	}
	else if (joint.compare("lHip") == 0)
	{
		toSet = human.joints[L_HIP];
	}
	else if (joint.compare("rKnee") == 0)
	{
		toSet = human.joints[R_KNEE];
	}
	else if (joint.compare("lKnee") == 0)
	{
		toSet = human.joints[L_ANKLE];
	}
	else if (joint.compare("rAnkle") == 0)
	{
		toSet = human.joints[R_ANKLE];
	}
	else if (joint.compare("lAnkle") == 0)
	{
		toSet = human.joints[L_SHOULDER];
	}
	else if (joint.compare("rShoulder") == 0)
	{
		toSet = human.joints[R_SHOULDER];
	}
	else if (joint.compare("lShoulder") == 0)
	{
		toSet = human.joints[L_SHOULDER];
	}
	else if (joint.compare("rElbow") == 0)
	{
		toSet = human.joints[R_ELBOW];
	}
	else if (joint.compare("lElbow") == 0)
	{
		toSet = human.joints[L_ELBOW];
	}
	else if (joint.compare("lWrist") == 0)
	{
		toSet = human.joints[L_WRIST];
	}
	else if (joint.compare("rWrist") == 0)
	{
		toSet = human.joints[R_WRIST];
	}
	else if (joint.compare("neck2head") == 0)
	{
		toSet = human.joints[NECK2HEAD];
	}
	else if (joint.compare("uTorso2neck") == 0)
	{
		toSet = human.joints[U_TORSO2NECK];
	}
	else if (joint.compare("waist") == 0)
	{
		toSet = human.joints[WAIST];
	}
	else if (joint.compare("lTorso2uTorso") == 0)
	{
		toSet = human.joints[L_TORSO2U_TORSO];
	}
	else
	{
		cerr << "Improper PD Controller specification" << endl;
	}


	PDController* ret = new PDController(kp, kd, toSet, optAngle, optRate);

	return ret;

}


VPDController* controllerReader::createVPDController(const Human& human, string part, string joint, Value* optAngle, Value* kp, Value* kd, Value* optRate, bool simbicon)
{

	Object* part_toSet;
	dJointID motor_toSet;


	if (part.compare("uTorso") == 0)
	{
		part_toSet = human.parts[U_TORSO];
		motor_toSet = human.uTorso2world_M;
	}
	else if (part.compare("lTorso") == 0)
	{
		part_toSet = human.parts[L_TORSO];
		motor_toSet = human.lTorso2world_M;
	}
	else if (part.compare("rThigh") == 0)
	{
		part_toSet = human.parts[R_THIGH];
		motor_toSet = human.rThigh2world_M;
	}
	else if (part.compare("lThigh") == 0)
	{
		part_toSet = human.parts[L_THIGH];
		motor_toSet = human.lThigh2world_M;
	}
	else if (part.compare("rShin") == 0)
	{
		part_toSet = human.parts[R_SHIN];
		motor_toSet = human.rShin2world_M;
	}
	else if (part.compare("lShin") == 0)
	{
		part_toSet = human.parts[L_SHIN];
		motor_toSet = human.lShin2world_M;
	}
	else if (part.compare("rFoot") == 0)
	{
		part_toSet = human.parts[R_FOOT];
		motor_toSet = human.rFoot2world_M;
	}
	else if (part.compare("lFoot") == 0)
	{
		part_toSet = human.parts[L_FOOT];
		motor_toSet = human.lFoot2world_M;
	}
	else if (part.compare("rArm") == 0)
	{
		part_toSet = human.parts[R_ARM];
		motor_toSet = human.rArm2world_M;
	}
	else if (part.compare("lArm") == 0)
	{
		part_toSet = human.parts[L_ARM];
		motor_toSet = human.lArm2world_M;
	}
	else if (part.compare("rForearm") == 0)
	{
		part_toSet = human.parts[R_FOREARM];
		motor_toSet = human.rForearm2world_M;
	}
	else if (part.compare("lForearm") == 0)
	{
		part_toSet = human.parts[L_FOREARM];
		motor_toSet = human.lForearm2world_M;
	}
	else if (part.compare("rHand") == 0)
	{
		part_toSet = human.parts[R_HAND];
		motor_toSet = human.rHand2world_M;
	}
	else if (part.compare("lHand") == 0)
	{
		part_toSet = human.parts[L_HAND];
		motor_toSet = human.lHand2world_M;
	}
	else if (part.compare("neck") == 0)
	{
		part_toSet = human.parts[NECK];
		motor_toSet = human.neck2world_M;
	}
	else if (part.compare("head") == 0)
	{
		part_toSet = human.parts[HEAD];
		motor_toSet = human.head2world_M;
	}
	else
	{
		cerr << "Improper VPD controller specification" << endl;
	}

	VPDController* ret = new VPDController(human, kp, kd, part_toSet, human.getJointFromString(joint), motor_toSet, optAngle, optRate, simbicon);

	return ret;


}
