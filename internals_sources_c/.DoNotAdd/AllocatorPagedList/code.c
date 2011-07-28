#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

#define NULL ((void*) 0)

static void* Allocator_InternalNew(Allocator allocator, long size)
{
	ASSERT_C("Allocator: size is greater than 512.", size <= 512);
	if(isNot2Power(size)) size = 1 << (mostSignificantOnePosition(size) + 1);
	if(size < sizeof(void*)) size = sizeof(void*);
	long positionInPages = mostSignificantOnePosition(size);

	struct AllocatedPage* page = allocator->pages[positionInPages];

	long overhead = (ALLOCATION_INFO_SIZE + size - 1) & ~(size - 1);
	long capacity = (sizeof(struct AllocatedPage) - overhead) / size;

	while(1)
	{
		if(page == NULL)
		{
			page = OSmappingMap(NULL, sizeof(struct AllocatedPage), 7, 34, -1, 0);
			page->nextPage = allocator->pages[positionInPages];
			page->linkToPage = allocator->pages + positionInPages;
			page->firstFree = (void*) (page->data + overhead);
			page->allocated = 0;
			if(allocator->pages[positionInPages] != NULL)
			{
				allocator->pages[positionInPages]->linkToPage = &(page->nextPage);
			}
			allocator->pages[positionInPages] = page;

			for(long i = 1; i < capacity; i++)
			{
				*((void**) (page->data + overhead + size * (i - 1))) = page->data + overhead + size * i;
			}
			*((void**) (page->data + overhead + size * (capacity - 1))) = NULL;
		}

		if(page->allocated < capacity)
		{
			void* toReturn = page->firstFree;
			page->firstFree = *((void**) toReturn);
			page->allocated++;
			return toReturn;
		}
		page = page->nextPage;
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
	if(toDelete != NULL)
	{
		struct AllocatedPage* page = (struct AllocatedPage*) (((long) toDelete) & ~(sizeof(struct AllocatedPage) - 1));
		page->allocated--;
		if(page->allocated == 0)
		{
			if(page->nextPage != NULL)
			{
				page->nextPage->linkToPage = page->linkToPage;
			}
			*(page->linkToPage) = page->nextPage;
			OSmappingUnmap(page, sizeof(struct AllocatedPage));
		} else {
			*((void**) toDelete) = page->firstFree;
			page->firstFree = toDelete;
		}
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
