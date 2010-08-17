#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

#define SvvInternalNumber_GID 0x100

SvvInternalRoutine(int, IsInRange, int, int LeftBound, int RightBound)
{
	return ((Receiver >= LeftBound) && (Receiver <= RightBound));
};

typedef struct SvvInternalNumber {
	long		entity;
} *SvvInternalNumber;

SvvInternalCreator(SvvInternalNumber);
SvvInternalAction(SvvInternalNumber, Init);
SvvInternalAction(SvvInternalNumber, Add, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, Sub, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, Mul, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, Div, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, AddInPlace, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, SubInPlace, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, MulInPlace, SvvInternalObject Arg);
SvvInternalAction(SvvInternalNumber, DivInPlace, SvvInternalObject Arg);

static inline long SvvInternalNumber_GetLong(SvvInternalObject Receiver)
{
	return GET_ENTITY(Receiver, SvvInternalNumber)->entity;
};

static inline void SvvInternalNumber_SetLong(SvvInternalObject Receiver, long ToSet)
{
	GET_ENTITY(Receiver, SvvInternalNumber)->entity = ToSet;
};
