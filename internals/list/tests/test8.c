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
	long int i;
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalListIterator iterator;
	
	
	for(i = 0; i < NODES; i++)
	{
		SvvInternalList_PushFront(list, INT_AS_OBJECT(i));
	};
	
	SvvInternalList_Sort(list);
	
	;
	for(iterator = SvvInternalList_GetFirst(list), i = 0; !SvvInternalListIterator_EndReached(iterator); SvvInternalListIterator_GetNext(iterator), i++)
	{
		if(OBJECT_AS_INT(SvvInternalListIterator_GetData(iterator)) != i)
		{
			DEBUG("Got %li, but %li expected.\n", OBJECT_AS_INT(SvvInternalListIterator_GetData(iterator)), i);
			return 1;
		};
	};
	SvvInternalListIterator_Destroy(iterator);
	
	SvvInternalList_Destroy(list);
	return 0;
};
