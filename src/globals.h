#ifndef GLOBALS_H
#define GLOBALS_H

#define dSINGLE

#include <stdlib.h>
#include <ode/ode.h>
#include "VECTOR.h"
#include <map>
#include <string>
#include <stack>

#include <GLFW/glfw3.h>


#define PI 3.1415926
#define DENSITY 0.5

class Object;
class Environment;

enum Part { L_TORSO, U_TORSO, PELVIS, HEAD, NECK, L_ARM, R_ARM, L_FOREARM, R_FOREARM,
	L_THIGH, R_THIGH, L_SHIN, R_SHIN, L_FOOT, R_FOOT, L_HAND, R_HAND, PART_COUNT };
enum Joint_Enum { NECK2HEAD, U_TORSO2NECK, L_SHOULDER, R_SHOULDER, L_ELBOW, R_ELBOW, L_HIP, R_HIP,
	L_KNEE, R_KNEE, L_ANKLE, R_ANKLE, L_TORSO2U_TORSO, WAIST, L_WRIST, R_WRIST, JOINT_COUNT };
enum Joint_Type { UNIVERSAL, HINGE, BALL, FIXED };
enum Basis { PART, JOINT, COP };

enum Object_Type { HUMAN, PLANE, ENVIRONMENT, HEIGHTFIELD };

int getJointEnumFromString(std::string);
int getPartEnumFromString(std::string);
std::string getPartNameFromEnum(Part);

extern GLFWwindow* window;

extern std::stack<std::map<std::string, std::string>* > lookupTable;
extern std::map<dGeomID, Object*> geom2obj;
extern Environment* env;

extern dGeomID plane;

const int MAX_CONTACTS = 6;

const dReal STEPSIZE = 0.0001;

const dReal PLANE_HEIGHT = 0;

const dReal STABILITY_TOLERANCE = .000001;

extern dReal TORQUE_LIMIT;

extern dReal fps;

const dReal KP = 300;
const dReal KD = 30;

extern float zoom;
extern bool norotate;
extern bool draw_com;
extern bool DRAW_CONTACT;
extern bool DISPLAY_COMVEL;
extern bool WRITE_ON_STABLE;
extern bool WRITE_ON_TRANSITION;
extern bool RECORD_STATES;
extern bool FIND_TRANSITIONS;
extern bool FAILURE_DETECTION;
extern bool SEARCH;
extern bool RAGDOLL;
extern bool VISUALIZATION;
extern bool RECORD_TRAJECTORY;
extern bool OPTIMIZE;
extern bool WRITE_CONTROLLER;

extern VECTOR IKPoint;

extern int joint_type;

extern dWorldID World;
extern dSpaceID Space;
extern dJointGroupID contactgroup;
extern dJointGroupID jointgroup;

#endif //GLOBALS_H
