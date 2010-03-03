#include "stdlib.h"
#include "internal_actions.h"
#include "internal_allocator.h"
#include "internal_object.h"

SvvInternalAction(SvvInternalAllocator, New, SvvInternalObject, int Size)
{
	void* ptr = malloc(Size);
	return LINK_AS_OBJECT(ptr);
};

SvvInternalAction(SvvInternalAllocator, Resize, SvvInternalObject, SvvInternalObject Object, int Size)
{
	void* ptr = realloc(Object.ptr_data, Size);
	return LINK_AS_OBJECT(ptr);
	
};


SvvInternalAction(SvvInternalAllocator, Delete, void, SvvInternalObject Object)
{
	void* ptr = OBJECT_AS_LINK(Object);
	free(ptr);
};

SvvInternalAllocator SvvDefaultAllocator;
