#include "internals/basics.h"

typedef struct AutoreleasePoolsStack {
	Object stack;
} *AutoreleasePoolsStack;

#define STACK(rcvr) ENTITY(rcvr, AutoreleasePoolsStack)->stack

#define AutoreleasePoolsStack_GID 0x80

DefaultOperations(AutoreleasePoolsStack);
DefaultInit(AutoreleasePoolsStack);
DefaultCreator(AutoreleasePoolsStack);

Action(AutoreleasePoolsStack, Clone)
{
	return AutoreleasePoolsStack_Create();
};

Action(AutoreleasePoolsStack, Compare, Object toCompare)
{
	return equal;
};

Action(AutoreleasePoolsStack, Destroy)
{
	return Object_Destroy(receiver);
};

Object autoreleasePoolsStack;