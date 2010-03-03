#include "internal_config.h"
#include "internal_actions.h"
#include "internal_object.h"
#include "internal_globals.h"
#include "internal_allocator.h"
#include "internal_list.h"
#include "internal_nothing.h"

SvvInternalCreator(SvvInternalList)
{
	// Caution: this function relays on list implementation
	SvvInternalList res = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalList)));
	res->head = SvvInternalListNode_Create();
	res->tail = SvvInternalListNode_Create();
	
	res->head->next = res->tail;
	res->tail->prev = res->head;
	
	res->head->prev = res->tail->next = OBJECT_AS_LINK(SvvInternalNothing);
	
	return res;
};


SvvInternalAction(SvvInternalList, Destroy, void)
{
	// Caution: this function relays on list implementation
	while(Receiver->head != Receiver->tail)
	{
		SvvInternalListNode node = Receiver->head->next;
		SvvInternalListNode_Destroy(Receiver->head);
		Receiver->head = node;
	};
	SvvInternalListNode_Destroy(Receiver->tail);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};


SvvInternalAction(SvvInternalList, Clean, void)
{
	// Caution: this function relays on list implementation
	while(Receiver->head->next != Receiver->tail)
	{
		SvvInternalListNode node = Receiver->head->next;
		SvvInternalListNode_Destroy(Receiver->head);
		Receiver->head = node;
	};
	Receiver->head->prev = OBJECT_AS_LINK(SvvInternalNothing);
};


SvvInternalAction(SvvInternalList, PushBack, void, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetLast(Receiver);
	SvvInternalListIterator_AddAfter(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, PushFront, void, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalListIterator_AddBefore(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, AddAfterPosition, void, int Position, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	SvvInternalListIterator_AddAfter(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, AddBeforePosition, void, int Position, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	SvvInternalListIterator_AddBefore(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, RemoveFirst, void, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalListIterator_SearchFirst(iterator, Object);
	if(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalListIterator_Remove(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator)
{
	// Caution: this function relays on iterator and list implementation
	SvvInternalListIterator iterator = SvvInternalListIterator_Create();
	iterator->data = Receiver->tail->prev;
	iterator->list = Receiver;
	return iterator;
};

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

SvvInternalAction(SvvInternalList, Search, SvvInternalList, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalList list = SvvInternalList_Create();
	
	SvvInternalListIterator_SearchFirst(iterator, Object);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalList_PushBack(list, LINK_AS_OBJECT(SvvInternalListIterator_Clone(iterator)));
		SvvInternalListIterator_SearchFirst(iterator, Object);
	};
	SvvInternalListIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalList, GetIteratorFromPosition, SvvInternalListIterator, int Position)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	return iterator;
};

SvvInternalAction(SvvInternalList, GetCreatingIteratorFromPosition, SvvInternalListIterator, int Position)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	int current_position = 0;
	
	while(current_position <= Position)
	{
		current_position++;
		if(SvvInternalListIterator_EndReached(iterator))
		{
			SvvInternalListIterator_AddBefore(iterator, SvvInternalNothing);
		} else {
			SvvInternalListIterator_GetNext(iterator);
		};
	};
	SvvInternalListIterator_GetPrev(iterator);
	return iterator;
};

SvvInternalAction(SvvInternalList, SearchPositions, SvvInternalList, SvvInternalObject Object)
{
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	int position = 0;

	while(!SvvInternalListIterator_EndReached(iterator)) 
	{
		if(SvvInternalObject_Compare(SvvInternalListIterator_GetData(iterator), Object) == 0)
		{
			SvvInternalList_PushBack(list, INT_AS_OBJECT(position));
		};
		position++;
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalList, Clone, SvvInternalList)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalList list = SvvInternalList_Create();
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
		SvvInternalList_PushBack(list, object);
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	return list;
};


SvvInternalAction(SvvInternalList, GetFirst, SvvInternalListIterator)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Create();
	iterator->data = Receiver->head->next;
	iterator->list = Receiver;
	return iterator;
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

SvvInternalAction(SvvInternalListIterator, SetData, void, SvvInternalObject Object)
{
	Receiver->data->data = Object;
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

SvvInternalCreator(SvvInternalListNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalListNode)));
};

SvvInternalAction(SvvInternalListNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};
