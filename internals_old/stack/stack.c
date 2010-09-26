#include "internals/basics.h"
#include "internals/stack/interface.h"
#include "internals/list/interface.h"

typedef struct Stack {
	Object list;
} *Stack;

#define LIST(rcvr) ENTITY(rcvr, Stack)->list

#define Stack_GID 0x70

DefaultOperations(Stack);
DefaultInit(Stack,
	LIST(receiver) = List_Create();
);

DefaultCreator(Stack);

Action(Stack, Destroy)
{
	Object_Release(LIST(receiver));
	return Object_Destroy(receiver);
};

Action(Stack, Compare, Object toCompare)
{
	return Object_Compare(LIST(receiver), LIST(toCompare));
};

Action(Stack, Push, Object object)
{
	List_PushBack(LIST(receiver), object);
	return receiver;
};

Action(Stack, Pop)
{
	Object iterator = List_Last(LIST(receiver));
	Object object = ListIterator_ThisData(iterator);
	ListIterator_ThisRemove(iterator);
	return object;
};

Action(Stack, Peek)
{
	Object iterator = List_Last(LIST(receiver));
	Object object = ListIterator_ThisData(iterator);
	return object;
};

Action(Stack, Clean)
{
	List_Clean(LIST(receiver));
	return receiver;
};

Action(Stack, IsEmpty)
{
	Object iterator = List_First(LIST(receiver));
	return ListIterator_ThisEnd(iterator);
};

Action(Stack, Clone)
{
	Object toReturn = Stack_Create();
	Object_Release(LIST(toReturn));
	LIST(toReturn) = List_Clone(LIST(receiver));
	return toReturn;
};
