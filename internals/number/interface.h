#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

Routine(int, IsInRange, int, int leftBound, int rightBound)
{
	return ((receiver >= leftBound) && (receiver <= rightBound));
};

typedef struct Number {
	long		entity;
} *Number;

#define LONG(receiver) (ENTITY(receiver, Number)->entity)

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
	return LONG(receiver);
};

static inline void Number_SetLong(Object receiver, long toSet)
{
	LONG(receiver) = toSet;
};

