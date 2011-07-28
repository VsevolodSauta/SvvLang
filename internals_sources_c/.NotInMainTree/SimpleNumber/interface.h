#pragma once

#include "internals/Object/interface.h"

typedef struct SimpleNumber {
	long		_long;
} *SimpleNumber;

Object SimpleNumber_Create();
Object SimpleNumber_Compare(Object _self, Object number);
Object SimpleNumber_Clone(Object _self);
Object SimpleNumber_Destroy(Object _self);

Object SimpleNumber_Inc(Object _self);
Object SimpleNumber_Dec(Object _self);
Object SimpleNumber_Add(Object _self, Object arg);
Object SimpleNumber_Sub(Object _self, Object arg);
Object SimpleNumber_Mul(Object _self, Object arg);
Object SimpleNumber_Div(Object _self, Object arg);
Object SimpleNumber_Mod(Object _self, Object arg);
Object SimpleNumber_AddInPlace(Object _self, Object arg);
Object SimpleNumber_SubInPlace(Object _self, Object arg);
Object SimpleNumber_MulInPlace(Object _self, Object arg);
Object SimpleNumber_DivInPlace(Object _self, Object arg);
Object SimpleNumber_ModInPlace(Object _self, Object arg);
Object SimpleNumber_Min(Object _self, Object arg);
Object SimpleNumber_Max(Object _self, Object arg);
Object SimpleNumber_Abs(Object _self);
Object SimpleNumber_Inv(Object _self);
Object SimpleNumber_Power(Object _self, Object arg);

Object SimpleNumber_IsOdd(Object _self);
Object SimpleNumber_IsEven(Object _self);
Object SimpleNumber_Set(Object _self, Object arg);

static inline long SimpleNumber_GetLong(Object _self)
{
	return ((SimpleNumber) (_self->entity))->_long;
}

inline static Object SimpleNumber_SetLong(Object _self, long toSet)
{
	((SimpleNumber) (_self->entity))->_long = toSet;
	return _self;
}

