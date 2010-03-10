#include "internals/list/interface.h"
//#include "internal_object.h"

/*
SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
SvvInternalAction(SvvInternalList, PushBack, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, PushFront, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, GetFirst, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, Clean, void);

SvvInternalAction(SvvInternalListIterator, GetNext, void); // O(1)
SvvInternalAction(SvvInternalListIterator, GetPrev, void); // O(1)
SvvInternalAction(SvvInternalListIterator, BeginReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, EndReached, int); // O(1)
*/

#define NODES 100000
#define TIMES 100

int main(void)
{
	int i, j;
	SvvInternalList list = SvvInternalList_Create();
	
	for(j = 0; j < TIMES; j++)
	{
		SvvInternalListIterator front, back;
		for(i = 0; i < NODES; i++)
		{
			if(i & 1)
			{
				SvvInternalList_PushBack(list, INT_AS_OBJECT(i));
			} else {
				SvvInternalList_PushFront(list, INT_AS_OBJECT(i));
			};
		};
		
		front = SvvInternalList_GetFirst(list);
		back = SvvInternalList_GetLast(list);
		
		while(!SvvInternalListIterator_EndReached(front))
		{
			SvvInternalListIterator_GetNext(front);
		};
		
		while(!SvvInternalListIterator_BeginReached(back))
		{
			SvvInternalListIterator_GetPrev(back);
		};
		
		SvvInternalListIterator_Destroy(front);
		SvvInternalListIterator_Destroy(back);
		
		SvvInternalList_Clean(list);
	};
	SvvInternalList_Destroy(list);
	return 0;
};
