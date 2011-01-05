#include "internals/basics.h"
#include "internals/Runtime/interface.h"
#include "internals/Machine/interface.h"
#include "os_dependent/linux.h"
#if MEMORY_DEBUG
#include <stdio.h>
#endif

#if DEBUG
int DLEVEL = 0;
#endif

Object _autoreleasePool;
Object _console;

void _start(void)
{
	_allocator = Allocator_Create();
	Object _runtime = Runtime_Create();
	Object _machine = Machine_Create();
	Machine_Run(_machine);
	Object_Release(_machine);
	Object_Release(_runtime);
#if MEMORY_DEBUG
	printf("Allocated: %i\nResized: %i\nFreed: %i\nNot freed: %i\n",
		Allocator_GetAllocated(_allocator),
		Allocator_GetResized(_allocator),
		Allocator_GetFreed(_allocator),
		Allocator_GetAllocated(_allocator) - Allocator_GetFreed(_allocator)
	);
	// Prev number of Not freed allocator objects was 24. Probably there is a bug in source code.
	printf(Allocator_GetAllocated(_allocator) - Allocator_GetFreed(_allocator) == 46 ? "Everything is OK.\n" : "Memory leaks detected.\n");
#endif
	Object_Release(_allocator);
	OSexit(0);
}