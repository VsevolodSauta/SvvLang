#include "internals/basics.h"

#define OBJECTS 1000000
#define TIMES 10

int main(void)
{
	SvvInternalObject obj[OBJECTS];
	int i, j;
	DEBUG("Starting...");
	for(j = 0; j < TIMES; j++)
	{
		for(i = 0; i < OBJECTS; i++)
		{
			obj[i] = SvvInternalAllocator_New(SvvDefaultAllocator, 16);
		};
		for(i = 0; i < OBJECTS; i++)
		{
			SvvInternalAllocator_Delete(SvvDefaultAllocator, obj[i]);
		};
	};
	DEBUG("Finishing.\n");
	return 0;
};