

struct createGlobal_impl
{
	typedef void result_type;

	template<typename S, typename F>
	void operator()( S const &name, F const &value) const
	{

        if (name.compare("TORQUELIMIT") == 0)
        {
            c_ptr->addGlobal(std::pair<GLOBAL_NAME, dReal>(SET_TORQUE_LIMIT, value));
        }
	}
};

boost::xpressive::function<createGlobal_impl>::type const createGlobal = {{}};

struct setName_impl
{
	typedef void result_type;

	template<typename V>
	void operator()( V const &val) const
	{
		c_ptr->setDisplayName(val);
	}
};

boost::xpressive::function<setName_impl>::type const setName = {{}};

struct newPhase_impl
{
	typedef void result_type;

	template<typename V>
	void operator()( V const &num ) const
	{
		phase_ptr = new Phase;
		phase_ptr->phase_num = num;
	        phase_ptr->isSwitch = false;
	}
};

boost::xpressive::function<newPhase_impl>::type const newPhase = {{}};

struct switchController_impl
{
	typedef void result_type;

	template<typename V>
	void operator()( V const &val ) const
	{
		phase_ptr->newControllerName = val;
		phase_ptr->isSwitch = true;
        phase_ptr->setSwitchPhase(0);
	}
};

boost::xpressive::function<switchController_impl>::type const switchController = {{}};

struct createOutParam_impl
{
	typedef void result_type;

	template<typename I>
	void operator()( I &inputs) const
	{
	//	char buff[32];
	//	sprintf(buff, "%f", inputs.top().at(0)->getdReal());
		phase_ptr->newControllerParams.push_back(inputs.top().at(0));
	}
};

boost::xpressive::function<createOutParam_impl>::type const createOutParam = {{}};

struct setSwitchPhase_impl 
{
	typedef void result_type;

	template<typename I>
	void operator()( I const &phase) const
	{
	//	char buff[32];
	//	sprintf(buff, "%f", inputs.top().at(0)->getdReal());
		phase_ptr->setSwitchPhase(phase);
	}
};

boost::xpressive::function<setSwitchPhase_impl>::type const setSwitchPhase = {{}};

struct setTransTo_impl
{
	typedef void result_type;

	template<typename V>
	void operator()( V const &num) const
	{
		trans_ptr = new Transition;
		trans_ptr->to = num;
	}
};

boost::xpressive::function<setTransTo_impl>::type const setTransTo = {{}};

struct setTransTime_impl
{
	typedef void result_type;

	template<typename I>
	void operator()( I &inputs) const
	{
		trans_ptr->type = TIME;
	        trans_ptr->dt = new Value(*(inputs.top().at(0)));

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransTime_impl>::type const setTransTime = {{}};

struct setTransStable_impl
{
	typedef void result_type;

	template<typename H, typename I>
	void operator()( H &human, I &inputs) const
	{
		trans_ptr->type = STABLE;
	        trans_ptr->human = (Human*)&human;
            trans_ptr->stabilityTolerance = new Value(*(inputs.top().at(0)));

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransStable_impl>::type const setTransStable = {{}};

struct setTransFallen_impl
{
	typedef void result_type;

	template<typename H, typename I, typename C>
	void operator()( H &human, I &inputs, C const &dir) const
	{
        if (dir == '<')
            trans_ptr->_int = new Value(false, -1);
        else if (dir == '>')
            trans_ptr->_int = new Value(false, 1);
        else if (dir == 'x')
            trans_ptr->_int = new Value(false, 0);
        else
            std::cerr << "In fallen transition type, expected '>' or '<', got " << dir << std::endl;

		trans_ptr->type = FALLEN;
	        trans_ptr->human = (Human*)&human;
	        trans_ptr->_float = new Value(*(inputs.top().at(0)));

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransFallen_impl>::type const setTransFallen = {{}};

struct setTransAngleRange_impl
{
	typedef void result_type;

	template<typename H, typename I>
	void operator()( H &human, I &inputs) const
	{

		trans_ptr->type = ANGLERANGE;
        trans_ptr->human = (Human*)&human;
        trans_ptr->_float = new Value(*(inputs.top().at(0)));
        trans_ptr->_float2 = new Value(*(inputs.top().at(1)));

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransAngleRange_impl>::type const setTransAngleRange = {{}};

struct setTransPress_impl
{
	typedef void result_type;

	template<typename C>
	void operator()( C const &c) const
	{
		trans_ptr->type = KEYPRESS;
	        trans_ptr->key = c;

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransPress_impl>::type const setTransPress = {{}};

struct setTransRelease_impl
{
	typedef void result_type;

	template<typename C>
	void operator()( C const &c) const
	{
		trans_ptr->type = KEYRELEASE;
	        trans_ptr->key = c;

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransRelease_impl>::type const setTransRelease = {{}};

struct setTransComplete_impl
{
	typedef void result_type;

	void operator()(void) const
	{
		trans_ptr->type = COMPLETE;
		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransComplete_impl>::type const setTransComplete = {{}};

struct setTransIters_impl
{
	typedef void result_type;

	template<typename I>
	void operator()( I &inputs) const
	{
		trans_ptr->type = ITERATIONS;
	        trans_ptr->_float = new Value(*(inputs.top().at(0)));
		trans_ptr->curr_iterations = 0;	
		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransIters_impl>::type const setTransIters = {{}};

struct setTransContact_impl
{
	typedef void result_type;

	template<typename H, typename V>
	void operator()(H &h,  V const &val) const
	{
		trans_ptr->type = CONTACT;
		trans_ptr->contact = h.getObjectFromString(val);
		phase_ptr->transitions.push_back(trans_ptr);

	}
};

boost::xpressive::function<setTransContact_impl>::type const setTransContact = {{}};

struct setTransNoContact_impl
{
	typedef void result_type;

	template<typename H, typename V>
	void operator()(H &h,  V const &val) const
	{
		trans_ptr->type = NO_CONTACT;
		trans_ptr->contact = h.getObjectFromString(val);
		phase_ptr->transitions.push_back(trans_ptr);

	}
};

boost::xpressive::function<setTransNoContact_impl>::type const setTransNoContact = {{}};

struct setTransRand_impl
{
	typedef void result_type;

	template<typename I>
	void operator()( I &inputs) const
	{
		trans_ptr->type = RANDOM;
	        trans_ptr->_float = new Value(*(inputs.top().at(0)));
		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransRand_impl>::type const setTransRand = {{}};

struct createPose_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT>
	void operator()(H &human, I &inputs, PRT const &part) const
	{

		Value* _kp;
		Value* _kd;
		if (inputs.top().size() < 2)
		{
			_kp = new Value(false, std::string("300"));
		}
		else
		{
			_kp = new Value(*(inputs.top().at(1)));
		}
		if (inputs.top().size() < 3)
		{
			_kd = new Value(false, std::string("30"));
		}
		else
		{
			_kd = new Value(*(inputs.top().at(2)));
		}


	//	HingePose* HP = new HingePose(human.getJointFromString(part), new Value(*(inputs.top().at(0))), _kp, _kd, new Value(false,"0"));

		HingePose* HP = new HingePose(human.getJointFromString(part), inputs.top().at(0), _kp, _kd, new Value(false, "0"));

		phase_ptr->actions.push_back(HP);



	}
};

boost::xpressive::function<createPose_impl>::type const createPose = {{}};

struct createLIPose_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT>
	void operator()(H &human, I &inputs, PRT const &part) const
	{

		Value* _kp;
		Value* _kd;
		if (inputs.top().size() < 3)
		{
			_kp = new Value(false, std::string("1000"));
		}
		else
		{
			_kp = new Value(*(inputs.top().at(1)));
		}
		if (inputs.top().size() < 4)
		{
			_kd = new Value(false, std::string("100"));
		}
		else
		{
			_kd = new Value(*(inputs.top().at(2)));
		}


		LIPose* LIP = new LIPose(human.getJointFromString(part), inputs.top().at(0), _kp, _kd, inputs.top().at(inputs.top().size()-1));

		phase_ptr->actions.push_back(LIP);



	}
};

boost::xpressive::function<createLIPose_impl>::type const createLIPose = {{}};

struct createPoseFB_impl
{
	typedef void result_type;

	template<typename H, typename I, typename JNT, typename ON_TYPE, typename ON>
	void operator()(H &human, I &inputs, JNT const &joint, ON_TYPE const &on_type, ON const &on ) const
	{
		
		Value* cd = new Value(*(inputs.top().at(0)));
		Value* cv = new Value(*(inputs.top().at(1)));

		Optimization* o;
		if (on_type.compare("joint") == 0)
		{
			o = new COMFB2(cd, cv, human.getJointFromString(on), human);
		}
		else if (on_type.compare("part") == 0)
		{
			o = new COMFB2(cd, cv, human.getObjectFromString(on)->Body, human);
		}
		else
		{
			std::cerr << "Expected 'part' or 'joint', got " << on_type << std::endl;
		}

		HingePoseOptSetter* HPOS = new HingePoseOptSetter(human.getJointFromString(joint), o);

		phase_ptr->actions.push_back(HPOS);

	}
};

boost::xpressive::function<createPoseFB_impl>::type const createPoseFB = {{}};

struct pushPhase_impl
{
	typedef void result_type;

	void operator()(void) const
	{
		c_ptr->phases.push_back(*phase_ptr);
	}
};

boost::xpressive::function<pushPhase_impl>::type const pushPhase = {{}};

struct createCOMFB_impl
{
	typedef void result_type;

	template<typename H, typename I, typename ON_TYPE, typename ON>
	void operator()(H &human, I &inputs, ON_TYPE const &type, ON const &on) const
	{

		Value* cd = new Value(*(inputs.top().at(0)));
		Value* cv = new Value(*(inputs.top().at(1)));

		delete opt_ptr;

		if (type == 'j')
		{
			opt_ptr = new COMFB2(cd, cv, human.getJointFromString(on), human);
		}
		else if (type == 'p')
		{
			opt_ptr = new COMFB2(cd, cv, human.getPartFromString(on), human);
		}
		else if (type == 'c')
		{
			opt_ptr = new COMFB2(cd, cv, human);
		}

	}
};

boost::xpressive::function<createCOMFB_impl>::type const createCOMFB = {{}};

struct createVPD_impl
{
	typedef void result_type;

	template<typename CR, typename H, typename I, typename S>
	void operator()(CR &cr, H &human, I &inputs, S const &part, S const &joint, S const &flags ) const
	{

		Value* angle = new Value(*(inputs.top().at(0)));
		Value* _kp;
		Value* _kd;
		if (inputs.top().size() < 2)
		{
			_kp = new Value(false, std::string("300"));
		}
		else
		{
			_kp = new Value(*(inputs.top().at(1)));
		}
		if (inputs.top().size() < 3)
		{
			_kd = new Value(false, std::string("30"));
		}
		else
		{
			_kd = new Value(*(inputs.top().at(2)));
		}

        bool simbicon = false;
        if (flags.compare("") != 0)
        {
            if (flags.compare("s") == 0)
            {
                simbicon = true;
            }
        }



		VPDController* VPD = cr->createVPDController(human, part, joint, angle, _kp, _kd,new Value(false, "0.0"), simbicon);

	//	VPD->setKP(new Value(false,_kp));
	//	VPD->setKD(new Value(false,_kd));
		VPD->optimization = opt_ptr;


		phase_ptr->actions.push_back(VPD);

		opt_ptr = new inactiveOptimization();


	}
};

boost::xpressive::function<createVPD_impl>::type const createVPD = {{}};

struct createEF_impl
{
	typedef void result_type;

	template<typename H, typename PRT, typename X, typename Y, typename Z>
	void operator()(H &human, PRT const &part, X const &x, Y const &y, Z const &z ) const
	{

		ExternalForceController* EF = new ExternalForceController(human.getPartFromString(part), new Value(false,x), new Value(false,y), new Value(false,z));


		phase_ptr->actions.push_back(EF);


	}
};

boost::xpressive::function<createEF_impl>::type const createEF = {{}};

struct createVF_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT, typename JNT>
	void operator()(H &human, I &inputs, PRT const &part, JNT const &joint) const
	{



		VirtualForceController* VF = new VirtualForceController(human.getObjectFromString(part), human.getJointFromString(joint), new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), new Value(*(inputs.top().at(2))));

		human.findJointPath(human.getObjectFromString(part), human.getJointFromString(joint), VF->getPath());

		phase_ptr->actions.push_back(VF);


	}
};

boost::xpressive::function<createVF_impl>::type const createVF = {{}};

struct createGC_impl
{
	typedef void result_type;

	template<typename H, typename O, typename B>
	void operator()(H &human,  O const &on, B const &by) const
	{



		GravityCompensator* GC = new GravityCompensator(human.getObjectFromString(on), human.getJointFromString(by), human);

//		human.findJointPath(human.getObjectFromString(on), human.getJointFromString(by), GC->getPath());

		phase_ptr->actions.push_back(GC);

	}
};

boost::xpressive::function<createGC_impl>::type const createGC = {{}};
/*
struct createSVF_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT, typename JNT>
	void operator()(H &human, I &inputs, PRT const &part, JNT const &joint) const
	{


		SimpleVFController* SVF = new SimpleVFController(human.getObjectFromString(part), human.getJointFromString(joint), new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), new Value(*(inputs.top().at(2))));


		phase_ptr->actions.push_back(SVF);


	}
};

boost::xpressive::function<createSVF_impl>::type const createSVF = {{}};
*/

struct createParam_impl
{
	typedef void result_type;

	template<typename P, typename V>
	void operator()(P &params,  V const &name) const
	{

		params.push_back(name);

	}
};

boost::xpressive::function<createParam_impl>::type const createParam = {{}};

struct pushVar_impl
{
	typedef void result_type;

	template<typename N, typename I>
	void operator()(bool v,  N const &name, I &inputs) const
	{


	//	params.push_back(name);
		inputs.top().push_back(new Value(v, name));

	}
};

boost::xpressive::function<pushVar_impl>::type const pushVar = {{}};

struct pushInputs_impl
{
	typedef void result_type;

	template<typename I>
	void operator()(I &inputs) const
	{

	//	params.push_back(name);
		inputs.push(std::vector<Value*>());

	}
};

boost::xpressive::function<pushInputs_impl>::type const pushInputs = {{}};

struct popInputs_impl
{
	typedef void result_type;

	template<typename I>
	void operator()(I &inputs) const
	{

	//	params.push_back(name);
		inputs.pop();

	}
};

boost::xpressive::function<popInputs_impl>::type const popInputs = {{}};

struct voidFound_impl
{
	typedef void result_type;

	void operator()() const
	{


	}
};

boost::xpressive::function<voidFound_impl>::type const voidFound = {{}};

struct createLInterp_impl
{
	typedef void result_type;

	template<typename I>
	void operator()(I &inputs) const
	{


		LI_ptr = new LInterpValue(new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), new Value(*(inputs.top().at(2))), new Value(*(inputs.top().at(3))), new Value(*(inputs.top().at(4))));


		inputs.pop();

		inputs.top().push_back(LI_ptr);


	}
};

boost::xpressive::function<createLInterp_impl>::type const createLInterp = {{}};

struct createIK_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT, typename G, typename JNT>
	void operator()(H &human, I &inputs, PRT const &part, G const &global, JNT const &joint) const
	{

		bool g = true; 
		if (global.compare("local") == 0)
		{
			g = false;
		}
		else if (global.compare("global") == 0)
		{
			g = true;
		}

		IKSolver* IK;
		if ( inputs.top().size() == 3) 
		{
		        IK = new IKSolver(human.getJointFromString(joint), human.getObjectFromString(part), new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), new Value(*(inputs.top().at(2))), g);
		}

		else if ( inputs.top().size() == 4)
		{
		        IK = new IKSolver(human.getJointFromString(joint), human.getObjectFromString(part), new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), new Value(*(inputs.top().at(2))), g, new Value(*(inputs.top().at(3))));
		}


		phase_ptr->actions.push_back(IK);


	}
};

boost::xpressive::function<createIK_impl>::type const createIK = {{}};

struct createVFFB_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT, typename JNT, typename F>
	void operator()(H &human, I &inputs, PRT const &part, JNT const &joint, F const &feet) const
	{

		bool lf=false, rf=false;
		if ( feet.compare("rFoot") == 0)
		{
			rf = true;
		}
		else if (feet.compare("lFoot") == 0)
		{
			lf = true;
		}
		else if (feet.compare("cop") == 0)
		{
		}

		VFFeedback* VFFB = new VFFeedback(human.getObjectFromString(part), human.getJointFromString(joint), new Value(*(inputs.top().at(0))), new Value(*(inputs.top().at(1))), human, feet);

		phase_ptr->actions.push_back(VFFB);
	}
};

boost::xpressive::function<createVFFB_impl>::type const createVFFB = {{}};

struct createVFSFB_impl
{
	typedef void result_type;

	template<typename H, typename I, typename PRT, typename JNT>
	void operator()(H &human, I &inputs, PRT const &part, JNT const &joint) const
	{

		VFSpeedFeedback* VFSFB = new VFSpeedFeedback(human.getObjectFromString(part), human.getJointFromString(joint), new Value(*(inputs.top().at(0))),  human, new Value(*(inputs.top().at(1))));

		phase_ptr->actions.push_back(VFSFB);
	}
};

boost::xpressive::function<createVFSFB_impl>::type const createVFSFB = {{}};

struct handleError_impl
{
	typedef void result_type;

	template<typename E, typename F>
	void operator()(E const &err, F &flag) const
	{
		flag = true;
		cerr << "Unexpected line found: " << err << endl;
	}
};

boost::xpressive::function<handleError_impl>::type const handleError = {{}};

struct createSave_impl
{
	typedef void result_type;

	template<typename H, typename S>
	void operator()(H &human, S const &savename) const
	{
		StateSaver* SS = new StateSaver(human, savename);
		phase_ptr->actions.push_back(SS);
	}
};

boost::xpressive::function<createSave_impl>::type const createSave = {{}};

struct createLoad_impl
{
	typedef void result_type;

	template<typename H, typename S>
	void operator()(H &human, S const &savename) const
	{
		StateLoader* SL = new StateLoader((Human&)human, savename);
		phase_ptr->actions.push_back(SL);
	}
};

boost::xpressive::function<createLoad_impl>::type const createLoad = {{}};

struct createMatch_impl
{
	typedef void result_type;

	template<typename H, typename I, typename J>
	void operator()(H &human, I &inputs, J const &joint, J const &other) const
	{
        Matcher* M;

        int args_size = inputs.top().size();

        if (args_size == 1 || args_size == 3)
        { 
		    M = new Matcher(human.getJointFromString(joint), human.getJointFromString(other), new Value(*(inputs.top().at(args_size-1))));
        }
        else
	    {
            M = new Matcher(human.getJointFromString(joint), human.getJointFromString(other));
        }

        if (args_size > 1)
        {
            M->setKP(new Value(*(inputs.top().at(0))));
            M->setKD(new Value(*(inputs.top().at(1))));
        }
        else
        {
            M->setKP(new Value(false, 1000));
            M->setKD(new Value(false, 100));
        }

		phase_ptr->actions.push_back(M);
	}
};

boost::xpressive::function<createMatch_impl>::type const createMatch = {{}};

struct createHold_impl
{
	typedef void result_type;

	template<typename H, typename J>
	void operator()(H &human, J const &joint) const
	{
		Holder* Hold = new Holder(human.getJointFromString(joint));
		phase_ptr->actions.push_back(Hold);
	}
};

boost::xpressive::function<createHold_impl>::type const createHold = {{}};

struct pushToggleVisible_impl
{
	typedef void result_type;

	template<typename S>
	void operator()(S const &obj_name) const
	{
        std::function<void()> func = [=]() { toggleVisible(obj_name); };
        EA_ptr->actions.push_back(func);
	}
};

boost::xpressive::function<pushToggleVisible_impl>::type const pushToggleVisible = {{}};

struct pushToggleCollidable_impl
{
	typedef void result_type;

	template<typename S>
	void operator()(S const &obj_name) const
	{
        std::function<void()> func = [=]() { toggleCollidable(obj_name); };
        EA_ptr->actions.push_back(func);
	}
};

boost::xpressive::function<pushToggleCollidable_impl>::type const pushToggleCollidable = {{}};

struct pushEnvAction_impl
{
	typedef void result_type;

	void operator()() const
	{
        EA_ptr = new EnvAction();
		phase_ptr->actions.push_back(EA_ptr);
	}
};

boost::xpressive::function<pushEnvAction_impl>::type const pushEnvAction = {{}};

struct setTransPass_impl
{
	typedef void result_type;

	template<typename H, typename I, typename S>
	void operator()( H &human, I &inputs, S const &ent_name) const
	{
		trans_ptr->type = PASS;
	        trans_ptr->human = (Human*)&human;
            trans_ptr->ent_name = ent_name;
            trans_ptr->dx = new Value(*(inputs.top().at(0)));
            trans_ptr->inside = false;

		phase_ptr->transitions.push_back(trans_ptr);
	}
};

boost::xpressive::function<setTransPass_impl>::type const setTransPass = {{}};
