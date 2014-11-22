#ifndef ACTION_H
#define ACTION_H


#define dSINGLE

#include "human.h"
#include "optimization.h"
#include "object.h"
#include "joint.h"
#include "globals.h"
#include "VECTOR.h"
#include "value.h"
#include <vector>
#include <ode/ode.h>



class Action
{

	public:

		virtual void performAction() = 0;
		virtual void reset() = 0;
        virtual void setOptimizable(std::vector<Value*>&) = 0;
        virtual bool writeToFile(std::ofstream&) = 0;

};

class PDController : public Action
{

	public:

		PDController(Value* a, Value* b, Joint* j, Value* optA, Value* optR) {kp = a; kd = b; joint = j; optAngle = optA; optRate = optR;};


		virtual void performAction();
        virtual void setOptimizable(std::vector<Value*>&);

		dReal getOptAngle() {return optAngle->getdReal();}
		void setOptAngle(Value* o) { optAngle = o; }
		Optimization* optimization;
		Joint* getJoint() { return joint; }
		void setKP(Value* a) { kp = a; }
		void setKD(Value* a) { kd = a; }

		virtual void reset() { return; }

        bool writeToFile(std::ofstream&);

	private:
		Value* kp;
	        Value* kd;
		Value* optAngle;
		Value* optRate;
		Joint* joint;

};

class VPDController : public Action
{

	public:
		VPDController(const Human& h, Value* a, Value* b, Object* p, Joint* j, dJointID m, Value* optA, Value* optR, bool simbicon_) { human = &h; kp = a; kd = b; part = p; joint = j; motor = m; optAngle = optA; optRate = optR; simbicon = simbicon_; };


	//VPDController() {};

		void performAction();
		dReal getOptAngle() {return optAngle->getdReal();}
		void setOptAngle(Value* o) { optAngle = o; }
		Optimization* optimization;
		dJointID getJoint() { return motor; }
		void setKP(Value* a) { kp = a; }
		void setKD(Value* a) { kd = a; }

		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

	private:
		const Human* human;
		Value* kp;
	        Value* kd;
		Value* optAngle;
		Value* optRate;
		Object* part;
        Joint* joint;
		dJointID motor;
        bool simbicon;

};


class ExternalForceController : public Action
{

	public:
		ExternalForceController(dBodyID a, Value* fx, Value* fy, Value* fz) {first = a; force_x = fx; force_y = fy; force_z = fz;}

		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

	private:

		dBodyID first;
		Value* force_x;
		Value* force_y;
	        Value* force_z;

};

class VirtualForceController : public Action
{

	public:
		VirtualForceController(const Object* o, Joint* b, Value* fx, Value* fy, Value* fz) {Fx = fx; Fy = fy; Fz = fz; on = o; by = b; com_based = false; }

		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);

		std::vector<std::pair<Joint*, bool> >& getPath() { return path; }

		void setForce(Value* fx, Value* fy, Value* fz) { delete Fx; delete Fy; delete Fz; Fx = fx; Fy = fy; Fz = fz; }


		void makeCOMBased(const Human& h) { com_based = true; human = &h; }

        bool writeToFile(std::ofstream&);

	private:
		std::vector<std::pair<Joint*, bool> > path;
		Value* Fx;
		Value* Fy;
		Value* Fz;
		const Object* on;
		bool com_based;
		const Human* human;
		Joint* by;

};

class VFFeedback : public Action
{
	public:
		VFFeedback(const Object* o, Joint* b, Value* CD, Value* CV, const Human& h, std::string ov ) { on = o; by = b; human = &h; cd = CD; cv = CV; counter = 0; createVF(); over = ov; }

		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);

		void createVF();
        bool writeToFile(std::ofstream&);

	private:
		Value* cd;
		Value* cv;
		const Object* on;
		const Human* human;
		Joint* by;
		VirtualForceController* VF;
        std::string over;
        int counter;
//		bool rfoot, lfoot;

};

class VFSpeedFeedback : public Action
{
    public:
        VFSpeedFeedback(const Object* o, Joint * b, Value* CV, const Human& h, Value* gs) { on = o; by = b; human = &h; cv = CV; goalSpeed = gs; initialized = false; }
        
        void performAction();
        virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);

        void createVF();
        bool writeToFile(std::ofstream&);

    private:
        Value* cv;
        const Object* on;
        const Human* human;
        Joint* by;
        Value* goalSpeed;
        bool initialized;

        VirtualForceController* VF;
};

class GravityCompensator : public Action
{

	public:
		GravityCompensator(const Object* o, Joint* b, const Human& h);

		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }

		std::vector<std::pair<Joint*, bool> >& getPath() { return path; }
        bool writeToFile(std::ofstream&);


	private:
		std::vector<std::pair<Joint*, bool> > path;
		const Object* on;
		Joint* by;
		std::vector<VirtualForceController*> controllers;

};

/*
class SimpleVFController : public Action
{
	public:
		SimpleVFController(const Object* o, Joint* b, Value* fx, Value* fy, Value* fz) {Fx = fx; Fy = fy; Fz = fz; on = o; by = b;}
		void performAction();
		virtual void reset() { return; }
	private:
		Value* Fx;
		Value* Fy;
		Value* Fz;
		const Object* on;
		Joint* by;
};
*/
class HingePose : public Action
{
	public: 
		HingePose(Joint* j, Value* optA, Value* KP, Value* KD, Value* optR) { joint = j; kp = KP; kd = KD; optAngle = optA; optRate = optR; 

            feedbackLaw = new inactiveOptimization();
        
        }


		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

		void setAngle(dReal a) { optAngle->set(false, a); }

	private:
        Optimization* feedbackLaw;
		Joint* joint;
		Value* kp;
	        Value* kd;
		Value* optAngle;
		Value* optRate;
};

class HingePoseOptSetter : public Action
{
	public:
	       	HingePoseOptSetter(Joint* j, Optimization* o) { joint = j; opt = o; }
		void performAction();
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }
        bool writeToFile(std::ofstream&);

	private:
		Joint* joint;
		Optimization* opt;

};

class LIPose : public Action
{

	public:
		LIPose(Joint* j, Value* a, Value* _kp, Value* _kd, Value* t) { joint = j; t_goal = t; ang_goal = a; t_elapsed = 0; kp = _kp; kd = _kd;
        
            pose = new HingePose(joint, new Value(false, ang_init), kp, kd, new Value(false, 0));
        
        }

		void performAction();
		virtual void reset() { t_elapsed = 0; return; }
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

	private:
		Joint* joint;

		dReal ang_init;
		Value* ang_goal;

        Value* kp;
        Value* kd;

		dReal t_elapsed;
		Value* t_goal;

		HingePose* pose;

};

class StateSaver : public Action
{
	public:
		StateSaver(const Human &h, std::string s) { human = &h; savefile = s; }

		void performAction() { if (!human->save(savefile)) { std::cerr << "Error Saving to file " << savefile << std::endl; } }
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }
        bool writeToFile(std::ofstream& ofs) { ofs << "SAVE" << savefile << ";\n"; }

	private:
		const Human* human;
		std::string savefile;
};

class StateLoader : public Action
{
	public:
		StateLoader(Human &h, std::string s) { human = &h; loadfile = s; }

		void performAction() { if (!human->load(loadfile)) { std::cerr << "Error Loading from file " << loadfile << std::endl; } }
		virtual void reset() { return; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }
        bool writeToFile(std::ofstream& ofs) { ofs << "LOAD " << loadfile << ";\n"; }

	private:
		Human* human;
		std::string loadfile;
};

class Matcher : public Action
{

	public:
		Matcher(Joint* j, Joint* o) { joint = j; other = o; LI_based = false; }
        Matcher(Joint* j, Joint* o, Value* v) { joint = j; other = o; time = v; LI_based = true; first = true; }

		void performAction();

		virtual void reset() { if (LI_based) { LI->reset(); } return; }
        virtual void setOptimizable(std::vector<Value*>&);
        bool writeToFile(std::ofstream&);

        void setKP(Value* kp) { KP = kp; }
        void setKD(Value* kd) { KD = kd; }

	private:
        bool LI_based;
        bool first;
        Value* time;
        LIPose* LI;
		Joint* joint;
		Joint* other;
        Value* KP;
        Value* KD;


};

class Holder : public Action
{
    public:
        Holder(Joint* j) { joint = j; first = true; 

            pose = new HingePose(joint, new Value(false, 0.), new Value(false, 1000), new Value(false, 100.), new Value(false, 0.));
        
        }


        void performAction();
        virtual void reset() { first = true; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }
        bool writeToFile(std::ofstream&);

    private:
        Joint* joint;
        HingePose* pose;
        bool first;

};

#endif // ACTION_H
