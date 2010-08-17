#include "internals/number/interface.h"
#include "internals/allocator/interface.h"
#include "internals/globals.h"

SvvInternalDefaultCreator(SvvInternalNumber);

SvvInternalAction(SvvInternalNumber, Init)
{
	return Receiver;
};

SvvInternalAction(SvvInternalNumber, Add, SvvInternalObject Arg)
{
	SvvInternalObject toReturn = SvvInternalNumber_Create();
	SvvInternalObject_Autorelease(toReturn);
	GET_ENTITY(toReturn, SvvInternalNumber)->entity = 
		GET_ENTITY(Receiver, SvvInternalNumber)->entity +
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return toReturn;
};

SvvInternalAction(SvvInternalNumber, Sub, SvvInternalObject Arg)
{
	SvvInternalObject toReturn = SvvInternalNumber_Create();
	SvvInternalObject_Autorelease(toReturn);
	GET_ENTITY(toReturn, SvvInternalNumber)->entity = 
		GET_ENTITY(Receiver, SvvInternalNumber)->entity -
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return toReturn;
};

SvvInternalAction(SvvInternalNumber, Mul, SvvInternalObject Arg)
{
	SvvInternalObject toReturn = SvvInternalNumber_Create();
	SvvInternalObject_Autorelease(toReturn);
	GET_ENTITY(toReturn, SvvInternalNumber)->entity = 
		GET_ENTITY(Receiver, SvvInternalNumber)->entity *
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return toReturn;
};

SvvInternalAction(SvvInternalNumber, Div, SvvInternalObject Arg)
{
	SvvInternalObject toReturn = SvvInternalNumber_Create();
	SvvInternalObject_Autorelease(toReturn);
	GET_ENTITY(toReturn, SvvInternalNumber)->entity = 
		GET_ENTITY(Receiver, SvvInternalNumber)->entity /
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return toReturn;
};

SvvInternalAction(SvvInternalNumber, AddInPlace, SvvInternalObject Arg)
{
	GET_ENTITY(Receiver, SvvInternalNumber)->entity += 
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return Receiver;
};

SvvInternalAction(SvvInternalNumber, SubInPlace, SvvInternalObject Arg)
{
	GET_ENTITY(Receiver, SvvInternalNumber)->entity -= 
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return Receiver;
};

SvvInternalAction(SvvInternalNumber, MulInPlace, SvvInternalObject Arg)
{
	GET_ENTITY(Receiver, SvvInternalNumber)->entity *= 
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return Receiver;
};

SvvInternalAction(SvvInternalNumber, DivInPlace, SvvInternalObject Arg)
{
	GET_ENTITY(Receiver, SvvInternalNumber)->entity /= 
		GET_ENTITY(Arg, SvvInternalNumber)->entity;
	return Receiver;
};

