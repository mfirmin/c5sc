#include "value.h"


void Value::set(bool var, std::string val)
{
	isVariable = var;
	value = val;
}
void Value::set(bool var, dReal val)
{
	isVariable = var;
	value = boost::lexical_cast<std::string>(val);
}
int Value::getInt()
{
	if (isVariable)
	{
		return atoi(lookupTable.top()->find(value)->second.c_str());
	}
	else
		return atoi(value.c_str());
}
dReal Value::getdReal()
{

	if (isVariable)
	{
		return atof(lookupTable.top()->find(value)->second.c_str());
	}
	else
		return atof(value.c_str());
}

dReal LInterpValue::getdReal()
{

	return (v_max->getdReal() - v_min->getdReal()) * ( (goal->getdReal() - g_min->getdReal()) / (g_max->getdReal() - g_min->getdReal()) ) + v_min->getdReal();

}

std::string Value::getString()
{
	if (isVariable)
	{
		return lookupTable.top()->find(value)->second;
	}
	else
		return value;
}
