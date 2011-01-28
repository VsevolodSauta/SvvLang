#include "internals/basics.h"
#include "internals/Queue/imports.h"


Object Queue_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Queue: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Queue));
	_self->gid =  5026058259973625856ull;
	Object_SetComparator(_self, &Queue_Compare);
	Object_SetDestructor(_self, &Queue_Destroy);
	Object_SetCloner(_self, &Queue_Clone);
	Object_SetDeepCloner(_self, &Queue_DeepClone);
	((Queue) (_self->entity))->_list = _nil;
	_self = Queue_Init(_self);
	DPOPS ("Queue: Create ended.")
	return _self;
}

Object Queue_Init(Object _self)
{
	DPUSHS ("Queue: Init begined.")
	Object_SetReleasing(&(((Queue) (_self->entity))->_list), List_Create());
	Object toReturn = _self;
	DPOPS ("Queue: Init ended.")
	return toReturn;
}

Object Queue_Push(Object _self, Object _object)
{
	DPUSHS ("Queue: Push begined.")
	List_PushBack((((Queue) (_self->entity))->_list), _object);
	Object toReturn = _self;
	DPOPS ("Queue: Push ended.")
	return toReturn;
}

Object Queue_Pop(Object _self)
{
	DPUSHS ("Queue: Pop begined.")
	Object toReturn = List_PopFront((((Queue) (_self->entity))->_list));
	DPOPS ("Queue: Pop ended.")
	return toReturn;
}

Object Queue_PopIfNotEmpty(Object _self)
{
	DPUSHS ("Queue: PopIfNotEmpty begined.")
	if((Queue_Empty(_self)) != _false)
	{
		Object toReturn = _nil;
		DPOPS ("Queue: PopIfNotEmpty ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = Queue_Pop(_self);
		DPOPS ("Queue: PopIfNotEmpty ended.")
		return toReturn;
	}
}

Object Queue_Remove(Object _self)
{
	DPUSHS ("Queue: Remove begined.")
	Object toReturn = List_RemoveFront((((Queue) (_self->entity))->_list));
	DPOPS ("Queue: Remove ended.")
	return toReturn;
}

Object Queue_RemoveIfNotEmpty(Object _self)
{
	DPUSHS ("Queue: RemoveIfNotEmpty begined.")
	if((Queue_Empty(_self)) != _false)
	{
		Object toReturn = _nil;
		DPOPS ("Queue: RemoveIfNotEmpty ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = Queue_Remove(_self);
		DPOPS ("Queue: RemoveIfNotEmpty ended.")
		return toReturn;
	}
}

Object Queue_Peek(Object _self)
{
	DPUSHS ("Queue: Peek begined.")
	Object toReturn = List_PeekFront((((Queue) (_self->entity))->_list));
	DPOPS ("Queue: Peek ended.")
	return toReturn;
}

Object Queue_Empty(Object _self)
{
	DPUSHS ("Queue: Empty begined.")
	Object toReturn = List_Empty((((Queue) (_self->entity))->_list));
	DPOPS ("Queue: Empty ended.")
	return toReturn;
}

Object Queue_Compare(Object _self, Object _queue)
{
	DPUSHS ("Queue: Compare begined.")
	Object toReturn = Object_Compare((((Queue) (_self->entity))->_list), (((Queue) (_queue->entity))->_list));
	DPOPS ("Queue: Compare ended.")
	return toReturn;
}

Object Queue_Destroy(Object _self)
{
	DPUSHS ("Queue: Destroy begined.")
	Object_Release((((Queue) (_self->entity))->_list));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Queue: Destroy ended.")
	return toReturn;
}

Object Queue_GetList(Object _self)
{
	DPUSHS ("Queue: GetList begined.")
	Object toReturn = Object_TempClone((((Queue) (_self->entity))->_list));
	DPOPS ("Queue: GetList ended.")
	return toReturn;
}

Object Queue_Clone(Object _self)
{
	DPUSHS ("Queue: Clone begined.")
	Object _toReturn;
	_toReturn = Queue_Create();
	Object_SetReleasing(&(((Queue) (_toReturn->entity))->_list), Object_Clone((((Queue) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("Queue: Clone ended.")
	return toReturn;
}

Object Queue_DeepClone(Object _self)
{
	DPUSHS ("Queue: DeepClone begined.")
	Object _toReturn;
	_toReturn = Queue_Create();
	Object_SetRetaining(&(((Queue) (_toReturn->entity))->_list), Object_DeepClone((((Queue) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("Queue: DeepClone ended.")
	return toReturn;
}
