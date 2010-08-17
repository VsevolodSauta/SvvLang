#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

#define Number_GID 0x100

Routine(int, IsInRange, int, int leftBound, int rightBound)
{
	return ((receiver >= leftBound) && (receiver <= rightBound));
};

typedef struct Number {
	long		entity;
} *Number;

Creator(Number);
Action(Number, Init);
Action(Number, Add, Object arg);
Action(Number, Sub, Object arg);
Action(Number, Mul, Object arg);
Action(Number, Div, Object arg);
Action(Number, AddInPlace, Object arg);
Action(Number, SubInPlace, Object arg);
Action(Number, MulInPlace, Object arg);
Action(Number, DivInPlace, Object arg);

static inline long Number_GetLong(Object receiver)
{
	return GET_ENTITY(receiver, Number)->entity;
};

static inline void Number_SetLong(Object receiver, long toSet)
{
	GET_ENTITY(receiver, Number)->entity = toSet;
};

