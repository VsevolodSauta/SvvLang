#include "internals/number/interface.h"
#include "internals/allocator/interface.h"
#include "internals/globals.h"
#include "internals/debugger.h"

#define Number_GID 0x30

Defaults(Number);

Action(Number, Clone)
{
	Object toReturn = Number_Create();
	LONG(toReturn) = LONG(receiver);
	return toReturn;
}

Action(Number, Compare, Object compareTo)
{
	if(LONG(receiver) > LONG(compareTo))
		return greater;
	if(LONG(receiver) < LONG(compareTo))
		return less;
	return equal;
}

Action(Number, Destroy)
{
	Allocator_Delete(allocator, ENTITY(receiver, void*));
	return Object_Destroy(receiver);
}


Action(Number, Add, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) + LONG(arg);
	return toReturn;
}

Action(Number, Sub, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) - LONG(arg);
	return toReturn;
}

Action(Number, Mul, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) * LONG(arg);
	return toReturn;
}

Action(Number, Div, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) / LONG(arg);
	return toReturn;
}

Action(Number, Mod, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	LONG(toReturn) = LONG(receiver) % LONG(arg);
	return toReturn;
}

Action(Number, AddInPlace, Object arg)
{
	LONG(receiver) += LONG(arg);
	return receiver;
}

Action(Number, SubInPlace, Object arg)
{
	LONG(receiver) -= LONG(arg);
	return receiver;
}

Action(Number, MulInPlace, Object arg)
{
	LONG(receiver) *= LONG(arg);
	return receiver;
}

Action(Number, DivInPlace, Object arg)
{
	LONG(receiver) /= LONG(arg);
	return receiver;
}

Action(Number, ModInPlace, Object arg)
{
	LONG(receiver) %= LONG(arg);
	return receiver;
}

Action(Number, Inc)
{
	LONG(receiver)++;
	return receiver;
}

Action(Number, Dec)
{
	LONG(receiver)--;
	return receiver;
}

Action(Number, IsOdd)
{
	return (LONG(receiver) & 1) ? true : false;
}

Action(Number, IsEven)
{
	return (LONG(receiver) & 1) == 0 ? true : false;
}

Action(Number, Dump)
{
	DEBUG("%li\n", LONG(receiver));
	return receiver;
}

Action(Number, Set, Object arg)
{
	LONG(receiver) = LONG(arg);
	return receiver;
}