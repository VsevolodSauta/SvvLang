#include "internals/NumberFactory/interface.h"
#include "internals/basics.h"

Object NumberFactory_FromLong(Object receiver, long arg)
{
	Object toReturn = Number_Create();
	Number_SetLong(toReturn, arg);
	return toReturn;
};

Object numberFactory;
