#include "internals/basics.h"
#include "internals/Queue/imports.h"


Object Queue_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Queue));
	toReturn->gid =  5026058259973625856ull;
	Object_SetComparator(toReturn, &Queue_Compare);
	Object_SetDestructor(toReturn, &Queue_Destroy);
	Object_SetCloner(toReturn, &Queue_Clone);
	((Queue) (toReturn->entity))->_list = _nil;
	toReturn = Queue_Init(toReturn);
	return toReturn;
}

Object Queue_Init(Object _self)
{
	Object_SetReleasing(&(((Queue) (_self->entity))->_list), List_Create());
	return _self;
}

Object Queue_Push(Object _self, Object _object)
{
	List_PushBack((((Queue) (_self->entity))->_list), _object);
	return _self;
}

Object Queue_Pop(Object _self)
{
	return List_PopFront((((Queue) (_self->entity))->_list));
}

Object Queue_Peek(Object _self)
{
	return List_PeekFront((((Queue) (_self->entity))->_list));
}

Object Queue_Compare(Object _self, Object _queue)
{
	return Object_Compare((((Queue) (_self->entity))->_list), (((Queue) (_queue->entity))->_list));
}

Object Queue_Destroy(Object _self)
{
	Object_Destroy((((Queue) (_self->entity))->_list));
	return Object_Destroy(_self);
}

Object Queue_GetList(Object _self)
{
	return Object_TempClone((((Queue) (_self->entity))->_list));
}

Object Queue_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = Queue_Create();
	Object_SetReleasing(&(((Queue) (_toReturn->entity))->_list), Object_Clone((((Queue) (_self->entity))->_list)));
	return _toReturn;
}
