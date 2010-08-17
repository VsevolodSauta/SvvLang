#include "internals/object/interface.h"
#include "internals/allocator/interface.h"
#include "internals/comparation/interface.h"
#include "internals/globals.h"

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

static Object Object_EmptyComparator(Object first, Object second)
{
	return equal;
};

Creator(Object)
{
	Object toReturn = Allocator_New(allocator, sizeof(struct Object));
	toReturn->links = 1;
	toReturn->compare = &Object_EmptyComparator;
	toReturn->destroy = &Object_Destroy;
	return toReturn;
};

Action(Object, Retain)
{
	receiver->links++;
	return receiver;
};

Action(Object, release)
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

void Object_Destroy(Object receiver)
{
	Allocator_Delete(allocator, receiver);
};
