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

#define NODES 10
#define TIMES 1

int main(void)
{
	INIT();
	
	long int i;
	long int l = 10, r = 5;
	Object list = List_Create();
	Object list2 = List_Create();
	Object temp_list;
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
	
	front = List_IteratorFromPosition(list2, INT_AS_OBJECT(l - 1));

	TEST("Checking for correctness of IteratorFromPosition", 
		OBJECT_AS_INT(ListIterator_ThisData(front)) == (l - 1));
		
	TEST("Checking lists' sizes",
		(OBJECT_AS_INT(List_Size(list)) == NODES) &&
		(OBJECT_AS_INT(List_Size(list2)) == l + r));

	// temp_list = (99998 99996 ... 8 6 4 2 0)
	temp_list = List_SublistBetweenPositions(list, INT_AS_OBJECT(0), INT_AS_OBJECT(NODES / 2));
	
	back = List_Last(temp_list);
	TEST("Checking for correctness of SublistBetweenPositions", 
		OBJECT_AS_INT(ListIterator_ThisData(back)) == 0);
	
	// list2 = (0 1 2 3 ... 98 99 _99998 99996 ... 8 6 4 2 0_ 100 101 .. 148 149)
	ListIterator_AddListAfter(front, temp_list);
	
	ListIterator_FromPositionToPosition(front, INT_AS_OBJECT(l - 1), INT_AS_OBJECT(l + NODES / 2));
	TEST("Checking for correctness of FromPositionToPosition", 
		OBJECT_AS_INT(ListIterator_ThisData(front)) == l);
	
	// temp_list = (1 3 5 7 9 ... 99997 99999)
	temp_list = List_SublistBetweenPositions(list, INT_AS_OBJECT(NODES / 2), INT_AS_OBJECT(NODES));
	// list2 = (0 1 2 3 ... 98 99 99998 99996 ... 8 6 4 2 0 _1 3 5 7 9 ... 99997 99999_ 100 101 .. 148 149)
	ListIterator_AddListBefore(front, temp_list);
	Object_Release(temp_list);
	
	front = List_IteratorFromPosition(list2, INT_AS_OBJECT(l));
	TEST("Checking for correctness of IteratorFromPosition after AddList{Before|After}", 
		OBJECT_AS_INT(ListIterator_ThisData(front)) == (NODES & (~1)) - ((!(NODES & 1)) * 2));
	back = List_IteratorFromPosition(list2, INT_AS_OBJECT(l + NODES - 1));
	TEST("Checking for correctness of IteratorFromPosition after AddList{Before|After}", 
		OBJECT_AS_INT(ListIterator_ThisData(back)) == (NODES & (~1)) - 1 + ((NODES & 1) * 2));
	temp_list = List_SublistBetweenIterators(list2, front, back);
	front = List_First(temp_list);
	back = List_Last(temp_list);
	
	for(i = 1; i < NODES / 2; i++)
	{
		if(OBJECT_AS_INT(ListIterator_ThisData(front)) != OBJECT_AS_INT(ListIterator_ThisData(back)) + 1)
		{
			DEBUG("Got %li and %li.\n", OBJECT_AS_INT(ListIterator_ThisData(front)), OBJECT_AS_INT(ListIterator_ThisData(back)));
			return 1;
		};
		ListIterator_Next(front);
		ListIterator_Prev(back);
	};
	
	Object_Release(list);
	Object_Release(list2);
	Object_Release(temp_list);
	return 0;
};
