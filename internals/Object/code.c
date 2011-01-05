#include "internals/basics.h"
#include "internals/AutoreleasePool/interface.h"

Object Object_Create(void)
{
//	DMSG("Object Create\n");
	Object toReturn = Allocator_New(_allocator, sizeof(struct Object));
	toReturn->links = 1;
	toReturn->gid = 2803832687958515712ull;
	Object_SetComparator(toReturn, &Object_EmptyComparator);
	Object_SetDestructor(toReturn, &Object_Destroy);
	Object_SetCloner(toReturn, &Object_Retain);
	toReturn->entity = Allocator_GetUndeletable(_allocator);
	return toReturn;
}

Object Object_Compare(Object receiver, Object object)
{
	if(object->gid > receiver->gid)
	{
		return _uncomparableLess;
	} else {
		if(object->gid < receiver->gid)
		{
			return _uncomparableGreater;
		} else {
			return (receiver->compare)(receiver, object);
		}
	}
}

Object Object_EmptyComparator(Object receiver, Object object)
{
	return _equal;
}

Object Object_Retain(Object receiver)
{
//	DMSG("Object Retain\n");
	receiver->links++;
	return receiver;
}

Object Object_Release(Object receiver)
{
//	DMSG("Object Release\n");
	if(!(--(receiver->links)))
	{
		receiver->destroy(receiver);
	}
	return receiver;
}

Object Object_Autorelease(Object receiver)
{
//	DMSG("Object Autorelease\n");
	AutoreleasePool_Add(_autoreleasePool, receiver);
	return receiver;
}

Object Object_Destroy(Object receiver)
{
//	DMSG("Object Destroy\n");
//	fflush(stdout);
	Allocator_Delete(_allocator, receiver->entity);
	return Allocator_Delete(_allocator, receiver);
}

Object Object_Clone(Object receiver)
{
	return receiver->clone(receiver);
}

Object Object_TempClone(Object receiver)
{
//	DMSG("Object TempClone\n");
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
	return NumberFactory_FromLong(_numberFactory, (long) (receiver->entity));
}

Object Object_Is(Object receiver, Object object)
{
	return (receiver == object) ? _true : _false;
}
