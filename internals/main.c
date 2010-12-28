#include "internals/basics.h"
#include "internals/Runtime/interface.h"
#include "internals/Machine/interface.h"
#include <stdio.h>

#if DEBUG
int DLEVEL = 0;
#endif

int main(int argc, char** argv)
{
	_allocator = Allocator_Create();
	Object runtime = Runtime_Create();
	Object machine = Machine_Create();
	Machine_Run(machine);
	Object_Release(machine);
	Object_Release(runtime);
#if MEMORY_DEBUG
	printf("Allocated: %i\nResized: %i\nFreed: %i\n",
		Allocator_GetAllocated(),
		Allocator_GetResized(),
		Allocator_GetFreed()
	);
	DMSG(Allocator_GetAllocated() - Allocator_GetFreed() == 24 ? "Everything is OK.\n" : "Memory leaks detected.\n");
	Allocator_Dump();
#endif
	return 0;
}