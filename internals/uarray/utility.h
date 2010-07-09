#pragma once
#include "internals/basics.h"
#include "internals/uarray/interface.h"

#define BYTE_PTR(object, position) (((char*) (Receiver->data)) + position)

inline int min(int a, int b)
{
	return (a < b ? a : b);
};

inline SvvInternalAction(SvvInternalUArray, GetAllocationSize, void)
{
	Receiver->allocated = (Receiver->size & (~(ARRAY_GRANULARITY - 1))) + ARRAY_GRANULARITY;
};

inline SvvInternalAction(SvvInternalUArray, Shrink, void)
{
	SvvInternalUArray_GetAllocationSize(Receiver);
	Receiver->data = OBJECT_AS_LINK(SvvInternalAllocator_Resize(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver->data), Receiver->allocated));
};

