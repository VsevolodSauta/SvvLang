#include "internals/basics.h"

#define OBJECTS 1000000
#define TIMES 10

int main(void)
{
	Object obj[OBJECTS];
	int i, j;
	DEBUG("Starting...");
	for(j = 0; j < TIMES; j++)
	{
		for(i = 0; i < OBJECTS; i++)
		{
			obj[i] = Object_Create();
		};
		for(i = 0; i < OBJECTS; i++)
		{
			Object_Release(obj[i]);
		};
	};
	DEBUG("Finishing.\n");
	return 0;
};