#include "internals/basics.h"

Object Number_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Number));
	toReturn->gid = 15425740279749906432ull;
	Object_SetComparator(toReturn, &Number_Compare);
	Object_SetDestructor(toReturn, &Number_Destroy);
	Object_SetCloner(toReturn, &Number_Clone);
	return toReturn;
}

Object Number_Clone(Object _self)
{
	Object toReturn = Number_Create();
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long;
	return toReturn;
}

Object Number_Compare(Object _self, Object number)
{
	if(((Number) (_self->entity))->_long > ((Number) (number->entity))->_long)
		return _greater;
	if(((Number) (_self->entity))->_long < ((Number) (number->entity))->_long)
		return _less;
	return _equal;
}

Object Number_Destroy(Object _self)
{
	return Object_Destroy(_self);
}


Object Number_Add(Object _self, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long + ((Number) (arg->entity))->_long;
	return toReturn;
}

Object Number_Sub(Object _self, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long - ((Number) (arg->entity))->_long;
	return toReturn;
}

Object Number_Mul(Object _self, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long * ((Number) (arg->entity))->_long;
	return toReturn;
}

Object Number_Div(Object _self, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long / ((Number) (arg->entity))->_long;
	return toReturn;
}

Object Number_Mod(Object _self, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->_long = ((Number) (_self->entity))->_long % ((Number) (arg->entity))->_long;
	return toReturn;
}

Object Number_AddInPlace(Object _self, Object arg)
{
	((Number) (_self->entity))->_long += ((Number) (arg->entity))->_long;
	return _self;
}

Object Number_SubInPlace(Object _self, Object arg)
{
	((Number) (_self->entity))->_long -= ((Number) (arg->entity))->_long;
	return _self;
}

Object Number_MulInPlace(Object _self, Object arg)
{
	((Number) (_self->entity))->_long *= ((Number) (arg->entity))->_long;
	return _self;
}

Object Number_DivInPlace(Object _self, Object arg)
{
	((Number) (_self->entity))->_long /= ((Number) (arg->entity))->_long;
	return _self;
}

Object Number_ModInPlace(Object _self, Object arg)
{
	((Number) (_self->entity))->_long %= ((Number) (arg->entity))->_long;
	return _self;
}

Object Number_Inc(Object _self)
{
	((Number) (_self->entity))->_long++;
	return _self;
}

Object Number_Dec(Object _self)
{
	((Number) (_self->entity))->_long--;
	return _self;
}

Object Number_Min(Object _self, Object arg)
{
	Object toReturn;
	if(((Number) (_self->entity))->_long < ((Number) (arg->entity))->_long)
	{
		toReturn = _self;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object Number_Max(Object _self, Object arg)
{
	Object toReturn;
	if(((Number) (_self->entity))->_long > ((Number) (arg->entity))->_long)
	{
		toReturn = _self;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object Number_Abs(Object _self)
{
	if(((Number) (_self->entity))->_long > 0)
	{
		return Object_TempClone(_self);
	} else {
		return Number_Inv(_self);
	}
}

Object Number_Inv(Object _self)
{
	Object toReturn = Object_TempClone(_self);
	((Number) (toReturn->entity))->_long = -((Number) (toReturn->entity))->_long;
	return toReturn;
}

Object Number_IsOdd(Object _self)
{
	return (((Number) (_self->entity))->_long & 1) ? _true : _false;
}

Object Number_IsEven(Object _self)
{
	return !(((Number) (_self->entity))->_long & 1) ? _true : _false;
}

Object Number_Set(Object _self, Object arg)
{
	((Number) (_self->entity))->_long = ((Number) (arg->entity))->_long;
	return _self;
}

