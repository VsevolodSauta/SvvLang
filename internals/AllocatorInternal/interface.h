#pragma once
#include "internals/Object/interface.h"

Object Allocator_Create();
void*  Allocator_New(Object receiver, int size);
void*  Allocator_Resize(Object receiver, void* toResize, int size);
Object Allocator_Delete(Object receiver, void* toDelete);
void*  Allocator_GetUndeletable(Object receiver);

#ifdef MEMORY_DEBUG
int Allocator_GetFreed();
int Allocator_GetResized();
int Allocator_GetAllocated();
#endif
