#include "internals/basics.h"
#include "internals/list/interface.h"

/*
Creator(List); // O(1)
Action(List, Destroy, void); // O(n)
Action(List, PushBack, void, Object Object); // O(1)
Action(List, PushFront, void, Object Object); // O(1)
*/

#define NODES 100

int main(void)
{
	INIT();
	
	Object j;
	Object nodes = NumberFactory_FromLong(numberFactory, NODES);
	Object list = List_Create();
	
	for(j = NumberFactory_FromLong(numberFactory, 0); Object_Compare(j, nodes) == less; Number_Inc(j))
	{
		if(Number_IsEven(j) == true)
		{
			List_PushBack(list, Object_TempClone(j));
		} else {
			List_PushFront(list, Object_TempClone(j));
		};
	};
	Object_Release(list);
	return 0;
};
