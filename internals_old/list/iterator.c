#include "internals/basics.h"

#include "internals/list/interface.h"
#include "internals/list/node.h"

#define NODE(receiver) (ENTITY(receiver, ListIterator)->node)
#define LIST(receiver) (ENTITY(receiver, ListIterator)->list)
#define HEAD(receiver) (ENTITY(receiver, List)->head)
#define TAIL(receiver) (ENTITY(receiver, List)->tail)
#define ITERATOR(receiver) (ENTITY(receiver, List)->iterator)

#define ListIterator_GID 0x41

Defaults(ListIterator);

Action(ListIterator, Compare, Object compareTo)
{
	return NODE(receiver) > NODE(compareTo) ? greater :
		NODE(receiver) < NODE(compareTo) ? less :
		 equal;
}

Action(ListIterator, Destroy)
{
	Object_Release(NODE(receiver));
	Object_Release(LIST(receiver));
	return Object_Destroy(receiver);
}

Action(ListIterator, Clone)
{
	Object toReturn = ListIterator_Create();
	Object_Retain(LIST(toReturn) = LIST(receiver));
	Object_Retain(NODE(toReturn) = NODE(receiver));
	return toReturn;
}

Action(ListIterator, InitWithListAndNode, Object list, Object node)
{
	Object_Retain(LIST(receiver) = list);
	Object_Retain(NODE(receiver) = node);
	return receiver;
}

Action(ListIterator, ResetNode, Object node)
{
	Object toRelease = NODE(receiver);
	Object_Retain(NODE(receiver) = node);
	Object_Release(toRelease);
	return receiver;
}

Action(ListIterator, Hide)
{
	return ListIterator_ResetNode(receiver, HEAD(LIST(receiver)));
};

Action(ListIterator, Next)
{
	return ListIterator_ResetNode(receiver, NEXT(NODE(receiver)));
}

Action(ListIterator, Prev)
{
	return ListIterator_ResetNode(receiver, PREV(NODE(receiver)));
}

Action(ListIterator, ToBegin)
{
	return ListIterator_ResetNode(receiver, NEXT(HEAD(LIST(receiver))));
}

Action(ListIterator, ToEnd)
{
	return ListIterator_ResetNode(receiver, PREV(TAIL(LIST(receiver))));
}

Action(ListIterator, ToPosition, Object position)
{
	Object zero = NumberFactory_FromLong(numberFactory, 0);
	Object positionClone = Object_Clone(position);
	if(Object_Compare(position, zero) == equal)
	{
		ListIterator_ToBegin(receiver);
	};
	if(Object_Compare(position, zero) == greater)
	{
		ListIterator_ToBegin(receiver);
		while(Object_Compare(positionClone, zero) == greater)
		{
			ListIterator_Next(receiver);
			Number_Dec(positionClone);
		}
	}
	if(Object_Compare(position, zero) == less)
	{
		ListIterator_ToEnd(receiver);
		Number_Inc(positionClone);
		while(Object_Compare(positionClone, zero) == less)
		{
			ListIterator_Prev(receiver);
			Number_Inc(positionClone);
		}
	}
	Object_Release(positionClone);
	return receiver;
}

Action(ListIterator, FromPositionToPosition, Object positionFrom, Object positionTo)
{
	Object quantity = Number_Sub(positionTo, positionFrom);
	Object zero = NumberFactory_FromLong(numberFactory, 0);
	while(Object_Compare(quantity, zero) == greater)
	{
		ListIterator_Next(receiver);
		Number_Dec(quantity);
	}
	while(Object_Compare(quantity, zero) == less)
	{
		ListIterator_Prev(receiver);
		Number_Inc(quantity);
	}
	return receiver;
}

Action(ListIterator, SearchFirst, Object object)
{
	while(ListIterator_ThisEnd(receiver) == false)
	{
		if(Object_Compare(ListIterator_ThisData(receiver), object) == equal)
		{
			break;
		}
		ListIterator_Next(receiver);
	}
	return receiver;
}

Action(ListIterator, SearchFirstPosition, Object object)
{
	Object position = NumberFactory_FromLong(numberFactory, 0);
	
	while(ListIterator_ThisEnd(receiver) == false)
	{
		if(Object_Compare(ListIterator_ThisData(receiver), object) == equal)
		{
			return position;
		}
		ListIterator_Next(receiver);
		Number_Inc(position);
	}
	return NumberFactory_FromLong(numberFactory, -1);
}


Action(ListIterator, ThisRemove)
{
	NEXT(PREV(NODE(receiver))) = NEXT(NODE(receiver));
	PREV(NEXT(NODE(receiver))) = PREV(NODE(receiver));
	Object_Release(NODE(receiver));
	return ListIterator_Next(receiver);
}

Action(ListIterator, NextRemove)
{
	Object toRemove = NEXT(NODE(receiver));
	PREV(NEXT(toRemove)) = PREV(toRemove);
	NEXT(PREV(toRemove)) = NEXT(toRemove);
	return Object_Release(toRemove);
}

Action(ListIterator, PrevRemove)
{
	Object toRemove = PREV(NODE(receiver));
	PREV(NEXT(toRemove)) = PREV(toRemove);
	NEXT(PREV(toRemove)) = NEXT(toRemove);
	return Object_Release(toRemove);
}


Action(ListIterator, ThisData)
{
	return DATA(NODE(receiver));
}

Action(ListIterator, NextData)
{
	return DATA(NEXT(NODE(receiver)));
}

Action(ListIterator, PrevData)
{
	return DATA(PREV(NODE(receiver)));
}

Action(ListIterator, SetData, Object object)
{
	Object_Retain(object);
	Object_Release(DATA(NODE(receiver)));
	DATA(NODE(receiver)) = object;
	return receiver;
}

Action(ListIterator, PrevSetData, Object object)
{
	Object_Retain(object);
	Object_Release(DATA(PREV(NODE(receiver))));
	DATA(PREV(NODE(receiver))) = object;
	return receiver;
}

Action(ListIterator, NextSetData, Object object)
{
	Object_Retain(object);
	Object_Release(DATA(NEXT(NODE(receiver))));
	DATA(NEXT(NODE(receiver))) = object;
	return receiver;
}

Action(ListIterator, AddAfter, Object object)
{
	Object savedNext = NEXT(NODE(receiver));
	Object addingElement = ListNode_Create();
	Object_Retain(DATA(addingElement) = object);
	NEXT(NODE(receiver)) = addingElement;
	PREV(addingElement) = NODE(receiver);
	NEXT(addingElement) = savedNext;
	PREV(savedNext) = addingElement;
	return receiver;
}

Action(ListIterator, AddBefore, Object object)
{
	Object savedPrev = PREV(NODE(receiver));
	Object addingElement = ListNode_Create();
	Object_Retain(DATA(addingElement) = object);
	PREV(NODE(receiver)) = addingElement;
	NEXT(addingElement) = NODE(receiver);
	PREV(addingElement) = savedPrev;
	NEXT(savedPrev) = addingElement;
	return receiver;
}


Action(ListIterator, ThisBegin)
{
	return PREV(NODE(receiver)) == nothing ? true : false;
}

Action(ListIterator, ThisEnd)
{
	return NEXT(NODE(receiver)) == nothing ? true : false;
}

Action(ListIterator, PrevBegin)
{
	return PREV(PREV(NODE(receiver))) == nothing ? true : false;
}

Action(ListIterator, NextEnd)
{
	return NEXT(NEXT(NODE(receiver))) == nothing ? true : false;
}


Action(ListIterator, AddListBefore, Object list)
{
	Object listIterator = List_First(list);
	while(ListIterator_ThisEnd(listIterator) == false)
	{
		ListIterator_AddBefore(receiver, ListIterator_ThisData(listIterator));
		ListIterator_Next(listIterator);
	}
	return receiver;
}

Action(ListIterator, AddListAfter, Object list)
{
	Object listIterator = List_Last(list);
	while(ListIterator_ThisBegin(listIterator) == false)
	{
		ListIterator_AddAfter(receiver, ListIterator_ThisData(listIterator));
		ListIterator_Prev(listIterator);
	}
	return list;
}

Action(ListIterator, RemoveCount, Object count)
{
	Object savedPrev = PREV(NODE(receiver));
	Object zero = NumberFactory_FromLong(numberFactory, 0);
	while(Object_Compare(count, zero) == greater)
	{
		Object_Release(NODE(receiver));
		ListIterator_Next(receiver);
		Number_Dec(count);
	}
	PREV(NODE(receiver)) = savedPrev;
	NEXT(savedPrev) = NODE(receiver);
	return receiver;
}
