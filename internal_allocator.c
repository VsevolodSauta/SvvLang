#include "stdlib.h"
#include "internal_actions.h"
#include "internal_allocator.h"
#include "internal_object.h"

SvvInternalAction(SvvInternalAllocator, New, SvvInternalObject, int Size)
{
	return (SvvInternalObject) malloc(Size);
};

SvvInternalAction(SvvInternalAllocator, Resize, SvvInternalObject, SvvInternalObject Object, int Size)
{
	return (SvvInternalObject) realloc(Object.ptr_data, Size);
};


SvvInternalAction(SvvInternalAllocator, Delete, void, SvvInternalObject Object)
{
	free(Object.ptr_data);
};

SvvInternalAllocator SvvDefaultAllocator;
