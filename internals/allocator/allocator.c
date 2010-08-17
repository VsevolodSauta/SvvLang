#include <stdlib.h>
#include "internals/allocator/interface.h"

void* SvvInternalAllocator_New(SvvInternalObject Receiver, int Size)
{
	return malloc(Size);
};

void* SvvInternalAllocator_Resize(SvvInternalObject Receiver, void* ToResize, int Size)
{
	return realloc(ToResize, Size);
};

void SvvInternalAllocator_Delete(SvvInternalObject Receiver, void* ToDelete)
{
	free(ToDelete);
};
