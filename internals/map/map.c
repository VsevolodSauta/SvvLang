#include "internals/basics.h"
#include "internals/map/interface.h"
#include "internals/map/node.h"

SvvInternalCreator(SvvInternalMap)
{
	SvvInternalMap set = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMap)));
	set->root = SvvInternalMapNode_Create();
	set->capacity = 0;
	SvvInternalMapNode_DeInit(set->root);
	return set;
};

SvvInternalAction(SvvInternalMap, Destroy, void)
{
	SvvInternalMapNode_CleanSubTree(Receiver->root);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalMap, Add, void, SvvInternalObject Key, SvvInternalObject Value)
{
	SvvInternalMapNode node = SvvInternalMapNode_GetNodeForKey(Receiver->root, Key);
	if(!SvvInternalMapNode_Inited(node))
	{
		SvvInternalMapNode_Init(node, Key, Value);
		Receiver->capacity++;
	};
};

SvvInternalAction(SvvInternalMap, RemoveKey, void, SvvInternalObject Key)
{
	SvvInternalMapNode node = SvvInternalMapNode_GetNodeForKey(Receiver->root, Key);
	if(SvvInternalMapNode_Inited(node))
	{
		SvvInternalMapNode_Remove(node);
		Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalMap, RemoveValue, void, SvvInternalObject Value)
{
	SvvInternalMapIterator iterator = SvvInternalMap_GetIterator(Receiver);
	while(!SvvInternalMapIterator_EndReached(iterator))
	{
		if(SvvInternalObject_Compare(SvvInternalMapIterator_GetValue(iterator), Value) == 0)
		{
			SvvInternalMapNode node = SvvInternalMapIterator_GetNode(iterator);
			SvvInternalMapIterator_Destroy(iterator);
			SvvInternalMapNode_Remove(node);
			return;
		};
	};
	SvvInternalMapIterator_Destroy(iterator);
	return;
};

SvvInternalAction(SvvInternalMap, Clean, void)
{
	SvvInternalMapNode_CleanSubTree(Receiver->root);
	Receiver->root = SvvInternalMapNode_Create();
	Receiver->capacity = 0;
	SvvInternalMapNode_DeInit(Receiver->root);
};

SvvInternalAction(SvvInternalMap, ExistsKey, int, SvvInternalObject Key)
{
	SvvInternalMapNode node = SvvInternalMapNode_GetNodeForKey(Receiver->root, Key);
	return SvvInternalMapNode_Inited(node);
};

SvvInternalAction(SvvInternalMap, GetValue, SvvInternalObject, SvvInternalObject Key)
{
	SvvInternalMapNode node = SvvInternalMapNode_GetNodeForKey(Receiver->root, Key);
	return SvvInternalMapNode_GetValue(node);
};

SvvInternalAction(SvvInternalMap, GetList, SvvInternalList)
{
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalObject object;
	SvvInternalMapIterator iterator = SvvInternalMap_GetIterator(Receiver);
	while(!SvvInternalMapIterator_EndReached(iterator))
	{
		object = SvvInternalMapIterator_GetKey(iterator);
		SvvInternalList_PushBack(list, object);
		object = SvvInternalMapIterator_GetValue(iterator);
		SvvInternalList_PushBack(list, object);
		SvvInternalMapIterator_GetNext(iterator);
	};
	SvvInternalMapIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalMap, AddList, void, SvvInternalList List)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(List);
	SvvInternalObject key;
	SvvInternalObject value;
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		key = SvvInternalListIterator_GetData(iterator);
		SvvInternalListIterator_GetNext(iterator);
		value = SvvInternalListIterator_GetData(iterator);
		SvvInternalListIterator_GetNext(iterator);
		SvvInternalMap_Add(Receiver, key, value);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalMap, GetIterator, SvvInternalMapIterator)
{
	SvvInternalMapIterator iterator = SvvInternalMapIterator_Create();
	if(SvvInternalMapNode_Inited(Receiver->root))
	{
		iterator->node = Receiver->root;
		SvvInternalMapIterator_AddCurrentNodeChildren(iterator);
	};
	
	return iterator;
};

SvvInternalAction(SvvInternalMap, GetCapacity, int)
{
	return Receiver->capacity;
};
