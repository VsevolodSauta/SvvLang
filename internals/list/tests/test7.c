#include "internals/basics.h"
#include "internals/list/interface.h"

/*
SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
SvvInternalAction(SvvInternalList, PushBack, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, PushFront, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, GetFirst, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, Clean, void);
SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int. int);
SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator, SvvInternalListIterator);
SvvInternalAction(SvvInternalListIterator, AddListBefore, void, SvvInternalList);
SvvInternalAction(SvvInternalListIterator, AddListAfter, void, SvvInternalList);
SvvInternalAction(SvvInternalListIterator, GetNext, void); // O(1)
SvvInternalAction(SvvInternalListIterator, GetPrev, void); // O(1)
SvvInternalAction(SvvInternalListIterator, BeginReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, EndReached, int); // O(1)
*/

#define NODES 100
#define TIMES 1

int main(void)
{
	int i, j;
	int l = 10, r = 5;
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalList list2 = SvvInternalList_Create();
	SvvInternalList temp_list;
	SvvInternalListIterator front, back;
	
	
	// list2 = (0 1 2 3 4 5 6 ... 148 149)
	for(i = 0; i < l + r; i++)
	{
		SvvInternalList_PushBack(list2, INT_AS_OBJECT(i));
	};
	
	// list = (99998 99996 ... 8 6 4 2 0 1 3 5 7 9 ... 99997 99999 )
	for(i = 0; i < NODES; i++)
	{
		if(i & 1)
		{
			SvvInternalList_PushBack(list, INT_AS_OBJECT(i));
		} else {
			SvvInternalList_PushFront(list, INT_AS_OBJECT(i));
		};
	};

	for(front = SvvInternalList_GetFirst(list), i = 0; i < NODES / 2; SvvInternalListIterator_GetNext(front), i++)
	{
		SvvInternalList_AddAfterPosition(list2, l - 1 + i, SvvInternalListIterator_GetData(front));
	};
	SvvInternalListIterator_Destroy(front);

	for(back = SvvInternalList_GetLast(list), i = 0; i < NODES / 2; SvvInternalListIterator_GetPrev(back), i++)
	{
		SvvInternalList_AddAfterPosition(list2, l + NODES / 2 - 1, SvvInternalListIterator_GetData(back));
	};
	SvvInternalListIterator_Destroy(back);
	

	front = SvvInternalList_GetIteratorFromPosition(list2, l);
	SvvInternalListIterator_RemoveCount(front, NODES);
	SvvInternalListIterator_Destroy(front);

	
	front = SvvInternalList_GetFirst(list2);
	for(i = 0; i < l + r; i++)
	{
		if(OBJECT_AS_INT(SvvInternalListIterator_GetData(front)) != i)
		{
			DEBUG("Got %li, but %li expected.\n", OBJECT_AS_INT(SvvInternalListIterator_GetData(front)), i);
			return 1;
		};
		SvvInternalListIterator_GetNext(front);
	};
	
	
	SvvInternalList_Destroy(list);
	SvvInternalList_Destroy(list2);
	return 0;
};
