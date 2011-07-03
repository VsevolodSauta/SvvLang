#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"

#define DEFAULT_STACK_SIZE (4096 * 16)

void* AllocatorForStack_Create()
{
	return Undestroyable_Create();
}

void* AllocatorForStack_New(Object _self)
{
	char* ptr = OSmappingMap((void*) 0, DEFAULT_STACK_SIZE, 7, 34, -1, 0);
	return ptr + DEFAULT_STACK_SIZE - 8;
}

Object AllocatorForStack_Delete(Object _self, void* toDelete)
{
	char* ptr = toDelete;
	OSmappingUnmap(ptr - DEFAULT_STACK_SIZE + 8, DEFAULT_STACK_SIZE);
	return _self;
}

Object _allocatorForStack;
