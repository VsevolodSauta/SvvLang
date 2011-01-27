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
	Object_SetDeepCloner(toReturn, &Stack_DeepClone);
	((Stack) (toReturn->entity))->_list = _nil;
	toReturn = Stack_Init(toReturn);
	return toReturn;
}

Object Stack_Init(Object _self)
{
	DPUSHS( "Stack: Initing." ) 
	Object_SetReleasing(&(((Stack) (_self->entity))->_list), List_Create());
	DPOPS( "Stack: Inited." ) 
	return _self;
}

Object Stack_Push(Object _self, Object _object)
{
	DPUSHS( "Stack: Pushing." ) 
	List_PushBack((((Stack) (_self->entity))->_list), _object);
	DPOPS( "Stack: Pushed." ) 
	return _self;
}

Object Stack_Pop(Object _self)
{
	DPUSHS( "Stack: Popping." ) 
	Object def = List_PopBack((((Stack) (_self->entity))->_list));
	DPOPS( "Stack: Popped." ) 
	return def;
}

Object Stack_Remove(Object _self)
{
	DPUSHS( "Stack: Removing." ) 
	Object def = List_RemoveBack((((Stack) (_self->entity))->_list));
	DPOPS( "Stack: Removed." ) 
	return def;
}

Object Stack_Peek(Object _self)
{
	DPUSHS( "Stack: Peeking." ) 
	Object def = List_PeekBack((((Stack) (_self->entity))->_list));
	DPOPS( "Stack: Peeked." ) 
	return def;
}

Object Stack_Empty(Object _self)
{
	return List_Empty((((Stack) (_self->entity))->_list));
}

Object Stack_Compare(Object _self, Object _stack)
{
	return Object_Compare((((Stack) (_self->entity))->_list), (((Stack) (_stack->entity))->_list));
}

Object Stack_Destroy(Object _self)
{
	DPUSHS( "Stack: Destroying." ) 
	Object_Release((((Stack) (_self->entity))->_list));
	DPOPS( "Stack: Destroyed." ) 
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
	Object_SetReleasing(&(((Stack) (_toReturn->entity))->_list), Object_Clone((((Stack) (_self->entity))->_list)));
	return _toReturn;
}

Object Stack_DeepClone(Object _self)
{
	Object _toReturn;
	_toReturn = Stack_Create();
	Object_SetRetaining(&(((Stack) (_toReturn->entity))->_list), Object_DeepClone((((Stack) (_self->entity))->_list)));
	return _toReturn;
}
