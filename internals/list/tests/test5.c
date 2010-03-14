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
	
	front = SvvInternalList_GetIteratorFromPosition(list2, l - 1);

	TEST("Checking for correctness of GetIteratorFromPosition", 
		OBJECT_AS_INT(SvvInternalListIterator_GetData(front)) == (l - 1));

	// temp_list = (99998 99996 ... 8 6 4 2 0)
	temp_list = SvvInternalList_GetSublistBetweenPositions(list, 0, NODES / 2);
	
	back = SvvInternalList_GetLast(temp_list);
	TEST("Checking for correctness of GetSublistBetweenPositions", 
		OBJECT_AS_INT(SvvInternalListIterator_GetData(back)) == 0);
	SvvInternalListIterator_Destroy(back);
	
	// list2 = (0 1 2 3 ... 98 99 _99998 99996 ... 8 6 4 2 0_ 100 101 .. 148 149)
	SvvInternalListIterator_AddListAfter(front, temp_list);
	SvvInternalList_Destroy(temp_list);
	
	SvvInternalListIterator_FromPositionToPosition(front, l - 1, l + NODES / 2);
	TEST("Checking for correctness of FromPositionToPosition", 
		OBJECT_AS_INT(SvvInternalListIterator_GetData(front)) == l);
	
	// temp_list = (1 3 5 7 9 ... 99997 99999)
	temp_list = SvvInternalList_GetSublistBetweenPositions(list, NODES / 2, NODES);
	// list2 = (0 1 2 3 ... 98 99 99998 99996 ... 8 6 4 2 0 _1 3 5 7 9 ... 99997 99999_ 100 101 .. 148 149)
	SvvInternalListIterator_AddListBefore(front, temp_list);
	SvvInternalList_Destroy(temp_list);
	SvvInternalListIterator_Destroy(front);
	
	front = SvvInternalList_GetIteratorFromPosition(list2, l);
	TEST("Checking for correctness of GetIteratorFromPosition after AddList{Before|After}", 
		OBJECT_AS_INT(SvvInternalListIterator_GetData(front)) == (NODES & (~1)) - ((!(NODES & 1)) * 2));
	back = SvvInternalList_GetIteratorFromPosition(list2, l + NODES - 1);
	TEST("Checking for correctness of GetIteratorFromPosition after AddList{Before|After}", 
		OBJECT_AS_INT(SvvInternalListIterator_GetData(back)) == (NODES & (~1)) - 1 + ((NODES & 1) * 2));
	temp_list = SvvInternalList_GetSublistBetweenIterators(list2, front, back);
	SvvInternalListIterator_Destroy(front);
	SvvInternalListIterator_Destroy(back);
	front = SvvInternalList_GetFirst(temp_list);
	back = SvvInternalList_GetLast(temp_list);
	
	for(i = 1; i < NODES / 2; i++)
	{
		if(OBJECT_AS_INT(SvvInternalListIterator_GetData(front)) != OBJECT_AS_INT(SvvInternalListIterator_GetData(back)) + 1)
		{
			DEBUG("Got %li and %li.\n", OBJECT_AS_INT(SvvInternalListIterator_GetData(front)), OBJECT_AS_INT(SvvInternalListIterator_GetData(back)));
			return 1;
		};
		SvvInternalListIterator_GetNext(front);
		SvvInternalListIterator_GetPrev(back);
	};
	
	SvvInternalListIterator_Destroy(front);
	SvvInternalListIterator_Destroy(back);
	
	SvvInternalList_Destroy(list);
	SvvInternalList_Destroy(list2);
	SvvInternalList_Destroy(temp_list);
	return 0;
};
