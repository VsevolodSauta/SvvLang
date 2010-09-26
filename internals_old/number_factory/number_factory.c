#include "internals/number_factory/interface.h"

Action(NumberFactory, FromLong, long arg)
{
	Object toReturn = Number_Create();
	Number_SetLong(toReturn, arg);
	return toReturn;
};

Object numberFactory;