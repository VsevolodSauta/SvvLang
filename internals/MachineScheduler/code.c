#include "internals/basics.h"
#include "internals/MachineScheduler/imports.h"


Object MachineScheduler_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("MachineScheduler: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct MachineScheduler));
	_self->gid =  4460415907327830016ull;
	Object_SetComparator(_self, &MachineScheduler_Compare);
	Object_SetDestructor(_self, &MachineScheduler_Destroy);
	Object_SetCloner(_self, &MachineScheduler_Clone);
	Object_SetDeepCloner(_self, &MachineScheduler_DeepClone);
	((MachineScheduler) (_self->entity))->_queue = _nil;
	_self = MachineScheduler_Init(_self);
	DPOPS ("MachineScheduler: Create ended.")
	return _self;
}

Object MachineScheduler_Init(Object _self)
{
	DPUSHS ("MachineScheduler: Init begined.")
	ASSERT_C ( "MachineScheduler:Init --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	(((MachineScheduler) (_self->entity))->_queue) = Queue_Create();
	Object toReturn = _self;
	DPOPS ("MachineScheduler: Init ended.")
	return toReturn;
}

Object MachineScheduler_GetNextUID(Object _self)
{
	DPUSHS ("MachineScheduler: GetNextUID begined.")
	ASSERT_C ( "MachineScheduler:GetNextUID --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	if((Queue_Empty((((MachineScheduler) (_self->entity))->_queue))) != _false)
	{
		Object toReturn = _nil;
		DPOPS ("MachineScheduler: GetNextUID ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = Queue_Pop((((MachineScheduler) (_self->entity))->_queue));
		DPOPS ("MachineScheduler: GetNextUID ended.")
		return toReturn;
	}
}

Object MachineScheduler_ScheduleUID(Object _self, Object _uid)
{
	DPUSHS ("MachineScheduler: ScheduleUID begined.")
	ASSERT_C ( "MachineScheduler:ScheduleUID --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	Queue_Push((((MachineScheduler) (_self->entity))->_queue), _uid);
	Object toReturn = _self;
	DPOPS ("MachineScheduler: ScheduleUID ended.")
	return toReturn;
}

Object MachineScheduler_Destroy(Object _self)
{
	DPUSHS ("MachineScheduler: Destroy begined.")
	ASSERT_C ( "MachineScheduler:Destroy --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	Object_Release((((MachineScheduler) (_self->entity))->_queue));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("MachineScheduler: Destroy ended.")
	return toReturn;
}

Object MachineScheduler_DeepClone(Object _self)
{
	DPUSHS ("MachineScheduler: DeepClone begined.")
	ASSERT_C ( "MachineScheduler:DeepClone --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	Object toReturn = _self;
	DPOPS ("MachineScheduler: DeepClone ended.")
	return toReturn;
}

Object MachineScheduler_Clone(Object _self)
{
	DPUSHS ("MachineScheduler: Clone begined.")
	ASSERT_C ( "MachineScheduler:Clone --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	Object toReturn = _self;
	DPOPS ("MachineScheduler: Clone ended.")
	return toReturn;
}

Object MachineScheduler_Compare(Object _self, Object _scheduler)
{
	DPUSHS ("MachineScheduler: Compare begined.")
	ASSERT_C ( "MachineScheduler:Compare --- Checking for correct object type failed.", _self->gid ==  4460415907327830016ull )
	Object toReturn = _equal;
	DPOPS ("MachineScheduler: Compare ended.")
	return toReturn;
}
