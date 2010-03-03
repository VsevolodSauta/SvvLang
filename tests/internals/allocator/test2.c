#include "internal_allocator.h"
#include "internal_object.h"
#include "internal_globals.h"
#include <unistd.h>

#define OBJECTS 10000000
#define TIMES 10

int main(void)
{
	SvvInternalObject obj[OBJECTS];
	int i, j;
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
	return 0;
};