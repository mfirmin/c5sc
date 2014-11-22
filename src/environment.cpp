
#include <iostream>
#include <string>
#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <map>
#include <utility>

#include "VECTOR.h"
#include "object.h"
#include "shape.h"
#include "globals.h"
#include "environment.h"
#include "heightfield.h"
#include "entity.h"

using namespace boost::xpressive;

#include "env_functions.h"

sregex OBJECTS_STRUCT;
sregex OBJECTS;
sregex OBJECT;
sregex BOX1_X, BOX2_X;
sregex SPHERE_X;
sregex STAIRS_X;
sregex PLANE_X;
sregex CUSTOM_X;
sregex HEIGHTFIELD_X;
sregex FRICTION;
sregex DEFINITION;
sregex DEFINITIONS;
sregex ENTITIES;
sregex ENTITY;
sregex NAME;

void Environment::setFromFile(std::string fname)
{
	std::ifstream ifs;
	ifs.open(fname.c_str());
	if (!ifs)
	{
		std::cerr << "Cannot open controller script: " << fname << std::endl;
		return;
	}
	std::string input( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));


    std::vector<obj_info*>* obj_info_ptr;

	sregex INT, FLOAT, COMMENT, FNAME, WORD;

	COMMENT = "#" >> *~_n >> _n;
	INT = sregex::compile("-?\\d+\\.?");
	FLOAT = sregex::compile("-?\\d*\\.\\d+");
    FNAME = +_w >> ".hf";
    WORD = +_w;
    NAME = +_w;

	BOX1_X = ("Box" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> "," 
 	 	     >> *space >> (s2= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s3= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s4= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s5= INT|FLOAT) >> *space >> ")")
		[ pushBox1(boost::xpressive::ref(obj_info_ptr), as<float>(s1), as<float>(s2), as<float>(s3), as<float>(s4), as<float>(s5) ) ];

	BOX2_X = ("Box" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> "," 
 	 	     >> *space >> (s2= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s3= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s4= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s5= INT|FLOAT) >> *space >> ","
		     >> *space >> (s6= INT|FLOAT) >> *space >> ","
		     >> *space >> (s7= INT|FLOAT) >> *space >> ")")
		[ pushBox2(boost::xpressive::ref(obj_info_ptr), as<float>(s1), as<float>(s2), as<float>(s3), as<float>(s4), as<float>(s5), as<float>(s6), as<float>(s7) ) ];

	SPHERE_X = ("Sphere" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> "," 
 	 	     >> *space >> (s2= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s3= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s4= INT|FLOAT) >> *space >> "," 
		     >> *space >> (s5= INT|FLOAT) >> *space >> ")")
		[ pushSphere(boost::xpressive::ref(obj_info_ptr), as<float>(s1), as<float>(s2), as<float>(s3), as<float>(s4), as<float>(s5) ) ];


	STAIRS_X = ("Stairs" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> ","
			>> *space >> (s2= INT|FLOAT) >> *space >> ","
			>> *space >> (s3= INT|FLOAT) >> *space >> ","
			>> *space >> (s4= INT) >> *space >> ")")
		[ pushStairs(boost::xpressive::ref(obj_info_ptr), as<float>(s1), as<float>(s2), as<float>(s3), as<int>(s4)) ];

	PLANE_X = ("2DPlane" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> ","
			>> *space >> (s2= INT|FLOAT) >> *space >> ","
			>> *space >> (s3= INT|FLOAT) >> *space >> ","
			>> *space >> (s4= INT|FLOAT) >> *space >> ")")
		[ pushPlane(boost::xpressive::ref(obj_info_ptr), as<float>(s1), as<float>(s2), as<float>(s3), as<float>(s4)) ];

    HEIGHTFIELD_X = ("Heightfield" >> *space >> "(" >> *space >> (s1 = FNAME) >> *space >> ")" ) [ pushHeightfield(boost::xpressive::ref(obj_info_ptr), as<std::string>(s1)) ];
    
    obj_info* custom = new obj_info;


    std::map<std::string, obj_info*> customMap;

    CUSTOM_X = ((s1= WORD) >> *space >> "(" >> *space >> (s2= INT|FLOAT) >> *space >> "," >> *space >> (s3= INT|FLOAT) >> *space >> "," >> *space >> (s4= INT|FLOAT) >> *space >> ")") [ pushCustom(boost::xpressive::ref(obj_info_ptr), boost::xpressive::ref(customMap), as<std::string>(s1), as<float>(s2), as<float>(s3), as<float>(s4)) ]; 

	FRICTION = (".friction" >> *space >> "(" >> *space >> (s1= INT|FLOAT) >> *space >> ")") [ setFriction(boost::xpressive::ref(obj_info_ptr), as<float>(s1)) ];


	OBJECT = (BOX1_X
		| BOX2_X
		| SPHERE_X
		| STAIRS_X
        | PLANE_X 
        | HEIGHTFIELD_X 
        | CUSTOM_X ) >> !(FRICTION);

    std::vector<std::string> names;

    ENTITY = (s1= NAME) [ push_back(boost::xpressive::ref(names), as<std::string>(s1)) ] >> *space >> "=" >> *space >> OBJECT;

	OBJECTS = ( ((OBJECT >> *space >> ";")|COMMENT) >> *space >> by_ref(OBJECTS))
		| OBJECT >> *space >> ";"
		| COMMENT;

    ENTITIES = ( ((ENTITY >> *space >> ";")|COMMENT) >> *space >> by_ref(ENTITIES))
        | ENTITY >> *space >> ";"
        | COMMENT;

	OBJECTS_STRUCT = ("ENTITIES" >> *space >> "{" >> *space >> ENTITIES >> *space >> "}") [ fillObjects(boost::xpressive::ref(names), boost::xpressive::ref(entities), boost::xpressive::ref(obj_info_ptr)) ];

    //map of custom object names to their obj_info ptr's.
//    custom->children = new std::vector<obj_info*>;
//    obj_info_ptr = custom->children;

    // fills in custom's children thru OBJECTS call, then calls createCustom to name it
    DEFINITION = ("DEFINE" >> *space >> (s1= WORD) [ newObjInfVecPtr(boost::xpressive::ref(obj_info_ptr)) ] >> *space >> "{" >> *space >> OBJECTS >> *space >> "}") [ createCustom(as<std::string>(s1), boost::xpressive::ref(obj_info_ptr), boost::xpressive::ref(customMap)) ] ;

    DEFINITIONS = (DEFINITION >> *space >> by_ref(DEFINITION))
            | DEFINITION; 


	smatch what;
	if (!regex_search(input, what, DEFINITIONS))
	{
	//	return;
	}


    std::vector<obj_info*> obj_info_vec;
    obj_info_ptr = &obj_info_vec;



	if (!regex_search(input, what, OBJECTS_STRUCT))
	{
		std::cerr << "Encountered syntax error while reading in script " << fname << std::endl;
		return;
	}



	return;


}

void Environment::addEntity(Entity* e)
{

    entities.insert(std::pair<std::string, Entity*>(e->getName(), e));

}
void Environment::deleteEntity(std::string s)
{
    
    delete entities.find(s)->second;

    entities.erase(s);

}
