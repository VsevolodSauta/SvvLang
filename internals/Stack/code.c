#include "internals/basics.h"
#include "internals/Stack/imports.h"


Object Stack_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Stack));
	toReturn->gid =  6822298517081180160ull;
	Object_SetComparator(toReturn, &Stack_Compare);
	Object_SetDestructor(toReturn, &Stack_Destroy);
	Object_SetCloner(toReturn, &Stack_Clone);
	toReturn = Stack_Init(toReturn);
	return toReturn;
}

Object Stack_Init(Object _self)
{
	(((Stack) (_self->entity))->_list) = List_Create();
	return _self;
}

Object Stack_Push(Object _self, Object _object)
{
	List_PushBack((((Stack) (_self->entity))->_list), _object);
	return _self;
}

Object Stack_Pop(Object _self)
{
	return List_PopBack((((Stack) (_self->entity))->_list));
}

Object Stack_Peek(Object _self)
{
	return List_PeekBack((((Stack) (_self->entity))->_list));
}

Object Stack_Compare(Object _self, Object _queue)
{
	return Object_Compare(Object_Hash((((Stack) (_self->entity))->_list)), Object_Hash((((Stack) (_queue->entity))->_list)));
}

Object Stack_Destroy(Object _self)
{
	List_Destroy((((Stack) (_self->entity))->_list));
	return Object_Destroy(_self);
}

Object Stack_GetList(Object _self)
{
	return Object_TempClone((((Stack) (_self->entity))->_list));
}

Object Stack_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = Stack_Create();
	Object_Release((((Stack) (_toReturn->entity))->_list));
	(((Stack) (_toReturn->entity))->_list) = Object_Clone((((Stack) (_self->entity))->_list));
	return _toReturn;
}
