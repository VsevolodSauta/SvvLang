#include "internals/basics.h"

#define Number_GID 0x30

Object Number_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct Number));
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
		return greater;
	if(((Number) (receiver->entity))->entity < ((Number) (number->entity))->entity)
		return less;
	return equal;
}

Object Number_Destroy(Object receiver)
{
	Allocator_Delete(allocator, receiver->entity);
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

Object Number_IsOdd(Object receiver)
{
	return (((Number) (receiver->entity))->entity & 1) ? true : false;
}

Object Number_IsEven(Object receiver)
{
	return (((Number) (receiver->entity))->entity & 1) == 0 ? true : false;
}

Object Number_Dump(Object receiver)
{
	DEBUG("%li\n", ((Number) (receiver->entity))->entity);
	return receiver;
}

Object Number_Set(Object receiver, Object arg)
{
	((Number) (receiver->entity))->entity = ((Number) (arg->entity))->entity;
	return receiver;
}

