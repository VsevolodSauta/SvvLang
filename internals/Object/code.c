#include "internals/basics.h"

#define Object_GID 0x20

Object Object_Create(void)
{
	Object toReturn = Allocator_New(allocator, sizeof(struct Object));
	toReturn->links = 1;
	Object_SetComparator(toReturn, &Object_EmptyComparator);
	Object_SetDestructor(toReturn, &Object_Destroy);
	Object_SetCloner(toReturn, &Object_Clone);
	toReturn->entity = Allocator_GetUndeletable(allocator);
	return toReturn;
}

Object Object_Compare(Object receiver, Object object)
{
	if(object->gid > receiver->gid)
	{
		return uncomparableLess;
	} else {
		if(object->gid < receiver->gid)
		{
			return uncomparableGreater;
		} else {
			return (receiver->compare)(receiver, object);
		}
	}
}

Object Object_EmptyComparator(Object receiver, Object object)
{
	return equal;
}

Object Object_Retain(Object receiver)
{
	receiver->links++;
	return receiver;
}

Object Object_Release(Object receiver)
{
	if(!(receiver->links--))
	{
		receiver->destroy(receiver);
	}
	return receiver;
}

Object Object_Autorelease(Object receiver)
{
	return receiver;
}

Object Object_Destroy(Object receiver)
{
	Allocator_Delete(allocator, receiver->entity);
	return Allocator_Delete(allocator, receiver);
}

Object Object_Clone(Object receiver)
{
	return Object_Create();
}

Object Object_TempClone(Object receiver)
{
	Object toReturn = receiver->clone(receiver);
	Object_Autorelease(toReturn);
	return toReturn;
}

Object Object_SetComparator(Object receiver, ObjectComparator comparator)
{
	receiver->compare = comparator;
	return receiver;
}

Object Object_SetCloner(Object receiver, ObjectCloner cloner)
{
	receiver->clone = cloner;
	return receiver;
}

Object Object_SetDestructor(Object receiver, ObjectDestructor destructor)
{
	receiver->destroy = destructor;
	return receiver;
}

Object Object_Hash(Object receiver)
{
	return NumberFactory_FromLong(numberFactory, (long) (receiver->entity));
}
