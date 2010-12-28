#include "internals/NumberFactory/interface.h"
#include "internals/basics.h"

Object NumberFactory_Create()
{
	return Undestroyable_Create();
}

Object NumberFactory_FromLong(Object receiver, long arg)
{
//	printf("Creating number.\n");
	Object toReturn = Number_Create();
	Number_SetLong(toReturn, arg);
	Object_Autorelease(toReturn);
	return toReturn;
};

Object _numberFactory;
