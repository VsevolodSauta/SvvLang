#include "internals/basics.h"

void* AllocatorForStack_Create();
void* AllocatorForStack_New(Object _self);
Object AllocatorForStack_Delete(Object _self, void* toDelete);
