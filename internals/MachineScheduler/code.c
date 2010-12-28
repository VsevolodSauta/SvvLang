#include "internals/basics.h"
#include "internals/MachineScheduler/imports.h"


Object MachineScheduler_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct MachineScheduler));
	toReturn->gid =  4460415907327830016ull;
	Object_SetComparator(toReturn, &MachineScheduler_Compare);
	Object_SetDestructor(toReturn, &MachineScheduler_Destroy);
	Object_SetCloner(toReturn, &MachineScheduler_Clone);
	((MachineScheduler) (toReturn->entity))->_placeholder = _nil;
	return toReturn;
}

Object MachineScheduler_GetNextObject(Object _self)
{
	Console_PrintLnString(_console, StringFactory_FromUTF8(_stringFactory, "Этот метод планировщика виртуального процессора виртуальной машины не реализован.", 153));
	return _nil;
}

Object MachineScheduler_Destroy(Object _self)
{
	return Object_Destroy(_self);
}

Object MachineScheduler_Clone(Object _self)
{
	return _self;
}

Object MachineScheduler_Compare(Object _self, Object _scheduler)
{
	return _equal;
}
