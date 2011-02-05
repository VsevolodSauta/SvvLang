#include "internals/basics.h"
#include "internals/ListNode/imports.h"


Object ListNode_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListNode: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListNode));
	_self->gid =  1592307763146065920ull;
	Object_SetComparator(_self, &ListNode_Compare);
	Object_SetDestructor(_self, &ListNode_Destroy);
	Object_SetCloner(_self, &ListNode_Clone);
	Object_SetDeepCloner(_self, &ListNode_DeepClone);
	((ListNode) (_self->entity))->_next = _nil;
	((ListNode) (_self->entity))->_prev = _nil;
	((ListNode) (_self->entity))->_data = _nil;
	_self = ListNode_Init(_self);
	DPOPS ("ListNode: Create ended.")
	return _self;
}

Object ListNode_Init(Object _self)
{
	DPUSHS ("ListNode: Init begined.")
	ASSERT_C ( "ListNode:Init --- Checking for correct object type failed.", _self->gid ==  1592307763146065920ull )
	Object toReturn = _self;
	DPOPS ("ListNode: Init ended.")
	return toReturn;
}

Object ListNode_Clone(Object _self)
{
	DPUSHS ("ListNode: Clone begined.")
	ASSERT_C ( "ListNode:Clone --- Checking for correct object type failed.", _self->gid ==  1592307763146065920ull )
	Object _toReturn;
	_toReturn = ListNode_Create();
	(((ListNode) (_toReturn->entity))->_next) = (((ListNode) (_self->entity))->_next);
	(((ListNode) (_toReturn->entity))->_prev) = (((ListNode) (_self->entity))->_prev);
	Object_SetRetaining(&(((ListNode) (_toReturn->entity))->_data), (((ListNode) (_self->entity))->_data));
	Object toReturn = _toReturn;
	DPOPS ("ListNode: Clone ended.")
	return toReturn;
}

Object ListNode_DeepClone(Object _self)
{
	DPUSHS ("ListNode: DeepClone begined.")
	ASSERT_C ( "ListNode:DeepClone --- Checking for correct object type failed.", _self->gid ==  1592307763146065920ull )
	Object _toReturn;
	_toReturn = ListNode_Create();
	(((ListNode) (_toReturn->entity))->_next) = (((ListNode) (_self->entity))->_next);
	(((ListNode) (_toReturn->entity))->_prev) = (((ListNode) (_self->entity))->_prev);
	Object_SetRetaining(&(((ListNode) (_toReturn->entity))->_data), Object_DeepClone((((ListNode) (_self->entity))->_data)));
	Object toReturn = _toReturn;
	DPOPS ("ListNode: DeepClone ended.")
	return toReturn;
}

Object ListNode_Compare(Object _self, Object _listNode)
{
	DPUSHS ("ListNode: Compare begined.")
	ASSERT_C ( "ListNode:Compare --- Checking for correct object type failed.", _self->gid ==  1592307763146065920ull )
	Object _candidate;
	_candidate = Object_Compare((((ListNode) (_self->entity))->_data), (((ListNode) (_listNode->entity))->_data));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("ListNode: Compare ended.")
		return toReturn;
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(Object_Hash((((ListNode) (_self->entity))->_next)), Object_Hash((((ListNode) (_listNode->entity))->_next))) == _equal)) != _false)
	{
		Object toReturn = Object_Compare(Object_Hash((((ListNode) (_self->entity))->_prev)), Object_Hash((((ListNode) (_listNode->entity))->_prev)));
		DPOPS ("ListNode: Compare ended.")
		return toReturn;
	}
	Object toReturn = Object_Compare(Object_Hash((((ListNode) (_self->entity))->_next)), Object_Hash((((ListNode) (_listNode->entity))->_next)));
	DPOPS ("ListNode: Compare ended.")
	return toReturn;
}

Object ListNode_Destroy(Object _self)
{
	DPUSHS ("ListNode: Destroy begined.")
	ASSERT_C ( "ListNode:Destroy --- Checking for correct object type failed.", _self->gid ==  1592307763146065920ull )
	Object_Release((((ListNode) (_self->entity))->_data));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListNode: Destroy ended.")
	return toReturn;
}
