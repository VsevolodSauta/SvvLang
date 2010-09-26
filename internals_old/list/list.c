#include "internals/basics.h"

#include "internals/list/interface.h"
#include "internals/list/node.h"

#define NODE(receiver) (ENTITY(receiver, ListIterator)->node)
#define LIST(receiver) (ENTITY(receiver, ListIterator)->list)
#define HEAD(receiver) (ENTITY(receiver, List)->head)
#define TAIL(receiver) (ENTITY(receiver, List)->tail)
#define ITERATOR(receiver) (ENTITY(receiver, List)->iterator)

#define List_GID 0x42

DefaultOperations(List);

Action(List, SystemIterator);

DefaultInit(List,
	HEAD(receiver) = ListNode_Create();
	TAIL(receiver) = ListNode_Create();
	
	PREV(TAIL(receiver)) = HEAD(receiver);
	NEXT(HEAD(receiver)) = TAIL(receiver);
	
	PREV(HEAD(receiver)) = NEXT(TAIL(receiver)) = nothing;
	
	ITERATOR(receiver) = List_SystemIterator(receiver);
)

DefaultCreator(List);

Action(List, Destroy)
{
	Object node = HEAD(receiver);
	do {
		Object nextNode = NEXT(node);
		Object_Release(node);
		node = nextNode;
	} while(node != TAIL(receiver));
	Object_Release(TAIL(receiver));
	return Object_Destroy(receiver);
}

Action(List, Clone)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	Object list = List_Create();
	while(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		Object object = ListIterator_ThisData(ITERATOR(receiver));
		List_PushBack(list, object);
		ListIterator_Next(ITERATOR(receiver));
	}
	ListIterator_Hide(ITERATOR(receiver));
	return list;
}

Action(List, Compare, Object compareTo)
{
	Object nativeIterator = List_First(receiver);
	Object foreignIterator = List_First(compareTo);
	while(1)
	{
		if(ListIterator_ThisEnd(nativeIterator) == true)
		{
			if(ListIterator_ThisEnd(foreignIterator) == true)
			{
				return equal;
			} else {
				return less;
			}
		}
		if(ListIterator_ThisEnd(foreignIterator) == true)
		{
			return greater;
		}
		
		Object candidateForReturning = Object_Compare(
			ListIterator_ThisData(nativeIterator),
			ListIterator_ThisData(foreignIterator)
		);
		
		if(candidateForReturning == equal)
		{
			ListIterator_Next(foreignIterator);
			ListIterator_Next(nativeIterator);
		} else {
			return candidateForReturning;
		}
	}
}

Action(List, Clean)
{
	Object node = NEXT(HEAD(receiver));
	do {
		Object nextNode = NEXT(node);
		Object_Release(node);
		node = nextNode;
	} while(node != TAIL(receiver));
	PREV(TAIL(receiver)) = HEAD(receiver);
	NEXT(HEAD(receiver)) = TAIL(receiver);
	return receiver;
}


Action(List, PushBack, Object object)
{
	ListIterator_ToEnd(ITERATOR(receiver));
	ListIterator_AddAfter(ITERATOR(receiver), object);
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, PushFront, Object object)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	ListIterator_AddBefore(ITERATOR(receiver), object);
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, AddAfterPosition, Object position, Object object)
{
	ListIterator_ToPosition(ITERATOR(receiver), position);
	ListIterator_AddAfter(ITERATOR(receiver), object);
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, AddBeforePosition, Object position, Object object)
{
	ListIterator_ToPosition(ITERATOR(receiver), position);
	ListIterator_AddBefore(ITERATOR(receiver), object);
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, RemoveFirst, Object object)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	ListIterator_SearchFirst(ITERATOR(receiver), object);
	if(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		ListIterator_ThisRemove(ITERATOR(receiver));
	}
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, Last)
{
	Object iterator = ListIterator_Create();
	Object_Autorelease(iterator);
	ListIterator_InitWithListAndNode(iterator, receiver, PREV(TAIL(receiver)));
	return iterator;
}

Action(List, First)
{
	Object iterator = ListIterator_Create();
	Object_Autorelease(iterator);
	ListIterator_InitWithListAndNode(iterator, receiver, NEXT(HEAD(receiver)));
	return iterator;
}

Action(List, SystemIterator)
{
	Object iterator = ListIterator_Create();
	ListIterator_InitWithListAndNode(iterator, receiver, HEAD(receiver));
	return iterator;
}

Action(List, DataFromPosition, Object position)
{
	ListIterator_ToPosition(ITERATOR(receiver), position);
	Object toReturn = ListIterator_ThisData(ITERATOR(receiver));
	ListIterator_Hide(ITERATOR(receiver));
	return toReturn;
}

Action(List, Search, Object object)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	Object list = List_Create();
	Object_Autorelease(list);
	
	ListIterator_SearchFirst(ITERATOR(receiver), object);
	while(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		Object toPush = Object_Clone(ITERATOR(receiver));
		List_PushBack(list, toPush);
		Object_Release(toPush);
		ListIterator_SearchFirst(ITERATOR(receiver), object);
	}
	return list;
}

Action(List, IteratorFromPosition, Object position)
{
	Object iterator = List_First(receiver);
	ListIterator_ToPosition(iterator, position);
	return iterator;
}

Action(List, CreatingIteratorFromPosition, Object position)
{
	Object iterator = List_First(receiver);
	Object currentPosition = NumberFactory_FromLong(numberFactory, 0);
	
	while(Object_Compare(currentPosition, position) != greater)
	{
		Number_Inc(currentPosition);
		if(ListIterator_ThisEnd(iterator) == true)
		{
			ListIterator_AddBefore(iterator, nothing);
		} else {
			ListIterator_Next(iterator);
		}
	}
	ListIterator_Prev(iterator);
	return iterator;
}

Action(List, SearchPositions, Object object)
{
	Object list = List_Create();
	ListIterator_ToBegin(ITERATOR(receiver));
	Object position = NumberFactory_FromLong(numberFactory, 0);

	while(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		if(Object_Compare(ListIterator_ThisData(ITERATOR(receiver)), object) == equal)
		{
			Object toPush = Object_Clone(position);
			List_PushBack(list, toPush);
			Object_Release(toPush);
		}
		Number_Inc(position);
		ListIterator_Next(ITERATOR(receiver));
	}
	ListIterator_Hide(ITERATOR(receiver));
	return list;
}

Action(List, SublistBetweenPositions, Object positionFrom, Object positionTo)
{
	ListIterator_ToPosition(ITERATOR(receiver), positionFrom);
	Object list = List_Create();
	Object_Autorelease(list);
	Object quantity = Number_Sub(positionTo, positionFrom);
	Object zero = NumberFactory_FromLong(numberFactory, 0);
	while(Object_Compare(quantity, zero) != equal)
	{
		List_PushBack(list, DATA(NODE(ITERATOR(receiver))));
		ListIterator_Next(ITERATOR(receiver));
		Number_Dec(quantity);
	}
	ListIterator_Hide(ITERATOR(receiver));
	return list;
}

Action(List, SublistBetweenIterators, Object positionFrom, Object positionTo)
{
	Object iterator = Object_Clone(positionFrom);
	Object list = List_Create();
	
	while(Object_Compare(iterator, positionTo) != equal)
	{
		List_PushBack(list, DATA(NODE(iterator)));
		ListIterator_Next(iterator);
	}
	Object_Release(iterator);
	return list;
}

#if 0
Action(List, Sort, void)
{
	ListIterator iterator = List_First(receiver);
	
	while(ListIterator_NextEnd(iterator) == false)
	{
		Object next_object = ListIterator_NextData(iterator);
		if(Object_Compare(ListIterator_Data(iterator), next_object) <= 0)
		{
			ListIterator_Next(iterator);
		} else {
			ListIterator_NextRemove(iterator);
			while(!ListIterator_PrevBegin(iterator))
			{
				if(Object_Compare(ListIterator_PrevData(iterator), next_object) <= 0)
				{
					break;
				} else {
					ListIterator_Prev(iterator);
				}
			}
			ListIterator_AddBefore(iterator, next_object);
		}
	}
	ListIterator_Destroy(iterator);
}
#endif

Action(List, Dump)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	while(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		DEBUG("%li ", (long int) ListIterator_ThisData(ITERATOR(receiver)));
		ListIterator_Next(ITERATOR(receiver));
	}
	DEBUG("\n");
	
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}

Action(List, Size)
{
	ListIterator_ToBegin(ITERATOR(receiver));
	Object toReturn = NumberFactory_FromLong(numberFactory, 0);
	
	while(ListIterator_ThisEnd(ITERATOR(receiver)) == false)
	{
		Number_Inc(toReturn);
		ListIterator_Next(ITERATOR(receiver));
	}
	
	ListIterator_Hide(ITERATOR(receiver));
	return toReturn;
}

Action(List, Concatenate, Object list)
{
	ListIterator_ToEnd(ITERATOR(receiver));
	ListIterator_AddListAfter(ITERATOR(receiver), list);
	ListIterator_Hide(ITERATOR(receiver));
	return receiver;
}
