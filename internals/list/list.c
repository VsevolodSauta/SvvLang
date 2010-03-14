#include "internals/basics.h"
#include "internals/list/interface.h"
#include "internals/list/node.h"

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

SvvInternalAction(SvvInternalList, Sort, void)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	
	while(!SvvInternalListIterator_NextEndReached(iterator))
	{
		SvvInternalObject next_object = SvvInternalListIterator_NextGetData(iterator);
		if(SvvInternalObject_Compare(SvvInternalListIterator_GetData(iterator), next_object) <= 0)
		{
			SvvInternalListIterator_GetNext(iterator);
		} else {
			SvvInternalListIterator_NextRemove(iterator);
			while(!SvvInternalListIterator_PrevBeginReached(iterator))
			{
				if(SvvInternalObject_Compare(SvvInternalListIterator_PrevGetData(iterator), next_object) <= 0)
				{
					break;
				} else {
					SvvInternalListIterator_GetPrev(iterator);
				};
			};
			SvvInternalListIterator_AddBefore(iterator, next_object);
		};
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, Dump, void)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		DEBUG("%li ", OBJECT_AS_INT(SvvInternalListIterator_GetData(iterator)));
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	DEBUG("\n");
};
