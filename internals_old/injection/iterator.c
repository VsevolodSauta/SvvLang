#include "internals/basics.h"
#include "internals/injection/node.h"
#include "internals/injection/interface.h"
#include "internals/stack/interface.h"

SvvInternalCreator(SvvInternalInjectionIterator)
{
	SvvInternalInjectionIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalInjectionIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalInjectionIterator, AddCurrentNodeChildren, void)
{
	if(SvvInternalInjectionNode_Inited(Receiver->node->right))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->right));
	};
	if(SvvInternalInjectionNode_Inited(Receiver->node->left))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->left));
	};

};

SvvInternalAction(SvvInternalInjectionIterator, GetNext, void)
{
	if(SvvInternalStack_IsEmpty(Receiver->path))
	{
		Receiver->node = OBJECT_AS_LINK(SvvInternalNothing);
	} else {
		Receiver->node = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalInjectionIterator_AddCurrentNodeChildren(Receiver);
	};
};

SvvInternalAction(SvvInternalInjectionIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->node);
};

SvvInternalAction(SvvInternalInjectionIterator, GetKey, SvvInternalObject)
{
	return SvvInternalInjectionNode_GetKey(Receiver->node);
};

SvvInternalAction(SvvInternalInjectionIterator, GetValue, SvvInternalObject)
{
	return SvvInternalInjectionNode_GetKey(
		SvvInternalInjectionNode_GetValue(Receiver->node));
};

SvvInternalAction(SvvInternalInjectionIterator, Destroy, void)
{
	SvvInternalStack_Destroy(Receiver->path);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalInjectionIterator, Clone, SvvInternalInjectionIterator)
{
	SvvInternalInjectionIterator iterator = SvvInternalInjectionIterator_Create();
	iterator->path = SvvInternalStack_Clone(Receiver->path);
	iterator->node = Receiver->node;
	return iterator;
};

SvvInternalAction(SvvInternalInjectionIterator, GetNode, SvvInternalInjectionNode)
{
	return Receiver->node;
};

