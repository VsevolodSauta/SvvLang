#include "internals/object/interface.h"
#include "internals/allocator/interface.h"
#include "internals/comparation/interface.h"
#include "internals/globals.h"

SvvInternalAction(SvvInternalObject, Compare, SvvInternalObject Object)
{
	if(Object->gid > Receiver->gid)
	{
		return UncomparableLess;
	} else {
		if(Object->gid < Receiver->gid)
		{
			return UncomparableGreater;
		} else {
			return (Receiver->compare)(Receiver, Object);
		};
	};
};

static SvvInternalObject SvvInternalObject_EmptyComparator(SvvInternalObject first, SvvInternalObject second)
{
	return Equal;
};

SvvInternalCreator(SvvInternalObject)
{
	SvvInternalObject toReturn = SvvInternalAllocator_New(Allocator, sizeof(struct SvvInternalObject));
	toReturn->links = 1;
	toReturn->compare = &SvvInternalObject_EmptyComparator;
	toReturn->destroy = &SvvInternalObject_Destroy;
	return toReturn;
};

SvvInternalAction(SvvInternalObject, Retain)
{
	Receiver->links++;
	return Receiver;
};

SvvInternalAction(SvvInternalObject, Release)
{
	if(!(Receiver->links--))
	{
		Receiver->destroy(Receiver);
	};
	return Receiver;
};

SvvInternalAction(SvvInternalObject, Autorelease)
{
	return Receiver;
};

void SvvInternalObject_Destroy(SvvInternalObject Receiver)
{
	SvvInternalAllocator_Delete(Allocator, Receiver);
};
