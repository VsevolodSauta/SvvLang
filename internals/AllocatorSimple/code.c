#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

#define DOUBLE_FREE_CHECK 0
#define SpaceInAllocator (2*10485760ull)
#define ITEM_SIZE 96

static char arr[SpaceInAllocator];
static unsigned long long int position = 0;
static char* pool;

Object Allocator_Create()
{
	pool = OSmappingMap((void*) 0x100000, ITEM_SIZE * SpaceInAllocator, 7, 34, -1, 0);
#if !DOUBLE_FREE_CHECK
	int i;
	for(i = 0; i < SpaceInAllocator; i++)
	{
		arr[i] = 1;
	}
#endif
	return Undestroyable_Create();
}

void* Allocator_New(Object _self, int size)
{
#if !DOUBLE_FREE_CHECK
	while(arr[position] == 0) position = (position + 1) % SpaceInAllocator;
#else
	position++;
#endif
	arr[position] = 0;
	return pool + position * ITEM_SIZE;
}

#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object _self, void* toResize, int size)
{
	return NULL;
}
#endif

Object Allocator_Delete(Object _self, void* toDelete)
{
	if(toDelete == 0) return _self;
	int intPtr = (((long) toDelete) - ((long) pool)) / ITEM_SIZE;
	ASSERT_C("Allocator: Double free.", arr[intPtr] == 0);
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
