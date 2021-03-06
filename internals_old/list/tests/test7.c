#include "internals/basics.h"
#include "internals/list/interface.h"

/*
Creator(List); // O(1)
Action(List, Destroy, void); // O(n)
Action(List, PushBack, void, Object Object); // O(1)
Action(List, PushFront, void, Object Object); // O(1)
Action(List, First, ListIterator); // O(1)
Action(List, Last, ListIterator); // O(1)
Action(List, Clean, void);
Action(List, SublistBetweenPositions, List, int. int);
Action(List, SublistBetweenIterators, List, ListIterator, ListIterator);
Action(ListIterator, AddListBefore, void, List);
Action(ListIterator, AddListAfter, void, List);
Action(ListIterator, Next, void); // O(1)
Action(ListIterator, Prev, void); // O(1)
Action(ListIterator, BeginReached, int); // O(1)
Action(ListIterator, EndReached, int); // O(1)
*/

#define NODES 100
#define TIMES 1

int main(void)
{
	INIT();
	
	long int i;
	int l = 10, r = 5;
	Object list = List_Create();
	Object list2 = List_Create();
	Object front, back;
	
	
	// list2 = (0 1 2 3 4 5 6 ... 148 149)
	for(i = 0; i < l + r; i++)
	{
		List_PushBack(list2, INT_AS_OBJECT(i));
	};
	
	// list = (99998 99996 ... 8 6 4 2 0 1 3 5 7 9 ... 99997 99999 )
	for(i = 0; i < NODES; i++)
	{
		if(i & 1)
		{
			List_PushBack(list, INT_AS_OBJECT(i));
		} else {
			List_PushFront(list, INT_AS_OBJECT(i));
		};
	};

	for(front = List_First(list), i = 0; i < NODES / 2; ListIterator_Next(front), i++)
	{
		List_AddAfterPosition(list2, INT_AS_OBJECT(l - 1 + i), ListIterator_ThisData(front));
	};

	for(back = List_Last(list), i = 0; i < NODES / 2; ListIterator_Prev(back), i++)
	{
		List_AddAfterPosition(list2, INT_AS_OBJECT(l + NODES / 2 - 1), ListIterator_ThisData(back));
	};
	

	front = List_IteratorFromPosition(list2, INT_AS_OBJECT(l));
	ListIterator_RemoveCount(front, INT_AS_OBJECT(NODES));

	
	front = List_First(list2);
	for(i = 0; i < l + r; i++)
	{
		if(OBJECT_AS_INT(ListIterator_ThisData(front)) != i)
		{
			DEBUG("Got %li, but %li expected.\n", OBJECT_AS_INT(ListIterator_ThisData(front)), i);
			return 1;
		};
		ListIterator_Next(front);
	};
	
	
	Object_Release(list);
	Object_Release(list2);
	return 0;
};
