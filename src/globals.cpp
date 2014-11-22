#define dSINGLE


#include <ode/ode.h>
#include "globals.h"
#include "VECTOR.h"

float zoom = 0;
dReal TORQUE_LIMIT = 1000;
bool norotate = false;
bool draw_com = false;
bool DRAW_CONTACT = false;
bool DISPLAY_COMVEL = false;
bool WRITE_ON_STABLE = false;
bool WRITE_ON_TRANSITION = false;
bool FAILURE_DETECTION = false;
bool RECORD_STATES = false;
bool FIND_TRANSITIONS = false;
bool SEARCH = false;
bool RAGDOLL = false;
bool VISUALIZATION = false;
bool RECORD_TRAJECTORY = false;
bool WRITE_CONTROLLER = false;
bool OPTIMIZE = false;

dReal fps = 60.0;

VECTOR IKPoint(100,100,100);
std::stack<std::map<std::string, std::string>* > lookupTable;
std::map<dGeomID, Object*> geom2obj;

GLFWwindow* window;
Environment* env;

int joint_type;
dGeomID plane;

dWorldID World;
dSpaceID Space;
dJointGroupID contactgroup;
dJointGroupID jointgroup;

int getPartEnumFromString(std::string str)
{
	if (str.compare("uTorso") == 0)
	{
		return U_TORSO;
	}
	else if (str.compare("lTorso") == 0)
	{
		return L_TORSO;
	}
	else if (str.compare("pelvis") == 0)
	{
		return PELVIS;
	}
	else if (str.compare("head") == 0)
	{
		return HEAD;
	}
	else if (str.compare("neck") == 0)
	{
		return NECK;
	}
	else if (str.compare("rArm") == 0)
	{
		return R_ARM;
	}
	else if (str.compare("lArm") == 0)
	{
		return L_ARM;
	}
	else if (str.compare("rForearm") == 0 || str.compare("rFArm") == 0)
	{
		return R_FOREARM;
	}
	else if (str.compare("lForearm") == 0 || str.compare("lFArm") == 0)
	{
		return L_FOREARM;
	}
	else if (str.compare("rThigh") == 0)
	{
		return R_THIGH;
	}
	else if (str.compare("lThigh") == 0)
	{
		return L_THIGH;
	}
	else if (str.compare("rShin") == 0)
	{
		return R_SHIN;
	}
	else if (str.compare("lShin") == 0)
	{
		return L_SHIN;
	}
	else if (str.compare("rFoot") == 0)
	{
		return R_FOOT;
	}
	else if (str.compare("lFoot") == 0)
	{
		return L_FOOT;
	}
	else if (str.compare("rHand") == 0)
	{
		return R_HAND;
	}
	else if (str.compare("lHand") == 0)
	{
		return L_HAND;
	}
	else
	{
		return -1;
	}
}

std::string getPartNameFromEnum(Part part)
{
	if (U_TORSO == part)
	{
		return "uTorso";
	}
	else if (L_TORSO == part)
	{
		return "lTorso";
	}
	else if (PELVIS == part)
	{
		return "pelvis";
	}
	else if (HEAD == part)
	{
		return "head";
	}
	else if (NECK == part)
	{
		return "neck";
	}
	else if (R_ARM == part)
	{
		return "rArm";
	}
	else if (L_ARM == part)
	{
		return "lArm";
	}
	else if (R_FOREARM == part)
	{
		return "rForearm";
	}
	else if (L_FOREARM == part)
	{
		return "lForearm";
	}
	else if (R_THIGH == part)
	{
		return "rThigh";
	}
	else if (L_THIGH == part)
	{
		return "lThigh";
	}
	else if (R_SHIN == part)
	{
		return "rShin";
	}
	else if (L_SHIN == part)
	{
		return "lShin";
	}
	else if (R_FOOT == part)
	{
		return "rFoot";
	}
	else if (L_FOOT == part)
	{
		return "lFoot";
	}
	else if (R_HAND == part)
	{
		return "rHand";
	}
	else if (L_HAND == part)
	{
		return "lHand";
	}
	else
	{
		return "UNKNOWN PART TYPE";
	}
}

int getJointEnumFromString(std::string str)
{

	if (str.compare("neck2head") == 0)
	{
		return NECK2HEAD;
	}
	else if (str.compare("uTorso2neck") == 0)
	{
		return U_TORSO2NECK;
	}
	else if (str.compare("rHip") == 0)
	{
		return R_HIP;
	}
	else if (str.compare("lHip") == 0)
	{
		return L_HIP;
	}
	else if (str.compare("rKnee") == 0)
	{
		return R_KNEE;
	}
	else if (str.compare("lKnee") == 0)
	{
		return L_KNEE;
	}
	else if (str.compare("rAnkle") == 0)
	{
		return R_ANKLE;
	}
	else if (str.compare("lAnkle") == 0)
	{
		return L_ANKLE;
	}
	else if (str.compare("rShoulder") == 0)
	{
		return R_SHOULDER;
	}
	else if (str.compare("lShoulder") == 0)
	{
		return L_SHOULDER;
	}
	else if (str.compare("rElbow") == 0)
	{
		return R_ELBOW;
	}
	else if (str.compare("lElbow") == 0)
	{
		return L_ELBOW;
	}
	else if (str.compare("waist") == 0)
	{
		return WAIST;
	}
	else if (str.compare("lTorso2uTorso") == 0)
	{
		return L_TORSO2U_TORSO;
	}
	else if (str.compare("lWrist") == 0)
	{
		return L_WRIST;
	}
	else if (str.compare("rWrist") == 0)
	{
		return R_WRIST;
	}
	else
	{
		return -1;
	}

}
