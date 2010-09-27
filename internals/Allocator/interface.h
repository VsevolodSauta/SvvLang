#pragma once
#include "internals/Object/interface.h"

void*  Allocator_New(Object receiver, int size);
void*  Allocator_Resize(Object receiver, void* toResize, int size);
Object Allocator_Delete(Object receiver, void* toDelete);
void*  Allocator_GetUndeletable(Object receiver);