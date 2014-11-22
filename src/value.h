#ifndef VALUE_H
#define VALUE_H

#define dSINGLE

#include <stdlib.h>
#include <string>
#include <map>
#include <ode/ode.h>
#include <boost/lexical_cast.hpp>

#include "globals.h"

class Value
{

	public:
		Value() { }
		Value(Value& other) { this->value = other.value; this->isVariable = other.isVariable; isLinterp = false;}
		Value(bool var, std::string val) { isVariable = var; value = val; isLinterp = false;}
		Value(bool var, float val) { isVariable = var; value = boost::lexical_cast<std::string>(val); isLinterp = false;}
		bool isVariable;
		bool isLinterp;

		std::string value;

		int getInt();
		virtual dReal getdReal();
		std::string getString();

		void set(bool, std::string);
		void set(bool, dReal val);

        std::string write() { std::string ret = (isVariable ? value : boost::lexical_cast<std::string>(this->getdReal())); return ret;}


		Value& operator=(const Value& other) { this->isVariable = other.isVariable; this->value= std::string(other.value); return *this; }


};


class LInterpValue : public Value
{

	public:
		LInterpValue() {}
		LInterpValue(Value* g, Value* gmin, Value* gmax, Value* vmin, Value* vmax) { goal = g; g_min = gmin; g_max = gmax; v_min = vmin; v_max = vmax; isVariable = false; isLinterp = true;}
		
		virtual	dReal getdReal();
	

	private:
		Value* goal;
		Value* g_min;
		Value* g_max;
		Value* v_min;
		Value* v_max;

};


#endif // VALUE_H
