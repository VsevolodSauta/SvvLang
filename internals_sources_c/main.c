#include "internals/basics.h"
#include "internals/Runtime/interface.h"
#include "internals/Machine/interface.h"
#include "os_dependent/linux.h"
#include "internals/AutoreleasePool/interface.h"
#include "internals/ThreadManager/interface.h"
#include "internals/initializers.h"

int DLEVEL = 0;

void _start(void)
{
	_allocator = Allocator_Create();
	_allocatorForStack = AllocatorForStack_Create();
	
	Object _runtime = Runtime_Create();
	__initAllClasses();
	
	Object _machine = Machine_Create();
	Machine_RestorePreviousState(_machine);
	AutoreleasePool_PushFrame(ThreadManager_AutoreleasePool(_threadManager));
#if 0
	int i;
	for(i = 1; i < argc; i++)
	{
		Object _objectToImportName = StringFactory_FromCUTF8(_stringFactory, argv[i]);
		Machine_ImportUID(_machine, _objectToImportName);
	}
#else
	Machine_ImportActor(_machine, StringFactory_FromCUTF8(_stringFactory, "SvvLanguage_C/externals/Приложение"));
#endif
	AutoreleasePool_PopFrame(ThreadManager_AutoreleasePool(_threadManager));
	Machine_Run(_machine);
	Object_Release(_machine);
	Object_Release(_runtime);
	Object_Release(_allocator);
	OSexit(0);
}