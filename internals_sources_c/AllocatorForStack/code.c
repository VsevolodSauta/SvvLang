#include "internals/basics.h"
#include "internals/Undestroyable/interface.h"
#include "internals/SuperClass/interface.h"

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

void AllocatorForStack_InitializeClass()
{
	Object _className = StringFactory_FromUTF8(_stringFactory, "AllocatorForStack", 17);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &AllocatorForStack_New), StringFactory_FromUTF8(_stringFactory, "New", 3), _className);
	SuperClass_RegisterMethodWithNameForClass(_superClass, MethodFactory_FromPointer(_methodFactory, &AllocatorForStack_Delete), StringFactory_FromUTF8(_stringFactory, "Delete", 6), _className);
}

Object _allocatorForStack;
