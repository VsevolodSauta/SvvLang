#include "internals/list/interface.h"
//#include "internal_object.h"

/*
SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
SvvInternalAction(SvvInternalList, PushBack, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, PushFront, void, SvvInternalObject Object); // O(1)
*/

#define NODES 100
#define TIMES 1

int main(void)
{
	int i, j;
	
	for(j = 0; j < TIMES; j++)
	{
		SvvInternalList list = SvvInternalList_Create();
		for(i = 0; i < NODES; i++)
		{
			if(i & 1)
			{
				SvvInternalList_PushBack(list, INT_AS_OBJECT(i));
			} else {
				SvvInternalList_PushFront(list, INT_AS_OBJECT(i));
			};
		};
		SvvInternalList_Destroy(list);
	};
	return 0;
};
