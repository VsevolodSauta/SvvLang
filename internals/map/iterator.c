#include "internals/basics.h"
#include "internals/map/node.h"
#include "internals/map/interface.h"
#include "internals/stack/interface.h"

SvvInternalCreator(SvvInternalMapIterator)
{
	SvvInternalMapIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMapIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalMapIterator, AddCurrentNodeChildren, void)
{
	if(SvvInternalMapNode_Inited(Receiver->node->right))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->right));
	};
	if(SvvInternalMapNode_Inited(Receiver->node->left))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->left));
	};

};

SvvInternalAction(SvvInternalMapIterator, GetNext, void)
{
	if(SvvInternalStack_IsEmpty(Receiver->path))
	{
		Receiver->node = OBJECT_AS_LINK(SvvInternalNothing);
	} else {
		Receiver->node = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalMapIterator_AddCurrentNodeChildren(Receiver);
	};
};

SvvInternalAction(SvvInternalMapIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->node);
};

SvvInternalAction(SvvInternalMapIterator, GetKey, SvvInternalObject)
{
	return SvvInternalMapNode_GetKey(Receiver->node);
};

SvvInternalAction(SvvInternalMapIterator, GetValue, SvvInternalObject)
{
	return SvvInternalMapNode_GetValue(Receiver->node);
};

SvvInternalAction(SvvInternalMapIterator, Destroy, void)
{
	SvvInternalStack_Destroy(Receiver->path);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalMapIterator, Clone, SvvInternalMapIterator)
{
	SvvInternalMapIterator iterator = SvvInternalMapIterator_Create();
	iterator->path = SvvInternalStack_Clone(Receiver->path);
	iterator->node = Receiver->node;
	return iterator;
};

SvvInternalAction(SvvInternalMapIterator, GetNode, SvvInternalMapNode)
{
	return Receiver->node;
};

