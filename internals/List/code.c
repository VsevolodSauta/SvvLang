#include "internals/basics.h"
#include "internals/List/imports.h"



Object List_Init(Object self)
{
	(((List) (self->entity))->head) = ListNode_Create();
	(((List) (self->entity))->tail) = ListNode_Create();
	(((ListNode) ((((List) (self->entity))->head)->entity))->next) = (((List) (self->entity))->tail);
	(((ListNode) ((((List) (self->entity))->tail)->entity))->prev) = (((List) (self->entity))->head);
	Object nil;
	(((ListNode) ((((List) (self->entity))->tail)->entity))->next) = (((ListNode) ((((List) (self->entity))->head)->entity))->prev) = nil;
	(((List) (self->entity))->iterator) = List_SystemIterator(self);
	return self;
}

Object List_Destroy(Object self)
{
	Object node;
	node = (((List) (self->entity))->head);
	Object nil;
	while(Object_Compare(node, nil) != equal)
	{
		Object nextNode;
		nextNode = (((ListNode) (node->entity))->next);
		Object_Release(node);
		node = nextNode;
	}
	return Object_Destroy(self);
}

Object List_Clone(Object self)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	Object list;
	list = List_Create();
	while(ListIterator_ThisEnd((((List) (self->entity))->iterator)) == false)
	{
		List_PushBack(list, ListIterator_ThisData((((List) (self->entity))->iterator)));
		ListIterator_Next((((List) (self->entity))->iterator));
	}
	ListIterator_Hide((((List) (self->entity))->iterator));
	return list;
}

Object List_Compare(Object self, Object list)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	ListIterator_ToBegin((((List) (list->entity))->iterator));
	while(1)
	{
		if(ListIterator_ThisEnd((((List) (self->entity))->iterator)) != false)
		{
			if(ListIterator_ThisEnd((((List) (list->entity))->iterator)) != false)
			{
				Object equal;
				return equal;
			}
			else
			{
				Object less;
				return less;
			}
		}
		if(ListIterator_ThisEnd((((List) (list->entity))->iterator)) != false)
		{
			Object greater;
			return greater;
		}
		Object candidateForReturning;
		candidateForReturning = Object_Compare(ListIterator_ThisData((((List) (self->entity))->iterator)), ListIterator_ThisData((((List) (list->entity))->iterator)));
		Object equal;
		if(Object_Compare(candidateForReturning, equal) == equal)
		{
			ListIterator_Next((((List) (list->entity))->iterator));
			ListIterator_Next((((List) (self->entity))->iterator));
		}
		else
		{
			return candidateForReturning;
		}
	}
}

Object List_Clean(Object self)
{
	Object node;
	node = (((ListNode) ((((List) (self->entity))->head)->entity))->next);
	while(Object_Compare(node, (((List) (self->entity))->tail)) != equal)
	{
		Object nextNode;
		nextNode = (((ListNode) (node->entity))->next);
		Object_Release(node);
		node = nextNode;
	}
	(((ListNode) ((((List) (self->entity))->head)->entity))->next) = (((List) (self->entity))->tail);
	(((ListNode) ((((List) (self->entity))->tail)->entity))->prev) = (((List) (self->entity))->head);
	return self;
}

Object List_PushBack(Object self, Object object)
{
	ListIterator_ToEnd((((List) (self->entity))->iterator));
	ListIterator_AddAfter((((List) (self->entity))->iterator), object);
	ListIterator_Hide((((List) (self->entity))->iterator));
	return self;
}

Object List_PushFront(Object self, Object object)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	ListIterator_AddBefore((((List) (self->entity))->iterator), object);
	List_Hide(self);
	return self;
}

Object List_AddAfterPosition(Object self, Object position, Object object)
{
	ListIterator_ToPosition((((List) (self->entity))->iterator), position);
	ListIterator_AddAfter((((List) (self->entity))->iterator), object);
	ListIterator_Hide((((List) (self->entity))->iterator));
	return self;
}

Object List_AddBeforePosition(Object self, Object position, Object object)
{
	ListIterator_ToPosition((((List) (self->entity))->iterator), position);
	ListIterator_AddBefore((((List) (self->entity))->iterator), object);
	ListIterator_Hide((((List) (self->entity))->iterator));
	return self;
}

Object List_RemoveFirst(Object self, Object object)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	ListIterator_SearchForward((((List) (self->entity))->iterator), object);
	if(ListIterator_ThisEnd((((List) (self->entity))->iterator)) == false)
	{
		ListIterator_ThisRemove((((List) (self->entity))->iterator));
	}
	ListIterator_Hide((((List) (self->entity))->iterator));
	return self;
}

Object List_Last(Object self)
{
	Object iterator;
	iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(iterator, self, (((ListNode) ((((List) (self->entity))->tail)->entity))->prev));
	return iterator;
}

Object List_First(Object self)
{
	Object iterator;
	iterator = Object_Autorelease(ListIterator_Create());
	ListIterator_InitWithListAndNode(iterator, self, (((ListNode) ((((List) (self->entity))->head)->entity))->next));
	return iterator;
}

Object List_SystemIterator(Object self)
{
	Object iterator;
	iterator = ListIterator_Create();
	ListIterator_InitWithListAndNode(iterator, self, (((List) (self->entity))->head));
	return iterator;
}

Object List_DataFromPosition(Object self, Object position)
{
	ListIterator_ToPosition((((List) (self->entity))->iterator), position);
	Object def = List_ThisData(self);
	ListIterator_Hide((((List) (self->entity))->iterator));
	return def;
}

Object List_Search(Object self, Object object)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	Object list;
	list = Object_Autorelease(List_Create());
	ListIterator_SearchForward((((List) (self->entity))->iterator), object);
	while(ListIterator_ThisEnd((((List) (self->entity))->iterator)) == false)
	{
		List_PushBack(list, Object_TempClone((((List) (self->entity))->iterator)));
		ListIterator_SearchForward((((List) (self->entity))->iterator), object);
	}
	return list;
}

Object List_IteratorFromPosition(Object self, Object position)
{
	return ListIterator_ToPosition(List_First(self), position);
}

Object List_CreatingIteratorFromPosition(Object self, Object position)
{
	Object iterator;
	iterator = List_First(self);
	Object currentPosition;
	currentPosition = NumberFactory_FromLong(numberFactory, 0);
	while(Object_Compare(currentPosition, position) != greater)
	{
		Number_Inc(currentPosition);
		if(ListIterator_ThisEnd(iterator) != false)
		{
			Object nil;
			ListIterator_AddBefore(iterator, nil);
		}
		else
		{
			ListIterator_Next(iterator);
		}
	}
	ListIterator_Prev(iterator);
	return iterator;
}

Object List_SearchPositions(Object self, Object object)
{
	Object list;
	list = List_Create();
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	Object position;
	position = NumberFactory_FromLong(numberFactory, 0);
	while(ListIterator_ThisEnd((((List) (self->entity))->iterator)) == false)
	{
		if(Object_Compare(ListIterator_ThisData((((List) (list->entity))->iterator)), object) == equal)
		{
			List_PushBack(list, Object_TempClone(position));
		}
		Number_Inc(position);
		ListIterator_Next((((List) (self->entity))->iterator));
	}
	ListIterator_Hide((((List) (self->entity))->iterator));
	return list;
}

Object List_SublistBetweenPositions(Object self, Object positionFrom, Object positionTo)
{
	ListIterator_ToPosition((((List) (self->entity))->iterator), positionFrom);
	Object list;
	list = Object_Autorelease(List_Create());
	Object position;
	position = Object_Clone(positionFrom);
	while(Object_Compare(position, positionTo) != greater)
	{
		List_PushBack(list, ListIterator_ThisData((((List) (self->entity))->iterator)));
		ListIterator_Next((((List) (self->entity))->iterator));
		Number_Inc(position);
	}
	ListIterator_Hide((((List) (self->entity))->iterator));
	Object_Release(position);
	return list;
}

Object List_SublistBetweenIterators(Object self, Object positionFrom, Object positionTo)
{
	Object iterator;
	iterator = Object_Clone(positionFrom);
	Object list;
	list = List_Create();
	while(Object_Compare(iterator, positionTo) != equal)
	{
		List_PushBack(list, ListIterator_ThisData(iterator));
		ListIterator_Next(iterator);
	}
	Object_Release(iterator);
	return list;
}

Object List_Size(Object self)
{
	ListIterator_ToBegin((((List) (self->entity))->iterator));
	Object toReturn;
	toReturn = NumberFactory_FromLong(numberFactory, 0);
	while(ListIterator_ThisEnd((((List) (self->entity))->iterator)) == false)
	{
		Number_Inc(toReturn);
		ListIterator_Next((((List) (self->entity))->iterator));
	}
	ListIterator_Hide((((List) (self->entity))->iterator));
	return toReturn;
}

Object List_Concatenate(Object self, Object list)
{
	ListIterator_ToEnd((((List) (self->entity))->iterator));
	ListIterator_AddListAfter((((List) (self->entity))->iterator), list);
	ListIterator_Hide((((List) (self->entity))->iterator));
	return self;
}

