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
	
	int i, j;
	Object list = List_Create();
	
	for(j = 0; j < TIMES; j++)
	{
		Object front, back;
		for(i = 0; i < NODES; i++)
		{
			if(i & 1)
			{
				List_PushBack(list, INT_AS_OBJECT(i));
			} else {
				List_PushFront(list, INT_AS_OBJECT(i));
			};
		};
		
		front = List_First(list);
		back = List_Last(list);
		
		while(!ListIterator_ThisEnd(front))
		{
			ListIterator_Next(front);
			ListIterator_Prev(back);
		};
		
		if(!ListIterator_ThisBegin(back))
		{
			return 1;
		};
		
		List_Clean(list);
	};
	Object_Release(list);
	return 0;
};
