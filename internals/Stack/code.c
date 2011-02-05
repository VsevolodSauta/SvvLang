#include "internals/basics.h"
#include "internals/Stack/imports.h"


Object Stack_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Stack: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Stack));
	_self->gid =  6822298517081180160ull;
	Object_SetComparator(_self, &Stack_Compare);
	Object_SetDestructor(_self, &Stack_Destroy);
	Object_SetCloner(_self, &Stack_Clone);
	Object_SetDeepCloner(_self, &Stack_DeepClone);
	((Stack) (_self->entity))->_list = _nil;
	_self = Stack_Init(_self);
	DPOPS ("Stack: Create ended.")
	return _self;
}

Object Stack_Init(Object _self)
{
	DPUSHS ("Stack: Init begined.")
	ASSERT_C ( "Stack:Init --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object_SetReleasing(&(((Stack) (_self->entity))->_list), List_Create());
	Object toReturn = _self;
	DPOPS ("Stack: Init ended.")
	return toReturn;
}

Object Stack_Push(Object _self, Object _object)
{
	DPUSHS ("Stack: Push begined.")
	ASSERT_C ( "Stack:Push --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	List_PushFront((((Stack) (_self->entity))->_list), _object);
	Object toReturn = _self;
	DPOPS ("Stack: Push ended.")
	return toReturn;
}

Object Stack_Pop(Object _self)
{
	DPUSHS ("Stack: Pop begined.")
	ASSERT_C ( "Stack:Pop --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = List_PopFront((((Stack) (_self->entity))->_list));
	DPOPS ("Stack: Pop ended.")
	return toReturn;
}

Object Stack_Remove(Object _self)
{
	DPUSHS ("Stack: Remove begined.")
	ASSERT_C ( "Stack:Remove --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = List_RemoveFront((((Stack) (_self->entity))->_list));
	DPOPS ("Stack: Remove ended.")
	return toReturn;
}

Object Stack_Peek(Object _self)
{
	DPUSHS ("Stack: Peek begined.")
	ASSERT_C ( "Stack:Peek --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = List_PeekFront((((Stack) (_self->entity))->_list));
	DPOPS ("Stack: Peek ended.")
	return toReturn;
}

Object Stack_ObjectAtPositionIfExists(Object _self, Object _position)
{
	DPUSHS ("Stack: ObjectAtPositionIfExists begined.")
	ASSERT_C ( "Stack:ObjectAtPositionIfExists --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = List_ObjectAtPositionIfExists((((Stack) (_self->entity))->_list), _position);
	DPOPS ("Stack: ObjectAtPositionIfExists ended.")
	return toReturn;
}

Object Stack_Empty(Object _self)
{
	DPUSHS ("Stack: Empty begined.")
	ASSERT_C ( "Stack:Empty --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = List_Empty((((Stack) (_self->entity))->_list));
	DPOPS ("Stack: Empty ended.")
	return toReturn;
}

Object Stack_Clean(Object _self)
{
	DPUSHS ("Stack: Clean begined.")
	ASSERT_C ( "Stack:Clean --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	List_Clean((((Stack) (_self->entity))->_list));
	Object toReturn = _self;
	DPOPS ("Stack: Clean ended.")
	return toReturn;
}

Object Stack_Compare(Object _self, Object _stack)
{
	DPUSHS ("Stack: Compare begined.")
	ASSERT_C ( "Stack:Compare --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = Object_Compare((((Stack) (_self->entity))->_list), (((Stack) (_stack->entity))->_list));
	DPOPS ("Stack: Compare ended.")
	return toReturn;
}

Object Stack_Destroy(Object _self)
{
	DPUSHS ("Stack: Destroy begined.")
	ASSERT_C ( "Stack:Destroy --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object_Release((((Stack) (_self->entity))->_list));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Stack: Destroy ended.")
	return toReturn;
}

Object Stack_GetList(Object _self)
{
	DPUSHS ("Stack: GetList begined.")
	ASSERT_C ( "Stack:GetList --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object toReturn = Object_TempClone((((Stack) (_self->entity))->_list));
	DPOPS ("Stack: GetList ended.")
	return toReturn;
}

Object Stack_Clone(Object _self)
{
	DPUSHS ("Stack: Clone begined.")
	ASSERT_C ( "Stack:Clone --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object _toReturn;
	_toReturn = Stack_Create();
	Object_SetReleasing(&(((Stack) (_toReturn->entity))->_list), Object_Clone((((Stack) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("Stack: Clone ended.")
	return toReturn;
}

Object Stack_DeepClone(Object _self)
{
	DPUSHS ("Stack: DeepClone begined.")
	ASSERT_C ( "Stack:DeepClone --- Checking for correct object type failed.", _self->gid ==  6822298517081180160ull )
	Object _toReturn;
	_toReturn = Stack_Create();
	Object_SetRetaining(&(((Stack) (_toReturn->entity))->_list), Object_DeepClone((((Stack) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("Stack: DeepClone ended.")
	return toReturn;
}
