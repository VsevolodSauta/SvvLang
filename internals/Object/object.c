#include "internals/object/interface.h"
#include "internals/allocator/interface.h"
#include "internals/globals.h"
#include "internals/config.h"

#include "internals/autorelease_pools_stack/interface.h"
#include "internals/autorelease_pool/interface.h"

#define Object_GID 0x20

Action(Object, Compare, Object object)
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
		};
	};
};

Action(Object, EmptyComparator, Object object)
{
	return equal;
};

Creator(Object)
{
	Object toReturn = Allocator_New(allocator, sizeof(struct Object));
	toReturn->links = 1;
	Object_SetComparator(toReturn, &Object_EmptyComparator);
	Object_SetDestructor(toReturn, &Object_Destroy);
	Object_SetCloner(toReturn, &Object_Clone);
	SET_ENTITY(toReturn, Allocator_GetUndeletable(allocator));
	return toReturn;
};

Action(Object, Retain)
{
	receiver->links++;
	return receiver;
};

Action(Object, Release)
{
	if(!(receiver->links--))
	{
		receiver->destroy(receiver);
	};
	return receiver;
};

Action(Object, Autorelease)
{
	return receiver;
};

Action(Object, Destroy)
{
	Allocator_Delete(allocator, receiver->entity);
	return Allocator_Delete(allocator, receiver);
};

Action(Object, Clone)
{
	return receiver->clone(receiver);
};

Action(Object, TempClone)
{
	Object toReturn = receiver->clone(receiver);
	Object_Autorelease(toReturn);
	return toReturn;
};

Action(Object, SetComparator, ObjectComparator comparator)
{
	receiver->compare = comparator;
	return receiver;
};

Action(Object, SetCloner, ObjectCloner cloner)
{
	receiver->clone = cloner;
	return receiver;
};

Action(Object, SetDestructor, ObjectDestructor destructor)
{
	receiver->destroy = destructor;
	return receiver;
};
