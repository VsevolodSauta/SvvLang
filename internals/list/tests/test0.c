#include "internals/list/interface.h"
//#include "internals/object/interface.h"

/*
SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
*/

#define LISTS 100000
#define TIMES 100

int main(void)
{
	int i, j;
	SvvInternalList list[LISTS];
	
	for(j = 0; j < TIMES; j++)
	{
		for(i = 0; i < LISTS; i++)
		{
			list[i] = SvvInternalList_Create();
		};
		for(i = 0; i < LISTS; i++)
		{
			SvvInternalList_Destroy(list[i]);
		};
	};
	return 0;
};
