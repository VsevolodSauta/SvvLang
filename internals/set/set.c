#include "internals/basics.h"
#include "internals/set/interface.h"
#include "internals/set/node.h"

// SvvInternalSet

SvvInternalCreator(SvvInternalSet)
{
	SvvInternalSet set = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalSet)));
	set->root = SvvInternalSetNode_Create();
	set->capacity = 0;
	SvvInternalSetNode_DeInit(set->root);
	return set;
};

SvvInternalAction(SvvInternalSet, Destroy, void)
{
	SvvInternalSetNode_CleanSubTree(Receiver->root);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalSet, Add, void, SvvInternalObject Object)
{
	SvvInternalSetNode node = SvvInternalSetNode_GetNodeForData(Receiver->root, Object);
	if(!SvvInternalSetNode_Inited(node))
	{
		SvvInternalSetNode_Init(node, Object);
		Receiver->capacity++;
	};
};

SvvInternalAction(SvvInternalSet, Remove, void, SvvInternalObject Object)
{
	SvvInternalSetNode node = SvvInternalSetNode_GetNodeForData(Receiver->root, Object);
	if(SvvInternalSetNode_Inited(node))
	{
		SvvInternalSetNode_Remove(node);
		Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalSet, Clean, void)
{
	SvvInternalSetNode_CleanSubTree(Receiver->root);
	Receiver->root = SvvInternalSetNode_Create();
	Receiver->capacity = 0;
	SvvInternalSetNode_DeInit(Receiver->root);
};

SvvInternalAction(SvvInternalSet, Exists, int, SvvInternalObject Object)
{
	SvvInternalSetNode node = SvvInternalSetNode_GetNodeForData(Receiver->root, Object);
	return SvvInternalSetNode_Inited(node);
};

SvvInternalAction(SvvInternalSet, GetList, SvvInternalList)
{
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalSetIterator iterator = SvvInternalSet_GetIterator(Receiver);
	while(!SvvInternalSetIterator_EndReached(iterator))
	{
		SvvInternalObject object = SvvInternalSetIterator_GetData(iterator);
		SvvInternalList_PushBack(list, object);
		SvvInternalSetIterator_GetNext(iterator);
	};
	SvvInternalSetIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalSet, AddList, void, SvvInternalList List)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(List);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
		SvvInternalSet_Add(Receiver, object);
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalSet, GetIterator, SvvInternalSetIterator)
{
	SvvInternalSetIterator iterator = SvvInternalSetIterator_Create();
	if(SvvInternalSetNode_Inited(Receiver->root))
	{
		iterator->node = Receiver->root;
		SvvInternalSetIterator_AddCurrentNodeChildren(iterator);
	};
	
	return iterator;
};

SvvInternalAction(SvvInternalSet, GetCapacity, int)
{
	return Receiver->capacity;
};

SvvInternalAction(SvvInternalSet, Dump, void)
{
	SvvInternalSetIterator iterator = SvvInternalSet_GetIterator(Receiver);
	while(!SvvInternalSetIterator_EndReached(iterator))
	{
		DEBUG("%li ", OBJECT_AS_INT(SvvInternalSetIterator_GetData(iterator)));
		SvvInternalSetIterator_GetNext(iterator);
	};
	SvvInternalSetIterator_Destroy(iterator);
	DEBUG("\n");
};
