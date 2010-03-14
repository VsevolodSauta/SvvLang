#include "internals/basics.h"
#include "internals/list/interface.h"
#include "internals/list/node.h"

SvvInternalAction(SvvInternalListIterator, SearchFirst, void, SvvInternalObject Object)
{
	while(!SvvInternalListIterator_EndReached(Receiver))
	{
		if(SvvInternalObject_Compare(SvvInternalListIterator_GetData(Receiver), Object) == 0)
		{
			return;
		};
		SvvInternalListIterator_GetNext(Receiver);
	};
};

SvvInternalAction(SvvInternalListIterator, SearchFirstPosition, int, SvvInternalObject Object)
{
	int position = 0;
	while(!SvvInternalListIterator_EndReached(Receiver))
	{
		if(SvvInternalObject_Compare(SvvInternalListIterator_GetData(Receiver), Object) == 0)
		{
			return position;
		};
		SvvInternalListIterator_GetNext(Receiver);
		position++;
	};
	return -1;
};

SvvInternalAction(SvvInternalListIterator, Remove, void)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(Receiver);
	Receiver->data->prev->next = Receiver->data->next;
	Receiver->data->next->prev = Receiver->data->prev;
	SvvInternalListIterator_GetNext(Receiver);
	SvvInternalListNode_Destroy(iterator->data);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalListIterator, NextRemove, void)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(Receiver);
	SvvInternalListIterator_GetNext(iterator);
	iterator->data->prev->next = iterator->data->next;
	iterator->data->next->prev = iterator->data->prev;
	SvvInternalListNode_Destroy(iterator->data);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalListIterator, PrevRemove, void)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(Receiver);
	SvvInternalListIterator_GetPrev(iterator);
	iterator->data->prev->next = iterator->data->next;
	iterator->data->next->prev = iterator->data->prev;
	SvvInternalListNode_Destroy(iterator->data);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalListIterator, GetNext, void)
{
	Receiver->data = Receiver->data->next;
};

SvvInternalAction(SvvInternalListIterator, GetPrev, void)
{
	Receiver->data = Receiver->data->prev;
};

SvvInternalAction(SvvInternalListIterator, ToPosition, void, int Position)
{
	Receiver->data = Receiver->list->head->next;
	while(Position)
	{
		SvvInternalListIterator_GetNext(Receiver);
		Position--;
	};
};

SvvInternalAction(SvvInternalListIterator, FromPositionToPosition, void, int PositionFrom, int PositionTo)
{
	int quantity = PositionTo - PositionFrom;
	while(quantity > 0)
	{
		SvvInternalListIterator_GetNext(Receiver);
		quantity--;
	};
	while(quantity < 0)
	{
		SvvInternalListIterator_GetPrev(Receiver);
		quantity++;
	};
};

SvvInternalAction(SvvInternalListIterator, GetData, SvvInternalObject)
{
	return Receiver->data->data;
};

SvvInternalAction(SvvInternalListIterator, NextGetData, SvvInternalObject)
{
	return Receiver->data->next->data;
};

SvvInternalAction(SvvInternalListIterator, PrevGetData, SvvInternalObject)
{
	return Receiver->data->prev->data;
};

SvvInternalAction(SvvInternalListIterator, SetData, void, SvvInternalObject Object)
{
	Receiver->data->data = Object;
};

SvvInternalAction(SvvInternalListIterator, PrevSetData, void, SvvInternalObject Object)
{
	Receiver->data->prev->data = Object;
};

SvvInternalAction(SvvInternalListIterator, NextSetData, void, SvvInternalObject Object)
{
	Receiver->data->next->data = Object;
};

SvvInternalCreator(SvvInternalListIterator)
{
	SvvInternalListIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalListIterator)));
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalListIterator, Clone, SvvInternalListIterator)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Create();
	SvvInternalMMU_Copy(SvvDefaultAllocator, LINK_AS_OBJECT(iterator), LINK_AS_OBJECT(Receiver), sizeof(SvvInternalListIterator*));
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, AddAfter, void, SvvInternalObject Object)
{
	SvvInternalListNode saved_next = Receiver->data->next;
	SvvInternalListNode adding_element = SvvInternalListNode_Create();
	Receiver->data->next = adding_element;
	adding_element->prev = Receiver->data;
	adding_element->data = Object;
	adding_element->next = saved_next;
	saved_next->prev = adding_element;
};

SvvInternalAction(SvvInternalListIterator, AddBefore, void, SvvInternalObject Object)
{
	SvvInternalListNode saved_prev = Receiver->data->prev;
	SvvInternalListNode adding_element = SvvInternalListNode_Create();
	Receiver->data->prev = adding_element;
	
	adding_element->next = Receiver->data;
	adding_element->data = Object;
	adding_element->prev = saved_prev;
	saved_prev->next = adding_element;
};


SvvInternalAction(SvvInternalListIterator, BeginReached, int)
{
	return IS_NOTHING(Receiver->data->prev);
};

SvvInternalAction(SvvInternalListIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->data->next);
};


SvvInternalAction(SvvInternalListIterator, PrevBeginReached, int)
{
	return IS_NOTHING(Receiver->data->prev->prev);
};

SvvInternalAction(SvvInternalListIterator, NextEndReached, int)
{
	return IS_NOTHING(Receiver->data->next->next);
};


SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int PositionFrom, int PositionTo)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIteratorFromPosition(Receiver, PositionFrom);
	SvvInternalList list = SvvInternalList_Create();
	int quantity = PositionTo - PositionFrom;
	
	while(quantity)
	{
		SvvInternalList_PushBack(list, SvvInternalListIterator_GetData(iterator));
		SvvInternalListIterator_GetNext(iterator);
		quantity--;
	};
	SvvInternalListIterator_Destroy(iterator);

	return list;
};

SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator PositionFrom, SvvInternalListIterator PositionTo)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(PositionFrom);
	SvvInternalList list = SvvInternalList_Create();
	
	while(SvvInternalListIterator_Compare(iterator, PositionTo) != 0)
	{
		SvvInternalList_PushBack(list, SvvInternalListIterator_GetData(iterator));
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	
	return list;
};

SvvInternalAction(SvvInternalListIterator, Compare, int, SvvInternalListIterator iterator)
{
	return SvvInternalMMU_Compare(SvvDefaultMMU, LINK_AS_OBJECT(Receiver), LINK_AS_OBJECT(iterator), sizeof(SvvInternalListIterator*));
};

SvvInternalAction(SvvInternalListIterator, AddListBefore, void, SvvInternalList list)
{
	SvvInternalListIterator list_iterator = SvvInternalList_GetFirst(list);
	while(!SvvInternalListIterator_EndReached(list_iterator))
	{
		SvvInternalListIterator_AddBefore(Receiver, SvvInternalListIterator_GetData(list_iterator));
		SvvInternalListIterator_GetNext(list_iterator);
	};
};

SvvInternalAction(SvvInternalListIterator, AddListAfter, void, SvvInternalList list)
{
	SvvInternalListIterator list_iterator = SvvInternalList_GetLast(list);
	while(!SvvInternalListIterator_BeginReached(list_iterator))
	{
		SvvInternalListIterator_AddAfter(Receiver, SvvInternalListIterator_GetData(list_iterator));
		SvvInternalListIterator_GetPrev(list_iterator);
	};
};

SvvInternalAction(SvvInternalListIterator, RemoveCount, void, int Count)
{
	SvvInternalListNode saved_prev = Receiver->data->prev;
	
	while(Count--)
	{
		SvvInternalListIterator_GetNext(Receiver);
		SvvInternalListNode_Destroy(Receiver->data->prev);
	};
	Receiver->data->prev = saved_prev;
	saved_prev->next = Receiver->data;
};
