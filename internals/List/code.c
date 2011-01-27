#include "internals/basics.h"
#include "internals/List/imports.h"


Object List_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct List));
	toReturn->gid =  3732711262168886272ull;
	Object_SetComparator(toReturn, &List_Compare);
	Object_SetDestructor(toReturn, &List_Destroy);
	Object_SetCloner(toReturn, &List_Clone);
	Object_SetDeepCloner(toReturn, &List_DeepClone);
	((List) (toReturn->entity))->_iterator = _nil;
	((List) (toReturn->entity))->_head = _nil;
	((List) (toReturn->entity))->_tail = _nil;
	toReturn = List_Init(toReturn);
	return toReturn;
}

Object List_Init(Object _self)
{
	DPUSHS( "List: Initing." ) 
	(((List) (_self->entity))->_head) = ListNode_Create();
	(((List) (_self->entity))->_tail) = ListNode_Create();
	(((ListNode) ((((List) (_self->entity))->_head)->entity))->_next) = (((List) (_self->entity))->_tail);
	(((ListNode) ((((List) (_self->entity))->_tail)->entity))->_prev) = (((List) (_self->entity))->_head);
	(((ListNode) ((((List) (_self->entity))->_tail)->entity))->_next) = (((ListNode) ((((List) (_self->entity))->_head)->entity))->_prev) = _nil;
	(((List) (_self->entity))->_iterator) = List_SystemIterator(_self);
	DPOPS( "List: Inited." ) 
	return _self;
}

Object List_Destroy(Object _self)
{
	DPUSHS( "List: Destroying." ) 
	Object_Release((((List) (_self->entity))->_iterator));
	Object _node;
	_node = (((List) (_self->entity))->_head);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_node, _nil) != _equal)) != _false)
	{
		Object _nextNode;
		_nextNode = (((ListNode) (_node->entity))->_next);
		Object_Release(_node);
		_node = _nextNode;
	}
	DPOPS( "List: Destroyed." ) 
	return Object_Destroy(_self);
}

Object List_Clone(Object _self)
{
	Object _list;
	_list = List_Create();
	ListIterator_ToEnd((((List) (_list->entity))->_iterator));
	ListIterator_AddListAfter((((List) (_list->entity))->_iterator), _self);
	ListIterator_Hide((((List) (_list->entity))->_iterator));
	return _list;
}

Object List_DeepClone(Object _self)
{
	Object _list;
	_list = List_Create();
	ListIterator_ToEnd((((List) (_list->entity))->_iterator));
	ListIterator_AddListAfterDeepClonning((((List) (_list->entity))->_iterator), _self);
	ListIterator_Hide((((List) (_list->entity))->_iterator));
	return _list;
}

Object List_Compare(Object _self, Object _list)
{
	Object _selfIterator;
	_selfIterator = List_First(_self);
	Object _listIterator;
	_listIterator = List_First(_list);
	while(1)
	{
		if((ListIterator_ThisEnd(_selfIterator)) != _false)
		{
			if((ListIterator_ThisEnd(_listIterator)) != _false)
			{
				return _equal;
			}
			else
			{
				return _less;
			}
		}
		if((ListIterator_ThisEnd(_listIterator)) != _false)
		{
			return _greater;
		}
		Object _candidateForReturning;
		_candidateForReturning = Object_Compare(ListIterator_ThisData(_selfIterator), ListIterator_ThisData(_listIterator));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidateForReturning, _equal) == _equal)) != _false)
		{
			ListIterator_Next(_listIterator);
			ListIterator_Next(_selfIterator);
		}
		else
		{
			return _candidateForReturning;
		}
	}
}

Object List_Clean(Object _self)
{
	Object _node;
	_node = (((ListNode) ((((List) (_self->entity))->_head)->entity))->_next);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_node, (((List) (_self->entity))->_tail)) != _equal)) != _false)
	{
		Object _nextNode;
		_nextNode = (((ListNode) (_node->entity))->_next);
		Object_Release(_node);
		_node = _nextNode;
	}
	(((ListNode) ((((List) (_self->entity))->_head)->entity))->_next) = (((List) (_self->entity))->_tail);
	(((ListNode) ((((List) (_self->entity))->_tail)->entity))->_prev) = (((List) (_self->entity))->_head);
	return _self;
}

Object List_PushFront(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_PushBack(Object _self, Object _object)
{
	DPUSHS( "List: Pushing back." ) 
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_AddAfter((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS( "List: Pushed back." ) 
	return _self;
}

Object List_PushSorted(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	while((Logic_And(Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator))), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData((((List) (_self->entity))->_iterator)), _object) == _less))) != _false)
	{
		ListIterator_Next((((List) (_self->entity))->_iterator));
	}
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_PeekFront(Object _self)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return def;
}

Object List_PeekBack(Object _self)
{
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return def;
}

Object List_PopFront(Object _self)
{
	DPUSHS( "List: Popping front." ) 
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = Object_Autorelease(Object_Retain(ListIterator_ThisData((((List) (_self->entity))->_iterator))));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS( "List: Popped front." ) 
	return def;
}

Object List_PopBack(Object _self)
{
	DPUSHS( "List: Popping back." ) 
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	Object def = Object_Autorelease(Object_Retain(ListIterator_ThisData((((List) (_self->entity))->_iterator))));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS( "List: Popped back." ) 
	return def;
}

Object List_RemoveFront(Object _self)
{
	DPUSHS( "List: Removing front." ) 
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS( "List: Removed front." ) 
	return _self;
}

Object List_RemoveBack(Object _self)
{
	DPUSHS( "List: Removing back." ) 
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS( "List: Removed back." ) 
	return _self;
}

Object List_AddAfterPosition(Object _self, Object _position, Object _object)
{
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_AddAfter((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_AddBeforePosition(Object _self, Object _position, Object _object)
{
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_Contains(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	Object def = Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return def;
}

Object List_RemoveFirst(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_RemoveFirstWithConfirmation(Object _self, Object _object)
{
	Object _confirmation;
	_confirmation = _false;
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		_confirmation = _true;
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _confirmation;
}

Object List_RemoveLast(Object _self, Object _object)
{
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_SearchBackward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisBegin((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_RemoveLastWithConfirmation(Object _self, Object _object)
{
	Object _confirmation;
	_confirmation = _false;
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_SearchBackward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisBegin((((List) (_self->entity))->_iterator)))) != _false)
	{
		_confirmation = _true;
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _confirmation;
}

Object List_RemoveEvery(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
		ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_RemoveEveryWithConfirmation(Object _self, Object _object)
{
	Object _confirmation;
	_confirmation = _false;
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		_confirmation = _true;
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
		ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _confirmation;
}

Object List_Last(Object _self)
{
	DPUSHS( "List: Getting last iterator" ) 
	Object _iterator;
	_iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(_iterator, _self, (((ListNode) ((((List) (_self->entity))->_tail)->entity))->_prev));
	DPOPS( "List: Last iterator got." ) 
	return _iterator;
}

Object List_First(Object _self)
{
	DPUSHS( "List: Getting first iterator" ) 
	Object _iterator;
	_iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(_iterator, _self, (((ListNode) ((((List) (_self->entity))->_head)->entity))->_next));
	DPOPS( "List: First iterator got." ) 
	return _iterator;
}

Object List_SystemIterator(Object _self)
{
	DPUSHS( "List: Getting system iterator." ) 
	Object _iterator;
	_iterator = ListIterator_Create();
	ListIterator_SystemInitWithListAndNode(_iterator, _self, _nil);
	DPOPS( "List: System iterator got." ) 
	return _iterator;
}

Object List_ObjectAtPosition(Object _self, Object _position)
{
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return def;
}

Object List_ListMapAtPosition(Object _self, Object _position)
{
	return List_ObjectAtPosition(_self, NumberFactory_FromLong(_numberFactory, 0));
}

Object List_Search(Object _self, Object _object)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object _list;
	_list = Object_Autorelease(List_Create());
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		List_PushBack(_list, Object_TempClone((((List) (_self->entity))->_iterator)));
		ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	}
	return _list;
}

Object List_IteratorFromPosition(Object _self, Object _position)
{
	return ListIterator_ToPosition(List_First(_self), _position);
}

Object List_CreatingIteratorFromPosition(Object _self, Object _position)
{
	Object _iterator;
	_iterator = List_First(_self);
	Object _currentPosition;
	_currentPosition = NumberFactory_FromLong(_numberFactory, 0);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentPosition, _position) != _greater)) != _false)
	{
		Number_Inc(_currentPosition);
		if((ListIterator_ThisEnd(_iterator)) != _false)
		{
			ListIterator_AddBefore(_iterator, _nil);
		}
		else
		{
			ListIterator_Next(_iterator);
		}
	}
	ListIterator_Prev(_iterator);
	return _iterator;
}

Object List_SearchPositions(Object _self, Object _object)
{
	Object _list;
	_list = List_Create();
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object _position;
	_position = NumberFactory_FromLong(_numberFactory, 0);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData((((List) (_list->entity))->_iterator)), _object) == _equal)) != _false)
		{
			List_PushBack(_list, Object_TempClone(_position));
		}
		Number_Inc(_position);
		ListIterator_Next((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _list;
}

Object List_SublistBetweenPositions(Object _self, Object _positionFrom, Object _positionTo)
{
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _positionFrom);
	Object _list;
	_list = Object_Autorelease(List_Create());
	Object _position;
	_position = Object_Clone(_positionFrom);
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _positionTo) != _greater)) != _false)
	{
		List_PushBack(_list, ListIterator_ThisData((((List) (_self->entity))->_iterator)));
		ListIterator_Next((((List) (_self->entity))->_iterator));
		Number_Inc(_position);
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object_Release(_position);
	return _list;
}

Object List_SublistBetweenIterators(Object _self, Object _positionFrom, Object _positionTo)
{
	Object _iterator;
	_iterator = Object_Clone(_positionFrom);
	Object _list;
	_list = List_Create();
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_iterator, _positionTo) != _equal)) != _false)
	{
		List_PushBack(_list, ListIterator_ThisData(_iterator));
		ListIterator_Next(_iterator);
	}
	Object_Release(_iterator);
	return _list;
}

Object List_Size(Object _self)
{
	DPUSHS( "List: Getting size." ) 
	Object _iterator;
	_iterator = Object_Clone((((List) (_self->entity))->_iterator));
	ListIterator_ToBegin(_iterator);
	Object _toReturn;
	_toReturn = NumberFactory_FromLong(_numberFactory, 0);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		Number_Inc(_toReturn);
		ListIterator_Next(_iterator);
	}
	Object_Release(_iterator);
	DPOPS( "List: Size got." ) 
	return _toReturn;
}

Object List_Empty(Object _self)
{
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisEnd((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return def;
}

Object List_Concatenate(Object _self, Object _list)
{
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_AddListAfter((((List) (_self->entity))->_iterator), _list);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	return _self;
}

Object List_SortInPlace(Object _self)
{
	return _self;
}
