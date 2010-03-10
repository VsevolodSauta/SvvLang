#include "internals/basics.h"
#include "internals/list/node.h"

SvvInternalCreator(SvvInternalListNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalListNode)));
};

SvvInternalAction(SvvInternalListNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};
