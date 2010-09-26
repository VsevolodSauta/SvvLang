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
	Object list = List_Create();
	Object iterator;
	
	
	for(i = 0; i < NODES; i++)
	{
		List_PushFront(list, INT_AS_OBJECT(i));
	};
	
	List_Sort(list);
	
	;
	for(iterator = List_First(list), i = 0; !ListIterator_ThisEnd(iterator); ListIterator_Next(iterator), i++)
	{
		if(OBJECT_AS_INT(ListIterator_ThisData(iterator)) != i)
		{
			DEBUG("Got %li, but %li expected.\n", OBJECT_AS_INT(ListIterator_ThisData(iterator)), i);
			return 1;
		};
	};
	
	Object_Release(list);
	return 0;
};
