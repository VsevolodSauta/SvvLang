#include "internals/basics.h"

static char arr[1048576];
static int position = 0;
static char* pool;

Object Allocator_Create()
{
	pool = OSmappingMap((void*) 0x100000, 512 * 1048576, 7, 34, -1, 0);
	return Undestroyable_Create();
}

void* Allocator_New(Object _self, int size)
{
	position++;
	arr[position] = 0;
	return pool + position * 512;
}

#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object _self, void* toResize, int size)
{
	return NULL;
}
#endif

Object Allocator_Delete(Object _self, void* toDelete)
{
	int intPtr = (((long) toDelete) - ((long) pool)) / 512;
	if(arr[intPtr] == 1)
	{
		DMSG("Allocator: Double free.");
	}
	arr[intPtr] = 1;
	return _self;
}

void*  Allocator_GetUndeletable(Object _self)
{
	return 0;
}

#if MEMORY_DEBUG
int Allocator_GetFreed(Object _self)
{
	return 0;
}

int Allocator_GetResized(Object _self)
{
	return 0;
}

int Allocator_GetAllocated(Object _self)
{
	return 0;
}
#endif

Object _nil;
Object _nothing;
Object _null;
Object _allocator;
