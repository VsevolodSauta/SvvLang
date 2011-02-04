#include "internals/basics.h"
#include "internals/ListIterator/imports.h"


Object ListIterator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListIterator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListIterator));
	_self->gid =   807984642922801280ull;
	Object_SetComparator(_self, &ListIterator_Compare);
	Object_SetDestructor(_self, &ListIterator_Destroy);
	Object_SetCloner(_self, &ListIterator_Clone);
	Object_SetDeepCloner(_self, &ListIterator_DeepClone);
	((ListIterator) (_self->entity))->_list = _nil;
	((ListIterator) (_self->entity))->_node = _nil;
	((ListIterator) (_self->entity))->_system = _nil;
	DPOPS ("ListIterator: Create ended.")
	return _self;
}

Object ListIterator_Compare(Object _self, Object _iterator)
{
	DPUSHS ("ListIterator: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = Object_Compare((((ListIterator) (_self->entity))->_node), (((ListIterator) (_iterator->entity))->_node));
	DPOPS ("ListIterator: Compare ended.")
	return toReturn;
}

Object ListIterator_Destroy(Object _self)
{
	DPUSHS ("ListIterator: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_Release((((ListIterator) (_self->entity))->_node));
	if((Object_Is((((ListIterator) (_self->entity))->_system), _false)) != _false)
	{
		Object_Release((((ListIterator) (_self->entity))->_list));
	}
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListIterator: Destroy ended.")
	return toReturn;
}

Object ListIterator_Clone(Object _self)
{
	DPUSHS ("ListIterator: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _toReturn;
	_toReturn = ListIterator_Create();
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_list), (((ListIterator) (_self->entity))->_list));
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_node), (((ListIterator) (_self->entity))->_node));
	(((ListIterator) (_toReturn->entity))->_system) = _false;
	Object toReturn = _toReturn;
	DPOPS ("ListIterator: Clone ended.")
	return toReturn;
}

Object ListIterator_DeepClone(Object _self)
{
	DPUSHS ("ListIterator: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _toReturn;
	_toReturn = ListIterator_Create();
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_list), (((ListIterator) (_self->entity))->_list));
	Object_SetRetaining(&(((ListIterator) (_toReturn->entity))->_node), (((ListIterator) (_self->entity))->_node));
	(((ListIterator) (_toReturn->entity))->_system) = _false;
	Object toReturn = _toReturn;
	DPOPS ("ListIterator: DeepClone ended.")
	return toReturn;
}

Object ListIterator_InitWithListAndNode(Object _self, Object _list, Object _node)
{
	DPUSHS ("ListIterator: InitWithListAndNode begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_list), _list);
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	(((ListIterator) (_self->entity))->_system) = _false;
	Object toReturn = _self;
	DPOPS ("ListIterator: InitWithListAndNode ended.")
	return toReturn;
}

Object ListIterator_SystemInitWithListAndNode(Object _self, Object _list, Object _node)
{
	DPUSHS ("ListIterator: SystemInitWithListAndNode begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_list), _list);
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	(((ListIterator) (_self->entity))->_system) = _true;
	Object_Release(_list);
	Object toReturn = _self;
	DPOPS ("ListIterator: SystemInitWithListAndNode ended.")
	return toReturn;
}

Object ListIterator_ResetNode(Object _self, Object _node)
{
	DPUSHS ("ListIterator: ResetNode begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _node);
	Object toReturn = _self;
	DPOPS ("ListIterator: ResetNode ended.")
	return toReturn;
}

Object ListIterator_Hide(Object _self)
{
	DPUSHS ("ListIterator: Hide begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), _nil);
	Object toReturn = _self;
	DPOPS ("ListIterator: Hide ended.")
	return toReturn;
}

Object ListIterator_Next(Object _self)
{
	DPUSHS ("ListIterator: Next begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next));
	Object toReturn = _self;
	DPOPS ("ListIterator: Next ended.")
	return toReturn;
}

Object ListIterator_Prev(Object _self)
{
	DPUSHS ("ListIterator: Prev begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev));
	Object toReturn = _self;
	DPOPS ("ListIterator: Prev ended.")
	return toReturn;
}

Object ListIterator_ToBegin(Object _self)
{
	DPUSHS ("ListIterator: ToBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((List) ((((ListIterator) (_self->entity))->_list)->entity))->_head)->entity))->_next));
	Object toReturn = _self;
	DPOPS ("ListIterator: ToBegin ended.")
	return toReturn;
}

Object ListIterator_ToEnd(Object _self)
{
	DPUSHS ("ListIterator: ToEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListIterator) (_self->entity))->_node), (((ListNode) ((((List) ((((ListIterator) (_self->entity))->_list)->entity))->_tail)->entity))->_prev));
	Object toReturn = _self;
	DPOPS ("ListIterator: ToEnd ended.")
	return toReturn;
}

Object ListIterator_ToPosition(Object _self, Object _position)
{
	DPUSHS ("ListIterator: ToPosition begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, NumberFactory_FromLong(_numberFactory, 0)) != _less)) != _false)
	{
		ListIterator_ToBegin(_self);
		Object _currentPosition;
		_currentPosition = NumberFactory_FromLong(_numberFactory, 0);
		while((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentPosition, _position) == _less)) != _false)
		{
			ListIterator_Next(_self);
			Number_Inc(_currentPosition);
		}
	}
	else
	{
		ListIterator_ToEnd(_self);
		Object _currentPosition;
		_currentPosition = NumberFactory_FromLong(_numberFactory, -1);
		while((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentPosition, _position) == _greater)) != _false)
		{
			Number_Dec(_currentPosition);
			ListIterator_Prev(_self);
		}
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: ToPosition ended.")
	return toReturn;
}

Object ListIterator_FromPositionToPosition(Object _self, Object _positionFrom, Object _positionTo)
{
	DPUSHS ("ListIterator: FromPositionToPosition begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
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
	Object toReturn = _self;
	DPOPS ("ListIterator: FromPositionToPosition ended.")
	return toReturn;
}

Object ListIterator_SearchForward(Object _self, Object _object)
{
	DPUSHS ("ListIterator: SearchForward begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	while((Logic_Not(ListIterator_ThisEnd(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			break;
		}
		ListIterator_Next(_self);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: SearchForward ended.")
	return toReturn;
}

Object ListIterator_SearchBackward(Object _self, Object _object)
{
	DPUSHS ("ListIterator: SearchBackward begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	while((Logic_Not(ListIterator_ThisBegin(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			break;
		}
		ListIterator_Prev(_self);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: SearchBackward ended.")
	return toReturn;
}

Object ListIterator_SearchForwardOffset(Object _self, Object _object)
{
	DPUSHS ("ListIterator: SearchForwardOffset begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _position;
	_position = NumberFactory_FromLong(_numberFactory, 0);
	while((Logic_Not(ListIterator_ThisEnd(_self))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_self), _object) == _equal)) != _false)
		{
			Object toReturn = _position;
			DPOPS ("ListIterator: SearchForwardOffset ended.")
			return toReturn;
		}
		ListIterator_Next(_self);
		Number_Inc(_position);
	}
	Object toReturn = NumberFactory_FromLong(_numberFactory, -1);
	DPOPS ("ListIterator: SearchForwardOffset ended.")
	return toReturn;
}

Object ListIterator_ThisRemove(Object _self)
{
	DPUSHS ("ListIterator: ThisRemove begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_prev) = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_next) = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	Object_Release((((ListIterator) (_self->entity))->_node));
	Object toReturn = _self;
	DPOPS ("ListIterator: ThisRemove ended.")
	return toReturn;
}

Object ListIterator_PrevRemove(Object _self)
{
	DPUSHS ("ListIterator: PrevRemove begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _toRemove;
	_toRemove = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_next)->entity))->_prev) = (((ListNode) (_toRemove->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_prev)->entity))->_next) = (((ListNode) (_toRemove->entity))->_next);
	Object_Release(_toRemove);
	Object toReturn = _self;
	DPOPS ("ListIterator: PrevRemove ended.")
	return toReturn;
}

Object ListIterator_NextRemove(Object _self)
{
	DPUSHS ("ListIterator: NextRemove begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _toRemove;
	_toRemove = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_next)->entity))->_prev) = (((ListNode) (_toRemove->entity))->_prev);
	(((ListNode) ((((ListNode) (_toRemove->entity))->_prev)->entity))->_next) = (((ListNode) (_toRemove->entity))->_next);
	Object_Release(_toRemove);
	Object toReturn = _self;
	DPOPS ("ListIterator: NextRemove ended.")
	return toReturn;
}

Object ListIterator_ThisData(Object _self)
{
	DPUSHS ("ListIterator: ThisData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: ThisData ended.")
	return toReturn;
}

Object ListIterator_NextData(Object _self)
{
	DPUSHS ("ListIterator: NextData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_data);
	DPOPS ("ListIterator: NextData ended.")
	return toReturn;
}

Object ListIterator_PrevData(Object _self)
{
	DPUSHS ("ListIterator: PrevData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_data);
	DPOPS ("ListIterator: PrevData ended.")
	return toReturn;
}

Object ListIterator_LogicData(Object _self)
{
	DPUSHS ("ListIterator: LogicData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: LogicData ended.")
	return toReturn;
}

Object ListIterator_NumberData(Object _self)
{
	DPUSHS ("ListIterator: NumberData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: NumberData ended.")
	return toReturn;
}

Object ListIterator_ListData(Object _self)
{
	DPUSHS ("ListIterator: ListData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: ListData ended.")
	return toReturn;
}

Object ListIterator_ListMapData(Object _self)
{
	DPUSHS ("ListIterator: ListMapData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: ListMapData ended.")
	return toReturn;
}

Object ListIterator_CharData(Object _self)
{
	DPUSHS ("ListIterator: CharData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data);
	DPOPS ("ListIterator: CharData ended.")
	return toReturn;
}

Object ListIterator_ThisSetData(Object _self, Object _object)
{
	DPUSHS ("ListIterator: ThisSetData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_data), _object);
	Object toReturn = _self;
	DPOPS ("ListIterator: ThisSetData ended.")
	return toReturn;
}

Object ListIterator_PrevSetData(Object _self, Object _object)
{
	DPUSHS ("ListIterator: PrevSetData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_data), _object);
	Object toReturn = _self;
	DPOPS ("ListIterator: PrevSetData ended.")
	return toReturn;
}

Object ListIterator_NextSetData(Object _self, Object _object)
{
	DPUSHS ("ListIterator: NextSetData begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object_SetRetaining(&(((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_data), _object);
	Object toReturn = _self;
	DPOPS ("ListIterator: NextSetData ended.")
	return toReturn;
}

Object ListIterator_AddAfter(Object _self, Object _object)
{
	DPUSHS ("ListIterator: AddAfter begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _addingElement;
	_addingElement = ListNode_Create();
	Object_SetRetaining(&(((ListNode) (_addingElement->entity))->_data), _object);
	Object _savedNext;
	_savedNext = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next);
	(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next) = _addingElement;
	(((ListNode) (_addingElement->entity))->_prev) = (((ListIterator) (_self->entity))->_node);
	(((ListNode) (_addingElement->entity))->_next) = _savedNext;
	(((ListNode) (_savedNext->entity))->_prev) = _addingElement;
	Object toReturn = _self;
	DPOPS ("ListIterator: AddAfter ended.")
	return toReturn;
}

Object ListIterator_AddBefore(Object _self, Object _object)
{
	DPUSHS ("ListIterator: AddBefore begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _addingElement;
	_addingElement = ListNode_Create();
	Object_SetRetaining(&(((ListNode) (_addingElement->entity))->_data), _object);
	Object _savedPrev;
	_savedPrev = (((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev);
	(((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev) = _addingElement;
	(((ListNode) (_addingElement->entity))->_next) = (((ListIterator) (_self->entity))->_node);
	(((ListNode) (_addingElement->entity))->_prev) = _savedPrev;
	(((ListNode) (_savedPrev->entity))->_next) = _addingElement;
	Object toReturn = _self;
	DPOPS ("ListIterator: AddBefore ended.")
	return toReturn;
}

Object ListIterator_ThisBegin(Object _self)
{
	DPUSHS ("ListIterator: ThisBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev), _nothing) == _equal);
	DPOPS ("ListIterator: ThisBegin ended.")
	return toReturn;
}

Object ListIterator_ThisEnd(Object _self)
{
	DPUSHS ("ListIterator: ThisEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next), _nothing) == _equal);
	DPOPS ("ListIterator: ThisEnd ended.")
	return toReturn;
}

Object ListIterator_PrevBegin(Object _self)
{
	DPUSHS ("ListIterator: PrevBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_prev)->entity))->_prev), _nothing) == _equal);
	DPOPS ("ListIterator: PrevBegin ended.")
	return toReturn;
}

Object ListIterator_NextEnd(Object _self)
{
	DPUSHS ("ListIterator: NextEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (_self->entity))->_node)->entity))->_next)->entity))->_next), _nothing) == _equal);
	DPOPS ("ListIterator: NextEnd ended.")
	return toReturn;
}

Object ListIterator_AddListBefore(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListBefore begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_First(_list);
	while((Logic_Not(ListIterator_ThisEnd(_listIterator))) != _false)
	{
		ListIterator_AddBefore(_self, ListIterator_ThisData(_listIterator));
		ListIterator_Next(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListBefore ended.")
	return toReturn;
}

Object ListIterator_AddListAfter(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListAfter begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_Last(_list);
	while((Logic_Not(ListIterator_ThisBegin(_listIterator))) != _false)
	{
		ListIterator_AddAfter(_self, ListIterator_ThisData(_listIterator));
		ListIterator_Prev(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListAfter ended.")
	return toReturn;
}

Object ListIterator_AddListBeforeClonning(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListBeforeClonning begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_First(_list);
	while((Logic_Not(ListIterator_ThisEnd(_listIterator))) != _false)
	{
		ListIterator_AddBefore(_self, Object_Clone(ListIterator_ThisData(_listIterator)));
		ListIterator_Next(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListBeforeClonning ended.")
	return toReturn;
}

Object ListIterator_AddListAfterClonning(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListAfterClonning begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_Last(_list);
	while((Logic_Not(ListIterator_ThisBegin(_listIterator))) != _false)
	{
		ListIterator_AddAfter(_self, Object_Clone(ListIterator_ThisData(_listIterator)));
		ListIterator_Prev(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListAfterClonning ended.")
	return toReturn;
}

Object ListIterator_AddListBeforeDeepClonning(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListBeforeDeepClonning begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_First(_list);
	while((Logic_Not(ListIterator_ThisEnd(_listIterator))) != _false)
	{
		ListIterator_AddBefore(_self, Object_DeepClone(ListIterator_ThisData(_listIterator)));
		ListIterator_Next(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListBeforeDeepClonning ended.")
	return toReturn;
}

Object ListIterator_AddListAfterDeepClonning(Object _self, Object _list)
{
	DPUSHS ("ListIterator: AddListAfterDeepClonning begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	Object _listIterator;
	_listIterator = List_Last(_list);
	while((Logic_Not(ListIterator_ThisBegin(_listIterator))) != _false)
	{
		ListIterator_AddAfter(_self, Object_DeepClone(ListIterator_ThisData(_listIterator)));
		ListIterator_Prev(_listIterator);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: AddListAfterDeepClonning ended.")
	return toReturn;
}

Object ListIterator_RemoveCount(Object _self, Object _count)
{
	DPUSHS ("ListIterator: RemoveCount begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
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
	Object toReturn = _self;
	DPOPS ("ListIterator: RemoveCount ended.")
	return toReturn;
}

Object ListIterator_StringSkipSpace(Object _self)
{
	DPUSHS ("ListIterator: StringSkipSpace begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	while((Char_IsSpace(ListIterator_CharData(_self))) != _false)
	{
		ListIterator_Next(_self);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: StringSkipSpace ended.")
	return toReturn;
}

Object ListIterator_StringSkipWhiteSpace(Object _self)
{
	DPUSHS ("ListIterator: StringSkipWhiteSpace begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==   807984642922801280ulll )
	while((Char_IsWhiteSpace(ListIterator_CharData(_self))) != _false)
	{
		ListIterator_Next(_self);
	}
	Object toReturn = _self;
	DPOPS ("ListIterator: StringSkipWhiteSpace ended.")
	return toReturn;
}
