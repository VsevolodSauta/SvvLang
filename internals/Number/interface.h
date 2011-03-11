#pragma once

#include "internals/Object/interface.h"

typedef struct Number {
	long		_long;
	long		_div;
} *Number;

Object Number_Create();
Object Number_Compare(Object _self, Object number);
Object Number_Clone(Object _self);
Object Number_Destroy(Object _self);

Object Number_Inc(Object _self);
Object Number_Dec(Object _self);
Object Number_Add(Object _self, Object arg);
Object Number_Sub(Object _self, Object arg);
Object Number_Mul(Object _self, Object arg);
Object Number_Div(Object _self, Object arg);
Object Number_Mod(Object _self, Object arg);
Object Number_AddInPlace(Object _self, Object arg);
Object Number_SubInPlace(Object _self, Object arg);
Object Number_MulInPlace(Object _self, Object arg);
Object Number_DivInPlace(Object _self, Object arg);
Object Number_ModInPlace(Object _self, Object arg);
Object Number_Min(Object _self, Object arg);
Object Number_Max(Object _self, Object arg);
Object Number_Abs(Object _self);
Object Number_Inv(Object _self);
Object Number_Power(Object _self, Object arg);

Object Number_IsOdd(Object _self);
Object Number_IsEven(Object _self);
Object Number_Set(Object _self, Object arg);

static inline long Number_GetLong(Object _self)
{
	return ((Number) (_self->entity))->_long / ((Number) (_self->entity))->_div;
}

inline static Object Number_SetLong(Object _self, long toSet)
{
	((Number) (_self->entity))->_long = toSet;
	((Number) (_self->entity))->_div = 1;
	return _self;
}

