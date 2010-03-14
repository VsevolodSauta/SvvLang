#include "internals/basics.h"
#include "internals/string_map/interface.h"

#include "internals/list/interface.h"
#include "internals/stack/interface.h"
#include "internals/string/interface.h"

SvvInternalCreator(SvvInternalStringMap)
{
	SvvInternalStringMap map = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringMap)));
	map->root = SvvInternalStringMapNode_Create();
	map->capacity = 0;
	return map;
};

SvvInternalAction(SvvInternalStringMap, Destroy, void)
{
	SvvInternalStringMapNode_CleanSubTree(Receiver->root);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringMap, Add, void, SvvInternalString Key, SvvInternalObject Value)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(Key);
	SvvInternalStringMapNode node = SvvInternalStringMapNode_GetCreatingNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	if(!SvvInternalStringMapNode_IsMapped(node))
	{
		Receiver->capacity++;
	};
	SvvInternalStringMapNode_Map(node, Value);
};

SvvInternalAction(SvvInternalStringMap, RemoveKey, void, SvvInternalString Key)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(Key);
	SvvInternalStringMapNode node = SvvInternalStringMapNode_GetNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	if((!IS_NOTHING(node)) && (SvvInternalStringMapNode_IsMapped(node)))
	{
		SvvInternalStringMapNode_UnMap(node);
		Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalStringMap, Clean, void)
{
	SvvInternalStringMapNode_CleanSubTree(Receiver->root);
	Receiver->root = SvvInternalStringMapNode_Create();
	Receiver->capacity = 0;
};

SvvInternalAction(SvvInternalStringMap, ExistsKey, int, SvvInternalString Key)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(Key);
	SvvInternalStringMapNode node = SvvInternalStringMapNode_GetNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	return (!IS_NOTHING(node)) && (SvvInternalStringMapNode_IsMapped(node));
};

SvvInternalAction(SvvInternalStringMap, GetValue, SvvInternalObject, SvvInternalString Key)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(Key);
	SvvInternalStringMapNode node = SvvInternalStringMapNode_GetNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
#if 0
	if((!IS_NOTHING(node)) && (SvvInternalStringMapNode_IsMapped(node)))
	{
		return SvvInternalStringMapNode_GetValue(node);
	};
#endif
	
	return SvvInternalStringMapNode_GetValue(node);
};


SvvInternalAction(SvvInternalStringMap, GetList, SvvInternalList)
{
	SvvInternalStringMapIterator iterator = SvvInternalStringMap_GetIterator(Receiver);
	SvvInternalList list = SvvInternalList_Create();
	while(!SvvInternalStringMapIterator_EndReached(iterator))
	{
		SvvInternalList_PushBack(list, LINK_AS_OBJECT(SvvInternalStringMapIterator_GetKey(iterator)));
		SvvInternalList_PushBack(list, SvvInternalStringMapIterator_GetValue(iterator));
		SvvInternalStringMapIterator_GetNext(iterator);
	};
	SvvInternalStringMapIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalStringMap, AddList, void, SvvInternalList List)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(List);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalString key = OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator));
		SvvInternalListIterator_GetNext(iterator);
		SvvInternalObject value = SvvInternalListIterator_GetData(iterator);
		SvvInternalListIterator_GetNext(iterator);
		SvvInternalStringMap_Add(Receiver, key, value);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalStringMap, GetIterator, SvvInternalStringMapIterator)
{
	SvvInternalStringMapIterator iterator = SvvInternalStringMapIterator_Create();
	SvvInternalStringMapIteratorElement element = SvvInternalStringMapIteratorElement_Create();
	element->node = Receiver->root;
	element->string = SvvInternalString_Create();
	
	SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(element));
	iterator->element = OBJECT_AS_LINK(SvvInternalNothing);
	SvvInternalStringMapIterator_GetNext(iterator);
	return iterator;
};

SvvInternalAction(SvvInternalStringMap, GetCapacity, int)
{
	return Receiver->capacity;
};
