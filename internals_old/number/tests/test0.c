#include "internals/basics.h"

#define NODES 100

int main(void)
{
	Object j;
	Object limit = NumberFactory_FromLong(numberFactory, NODES);
	less = Object_Create();
	greater = Object_Create();
	equal = Object_Create();
	
	for(j = NumberFactory_FromLong(numberFactory, 0); Object_Compare(j, limit) == less; Number_Inc(j))
	{
		Number_Dump(j);
	};
	return 0;
};
