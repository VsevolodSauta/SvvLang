#pragma once
#include "internals/Object/interface.h"

#define ALLOCATION_UNIT_SIZE 4096
#define ALLOCATION_INFO_SIZE sizeof(struct AllocationInfo)

struct AllocatedPage {
	union {
		struct AllocationInfo {
			struct AllocatedPage* nextPage;
			struct AllocatedPage** linkToPage;
			void** firstFree;
			long allocated;
		};
		char data[ALLOCATION_UNIT_SIZE];
	};
};

typedef struct AllocatorPaged {
	// SpinLock lock;
	struct AllocatedPage* pages[10];
} *Allocator;

Object Allocator_Create();
Object Allocator_Clone(Object _self);
Object Allocator_DeepClone(Object _self);
Object Allocator_Destroy(Object _self);
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

void Allocator_InitializeClass();

extern Object _allocator;
extern Object _nothing;
extern Object _nil;
extern Object _null;
