#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

#if 0
Routine(int, IsInRange, int, int leftBound, int rightBound)
{
	return ((receiver >= leftBound) && (receiver <= rightBound));
};
#endif

typedef struct Number {
	long		entity;
} *Number;

#define LONG(receiver) (ENTITY(receiver, Number)->entity)

Creator(Number);
Action(Number, Inc);
Action(Number, Dec);
Action(Number, Add, Object arg);
Action(Number, Sub, Object arg);
Action(Number, Mul, Object arg);
Action(Number, Div, Object arg);
Action(Number, Mod, Object arg);
Action(Number, AddInPlace, Object arg);
Action(Number, SubInPlace, Object arg);
Action(Number, MulInPlace, Object arg);
Action(Number, DivInPlace, Object arg);
Action(Number, ModInPlace, Object arg);
Action(Number, IsOdd);
Action(Number, IsEven);
Action(Number, Dump);
Action(Number, Set, Object arg);

static inline long Number_GetLong(Object receiver)
{
	return LONG(receiver);
};

inline static Action(Number, SetLong, long toSet)
{
	LONG(receiver) = toSet;
	return receiver;
};

