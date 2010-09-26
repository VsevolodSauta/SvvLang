#include "internals/basics.h"
#include "internals/set/interface.h"
#include "internals/set/node.h"

#include "internals/stack/interface.h"

SvvInternalCreator(SvvInternalSetIterator)
{
	SvvInternalSetIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalSetIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalSetIterator, AddCurrentNodeChildren, void)
{
	if(SvvInternalSetNode_Inited(Receiver->node->right))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->right));
	};
	if(SvvInternalSetNode_Inited(Receiver->node->left))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->left));
	};

};

SvvInternalAction(SvvInternalSetIterator, GetNext, void)
{
	if(SvvInternalStack_IsEmpty(Receiver->path))
	{
		Receiver->node = OBJECT_AS_LINK(SvvInternalNothing);
	} else {
		Receiver->node = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalSetIterator_AddCurrentNodeChildren(Receiver);
	};
};

SvvInternalAction(SvvInternalSetIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->node);
};

SvvInternalAction(SvvInternalSetIterator, GetData, SvvInternalObject)
{
	return Receiver->node->data;
};

SvvInternalAction(SvvInternalSetIterator, Destroy, void)
{
	SvvInternalStack_Destroy(Receiver->path);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalSetIterator, Clone, SvvInternalSetIterator)
{
	SvvInternalSetIterator iterator = SvvInternalSetIterator_Create();
	iterator->path = SvvInternalStack_Clone(Receiver->path);
	iterator->node = Receiver->node;
	return iterator;
};

