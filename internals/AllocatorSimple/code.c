#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

#define DOUBLE_FREE_CHECK 0
#define POOL_SIZE (20*1048576ull)
#define ITEM_SIZE 64

static char arr[POOL_SIZE];
static unsigned long long int position = 0;
static char* pool;

Object Allocator_Create()
{
	pool = OSmappingMap((void*) 0x100000, ITEM_SIZE * POOL_SIZE, 7, 34, -1, 0);
	int i;
	for(i = 0; i < POOL_SIZE; i++)
	{
		arr[i] = 1;
	}
	return Undestroyable_Create();
}

void* Allocator_New(Object _self, int size)
{
	ASSERT_C("Allocator: size is greater than ITEM_SIZE.", size <= ITEM_SIZE);
	register long long toAllocate;
	do {
		toAllocate = 1;
		asm volatile (
			"lock\n"
			"xadd %1, %0\n"
			: "=m" (position),
			  "=r" (toAllocate)
		);
		toAllocate %= POOL_SIZE;
	} while(!arr[toAllocate]);
	arr[toAllocate] = 0;
	return pool + toAllocate * ITEM_SIZE;
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
