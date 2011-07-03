#include "internals/basics.h"
#include "internals/List/imports.h"


Object List_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("List: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct List));
	_self->gid =  3732711262168886272ull;
	Object_SetComparator(_self, &List_Compare);
	Object_SetDestructor(_self, &List_Destroy);
	Object_SetCloner(_self, &List_Clone);
	Object_SetDeepCloner(_self, &List_DeepClone);
	((List) (_self->entity))->_iterator = _nil;
	((List) (_self->entity))->_head = _nil;
	((List) (_self->entity))->_tail = _nil;
	_self = List_Init(_self);
	DPOPS ("List: Create ended.")
	return _self;
}

Object List_Init(Object _self)
{
	DPUSHS ("List: Init begined.")
	ASSERT_C ( "List:Init --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	(((List) (_self->entity))->_head) = ListNode_Create();
	(((List) (_self->entity))->_tail) = ListNode_Create();
	(((ListNode) ((((List) (_self->entity))->_head)->entity))->_next) = (((List) (_self->entity))->_tail);
	(((ListNode) ((((List) (_self->entity))->_tail)->entity))->_prev) = (((List) (_self->entity))->_head);
	(((ListNode) ((((List) (_self->entity))->_tail)->entity))->_next) = (((ListNode) ((((List) (_self->entity))->_head)->entity))->_prev) = _nil;
	(((List) (_self->entity))->_iterator) = List_SystemIterator(_self);
	Object toReturn = _self;
	DPOPS ("List: Init ended.")
	return toReturn;
}

Object List_Destroy(Object _self)
{
	DPUSHS ("List: Destroy begined.")
	ASSERT_C ( "List:Destroy --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
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
	Object toReturn = Object_Destroy(_self);
	DPOPS ("List: Destroy ended.")
	return toReturn;
}

Object List_Clone(Object _self)
{
	DPUSHS ("List: Clone begined.")
	ASSERT_C ( "List:Clone --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _list;
	_list = List_Create();
	ListIterator_ToEnd((((List) (_list->entity))->_iterator));
	ListIterator_AddListAfter((((List) (_list->entity))->_iterator), _self);
	ListIterator_Hide((((List) (_list->entity))->_iterator));
	Object toReturn = _list;
	DPOPS ("List: Clone ended.")
	return toReturn;
}

Object List_DeepClone(Object _self)
{
	DPUSHS ("List: DeepClone begined.")
	ASSERT_C ( "List:DeepClone --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _list;
	_list = List_Create();
	ListIterator_ToEnd((((List) (_list->entity))->_iterator));
	ListIterator_AddListAfterDeepClonning((((List) (_list->entity))->_iterator), _self);
	ListIterator_Hide((((List) (_list->entity))->_iterator));
	Object toReturn = _list;
	DPOPS ("List: DeepClone ended.")
	return toReturn;
}

Object List_Compare(Object _self, Object _list)
{
	DPUSHS ("List: Compare begined.")
	ASSERT_C ( "List:Compare --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:Compare --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
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
				Object toReturn = _equal;
				DPOPS ("List: Compare ended.")
				return toReturn;
			}
			else
			{
				Object toReturn = _less;
				DPOPS ("List: Compare ended.")
				return toReturn;
			}
		}
		if((ListIterator_ThisEnd(_listIterator)) != _false)
		{
			Object toReturn = _greater;
			DPOPS ("List: Compare ended.")
			return toReturn;
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
			Object toReturn = _candidateForReturning;
			DPOPS ("List: Compare ended.")
			return toReturn;
		}
	}
}

Object List_Clean(Object _self)
{
	DPUSHS ("List: Clean begined.")
	ASSERT_C ( "List:Clean --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
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
	Object toReturn = _self;
	DPOPS ("List: Clean ended.")
	return toReturn;
}

Object List_PushFront(Object _self, Object _object)
{
	DPUSHS ("List: PushFront begined.")
	ASSERT_C ( "List:PushFront --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: PushFront ended.")
	return toReturn;
}

Object List_PushBack(Object _self, Object _object)
{
	DPUSHS ("List: PushBack begined.")
	ASSERT_C ( "List:PushBack --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_AddAfter((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: PushBack ended.")
	return toReturn;
}

Object List_PushSorted(Object _self, Object _object)
{
	DPUSHS ("List: PushSorted begined.")
	ASSERT_C ( "List:PushSorted --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	while((Logic_And(Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator))), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData((((List) (_self->entity))->_iterator)), _object) == _less))) != _false)
	{
		ListIterator_Next((((List) (_self->entity))->_iterator));
	}
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: PushSorted ended.")
	return toReturn;
}

Object List_PeekFront(Object _self)
{
	DPUSHS ("List: PeekFront begined.")
	ASSERT_C ( "List:PeekFront --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: PeekFront ended.")
	return def;
}

Object List_PeekBack(Object _self)
{
	DPUSHS ("List: PeekBack begined.")
	ASSERT_C ( "List:PeekBack --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: PeekBack ended.")
	return def;
}

Object List_PopFront(Object _self)
{
	DPUSHS ("List: PopFront begined.")
	ASSERT_C ( "List:PopFront --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = Object_Autorelease(Object_Retain(ListIterator_ThisData((((List) (_self->entity))->_iterator))));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: PopFront ended.")
	return def;
}

Object List_PopBack(Object _self)
{
	DPUSHS ("List: PopBack begined.")
	ASSERT_C ( "List:PopBack --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	Object def = Object_Autorelease(Object_Retain(ListIterator_ThisData((((List) (_self->entity))->_iterator))));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: PopBack ended.")
	return def;
}

Object List_RemoveFront(Object _self)
{
	DPUSHS ("List: RemoveFront begined.")
	ASSERT_C ( "List:RemoveFront --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveFront ended.")
	return toReturn;
}

Object List_RemoveBack(Object _self)
{
	DPUSHS ("List: RemoveBack begined.")
	ASSERT_C ( "List:RemoveBack --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveBack ended.")
	return toReturn;
}

Object List_PushBackIfAbsent(Object _self, Object _object)
{
	DPUSHS ("List: PushBackIfAbsent begined.")
	ASSERT_C ( "List:PushBackIfAbsent --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData((((List) (_self->entity))->_iterator)), _object) == _equal)) != _false)
		{
			ListIterator_Hide((((List) (_self->entity))->_iterator));
			Object toReturn = _self;
			DPOPS ("List: PushBackIfAbsent ended.")
			return toReturn;
		}
		ListIterator_Next((((List) (_self->entity))->_iterator));
	}
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: PushBackIfAbsent ended.")
	return toReturn;
}

Object List_AddAfterPosition(Object _self, Object _position, Object _object)
{
	DPUSHS ("List: AddAfterPosition begined.")
	ASSERT_C ( "List:AddAfterPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:AddAfterPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_AddAfter((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: AddAfterPosition ended.")
	return toReturn;
}

Object List_AddBeforePosition(Object _self, Object _position, Object _object)
{
	DPUSHS ("List: AddBeforePosition begined.")
	ASSERT_C ( "List:AddBeforePosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:AddBeforePosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_AddBefore((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: AddBeforePosition ended.")
	return toReturn;
}

Object List_ObjectAtPosition(Object _self, Object _position)
{
	DPUSHS ("List: ObjectAtPosition begined.")
	ASSERT_C ( "List:ObjectAtPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:ObjectAtPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	Object def = ListIterator_ThisData((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: ObjectAtPosition ended.")
	return def;
}

Object List_ObjectAtPositionIfExists(Object _self, Object _position)
{
	DPUSHS ("List: ObjectAtPositionIfExists begined.")
	ASSERT_C ( "List:ObjectAtPositionIfExists --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:ObjectAtPositionIfExists --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_self), _position) == _greater)) != _false)
	{
		Object toReturn = List_ObjectAtPosition(_self, _position);
		DPOPS ("List: ObjectAtPositionIfExists ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = _nil;
		DPOPS ("List: ObjectAtPositionIfExists ended.")
		return toReturn;
	}
}

Object List_RemoveObjectAtPosition(Object _self, Object _position)
{
	DPUSHS ("List: RemoveObjectAtPosition begined.")
	ASSERT_C ( "List:RemoveObjectAtPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:RemoveObjectAtPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveObjectAtPosition ended.")
	return toReturn;
}

Object List_ReplaceAtPositionWithObject(Object _self, Object _position, Object _object)
{
	DPUSHS ("List: ReplaceAtPositionWithObject begined.")
	ASSERT_C ( "List:ReplaceAtPositionWithObject --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:ReplaceAtPositionWithObject --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToPosition((((List) (_self->entity))->_iterator), _position);
	ListIterator_ThisSetData((((List) (_self->entity))->_iterator), _object);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: ReplaceAtPositionWithObject ended.")
	return toReturn;
}

Object List_Contains(Object _self, Object _object)
{
	DPUSHS ("List: Contains begined.")
	ASSERT_C ( "List:Contains --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	Object def = Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: Contains ended.")
	return def;
}

Object List_RemoveFirst(Object _self, Object _object)
{
	DPUSHS ("List: RemoveFirst begined.")
	ASSERT_C ( "List:RemoveFirst --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveFirst ended.")
	return toReturn;
}

Object List_RemoveFirstExactlySame(Object _self, Object _object)
{
	DPUSHS ("List: RemoveFirstExactlySame begined.")
	ASSERT_C ( "List:RemoveFirstExactlySame --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForwardExactlySame((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveFirstExactlySame ended.")
	return toReturn;
}

Object List_RemoveFirstWithConfirmation(Object _self, Object _object)
{
	DPUSHS ("List: RemoveFirstWithConfirmation begined.")
	ASSERT_C ( "List:RemoveFirstWithConfirmation --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
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
	Object toReturn = _confirmation;
	DPOPS ("List: RemoveFirstWithConfirmation ended.")
	return toReturn;
}

Object List_RemoveLast(Object _self, Object _object)
{
	DPUSHS ("List: RemoveLast begined.")
	ASSERT_C ( "List:RemoveLast --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_SearchBackward((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisBegin((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveLast ended.")
	return toReturn;
}

Object List_RemoveLastExactlySame(Object _self, Object _object)
{
	DPUSHS ("List: RemoveLastExactlySame begined.")
	ASSERT_C ( "List:RemoveLastExactlySame --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_SearchBackwardExactlySame((((List) (_self->entity))->_iterator), _object);
	if((Logic_Not(ListIterator_ThisBegin((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveLastExactlySame ended.")
	return toReturn;
}

Object List_RemoveLastWithConfirmation(Object _self, Object _object)
{
	DPUSHS ("List: RemoveLastWithConfirmation begined.")
	ASSERT_C ( "List:RemoveLastWithConfirmation --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
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
	Object toReturn = _confirmation;
	DPOPS ("List: RemoveLastWithConfirmation ended.")
	return toReturn;
}

Object List_RemoveEvery(Object _self, Object _object)
{
	DPUSHS ("List: RemoveEvery begined.")
	ASSERT_C ( "List:RemoveEvery --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		ListIterator_ThisRemove((((List) (_self->entity))->_iterator));
		ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	}
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: RemoveEvery ended.")
	return toReturn;
}

Object List_RemoveEveryWithConfirmation(Object _self, Object _object)
{
	DPUSHS ("List: RemoveEveryWithConfirmation begined.")
	ASSERT_C ( "List:RemoveEveryWithConfirmation --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
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
	Object toReturn = _confirmation;
	DPOPS ("List: RemoveEveryWithConfirmation ended.")
	return toReturn;
}

Object List_Last(Object _self)
{
	DPUSHS ("List: Last begined.")
	ASSERT_C ( "List:Last --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(_iterator, _self, (((ListNode) ((((List) (_self->entity))->_tail)->entity))->_prev));
	Object toReturn = _iterator;
	DPOPS ("List: Last ended.")
	return toReturn;
}

Object List_First(Object _self)
{
	DPUSHS ("List: First begined.")
	ASSERT_C ( "List:First --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(_iterator, _self, (((ListNode) ((((List) (_self->entity))->_head)->entity))->_next));
	Object toReturn = _iterator;
	DPOPS ("List: First ended.")
	return toReturn;
}

Object List_SystemIterator(Object _self)
{
	DPUSHS ("List: SystemIterator begined.")
	ASSERT_C ( "List:SystemIterator --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = ListIterator_Create();
	ListIterator_SystemInitWithListAndNode(_iterator, _self, _nil);
	Object toReturn = _iterator;
	DPOPS ("List: SystemIterator ended.")
	return toReturn;
}

Object List_SystemFirst(Object _self)
{
	DPUSHS ("List: SystemFirst begined.")
	ASSERT_C ( "List:SystemFirst --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = ListIterator_Create();
	ListIterator_InitWithListAndNode(_iterator, _self, (((ListNode) ((((List) (_self->entity))->_head)->entity))->_next));
	Object toReturn = _iterator;
	DPOPS ("List: SystemFirst ended.")
	return toReturn;
}

Object List_ListMapAtPosition(Object _self, Object _position)
{
	DPUSHS ("List: ListMapAtPosition begined.")
	ASSERT_C ( "List:ListMapAtPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:ListMapAtPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	Object toReturn = List_ObjectAtPosition(_self, _position);
	DPOPS ("List: ListMapAtPosition ended.")
	return toReturn;
}

Object List_Search(Object _self, Object _object)
{
	DPUSHS ("List: Search begined.")
	ASSERT_C ( "List:Search --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object _list;
	_list = Object_Autorelease(List_Create());
	ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	while((Logic_Not(ListIterator_ThisEnd((((List) (_self->entity))->_iterator)))) != _false)
	{
		List_PushBack(_list, Object_TempClone((((List) (_self->entity))->_iterator)));
		ListIterator_SearchForward((((List) (_self->entity))->_iterator), _object);
	}
	Object toReturn = _list;
	DPOPS ("List: Search ended.")
	return toReturn;
}

Object List_IteratorFromPosition(Object _self, Object _position)
{
	DPUSHS ("List: IteratorFromPosition begined.")
	ASSERT_C ( "List:IteratorFromPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:IteratorFromPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
	Object toReturn = ListIterator_ToPosition(List_First(_self), _position);
	DPOPS ("List: IteratorFromPosition ended.")
	return toReturn;
}

Object List_CreatingIteratorFromPosition(Object _self, Object _position)
{
	DPUSHS ("List: CreatingIteratorFromPosition begined.")
	ASSERT_C ( "List:CreatingIteratorFromPosition --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:CreatingIteratorFromPosition --- Checking for correct parameter type failed at parameter _position.", _position->gid == 15425740279749906432ull || _position == _nil )
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
	Object toReturn = _iterator;
	DPOPS ("List: CreatingIteratorFromPosition ended.")
	return toReturn;
}

Object List_SearchPositions(Object _self, Object _object)
{
	DPUSHS ("List: SearchPositions begined.")
	ASSERT_C ( "List:SearchPositions --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
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
	Object toReturn = _list;
	DPOPS ("List: SearchPositions ended.")
	return toReturn;
}

Object List_SublistBetweenPositions(Object _self, Object _positionFrom, Object _positionTo)
{
	DPUSHS ("List: SublistBetweenPositions begined.")
	ASSERT_C ( "List:SublistBetweenPositions --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:SublistBetweenPositions --- Checking for correct parameter type failed at parameter _positionFrom.", _positionFrom->gid == 15425740279749906432ull || _positionFrom == _nil )
	ASSERT_C ( "List:SublistBetweenPositions --- Checking for correct parameter type failed at parameter _positionTo.", _positionTo->gid == 15425740279749906432ull || _positionTo == _nil )
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
	Object toReturn = _list;
	DPOPS ("List: SublistBetweenPositions ended.")
	return toReturn;
}

Object List_SublistBetweenIterators(Object _self, Object _positionFrom, Object _positionTo)
{
	DPUSHS ("List: SublistBetweenIterators begined.")
	ASSERT_C ( "List:SublistBetweenIterators --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:SublistBetweenIterators --- Checking for correct parameter type failed at parameter _positionFrom.", _positionFrom->gid ==   807984642922801280ull || _positionFrom == _nil )
	ASSERT_C ( "List:SublistBetweenIterators --- Checking for correct parameter type failed at parameter _positionTo.", _positionTo->gid ==   807984642922801280ull || _positionTo == _nil )
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
	Object toReturn = _list;
	DPOPS ("List: SublistBetweenIterators ended.")
	return toReturn;
}

Object List_Size(Object _self)
{
	DPUSHS ("List: Size begined.")
	ASSERT_C ( "List:Size --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
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
	Object toReturn = _toReturn;
	DPOPS ("List: Size ended.")
	return toReturn;
}

Object List_Empty(Object _self)
{
	DPUSHS ("List: Empty begined.")
	ASSERT_C ( "List:Empty --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToBegin((((List) (_self->entity))->_iterator));
	Object def = ListIterator_ThisEnd((((List) (_self->entity))->_iterator));
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	DPOPS ("List: Empty ended.")
	return def;
}

Object List_ConcatenateRight(Object _self, Object _list)
{
	DPUSHS ("List: ConcatenateRight begined.")
	ASSERT_C ( "List:ConcatenateRight --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:ConcatenateRight --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	ASSERT_Q ( "Список занят. Итератор не на месте.", ListIterator_Hidden((((List) (_self->entity))->_iterator)) )
	ListIterator_ToEnd((((List) (_self->entity))->_iterator));
	ListIterator_AddListAfter((((List) (_self->entity))->_iterator), _list);
	ListIterator_Hide((((List) (_self->entity))->_iterator));
	Object toReturn = _self;
	DPOPS ("List: ConcatenateRight ended.")
	return toReturn;
}

Object List_Set(Object _self, Object _list)
{
	DPUSHS ("List: Set begined.")
	ASSERT_C ( "List:Set --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	ASSERT_C ( "List:Set --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	List_Clean(_self);
	List_ConcatenateRight(_self, _list);
	Object toReturn = _self;
	DPOPS ("List: Set ended.")
	return toReturn;
}

Object List_SortInPlace(Object _self)
{
	DPUSHS ("List: SortInPlace begined.")
	ASSERT_C ( "List:SortInPlace --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object toReturn = _self;
	DPOPS ("List: SortInPlace ended.")
	return toReturn;
}

Object List_PrintLn(Object _self)
{
	DPUSHS ("List: PrintLn begined.")
	ASSERT_C ( "List:PrintLn --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Console_WriteLnString(_console, _self);
	Object toReturn = _self;
	DPOPS ("List: PrintLn ended.")
	return toReturn;
}

Object List_Print(Object _self)
{
	DPUSHS ("List: Print begined.")
	ASSERT_C ( "List:Print --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Console_WriteString(_console, _self);
	Object toReturn = _self;
	DPOPS ("List: Print ended.")
	return toReturn;
}

Object List_LooksLikeString(Object _self)
{
	DPUSHS ("List: LooksLikeString begined.")
	ASSERT_C ( "List:LooksLikeString --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = List_First(_self);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, ListIterator_ThisData(_iterator)->gid == 15931002582760847360ull)) != _false)
		{
			Object toReturn = _no;
			DPOPS ("List: LooksLikeString ended.")
			return toReturn;
		}
		ListIterator_Next(_iterator);
	}
	Object toReturn = _yes;
	DPOPS ("List: LooksLikeString ended.")
	return toReturn;
}

Object List_LooksLikeUID(Object _self)
{
	DPUSHS ("List: LooksLikeUID begined.")
	ASSERT_C ( "List:LooksLikeUID --- Checking for correct object type failed.", _self->gid ==  3732711262168886272ull )
	Object _iterator;
	_iterator = List_First(_self);
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		Object toReturn = _no;
		DPOPS ("List: LooksLikeUID ended.")
		return toReturn;
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '<')) != _equal)) != _false)
	{
		Object toReturn = _no;
		DPOPS ("List: LooksLikeUID ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	while((Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '0')) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '9')) != _greater))) != _false)
	{
		ListIterator_Next(_iterator);
	}
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		Object toReturn = _no;
		DPOPS ("List: LooksLikeUID ended.")
		return toReturn;
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '>')) != _equal)) != _false)
	{
		Object toReturn = _no;
		DPOPS ("List: LooksLikeUID ended.")
		return toReturn;
	}
	if((Logic_Not(ListIterator_NextEnd(_iterator))) != _false)
	{
		Object toReturn = _no;
		DPOPS ("List: LooksLikeUID ended.")
		return toReturn;
	}
	Object toReturn = _yes;
	DPOPS ("List: LooksLikeUID ended.")
	return toReturn;
}
