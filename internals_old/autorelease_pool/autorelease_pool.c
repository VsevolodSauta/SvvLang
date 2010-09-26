#include "internals/basics.h"
#include "internals/list/interface.h"


typedef struct AutoreleasePool {
	Object list;
} *AutoreleasePool;

#define LIST(rcvr) ((AutoreleasePool) (rcvr->entity))->list

#define AutoreleasePool_GID 0x60

DefaultOperations(AutoreleasePool);
DefaultInit(AutoreleasePool,
	LIST(receiver) = List_Create();
);
DefaultCreator(AutoreleasePool);

Action(AutoreleasePool, Compare, Object compareTo)
{
	return equal;
};

Action(AutoreleasePool, Destroy)
{
	Object_Release(LIST(receiver));
	return Object_Destroy(receiver);
};

Action(AutoreleasePool, Clone)
{
	return AutoreleasePool_Create();
};

Action(AutoreleasePool, Add, Object object)
{
	List_PushBack(LIST(receiver), object);
	Object_Release(object);
	return receiver;
};

Action(AutoreleasePool, Remove, Object object)
{
	List_RemoveFirst(LIST(receiver), object);
	return receiver;
};

Action(AutoreleasePool, Drain)
{
	List_Clean(LIST(receiver));
	return receiver;
};

