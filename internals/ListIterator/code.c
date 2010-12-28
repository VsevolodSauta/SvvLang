#include "internals/basics.h"
#include "internals/ListIterator/imports.h"


Object ListIterator_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct ListIterator));
	toReturn->gid =   807984642922801280ull;
	Object_SetComparator(toReturn, &ListIterator_Compare);
	Object_SetDestructor(toReturn, &ListIterator_Destroy);
	Object_SetCloner(toReturn, &ListIterator_Clone);
	((ListIterator) (toReturn->entity))->_list = _nil;
	((ListIterator) (toReturn->entity))->_node = _nil;
	((ListIterator) (toReturn->entity))->_system = _nil;
	return toReturn;
}

Object ListIterator_Compare(Object _self, Object _iterator)
{
	return Object_Compare((((ListIterator) (_self->entity))->_node), (((ListIterator) (_iterator->entity))->_node));
}

Object ListIterator_Destroy(Object _self)
{
	Object_Release((((ListIterator) (_self->entity))->_node));
	if((Object_Is((((ListIterator) (_self->entity))->_system), _false)) != _false)
	{
		Object_Release((((ListIterator) (_self->entity))->_list));
	}
	return Object_Destroy(_self);
}

Object ListIterator_Clone(Object _self)
{
	DPUSHS( "List Iterator: Cloning." ) 
	Object _toReturn;
	_toReturn = ListIterator_Create();
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_list), (((ListIterator) (_self->entity))->_list));
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_node), (((ListIterator) (_self->entity))->_node));
	(((ListIterator) (_toReturn->entity))->_system) = _false;
	DPOPS( "List Iterator: Clonned." ) 
	return _toReturn;
}

Object ListIterator_InitWithListAndNode(Object _self, Object _list, Object _node)
{
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_list), _list);
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	(((ListIterator) (_self->entity))->_system) = _false;
	return _self;
}

Object ListIterator_SystemInitWithListAndNode(Object _self, Object _list, Object _node)
{
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_list), _list);
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	(((ListIterator) (_self->entity))->_system) = _true;
	Object_Release(_list);
	return _self;
}

Object ListIterator_ResetNode(Object _self, Object _node)
{
	DMSGS( "List Iterator: Reseting node." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	return _self;
}

Object ListIterator_Hide(Object _self)
{
	DPUSHS( "List Iterator: Hiding." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _nil);
	DPOPS( "List Iterator: Hidden." ) 
	return _self;
}

Object ListIterator_Next(Object _self)
{
	DMSGS( "List Iterator: Advancing." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next));
	return _self;
}

Object ListIterator_Prev(Object _self)
{
	DMSGS( "List Iterator: Returning." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev));
	return _self;
}

Object ListIterator_ToBegin(Object _self)
{
	DMSGS( "List Iterator: Bringing to begin." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((List) ((((ListIterator) (_self->entity))->_list)->entity))->_head)->entity))->_next));
	return _self;
}

Object ListIterator_ToEnd(Object _self)
{
	DMSGS( "List Iterator: Bringing to end." ) 
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((List) ((((ListIterator) (_self->entity))->_list)->entity))->_tail)->entity))->_prev));
	return _self;
}

Object ListIterator_ToPosition(Object _self, Object _position)
{
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, NumberFactory_FromLong(_numberFactory, 0)) != _less)) != _false)
	{
		ListIterator_ToBegin(_self);
		Object _currentPosition;
		_currentPosition = NumberFactory_FromLong(_numberFactory, 0);
		while((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentPosition, _position) == _less)) != _false)
		{
			ListIterator_Next(_self);
			Number_Inc(_position);
		}
		return _self;
	}
	ListIterator_ToEnd(_self);
	Object _currentPosition;
	_currentPosition = NumberFactory_FromLong(_numberFactory, -1);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentPosition, _position) == _greater)) != _false)
	{
		Number_Dec(_currentPosition);
		ListIterator_Prev(_self);
	}
	return _self;
}

Object ListIterator_FromPositionToPosition(Object _self, Object _positionFrom, Object _positionTo)
{
	Object _quantity;
	_quantity = Number_Sub(_positionTo, _positionFrom);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_quantity, NumberFactory_FromLong(_numberFactory, 0)) == _less)) != _false)
	{
		ListIterator_Prev(_self);
		Number_Inc(_quantity);
	}
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_quantity, NumberFactory_FromLong(_numberFactory, 0)) == _greater)) != _false)
	{
		ListIterator_Next(_self);
		Number_Dec(_quantity);
	}
	return _self;
}

Object ListIterator_SearchForward(Object _self, Object _object)
{
	while((Logic_Not(ListIterator_ThisEnd(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			break;
		}
		ListIterator_Next(_self);
	}
	return _self;
}

Object ListIterator_SearchBackward(Object _self, Object _object)
{
	while((Logic_Not(ListIterator_ThisBegin(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			break;
		}
		ListIterator_Prev(_self);
	}
	return _self;
}

Object ListIterator_SearchForwardOffset(Object _self, Object _object)
{
	Object _position;
	_position = NumberFactory_FromLong(_numberFactory, 0);
	while((Logic_Not(ListIterator_ThisEnd(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			return _position;
		}
		ListIterator_Next(_self);
		Number_Inc(_position);
	}
	return NumberFactory_FromLong(_numberFactory, -1);
}

Object ListIterator_ThisRemove(Object _self)
{
	(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_prev) = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_next) = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	Object_Release((((ListIterator) (_self->entity))->_node));
	return ListIterator_Next(_self);
}

Object ListIterator_PrevRemove(Object _self)
{
	Object _toRemove;
	_toRemove = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_next)->entity))->_prev) = (((ListNode) (_toRemove->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_prev)->entity))->_next) = (((ListNode) (_toRemove->entity))->_next);
	Object_Release(_toRemove);
	return _self;
}

Object ListIterator_NextRemove(Object _self)
{
	Object _toRemove;
	_toRemove = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_next)->entity))->_prev) = (((ListNode) (_toRemove->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_prev)->entity))->_next) = (((ListNode) (_toRemove->entity))->_next);
	Object_Release(_toRemove);
	return _self;
}

Object ListIterator_ThisData(Object _self)
{
	DMSGS( "List Iterator: Getting this data." ) 
	return (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
}

Object ListIterator_NextData(Object _self)
{
	DMSGS( "List Iterator: Getting next data." ) 
	return (((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_data);
}

Object ListIterator_PrevData(Object _self)
{
	DMSGS( "List Iterator: Getting previous data." ) 
	return (((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_data);
}

Object ListIterator_LogicData(Object _self)
{
	return (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
}

Object ListIterator_NumberData(Object _self)
{
	return (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
}

Object ListIterator_ListData(Object _self)
{
	return (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
}

Object ListIterator_ListMapData(Object _self)
{
	return (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
}

Object ListIterator_ThisSetData(Object _self, Object _object)
{
	DMSGS( "List Iterator: Setting this data." ) 
	Object_SetRetaining(&(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data), _object);
	return _self;
}

Object ListIterator_PrevSetData(Object _self, Object _object)
{
	DMSGS( "List Iterator: Setting previous data." ) 
	Object_SetRetaining(&(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_data), _object);
	return _self;
}

Object ListIterator_NextSetData(Object _self, Object _object)
{
	DMSGS( "List Iterator: Setting next data." ) 
	Object_SetRetaining(&(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_data), _object);
	return _self;
}

Object ListIterator_AddAfter(Object _self, Object _object)
{
	DPUSHS( "List Iterator: Adding data to the next." ) 
	Object _addingElement;
	_addingElement = ListNode_Create();
	Object_SetRetaining(&(((ListNode) (_addingElement->entity))->_data), _object);
	Object _savedNext;
	_savedNext = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next) = _addingElement;
	(((ListNode) (_addingElement->entity))->_prev) = (((ListIterator) (_self->entity))->_node);
	(((ListNode) (_addingElement->entity))->_next) = _savedNext;
	(((ListNode) (_savedNext->entity))->_prev) = _addingElement;
	DPOPS( "List Iterator: Data added to the next." ) 
	return _self;
}

Object ListIterator_AddBefore(Object _self, Object _object)
{
	DPUSHS( "List Iterator: Adding data to the prev." ) 
	Object _addingElement;
	_addingElement = ListNode_Create();
	Object_SetRetaining(&(((ListNode) (_addingElement->entity))->_data), _object);
	Object _savedPrev;
	_savedPrev = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev) = _addingElement;
	(((ListNode) (_addingElement->entity))->_next) = (((ListIterator) (_self->entity))->_node);
	(((ListNode) (_addingElement->entity))->_prev) = _savedPrev;
	(((ListNode) (_savedPrev->entity))->_next) = _addingElement;
	DPOPS( "List Iterator: Data added to the prev." ) 
	return _self;
}

Object ListIterator_ThisBegin(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev), _nothing) == _equal);
}

Object ListIterator_ThisEnd(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next), _nothing) == _equal);
}

Object ListIterator_PrevBegin(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_prev), _nothing) == _equal);
}

Object ListIterator_NextEnd(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_next), _nothing) == _equal);
}

Object ListIterator_AddListBefore(Object _self, Object _list)
{
	Object _listIterator;
	_listIterator = List_First(_list);
	while((Logic_Not(ListIterator_ThisEnd(_listIterator))) != _false)
	{
		ListIterator_AddBefore(_self, ListIterator_ThisData(_listIterator));
		ListIterator_Next(_listIterator);
	}
	return _self;
}

Object ListIterator_AddListAfter(Object _self, Object _list)
{
	Object _listIterator;
	_listIterator = List_Last(_list);
	while((Logic_Not(ListIterator_ThisBegin(_listIterator))) != _false)
	{
		ListIterator_AddAfter(_self, ListIterator_ThisData(_listIterator));
		ListIterator_Prev(_listIterator);
	}
	return _self;
}

Object ListIterator_RemoveCount(Object _self, Object _count)
{
	Object _savedPrev;
	_savedPrev = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	Object _deletedCount;
	_deletedCount = NumberFactory_FromLong(_numberFactory, 0);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_deletedCount, _count) == _less)) != _false)
	{
		Object_Release((((ListIterator) (_self->entity))->_node));
		ListIterator_Next(_self);
		Number_Inc(_deletedCount);
	}
	(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev) = _savedPrev;
	(((ListNode) (_savedPrev->entity))->_next) = (((ListIterator) (_self->entity))->_node);
	return _self;
}
