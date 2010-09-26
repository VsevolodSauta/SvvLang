#include "internals/basics.h"
#include "internals/ListIterator/imports.h"

Object ListIterator_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct ListIterator));
	Object_SetComparator(toReturn, &ListIterator_Compare);
	Object_SetDestructor(toReturn, &ListIterator_Destroy);
	Object_SetCloner(toReturn, &ListIterator_Clone);
	return toReturn;
}


Object ListIterator_Compare(Object self, Object iterator)
{
	return Object_Compare((((ListIterator) (self->entity))->node), (((ListIterator) (iterator->entity))->node));
}

Object ListIterator_Destroy(Object self)
{
	Object_Release((((ListIterator) (self->entity))->node));
	Object_Release((((ListIterator) (self->entity))->list));
	return Object_Destroy(self);
}

Object ListIterator_Clone(Object self)
{
	Object toReturn;
	toReturn = ListIterator_Create();
	(((ListIterator) (toReturn->entity))->list) = (((ListIterator) (self->entity))->list);
	(((ListIterator) (toReturn->entity))->node) = (((ListIterator) (self->entity))->node);
	Object_Retain((((ListIterator) (toReturn->entity))->list));
	Object_Retain((((ListIterator) (toReturn->entity))->node));
	return toReturn;
}

Object ListIterator_InitWithNodeAndList(Object self, Object list, Object node)
{
	Object_Retain(list);
	Object_Retain(node);
	(((ListIterator) (self->entity))->list) = list;
	(((ListIterator) (self->entity))->node) = node;
	return self;
}

Object ListIterator_ResetNode(Object self, Object node)
{
	Object_Retain(node);
	Object_Release((((ListIterator) (self->entity))->node));
	(((ListIterator) (self->entity))->node) = node;
	return self;
}

Object ListIterator_Hide(Object self)
{
	return ListIterator_ResetNode(self, (((List) ((((ListIterator) (self->entity))->list)->entity))->head));
}

Object ListIterator_Next(Object self)
{
	return ListIterator_ResetNode(self, (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next));
}

Object ListIterator_Prev(Object self)
{
	return ListIterator_ResetNode(self, (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev));
}

Object ListIterator_ToBegin(Object self)
{
	return ListIterator_ResetNode(self, (((ListNode) ((((List) ((((ListIterator) (self->entity))->list)->entity))->head)->entity))->next));
}

Object ListIterator_ToEnd(Object self)
{
	return ListIterator_ResetNode(self, (((ListNode) ((((List) ((((ListIterator) (self->entity))->list)->entity))->tail)->entity))->prev));
}

Object ListIterator_ToPosition(Object self, Object position)
{
	if(Object_Compare(position, NumberFactory_FromLong(numberFactory, 0)) != less)
	{
		ListIterator_ToBegin(self);
		Object currentPosition;
		currentPosition = NumberFactory_FromLong(numberFactory, 0);
		while(Object_Compare(currentPosition, position) == less)
		{
			ListIterator_Next(self);
			Number_Inc(position);
		}
		return self;
	}
	ListIterator_ToEnd(self);
	Object currentPosition;
	currentPosition = NumberFactory_FromLong(numberFactory, -1);
	while(Object_Compare(currentPosition, position) == greater)
	{
		Number_Dec(currentPosition);
		ListIterator_Prev(self);
	}
	return self;
}

Object ListIterator_FromPositionToPosition(Object self, Object positionFrom, Object positionTo)
{
	Object quantity;
	quantity = Number_Sub(positionTo, positionFrom);
	while(Object_Compare(quantity, NumberFactory_FromLong(numberFactory, 0)) == less)
	{
		ListIterator_Prev(self);
		Object_Inc(quantity);
	}
	while(Object_Compare(quantity, NumberFactory_FromLong(numberFactory, 0)) == greater)
	{
		ListIterator_Next(self);
		Object_Dec(quantity);
	}
	return self;
}

Object ListIterator_SearchForward(Object self, Object object)
{
	while(ListIterator_ThisEnd(self) == false)
	{
		if(Object_Compare(ListIterator_ThisData(self), object) == equal)
		{
			break;
		}
		ListIterator_Next(self);
	}
	return self;
}

Object ListIterator_SearchForwardOffset(Object self, Object object)
{
	Object toReturn;
	toReturn = NumberFactory_FromLong(numberFactory, 0);
	while(ListIterator_ThisEnd(self) == false)
	{
		if(Object_Compare(ListIterator_ThisData(self), object) == equal)
		{
			Object position;
			return position;
		}
		ListIterator_Next(self);
		Object position;
		Object_Inc(position);
	}
	return NumberFactory_FromLong(numberFactory, -1);
}

Object ListIterator_ThisRemove(Object self)
{
	(((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next)->entity))->prev) = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next);
	(((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev)->entity))->next) = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev);
	Object_Release((((ListIterator) (self->entity))->node));
	return ListIterator_Next(self);
}

Object ListIterator_PrevRemove(Object self)
{
	Object toRemove;
	toRemove = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next);
	(((ListNode) ((((ListNode) (toRemove->entity))->next)->entity))->prev) = (((ListNode) (toRemove->entity))->prev);
	(((ListNode) ((((ListNode) (toRemove->entity))->prev)->entity))->next) = (((ListNode) (toRemove->entity))->next);
	Object_Release(toRemove);
	return self;
}

Object ListIterator_NextRemove(Object self)
{
	Object toRemove;
	toRemove = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev);
	(((ListNode) ((((ListNode) (toRemove->entity))->next)->entity))->prev) = (((ListNode) (toRemove->entity))->prev);
	(((ListNode) ((((ListNode) (toRemove->entity))->prev)->entity))->next) = (((ListNode) (toRemove->entity))->next);
	Object_Release(toRemove);
	return self;
}

Object ListIterator_ThisData(Object self)
{
	return (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->data);
}

Object ListIterator_NextData(Object self)
{
	return (((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next)->entity))->data);
}

Object ListIterator_PrevData(Object self)
{
	return (((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev)->entity))->data);
}

Object ListIterator_ThisSetData(Object self, Object object)
{
	Object_Retain(object);
	Object_Release((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->data));
	(((ListNode) ((((ListIterator) (self->entity))->node)->entity))->data) = object;
	return self;
}

Object ListIterator_PrevSetData(Object self, Object object)
{
	Object_Retain(object);
	Object_Release((((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev)->entity))->data));
	(((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev)->entity))->data) = object;
	return self;
}

Object ListIterator_NextSetData(Object self, Object object)
{
	Object_Retain(object);
	Object_Release((((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next)->entity))->data));
	(((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next)->entity))->data) = object;
	return self;
}

Object ListIterator_AddAfter(Object self, Object object)
{
	Object_Retain(object);
	Object addingElement;
	addingElement = ListNode_Create();
	(((ListNode) (addingElement->entity))->data) = object;
	Object savedNext;
	savedNext = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next);
	(((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next) = addingElement;
	(((ListNode) (addingElement->entity))->prev) = (((ListIterator) (self->entity))->node);
	(((ListNode) (addingElement->entity))->next) = savedNext;
	(((ListNode) (savedNext->entity))->prev) = addingElement;
	return self;
}

Object ListIterator_AddBefore(Object self, Object object)
{
	Object_Retain(object);
	Object addingElement;
	addingElement = ListNode_Create();
	(((ListNode) (addingElement->entity))->data) = object;
	Object savedPrev;
	savedPrev = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev);
	(((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev) = addingElement;
	(((ListNode) (addingElement->entity))->next) = (((ListIterator) (self->entity))->node);
	(((ListNode) (addingElement->entity))->prev) = savedPrev;
	(((ListNode) (savedPrev->entity))->next) = addingElement;
	return self;
}

Object ListIterator_ThisBegin(Object self)
{
	Object nothing;
	return LogicFactory_FromLong(logicFactory, Object_Compare((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev), nothing) == equal);
}

Object ListIterator_ThisEnd(Object self)
{
	Object nothing;
	return LogicFactory_FromLong(logicFactory, Object_Compare((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next), nothing) == equal);
}

Object ListIterator_PrevBegin(Object self)
{
	Object nothing;
	return LogicFactory_FromLong(logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev)->entity))->prev), nothing) == equal);
}

Object ListIterator_NextEnd(Object self)
{
	Object nothing;
	return LogicFactory_FromLong(logicFactory, Object_Compare((((ListNode) ((((ListNode) ((((ListIterator) (self->entity))->node)->entity))->next)->entity))->next), nothing) == equal);
}

Object ListIterator_AddListBefore(Object self, Object list)
{
	Object listIterator;
	listIterator = List_First(list);
	while(ListIterator_ThisEnd(listIterator) == false)
	{
		ListIterator_AddBefore(self, ListIterator_ThisData(listIterator));
		ListIterator_Next(listIterator);
	}
	return self;
}

Object ListIterator_AddListAfter(Object self, Object list)
{
	Object listIterator;
	listIterator = List_Last(list);
	while(ListIterator_ThisBegin(listIterator) == false)
	{
		ListIterator_AddAfter(self, ListIterator_ThisData(listIterator));
		ListIterator_Prev(listIterator);
	}
	return self;
}

Object ListIterator_RemoveCount(Object self, Object count)
{
	Object savedPrev;
	savedPrev = (((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev);
	Object deletedCount;
	deletedCount = NumberFactory_FromLong(numberFactory, 0);
	while(Object_Compare(deletedCount, count) == less)
	{
		ListNode_release((((ListIterator) (self->entity))->node));
		ListIterator_Next(self);
		Number_Inc(deletedCount);
	}
	(((ListNode) ((((ListIterator) (self->entity))->node)->entity))->prev) = savedPrev;
	(((ListNode) (savedPrev->entity))->next) = (((ListIterator) (self->entity))->node);
	return self;
}

