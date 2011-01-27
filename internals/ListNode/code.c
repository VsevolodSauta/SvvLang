#include "internals/basics.h"
#include "internals/ListNode/imports.h"


Object ListNode_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct ListNode));
	toReturn->gid =  1592307763146065920ull;
	Object_SetComparator(toReturn, &ListNode_Compare);
	Object_SetDestructor(toReturn, &ListNode_Destroy);
	Object_SetCloner(toReturn, &ListNode_Clone);
	Object_SetDeepCloner(toReturn, &ListNode_DeepClone);
	((ListNode) (toReturn->entity))->_next = _nil;
	((ListNode) (toReturn->entity))->_prev = _nil;
	((ListNode) (toReturn->entity))->_data = _nil;
	toReturn = ListNode_Init(toReturn);
	return toReturn;
}

Object ListNode_Init(Object _self)
{
	DMSGS( "List Node: Init." ) 
	return _self;
}

Object ListNode_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = ListNode_Create();
	(((ListNode) (_toReturn->entity))->_next) = (((ListNode) (_self->entity))->_next);
	(((ListNode) (_toReturn->entity))->_prev) = (((ListNode) (_self->entity))->_prev);
	Object_SetRetaining(&(((ListNode) (_toReturn->entity))->_data), (((ListNode) (_self->entity))->_data));
	return _toReturn;
}

Object ListNode_DeepClone(Object _self)
{
	Object _toReturn;
	_toReturn = ListNode_Create();
	(((ListNode) (_toReturn->entity))->_next) = (((ListNode) (_self->entity))->_next);
	(((ListNode) (_toReturn->entity))->_prev) = (((ListNode) (_self->entity))->_prev);
	Object_SetRetaining(&(((ListNode) (_toReturn->entity))->_data), Object_DeepClone((((ListNode) (_self->entity))->_data)));
	return _toReturn;
}

Object ListNode_Compare(Object _self, Object _listNode)
{
	Object _candidate;
	_candidate = Object_Compare((((ListNode) (_self->entity))->_data), (((ListNode) (_listNode->entity))->_data));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		return _candidate;
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(Object_Hash((((ListNode) (_self->entity))->_next)), Object_Hash((((ListNode) (_listNode->entity))->_next))) == _equal)) != _false)
	{
		return Object_Compare(Object_Hash((((ListNode) (_self->entity))->_prev)), Object_Hash((((ListNode) (_listNode->entity))->_prev)));
	}
	return Object_Compare(Object_Hash((((ListNode) (_self->entity))->_next)), Object_Hash((((ListNode) (_listNode->entity))->_next)));
}

Object ListNode_Destroy(Object _self)
{
	Object_Release((((ListNode) (_self->entity))->_data));
	return Object_Destroy(_self);
}
