#include "internals/basics.h"
#include "internals/list/interface.h"

/*
SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
*/

#define LISTS 100
#define TIMES 1

int main(void)
{
	INIT();
	
	int i, j;
	Object list[LISTS];
	
	for(j = 0; j < TIMES; j++)
	{
		for(i = 0; i < LISTS; i++)
		{
			list[i] = List_Create();
		};
		for(i = 0; i < LISTS; i++)
		{
			Object_Release(list[i]);
		};
	};
	return 0;
};
