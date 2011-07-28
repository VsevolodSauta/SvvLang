#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

#define NULL ((void*) 0)

/*

Alg.
Allocate > 512 using mmap.
Allocate <= 512 using mmaped regions.

Mmaped regions are 4096 bytes long.
Region layout:
 - 512 bytes: system data
 -- 8 bytes: size of pieces
 -- 8 bytes: next in list
 -- 496 bytes: bitmap of allocated/free pieces
 - 3584 bytes: user's data

Minimum allocation size == 8.
Allocation block size is power of 2.

*/

static void* Allocator_InternalNew(Allocator allocator, long size)
{
	ASSERT_C("Allocator: size is greater than 512.", size <= 512);
	if(isNot2Power(size)) size = 1 << (mostSignificantOnePosition(size) + 1);
	if(size < 8) size = 8;
	long positionInPages = mostSignificantOnePosition(size);

	struct AllocatedPage** linkToPage = allocator->pages + positionInPages;
	struct AllocatedPage* page = *linkToPage;

	while(1)
	{
		if(page == NULL)
		{
			*linkToPage = page = OSmappingMap(NULL, sizeof(struct AllocatedPage), 7, 34, -1, 0);
			page->linkToPage = linkToPage;
			page->sizeOfElement = size;
			page->next = NULL;
			page->allocated = 0;
			for(long i = 0; i < ALLOCATION_INFO_SIZE; i++)
			{
				page->allocationInfo[i] = 0;
			}
		}
		
		long capacity = sizeof(page->data) / page->sizeOfElement;
		if(page->allocated < capacity)
		{
			for(long i = 0; i < ALLOCATION_INFO_SIZE; i++)
			{
				long zeroPosition = leastSignificantZeroPosition(page->allocationInfo[i]);
				if(zeroPosition == -1) continue;
				long positionInData = size * (zeroPosition + i * sizeof(long) * 8);
				ASSERT_C("Allocator: UNREACHABLE reached.", positionInData < sizeof(page->data));
				page->allocated++;
				page->allocationInfo[i] |= 1l << zeroPosition;
				return page->data + positionInData;
			}
		}
		linkToPage = &(page->next);
		page = *linkToPage;
	}
}

Object Allocator_Create()
{
	struct AllocatorPaged allocatorOnStack;
	for(int i = 0; i < 10; i++)
	{
		allocatorOnStack.pages[i] = NULL;
	}
	
	Allocator allocatorOnHeap = Allocator_InternalNew(&allocatorOnStack, sizeof(allocatorOnStack));
	copyMemory((char*) allocatorOnHeap, (char*) &allocatorOnStack, sizeof(allocatorOnStack));
	Object allocatorObject = Allocator_InternalNew(allocatorOnHeap, sizeof(struct Object));
	allocatorObject->links = 1;
	allocatorObject->gid = 13474595845139800064ull;
        Object_SetComparator(allocatorObject, &Object_EmptyComparator);
        Object_SetDestructor(allocatorObject, &Object_Destroy);
        Object_SetCloner(allocatorObject, &Object_Retain);
        Object_SetDeepCloner(allocatorObject, &Object_Retain);
        allocatorObject->entity = allocatorOnHeap;
        return allocatorObject;

}

void* Allocator_New(Object _self, long size)
{
	return Allocator_InternalNew(_self->entity, size);
}

#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object _self, void* toResize, long size)
{
	return NULL;
}
#endif

Object Allocator_Delete(Object _self, void* toDelete)
{
	struct AllocatedPage* page = (struct AllocatedPage*) (((long) toDelete) & ~((1 << 12) - 1));
	long positionInData = (((long) toDelete) - ((long) (page->data))) / page->sizeOfElement;
	page->allocationInfo[positionInData / (sizeof(long) * 8)] &= ~(1l << (positionInData % ((sizeof(long) * 8))));
	page->allocated--;
	if(page->allocated == 0)
	{
		if(page->next != NULL)
		{
			page->next->linkToPage = page->linkToPage;
		}
		*(page->linkToPage) = page->next;
		OSmappingUnmap(page, sizeof(struct AllocatedPage));
	}
	return _self;
}

void*  Allocator_GetUndeletable(Object _self)
{
	return 0;
}

#if MEMORY_DEBUG
long Allocator_GetFreed(Object _self)
{
	return 0;
}

long Allocator_GetResized(Object _self)
{
	return 0;
}

long Allocator_GetAllocated(Object _self)
{
	return 0;
}
#endif

Object _nil;
Object _nothing;
Object _null;
Object _allocator;
