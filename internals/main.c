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
	Object _runtime = Runtime_Create();
	Object _machine = Machine_Create();
	Machine_Run(_machine);
	Object_Release(_machine);
	Object_Release(_runtime);
	Object_Release(_allocator);
#if MEMORY_DEBUG
	printf("Allocated: %i\nResized: %i\nFreed: %i\n",
		Allocator_GetAllocated(_allocator),
		Allocator_GetResized(_allocator),
		Allocator_GetFreed(_allocator)
	);
	printf(Allocator_GetAllocated(_allocator) - Allocator_GetFreed(_allocator) == 24 ? "Everything is OK.\n" : "Memory leaks detected.\n");
#endif
	return 0;
}