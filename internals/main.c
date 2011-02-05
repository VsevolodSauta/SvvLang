#include "internals/basics.h"
#include "internals/Runtime/interface.h"
#include "internals/Machine/interface.h"
#include "os_dependent/linux.h"
#include "internals/AutoreleasePool/interface.h"
#if MEMORY_DEBUG
#include <stdio.h>
#endif

int DLEVEL = 0;

Object _autoreleasePool;
Object _console;
Object _json;

#if STDLIB
int main(void)
#else
void _start(void)
#endif
{
	_allocator = Allocator_Create();
	Object _runtime = Runtime_Create();
	Object _machine = Machine_Create();
	Machine_RestorePreviousState(_machine);
	AutoreleasePool_PushFrame(_autoreleasePool);
#if 0
	int i;
	for(i = 1; i < argc; i++)
	{
		Object _objectToImportName = StringFactory_FromCUTF8(_stringFactory, argv[i]);
		Machine_ImportUID(_machine, _objectToImportName);
	}
#else
	Object _objectToImportName = StringFactory_FromCUTF8(_stringFactory, "Приложение");
	Machine_ImportUID(_machine, _objectToImportName);
#endif
	AutoreleasePool_PopFrame(_autoreleasePool);
	Machine_Run(_machine);
	Object_Release(_machine);
	Object_Release(_runtime);
#if 0 // MEMORY_DEBUG
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