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
	LONG(toReturn) = LONG(receiver) + LONG(arg);
	return toReturn;
};

Action(Number, Sub, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) - LONG(arg);
	return toReturn;
};

Action(Number, Mul, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) * LONG(arg);
	return toReturn;
};

Action(Number, Div, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) / LONG(arg);
	return toReturn;
};

Action(Number, AddInPlace, Object arg)
{
	LONG(receiver) += LONG(arg);
	return receiver;
};

Action(Number, SubInPlace, Object arg)
{
	LONG(receiver) -= LONG(arg);
	return receiver;
};

Action(Number, MulInPlace, Object arg)
{
	LONG(receiver) *= LONG(arg);
	return receiver;
};

Action(Number, DivInPlace, Object arg)
{
	LONG(receiver) /= LONG(arg);
	return receiver;
};

