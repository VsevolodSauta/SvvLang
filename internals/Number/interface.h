#pragma once

#include "internals/Object/interface.h"

typedef struct Number {
	long		entity;
} *Number;

Object Number_Create();
Object Number_Compare(Object receiver, Object number);
Object Number_Clone(Object receiver);
Object Number_Destroy(Object receiver);

Object Number_Inc(Object receiver);
Object Number_Dec(Object receiver);
Object Number_Add(Object receiver, Object arg);
Object Number_Sub(Object receiver, Object arg);
Object Number_Mul(Object receiver, Object arg);
Object Number_Div(Object receiver, Object arg);
Object Number_Mod(Object receiver, Object arg);
Object Number_AddInPlace(Object receiver, Object arg);
Object Number_SubInPlace(Object receiver, Object arg);
Object Number_MulInPlace(Object receiver, Object arg);
Object Number_DivInPlace(Object receiver, Object arg);
Object Number_ModInPlace(Object receiver, Object arg);
Object Number_IsOdd(Object receiver);
Object Number_IsEven(Object receiver);
Object Number_Dump(Object receiver);
Object Number_Set(Object receiver, Object arg);

static inline long Number_GetLong(Object receiver)
{
	return ((Number) (receiver->entity))->entity;
};

inline static Object Number_SetLong(Object receiver, long toSet)
{
	((Number) (receiver->entity))->entity = toSet;
	return receiver;
};

