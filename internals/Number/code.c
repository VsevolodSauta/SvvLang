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

Object Number_Clone(Object receiver)
{
	Object toReturn = Number_Create();
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity;
	return toReturn;
}

Object Number_Compare(Object receiver, Object number)
{
	if(((Number) (receiver->entity))->entity > ((Number) (number->entity))->entity)
		return _greater;
	if(((Number) (receiver->entity))->entity < ((Number) (number->entity))->entity)
		return _less;
	return _equal;
}

Object Number_Destroy(Object receiver)
{
	return Object_Destroy(receiver);
}


Object Number_Add(Object receiver, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity + ((Number) (arg->entity))->entity;
	return toReturn;
}

Object Number_Sub(Object receiver, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity - ((Number) (arg->entity))->entity;
	return toReturn;
}

Object Number_Mul(Object receiver, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity * ((Number) (arg->entity))->entity;
	return toReturn;
}

Object Number_Div(Object receiver, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity / ((Number) (arg->entity))->entity;
	return toReturn;
}

Object Number_Mod(Object receiver, Object arg)
{
	Object toReturn = Number_Create();
	Object_Autorelease(toReturn);
	((Number) (toReturn->entity))->entity = ((Number) (receiver->entity))->entity % ((Number) (arg->entity))->entity;
	return toReturn;
}

Object Number_AddInPlace(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity += ((Number) (arg->entity))->entity;
	return receiver;
}

Object Number_SubInPlace(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity -= ((Number) (arg->entity))->entity;
	return receiver;
}

Object Number_MulInPlace(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity *= ((Number) (arg->entity))->entity;
	return receiver;
}

Object Number_DivInPlace(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity /= ((Number) (arg->entity))->entity;
	return receiver;
}

Object Number_ModInPlace(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity %= ((Number) (arg->entity))->entity;
	return receiver;
}

Object Number_Inc(Object receiver)
{
	((Number) (receiver->entity))->entity++;
	return receiver;
}

Object Number_Dec(Object receiver)
{
	((Number) (receiver->entity))->entity--;
	return receiver;
}

Object Number_Min(Object receiver, Object arg)
{
	Object toReturn;
	if(((Number) (receiver->entity))->entity < ((Number) (arg->entity))->entity)
	{
		toReturn = receiver;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object Number_Max(Object receiver, Object arg)
{
	Object toReturn;
	if(((Number) (receiver->entity))->entity > ((Number) (arg->entity))->entity)
	{
		toReturn = receiver;
	} else {
		toReturn = arg;
	}
	return Object_TempClone(toReturn);
}

Object Number_Abs(Object receiver)
{
	if(((Number) (receiver->entity))->entity > 0)
	{
		return Object_TempClone(receiver);
	} else {
		return Number_Inv(receiver);
	}
}

Object Number_Inv(Object receiver)
{
	Object toReturn = Object_TempClone(receiver);
	((Number) (toReturn->entity))->entity = -((Number) (toReturn->entity))->entity;
	return toReturn;
}

Object Number_IsOdd(Object receiver)
{
	return (((Number) (receiver->entity))->entity & 1) ? _true : _false;
}

Object Number_IsEven(Object receiver)
{
	return !(((Number) (receiver->entity))->entity & 1) ? _true : _false;
}

Object Number_Set(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity = ((Number) (arg->entity))->entity;
	return receiver;
}

