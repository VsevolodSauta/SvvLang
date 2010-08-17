#pragma once
#include "internals/object/interface.h"

void* Allocator_New(Object receiver, int size);
void* Allocator_Resize(Object receiver, void* toResize, int size);
void  Allocator_Delete(Object receiver, void* toDelete);
