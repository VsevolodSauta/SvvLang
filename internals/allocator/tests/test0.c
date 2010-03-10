#include "internals/basics.h"

int main(void)
{
	SvvInternalObject obj = SvvInternalAllocator_New(SvvDefaultAllocator, 10);
	DEBUG("Allocated...");
	SvvInternalAllocator_Delete(SvvDefaultAllocator, obj);
	DEBUG(" deleted.\n");
	return 0;
};