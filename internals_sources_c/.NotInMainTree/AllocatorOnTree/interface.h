#pragma once
#include "internals/Object/interface.h"

Object Allocator_Create();
void*  Allocator_New(Object receiver, int size);
#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object receiver, void* toResize, int size);
#endif
Object Allocator_Delete(Object receiver, void* toDelete);
void*  Allocator_GetUndeletable(Object receiver);

#if MEMORY_DEBUG
int Allocator_GetFreed();
int Allocator_GetResized();
int Allocator_GetAllocated();
#endif
