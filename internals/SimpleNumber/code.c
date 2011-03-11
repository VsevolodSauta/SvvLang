#include "internals/basics.h"

Object SimpleNumber_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct SimpleNumber));
	toReturn->gid = 13183216621426163712ull;
	Object_SetComparator(toReturn, &SimpleNumber_Compare);
	Object_SetDestructor(toReturn, &SimpleNumber_Destroy);
	Object_SetCloner(toReturn, &SimpleNumber_Clone);
	return toReturn;
}

Object SimpleNumber_Clone(Object _self)
{
	Object toReturn = SimpleNumber_Create();
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long;
	return toReturn;
}

Object SimpleNumber_Compare(Object _self, Object number)
{
	if(((SimpleNumber) (_self->entity))->_long > ((SimpleNumber) (number->entity))->_long)
		return _greater;
	if(((SimpleNumber) (_self->entity))->_long < ((SimpleNumber) (number->entity))->_long)
		return _less;
	return _equal;
}

Object SimpleNumber_Destroy(Object _self)
{
	return Object_Destroy(_self);
}


Object SimpleNumber_Add(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long + ((SimpleNumber) (arg->entity))->_long;
	return toReturn;
}

Object SimpleNumber_Sub(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long - ((SimpleNumber) (arg->entity))->_long;
	return toReturn;
}

Object SimpleNumber_Mul(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long * ((SimpleNumber) (arg->entity))->_long;
	return toReturn;
}

Object SimpleNumber_Power(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	long count = ((SimpleNumber) (arg->entity))->_long;
	long result = 1;
	while(count--)
	{
		result *= ((SimpleNumber) (_self->entity))->_long;
	}
	SimpleNumber_SetLong(toReturn, result);
	return toReturn;
}

Object SimpleNumber_Div(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long / ((SimpleNumber) (arg->entity))->_long;
	return toReturn;
}

Object SimpleNumber_Mod(Object _self, Object arg)
{
	Object toReturn = SimpleNumber_Create();
	Object_Autorelease(toReturn);
	((SimpleNumber) (toReturn->entity))->_long = ((SimpleNumber) (_self->entity))->_long % ((SimpleNumber) (arg->entity))->_long;
	return toReturn;
}

Object SimpleNumber_AddInPlace(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long += ((SimpleNumber) (arg->entity))->_long;
	return _self;
}

Object SimpleNumber_SubInPlace(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long -= ((SimpleNumber) (arg->entity))->_long;
	return _self;
}

Object SimpleNumber_MulInPlace(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long *= ((SimpleNumber) (arg->entity))->_long;
	return _self;
}

Object SimpleNumber_DivInPlace(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long /= ((SimpleNumber) (arg->entity))->_long;
	return _self;
}

Object SimpleNumber_ModInPlace(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long %= ((SimpleNumber) (arg->entity))->_long;
	return _self;
}

Object SimpleNumber_Inc(Object _self)
{
	((SimpleNumber) (_self->entity))->_long++;
	return _self;
}

Object SimpleNumber_Dec(Object _self)
{
	((SimpleNumber) (_self->entity))->_long--;
	return _self;
}

Object SimpleNumber_Min(Object _self, Object arg)
{
	Object toReturn;
	if(((SimpleNumber) (_self->entity))->_long < ((SimpleNumber) (arg->entity))->_long)
	{
		toReturn = _self;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object SimpleNumber_Max(Object _self, Object arg)
{
	Object toReturn;
	if(((SimpleNumber) (_self->entity))->_long > ((SimpleNumber) (arg->entity))->_long)
	{
		toReturn = _self;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object SimpleNumber_Abs(Object _self)
{
	if(((SimpleNumber) (_self->entity))->_long > 0)
	{
		return Object_TempClone(_self);
	} else {
		return SimpleNumber_Inv(_self);
	}
}

Object SimpleNumber_Inv(Object _self)
{
	Object toReturn = Object_TempClone(_self);
	((SimpleNumber) (toReturn->entity))->_long = -((SimpleNumber) (toReturn->entity))->_long;
	return toReturn;
}

Object SimpleNumber_IsOdd(Object _self)
{
	return (((SimpleNumber) (_self->entity))->_long & 1) ? _true : _false;
}

Object SimpleNumber_IsEven(Object _self)
{
	return !(((SimpleNumber) (_self->entity))->_long & 1) ? _true : _false;
}

Object SimpleNumber_Set(Object _self, Object arg)
{
	((SimpleNumber) (_self->entity))->_long = ((SimpleNumber) (arg->entity))->_long;
	return _self;
}