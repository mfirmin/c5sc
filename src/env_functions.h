
Object* OI2Box(obj_info* oi)
{

		dReal rot[4] = {0,0,0,0};

		Shape* shape = new Box(oi->mass, oi->pos, VECTOR(0,0,0), rot, oi->dim);

		Object* o = new Object();
		o->Body = dBodyCreate(World);

		o->parent = NULL;
		o->shape = shape;
		o->setFriction(-1);

		o->human_part = false;

        o->setVisible(oi->visible);
        o->setCollidable(oi->collidable);

		shape->initialize(o->Body, o->Geom[0]);
		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


		dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
		dJointAttach(lin_motor, o->Body, 0);
		dJointSetLMotorNumAxes(lin_motor,1);
		dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
		dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
		dJointSetLMotorParam(lin_motor,dParamVel, 0);

		dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
		dJointAttach(ang_motor, o->Body, 0);
		dJointSetAMotorNumAxes(ang_motor,2);
		dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
		dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
		dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
		dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
		dJointSetAMotorParam(ang_motor, dParamVel, 0);
		dJointSetAMotorParam(ang_motor, dParamVel2, 0);

        return o;
}

Object* OI2Sphere(obj_info* oi)
{

		dReal rot[4] = {0,0,0,0};

		Shape* shape = new Sphere(oi->mass, oi->pos, VECTOR(0,0,0), rot, oi->rad);

		Object* o = new Object();
		o->Body = dBodyCreate(World);

		o->parent = NULL;
		o->shape = shape;
		o->setFriction(-1);

		o->human_part = false;
        o->setVisible(oi->visible);
        o->setCollidable(oi->collidable);

		shape->initialize(o->Body, o->Geom[0]);
		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


		dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
		dJointAttach(lin_motor, o->Body, 0);
		dJointSetLMotorNumAxes(lin_motor,1);
		dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
		dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
		dJointSetLMotorParam(lin_motor,dParamVel, 0);

		dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
		dJointAttach(ang_motor, o->Body, 0);
		dJointSetAMotorNumAxes(ang_motor,2);
		dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
		dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
		dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
		dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
		dJointSetAMotorParam(ang_motor, dParamVel, 0);
		dJointSetAMotorParam(ang_motor, dParamVel2, 0);

        return o;
}

Object* OI2Plane(obj_info* oi)
{

		Object* o = new Plane(oi->pos.x, oi->pos.y, oi->pos2.x, oi->pos2.y);

		o->parent = NULL;
		o->setFriction(-1);

		o->human_part = false;
        o->setVisible(oi->visible);
        o->setCollidable(oi->collidable);


		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


        return o;
}

Object* OI2Heightfield(obj_info* oi)
{

		Object* o = new Heightfield((char*)(oi->name.c_str()));

		o->parent = NULL;
		o->setFriction(-1);

		o->human_part = false;

        o->setVisible(oi->visible);
        o->setCollidable(oi->collidable);

		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));

        return o;
}

void OI2Custom(std::vector<Object*>* objs, obj_info* oi)
{
    for (int i = 0; i <  oi->children->size(); i++)
    {
        switch (oi->children->at(i)->type)
        {
            case BOX_:
                objs->push_back(OI2Box(oi->children->at(i)));
                break;
            case SPHERE_:
                objs->push_back(OI2Sphere(oi->children->at(i)));
                break;
            case PLANE_:
                objs->push_back(OI2Plane(oi->children->at(i)));
                break;
            case HEIGHTFIELD_:
                objs->push_back(OI2Heightfield(oi->children->at(i)));
                break;
            case CUSTOM_:
                OI2Custom(objs, oi->children->at(i));
                break;
            default:
                break;
        }
    }

}

struct pushBox1_impl
{
	typedef void result_type;

	template<typename O, typename F>
	void operator()( O &objs, F const &m, F const &s, F const &x, F const &y, F const &z ) const
	{


        obj_info *o = new obj_info;
        o->type = BOX_;
        o->mass = m;
        o->pos = VECTOR(x,y,z);
        o->dim = VECTOR(s,s,s);

        objs->push_back(o);
/*
*/
	}
};

function<pushBox1_impl>::type const pushBox1 = {{}};

struct pushBox2_impl
{
	typedef void result_type;

	template<typename O, typename F>
	void operator()( O &objs, F const &m, F const &s1, F const s2, F const s3, F const &x, F const &y, F const &z ) const
	{
        obj_info *o = new obj_info;
        o->type = BOX_;
        o->mass = m;
        o->pos = VECTOR(x,y,z);
        o->dim = VECTOR(s1,s2,s3);

        objs->push_back(o);
/*
		dReal rot[4] = {0,0,0,0};

		Shape* shape = new Box(m, VECTOR(x,y,z), VECTOR(0,0,0), rot, VECTOR(s1,s2,s3));

		Object* o = new Object();
		o->Body = dBodyCreate(World);

		o->parent = NULL;
		o->shape = shape;
		o->setFriction(-1);

		o->human_part = false;

		shape->initialize(o->Body, o->Geom[0]);
		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


		dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
		dJointAttach(lin_motor, o->Body, 0);
		dJointSetLMotorNumAxes(lin_motor,1);
		dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
		dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
		dJointSetLMotorParam(lin_motor,dParamVel, 0);

		dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
		dJointAttach(ang_motor, o->Body, 0);
		dJointSetAMotorNumAxes(ang_motor,2);
		dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
		dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
		dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
		dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
		dJointSetAMotorParam(ang_motor, dParamVel, 0);
		dJointSetAMotorParam(ang_motor, dParamVel2, 0);

		objs->push_back(o);
*/
	}
};

function<pushBox2_impl>::type const pushBox2 = {{}};

struct pushSphere_impl
{
	typedef void result_type;

	template<typename O, typename F>
	void operator()( O &objs, F const &m, F const &r, F const &x, F const &y, F const &z ) const
	{

        obj_info *o = new obj_info;
        o->type = SPHERE_;
        o->mass = m;
        o->rad = r;
        o->pos = VECTOR(x,y,z);

        objs->push_back(o);
/*
		dReal rot[4] = {0,0,0,0};

		Shape* shape = new Sphere(m, VECTOR(x,y,z), VECTOR(0,0,0), rot, r);

		Object* o = new Object();
		o->Body = dBodyCreate(World);

		o->parent = NULL;
		o->shape = shape;
		o->setFriction(-1);

		o->human_part = false;

		shape->initialize(o->Body, o->Geom[0]);
		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


		dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
		dJointAttach(lin_motor, o->Body, 0);
		dJointSetLMotorNumAxes(lin_motor,1);
		dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
		dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
		dJointSetLMotorParam(lin_motor,dParamVel, 0);

		dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
		dJointAttach(ang_motor, o->Body, 0);
		dJointSetAMotorNumAxes(ang_motor,2);
		dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
		dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
		dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
		dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
		dJointSetAMotorParam(ang_motor, dParamVel, 0);
		dJointSetAMotorParam(ang_motor, dParamVel2, 0);

		objs->push_back(o);
*/
	}
};

function<pushSphere_impl>::type const pushSphere = {{}};


struct pushStairs_impl
{
	typedef void result_type;

	template<typename O, typename F, typename I>
	void operator()( O &objs, F const &start, F const &length, F const &height, I const &num) const
	{
        std::cout << "starting to push stairs" << std::endl;
        obj_info *o = new obj_info;
        o->type = CUSTOM_;
        o->mass = 1000;
        o->pos = VECTOR(0,0,0);
        o->children = new std::vector<obj_info*>;

        for (int i = 0; i < num; i++)
        {
            
            obj_info *o_child = new obj_info;
            o_child->type = BOX_;
            o_child->mass = 1000;
            o_child->pos = VECTOR(start+length/2.0+length*i, height/2.0*(i+1),-10);
            o_child->dim = VECTOR(length,height*(i+1),5);

            o->children->push_back(o_child);
        }

        objs->push_back(o);

        std::cout << "stairs pushed" << std::endl;
/*
		for (int i = 0; i < num; i++)
		{
			dReal rot[4] = {0,0,0,0};

			Shape* shape = new Box(1000, VECTOR(start+length/2.0+length*i, height/2.0*(i+1),-10), VECTOR(0,0,0), rot, VECTOR(length,height*(i+1),5));

			Object* o = new Object();
			o->Body = dBodyCreate(World);

			o->parent = NULL;
			o->shape = shape;

			o->human_part = false;
			o->setFriction(-1);

			shape->initialize(o->Body, o->Geom[0]);
			geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


			dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
			dJointAttach(lin_motor, o->Body, 0);
			dJointSetLMotorNumAxes(lin_motor,1);
			dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
			dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
			dJointSetLMotorParam(lin_motor,dParamVel, 0);

			dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
			dJointAttach(ang_motor, o->Body, 0);
			dJointSetAMotorNumAxes(ang_motor,2);
			dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
			dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
			dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
			dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
			dJointSetAMotorParam(ang_motor, dParamVel, 0);
			dJointSetAMotorParam(ang_motor, dParamVel2, 0);

			objs->push_back(o);

		}
*/
	}
};

function<pushStairs_impl>::type const pushStairs = {{}};

struct pushPlane_impl
{
	typedef void result_type;

	template<typename O, typename V>
	void operator()( O &objs, V const &x1, V const &y1, V const &x2, V const &y2) const
	{

        obj_info *o = new obj_info;
        o->type = PLANE_;
        o->pos = VECTOR(x1,y1,-10);
        o->pos2 = VECTOR(x2,y2,-10);

        objs->push_back(o);

        /*
		dReal rot[4] = {0,0,0,0};

		Object* o = new Plane(x1, y1, x2, y2);

		o->parent = NULL;
		o->setFriction(-1);

		o->human_part = false;

		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));




        objs->push_back(o);
*/

	}
};

function<pushPlane_impl>::type const pushPlane = {{}};

struct pushHeightfield_impl
{
	typedef void result_type;

	template<typename O, typename S>
	void operator()( O &objs, S const name) const
	{

        obj_info *o = new obj_info;
        o->type = HEIGHTFIELD_;
        o->name = name;


        objs->push_back(o);
        /*
		dReal rot[4] = {0,0,0,0};

		Object* o = new Heightfield((char*)(name.c_str()));

		o->parent = NULL;
		o->setFriction(-1);

		o->human_part = false;

		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));




        objs->push_back(o);

*/
	}
};

function<pushHeightfield_impl>::type const pushHeightfield = {{}};

struct pushCustom_impl
{
	typedef void result_type;

	template<typename O, typename M, typename S, typename F>
	void operator()( O &objs, M &customMap, S const &name, F const &x, F const &y, F const &z) const
	{


        obj_info* o = new obj_info(customMap.find(name)->second);
        
        o->addPos(VECTOR(x,y,z));
        
        // PROBLEM: HAS NO TYPE SET
        objs->push_back(o);

//        objs->push_back(custom);
        /*
		dReal rot[4] = {0,0,0,0};

		Object* o = new Custom((char*)(name.c_str()));

		o->parent = NULL;
		o->setFriction(-1);

		o->human_part = false;

		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));




        objs->push_back(o);

*/
	}
};

function<pushCustom_impl>::type const pushCustom = {{}};

struct setFriction_impl
{
	typedef void result_type;

	template<typename O, typename F>
	void operator()( O &objs, F const &f ) const
	{

//		objs->back()->setFriction(f);

	}
};

function<setFriction_impl>::type const setFriction = {{}};

struct fillObjects_impl
{
	typedef void result_type;

	template<typename N, typename E, typename OI>
	void operator()( N &names, E &entities, OI &obj_inf_ptr) const
	{
        

        for (int i = 0; i < obj_inf_ptr->size(); i++)
        {
            Entity* ent = new Entity(names.at(i));

            
            switch (obj_inf_ptr->at(i)->type)
            {
                case BOX_:
                    ent->getBodies().push_back(OI2Box(obj_inf_ptr->at(i)));
                    break;
                case SPHERE_:
                    ent->getBodies().push_back(OI2Sphere(obj_inf_ptr->at(i)));
                    break;
                case PLANE_:
                    ent->getBodies().push_back(OI2Plane(obj_inf_ptr->at(i)));
                    break;
                case HEIGHTFIELD_:
                    ent->getBodies().push_back(OI2Heightfield(obj_inf_ptr->at(i)));
                    break;
                case CUSTOM_:
                    OI2Custom(&(ent->getBodies()), obj_inf_ptr->at(i));
                    break;
                default:
                    break;
            }

            entities.insert(std::pair<std::string, Entity*>(names.at(i), ent));

        }

/*
		dReal rot[4] = {0,0,0,0};

		Shape* shape = new Box(m, VECTOR(x,y,z), VECTOR(0,0,0), rot, VECTOR(s,s,s));

		Object* o = new Object();
		o->Body = dBodyCreate(World);

		o->parent = NULL;
		o->shape = shape;
		o->setFriction(-1);

		o->human_part = false;

		shape->initialize(o->Body, o->Geom[0]);
		geom2obj.insert(std::pair<dGeomID, Object*>(o->Geom[0], o));


		dJointID lin_motor = dJointCreateLMotor(World, jointgroup);
		dJointAttach(lin_motor, o->Body, 0);
		dJointSetLMotorNumAxes(lin_motor,1);
		dJointSetLMotorAxis(lin_motor,0,1,0,0,1);
		dJointSetLMotorParam(lin_motor,dParamFMax, 1000000);
		dJointSetLMotorParam(lin_motor,dParamVel, 0);

		dJointID ang_motor = dJointCreateAMotor(World, jointgroup);
		dJointAttach(ang_motor, o->Body, 0);
		dJointSetAMotorNumAxes(ang_motor,2);
		dJointSetAMotorAxis(ang_motor, 0, 0, 0, 1, 0);
		dJointSetAMotorAxis(ang_motor, 1, 0, 1, 0, 0);
		dJointSetAMotorParam(ang_motor, dParamFMax, 10000000);
		dJointSetAMotorParam(ang_motor, dParamFMax2, 10000000);
		dJointSetAMotorParam(ang_motor, dParamVel, 0);
		dJointSetAMotorParam(ang_motor, dParamVel2, 0);

		objs->push_back(o);
*/
	}
};

function<fillObjects_impl>::type const fillObjects = {{}};

struct createCustom_impl
{
	typedef void result_type;

	template<typename S, typename OI, typename M>
	void operator()( S const &name, OI &children, M &customMap ) const
	{
        obj_info* custom = new obj_info;
        
        custom->name = name;
        custom->type = CUSTOM_;
        custom->pos = VECTOR(0,0,0);

        custom->children = children;
       /* 
        for (int i = 0; i < children->size(); i++)
        {
            std::cout << custom->children->at(i)->type << std::endl;
            std::cout << "pos: " << custom->children->at(i)->pos.x << std::endl;
        }
        */

        customMap.insert(std::pair<std::string, obj_info*>(name, custom));

//		objs->back()->createCustom(f);

	}
};

function<createCustom_impl>::type const createCustom = {{}};

struct newObjInfVecPtr_impl
{
	typedef void result_type;

	template<typename O>
	void operator()( O &obj_inf_ptr) const
	{

        obj_inf_ptr = new std::vector<obj_info*>;
            

/*
*/
	}
};

function<newObjInfVecPtr_impl>::type const newObjInfVecPtr = {{}};
