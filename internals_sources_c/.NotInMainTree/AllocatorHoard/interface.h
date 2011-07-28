#pragma once
#include "internals/Object/interface.h"

#define ALLOCATION_INFO_SIZE ((512 - 2*sizeof(long) - 2*sizeof(void*)) / sizeof(unsigned long))

struct AllocatedPage {
	long sizeOfElement;
	long allocated;
	struct AllocatedPage* next;
	struct AllocatedPage** linkToPage;
	unsigned long allocationInfo[ALLOCATION_INFO_SIZE];
	char data[4096 - 512];
};

typedef struct AllocatorPaged {
	// SpinLock lock;
	struct AllocatedPage* pages[10];
} *Allocator;

Object Allocator_Create();
void*  Allocator_New(Object receiver, long size);
#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object receiver, void* toResize, long size);
#endif
Object Allocator_Delete(Object receiver, void* toDelete);
void*  Allocator_GetUndeletable(Object receiver);

#if MEMORY_DEBUG
long Allocator_GetFreed();
long Allocator_GetResized();
long Allocator_GetAllocated();
#endif
