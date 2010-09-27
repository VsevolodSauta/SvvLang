#include <stdlib.h>
#include "internals/basics.h"

#define Allocator_GID 0x10

void* Allocator_New(Object receiver, int size)
{
	return malloc(size);
}

void* Allocator_Resize(Object receiver, void* toResize, int size)
{
	return realloc(toResize, size);
}

Object Allocator_Delete(Object receiver, void* toDelete)
{
	free(toDelete);
	return nothing;
}

void* Allocator_GetUndeletable(Object receiver)
{
	return NULL;
}

Object allocator;
Object nothing;
Object nil;
