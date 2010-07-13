#include <stdlib.h>
#include "internals/actions.h"
#include "internals/object/interface.h"
#include "internals/allocator/interface.h"

SvvInternalAction(SvvInternalAllocator, New, SvvInternalObject, int Size)
{
	void* ptr = malloc(Size);
	return LINK_AS_OBJECT(ptr);
};

SvvInternalAction(SvvInternalAllocator, Resize, SvvInternalObject, SvvInternalObject Object, int Size)
{
	void* ptr = realloc(OBJECT_AS_LINK(Object), Size);
	return LINK_AS_OBJECT(ptr);
};


SvvInternalAction(SvvInternalAllocator, Delete, void, SvvInternalObject Object)
{
	void* ptr = OBJECT_AS_LINK(Object);
	free(ptr);
};

SvvInternalAllocator SvvDefaultAllocator;
