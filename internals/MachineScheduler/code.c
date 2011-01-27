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
	Object_SetDeepCloner(toReturn, &MachineScheduler_DeepClone);
	((MachineScheduler) (toReturn->entity))->_queue = _nil;
	toReturn = MachineScheduler_Init(toReturn);
	return toReturn;
}

Object MachineScheduler_Init(Object _self)
{
	(((MachineScheduler) (_self->entity))->_queue) = Queue_Create();
	return _self;
}

Object MachineScheduler_GetNextObject(Object _self)
{
	if((Queue_Empty((((MachineScheduler) (_self->entity))->_queue))) != _false)
	{
		return _nil;
	}
	else
	{
		return Queue_Pop((((MachineScheduler) (_self->entity))->_queue));
	}
}

Object MachineScheduler_Schedule(Object _self, Object _uid)
{
	Queue_Push((((MachineScheduler) (_self->entity))->_queue), _uid);
	return _self;
}

Object MachineScheduler_Destroy(Object _self)
{
	Object_Release((((MachineScheduler) (_self->entity))->_queue));
	return Object_Destroy(_self);
}

Object MachineScheduler_DeepClone(Object _self)
{
	return _self;
}

Object MachineScheduler_Clone(Object _self)
{
	return _self;
}

Object MachineScheduler_Compare(Object _self, Object _scheduler)
{
	return _equal;
}
