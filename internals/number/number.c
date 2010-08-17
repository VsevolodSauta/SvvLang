#include "internals/number/interface.h"
#include "internals/allocator/interface.h"
#include "internals/globals.h"

#define Number_GID 0x30

DefaultCreator(Number);

Action(Number, Init)
{
	return receiver;
};

Action(Number, Add, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	GET_ENTITY(toReturn, Number)->entity = 
		GET_ENTITY(receiver, Number)->entity +
		GET_ENTITY(arg, Number)->entity;
	return toReturn;
};

Action(Number, Sub, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	GET_ENTITY(toReturn, Number)->entity = 
		GET_ENTITY(receiver, Number)->entity -
		GET_ENTITY(arg, Number)->entity;
	return toReturn;
};

Action(Number, Mul, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	GET_ENTITY(toReturn, Number)->entity = 
		GET_ENTITY(receiver, Number)->entity *
		GET_ENTITY(arg, Number)->entity;
	return toReturn;
};

Action(Number, Div, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	GET_ENTITY(toReturn, Number)->entity = 
		GET_ENTITY(receiver, Number)->entity /
		GET_ENTITY(arg, Number)->entity;
	return toReturn;
};

Action(Number, AddInPlace, Object arg)
{
	GET_ENTITY(receiver, Number)->entity += 
		GET_ENTITY(arg, Number)->entity;
	return receiver;
};

Action(Number, SubInPlace, Object arg)
{
	GET_ENTITY(receiver, Number)->entity -= 
		GET_ENTITY(arg, Number)->entity;
	return receiver;
};

Action(Number, MulInPlace, Object arg)
{
	GET_ENTITY(receiver, Number)->entity *= 
		GET_ENTITY(arg, Number)->entity;
	return receiver;
};

Action(Number, DivInPlace, Object arg)
{
	GET_ENTITY(receiver, Number)->entity /= 
		GET_ENTITY(arg, Number)->entity;
	return receiver;
};

