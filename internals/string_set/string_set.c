#include "internals/basics.h"
#include "internals/string_set/interface.h"

#include "internals/list/interface.h"
#include "internals/stack/interface.h"
#include "internals/string/interface.h"

SvvInternalCreator(SvvInternalStringSet)
{
	SvvInternalStringSet set = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSet)));
	set->root = SvvInternalStringSetNode_Create();
	return set;
};

SvvInternalAction(SvvInternalStringSet, Destroy, void)
{
	SvvInternalStringSetNode_CleanSubTree(Receiver->root);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringSet, Add, void, SvvInternalString String)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(String);
	SvvInternalStringSetNode node = SvvInternalStringSetNode_GetCreatingNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	SvvInternalStringSetNode_Set(node);
};

SvvInternalAction(SvvInternalStringSet, Remove, void, SvvInternalString String)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(String);
	SvvInternalStringSetNode node = SvvInternalStringSetNode_GetNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	if(!IS_NOTHING(node))
	{
		SvvInternalStringSetNode_UnSet(node);
	};
};

SvvInternalAction(SvvInternalStringSet, Clean, void)
{
	SvvInternalStringSetNode_CleanSubTree(Receiver->root);
	Receiver->root = SvvInternalStringSetNode_Create();
};

SvvInternalAction(SvvInternalStringSet, Exists, int, SvvInternalString String)
{
	SvvInternalStringIterator iterator = SvvInternalString_GetFirst(String);
	SvvInternalStringSetNode node = SvvInternalStringSetNode_GetNodeForData(Receiver->root, iterator);
	SvvInternalStringIterator_Destroy(iterator);
	return !IS_NOTHING(node);
};

SvvInternalAction(SvvInternalStringSet, GetList, SvvInternalList)
{
	SvvInternalStringSetIterator iterator = SvvInternalStringSet_GetIterator(Receiver);
	SvvInternalList list = SvvInternalList_Create();
	while(!SvvInternalStringSetIterator_EndReached(iterator))
	{
		SvvInternalList_PushBack(list, LINK_AS_OBJECT(SvvInternalStringSetIterator_GetData(iterator)));
		SvvInternalStringSetIterator_GetNext(iterator);
	};
	SvvInternalStringSetIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalStringSet, AddList, void, SvvInternalList List)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(List);
	while(!SvvInternalListIterator_EndReached(iterator))
	{
		SvvInternalStringSet_Add(Receiver, OBJECT_AS_LINK(SvvInternalListIterator_GetData(iterator)));
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalStringSet, GetIterator, SvvInternalStringSetIterator)
{
	SvvInternalStringSetIterator iterator = SvvInternalStringSetIterator_Create();
	SvvInternalStringSetIteratorElement element = SvvInternalStringSetIteratorElement_Create();
	element->node = Receiver->root;
	element->string = SvvInternalString_Create();
	
	SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(element));
	iterator->element = OBJECT_AS_LINK(SvvInternalNothing);
	SvvInternalStringSetIterator_GetNext(iterator);
	return iterator;
};
