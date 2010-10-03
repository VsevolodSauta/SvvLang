#include <stdlib.h>
#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

Object Allocator_Create()
{
	return Undestroyable_Create();
}

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
	return _nothing;
}

void* Allocator_GetUndeletable(Object receiver)
{
	return NULL;
}

Object _allocator;
Object _nothing;
Object _nil;
Object _null;
