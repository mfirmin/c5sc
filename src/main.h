
// Global Constants (move these to a globals.h (.cpp?) file later?

#include "shape.h"
#include "fltReader.h"
#include "environment.h"
#include "heightfield.h"
#include "object.h"
#include "transitionFinder.h"
#include "trajectory.h"
#include "optimizer.h"
#include "hierarchy.h"

// Function Definitions
void DrawGeom (dGeomID, const Shape* const, int);
void DrawSphere(const dReal);
void DrawBox(const dReal*);
void drawHF(dReal* data, int size, dReal start, dReal width);
void drawPlane(Plane*);
void Draw(dGeomID, const dReal*, const dReal*, const Shape* const, int);
void drawArrow(const dReal, const dReal, const dReal, const dReal);
GLvoid setMaterialProperties( GLfloat r, GLfloat g, GLfloat b, GLfloat alpha=1.0);
GLvoid init_lightsource();

bool S_DOWN = false;
bool L_DOWN = false;

bool PUSH_FORWARD = false;
bool PUSH_BACKWARD = false;

TransitionFinder tf;
Trajectory* traj;
Optimizer optimizer;
Hierarchy currHierarchy;

Human human;

fltReader flt_reader;

int addedEntities;
double speed;

// ODE constants (should probably get rid of these...
float GeomMatrix[16];
dJointID CoMMotor;
dJointID CoMAMotor;

