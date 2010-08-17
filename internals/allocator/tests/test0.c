#include "internals/basics.h"

int main(void)
{
	Object obj = Allocator_New(allocator, 10);
	DEBUG("Allocated...");
	Allocator_Delete(allocator, obj);
	DEBUG(" deleted.\n");
	return 0;
};