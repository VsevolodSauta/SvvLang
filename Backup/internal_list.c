#include "internal_config.h"
#include "internal_actions.h"
#include "internal_object.h"
#include "internal_globals.h"
#include "internal_allocator.h"
#include "internal_list.h"
#include "internal_nothing.h"

SvvInternalCreator(SvvInternalList)
{
	SvvInternalList res = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalList*)));
	res->next = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalList*)));
	res->prev res->next->next = OBJECT_AS_LINK(SvvInternalNothing);
	return res;
};


SvvInternalAction(SvvInternalList, Destroy, void)
{
	while(!IS_NOTHING(Receiver->next))
	{
		Receiver = Receiver->next;
		SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver->prev));
	};
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};


SvvInternalAction(SvvInternalList, Append, void, SvvInternalObject Object)
{
	SvvInternalListIterator_AddAfter(SvvInternalList_GetLast(Receiver), Object);
};

SvvInternalAction(SvvInternalList, AddAfterPosition, void, int Position, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	SvvInternalListIterator_AddAfter(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, AddBeforePosition, void, int Position, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	SvvInternalListIterator_AddBefore(iterator, Object);
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, RemoveFirst, void, SvvInternalObject Object)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	SvvInternalListIterator_SearchFirst(iterator, Object);
	if(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalListIterator_Remove(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_GetPrev(iterator);
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, SearchFirst, void, SvvInternalObject Object)
{
	while(!SvvInternalIterator_EndReached(Receiver))
	{
		if(SvvInternalObject_Compare(SvvInternalListIterator_GetData(Receiver), Object) == 0)
		{
			return;
		};
		SvvInternalListIterator_GetNext(Receiver);
	};
};

SvvInternalAction(SvvInternalListIterator, SearchFirstNumber, int, SvvInternalObject Object)
{
	int position = 0;
	while(!SvvInternalIterator_EndReached(Receiver))
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
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	SvvInternalList list = SvvInternalList_Create();
	
	SvvInternalListIterator_SearchFirst(iterator, Object);
	while(!SvvInternalIterator_EndReached(iterator))
	{
#warning To Optimize
		SvvInternalList_Append(list, LINK_AS_OBJECT(SvvInternalListIterator_Clone(iterator)));
		SvvInternalListIterator_SearchFirst(iterator, Object);
	};
	SvvInternalListIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalList, GetIteratorFromNumber, SvvInternalListIterator, int Position)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	SvvInternalListIterator_ToPosition(iterator, Position);
	return iterator;
};

SvvInternalAction(SvvInternalList, GetCreatingIteratorFromNumber, SvvInternalListIterator, int Position)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
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

SvvInternalAction(SvvInternalList, SearchNumbers, SvvInternalList, SvvInternalObject Object)
{
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	int position = 0;

	while(!SvvInternalListIterator_EndReached(iterator)) 
	{
		if(SvvInternalObject_Compare(iterator->data->data, Object) == 0)
		{
#warning To Optimize
			SvvInternalList_Append(list, INT_AS_OBJECT(position));
		};
		position++;
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalList, GetIterator, SvvInternalListIterator)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Create();
	iterator->data = Receiver->next;
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, Remove, void)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(Receiver);
	Receiver->data->prev->next = Receiver->data->next;
	Receiver->data->next->prev = Receiver->data->prev;
	SvvInternalListIterator_GetNext(Receiver);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(iterator->data));
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
	Receiver->data = Receiver->head->next;
	while(Position)
	{
		SvvInternalListIterator_GetNext(Receiver);
		Position--;
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
	SvvInternalListIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalListIterator*)));
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalListIterator, Clone, SvvInternalListIterator)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Create();
	SvvInternalMMU_Copy(SvvDefaultIterator, LINK_AS_OBJECT(iterator), LINK_AS_OBJECT(Receiver), sizeof(SvvInternalListIterator*));
	return iterator;
};

SvvInternalAction(SvvInternalListIterator, AddAfter, void, SvvInternalObject Object)
{
	SvvInternalList saved_next = Receiver->data->next;
	SvvInternalList adding_element = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalList*)));
	Receiver->data->next = adding_element;
	adding_element->prev = Receiver->data;
	adding_element->data = Object;
	adding_element->next = saved_next;
	saved_next->prev = adding_element;
};

SvvInternalAction(SvvInternalListIterator, AddBefore, void, SvvInternalObject Object)
{
	SvvInternalList saved_prev = Receiver->data->prev;
	SvvInternalList adding_element = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalList*)));
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


SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int Position1, int Position2)
{
	
};

SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator Position1, SvvInternalListIterator Position2)
{
	SvvInternalListIterator iterator = SvvInternalListIterator_Clone(Position1);
	SvvInternalList list = SvvInternalList_Create();
	
	while(SvvInternalListIterator_Compare(iterator, Position2) != 0)
	{
		SvvInternalList_Append(list, iterator->data->data);
		SvvInternalListIterator_GetNext(iterator);
	};
};

SvvInternalAction(SvvInternalListIterator, Compare, int, SvvInternalListIterator iterator)
{
	return SvvInternaMMU_Compare(SvvDefaultMMU, LINK_AS_OBJECT(Receiver), LINK_AS_OBJECT(iterator), sizeof(SvvInternalListIterator*));
};
