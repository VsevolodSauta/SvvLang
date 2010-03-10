#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"
#include "internal_string_set.h"
#include "internal_allocator.h"
#include "internal_globals.h"
#include "internal_nothing.h"
#include "internal_map.h"
#include "internal_string.h"

#define SET_FLAG 1

SvvInternalCreator(SvvInternalStringSetNode)
{
	SvvInternalStringSetNode node = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSetNode)));
	node->next_char = SvvInternalMap_Create();
	node->flags = 0;
	return node;
};

SvvInternalAction(SvvInternalStringSetNode, IsSet, int)
{
	return (Receiver->flags & SET_FLAG) != 0;
};

SvvInternalAction(SvvInternalStringSetNode, Set, void)
{
	Receiver->flags |= SET_FLAG;
};

SvvInternalAction(SvvInternalStringSetNode, UnSet, void)
{
	Receiver->flags &= ~SET_FLAG;
	while((!SvvInternalStringSetNode_IsSet(Receiver)) && (SvvInternalMap_GetCapacity(Receiver->next_char) == 0))
	{
		SvvInternalStringSetNode node = Receiver->parent;
		if(!IS_NOTHING(node))
		{
			SvvInternalStringSetNode_Destroy(Receiver);
			SvvInternalMap_RemoveValue(node->next_char, LINK_AS_OBJECT(Receiver));
		};
	};
};


SvvInternalAction(SvvInternalStringSetNode, GetNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator)
{
	while(!SvvInternalStringIterator_EndReached(Iterator))
	{
		SvvInternalChar current_char = SvvInternalStringIterator_GetChar(Iterator);
		SvvInternalStringIterator_GetNext(Iterator);
		if(SvvInternalMap_ExistsKey(Receiver->next_char, CHAR_AS_OBJECT(current_char)))
		{
			Receiver = OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver->next_char, CHAR_AS_OBJECT(current_char)));
		} else {
			return OBJECT_AS_LINK(SvvInternalNothing);
		};
	};
	return Receiver;
};


SvvInternalAction(SvvInternalStringSetNode, GetCreatingNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator)
{
	while(!SvvInternalStringIterator_EndReached(Iterator))
	{
		SvvInternalChar current_char = SvvInternalStringIterator_GetChar(Iterator);
		SvvInternalStringIterator_GetNext(Iterator);
		if(SvvInternalMap_ExistsKey(Receiver->next_char, CHAR_AS_OBJECT(current_char)))
		{
			Receiver = OBJECT_AS_LINK(SvvInternalMap_GetValue(Receiver->next_char, CHAR_AS_OBJECT(current_char)));
		} else {
			SvvInternalStringSetNode node = SvvInternalStringSetNode_Create();
			SvvInternalMap_Add(Receiver->next_char, CHAR_AS_OBJECT(current_char), LINK_AS_OBJECT(node));
			Receiver = node;
		};
	};
	return Receiver;
};


SvvInternalAction(SvvInternalStringSetNode, CleanSubTree, void)
{
	SvvInternalMapIterator iterator = SvvInternalMap_GetIterator(Receiver->next_char);
	while(!SvvInternalMapIterator_EndReached(iterator))
	{
		SvvInternalStringSetNode_CleanSubTree(OBJECT_AS_LINK(SvvInternalMapIterator_GetValue(iterator)));
		SvvInternalMapIterator_GetNext(iterator);
	};
	SvvInternalMapIterator_Destroy(iterator);
	SvvInternalMap_Destroy(Receiver->next_char);
	SvvInternalStringSetNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalStringSetNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalCreator(SvvInternalStringSetIteratorPathElement)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSetIteratorPathElement)));
};

SvvInternalAction(SvvInternalStringSetIteratorPathElement, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringSetIteratorPathElement, Clone, SvvInternalStringSetIteratorPathElement)
{
	SvvInternalStringSetIteratorPathElement element = SvvInternalStringSetIteratorPathElement_Create();
	element->string = SvvInternalString_Clone(Receiver->string);
	element->node = Receiver->node;
	return element;
};



SvvInternalCreator(SvvInternalStringSetIterator)
{
	SvvInternalStringSetIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringSetIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalStringSetIterator, GetNext, void)
{
	while(1)
	{
		if(!IS_NOTHING(Receiver->element))
		{
			SvvInternalStringSetIteratorPathElement_Destroy(Receiver->element);
		};
		
		if(SvvInternalStack_IsEmpty(Receiver->path))
		{
			Receiver->element = OBJECT_AS_LINK(SvvInternalNothing);
			break;
		} else {
			Receiver->element = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
			SvvInternalMapIterator iterator = SvvInternalMap_GetIterator(Receiver->element->node->next_char);
			while(!SvvInternalMapIterator_EndReached(iterator))
			{
				SvvInternalStringSetIteratorPathElement element = SvvInternalStringSetIteratorPathElement_Create();
				element->node = OBJECT_AS_LINK(SvvInternalMapIterator_GetValue(iterator));
				element->string = SvvInternalString_Clone(Receiver->element->string);
				SvvInternalString_AppendChar(element->string, OBJECT_AS_CHAR(SvvInternalMapIterator_GetKey(iterator)));
				SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
				SvvInternalMapIterator_GetNext(iterator);
			};
			SvvInternalMapIterator_Destroy(iterator);
			if(SvvInternalStringSetNode_IsSet(Receiver->element->node))
			{
				break;
			};
		};
	};
};

SvvInternalAction(SvvInternalStringSetIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->element);
};

SvvInternalAction(SvvInternalStringSetIterator, GetData, SvvInternalString)
{
	return SvvInternalString_Clone(Receiver->element->string);
};

SvvInternalAction(SvvInternalStringSetIterator, Destroy, void)
{
	while(!SvvInternalStack_IsEmpty(Receiver->path))
	{
		SvvInternalStringSetIteratorPathElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalStringSetIteratorPathElement_Destroy(element);
	};
	SvvInternalStringSetIteratorPathElement_Destroy(Receiver->element);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringSetIterator, Clone, SvvInternalStringSetIterator)
{
	SvvInternalStack intermediate_stack = SvvInternalStack_Create();
	SvvInternalStringSetIterator iterator = SvvInternalStringSetIterator_Create();
	
	while(!SvvInternalStack_IsEmpty(Receiver->path)){
		SvvInternalStack_Push(intermediate_stack, SvvInternalStack_Pop(Receiver->path));
	};
	
	while(!SvvInternalStack_IsEmpty(intermediate_stack)){
		SvvInternalStringSetIteratorPathElement element = OBJECT_AS_LINK(SvvInternalStack_Pop(intermediate_stack));
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(element));
		SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(SvvInternalStringSetIteratorPathElement_Clone(element)));
	};
	
	iterator->element = SvvInternalStringSetIteratorPathElement_Clone(Receiver->element);
	SvvInternalStack_Destroy(intermediate_stack);
	return iterator;
};

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
	SvvInternalStringSetIteratorPathElement element = SvvInternalStringSetIteratorPathElement_Create();
	element->node = Receiver->root;
	element->string = SvvInternalString_Create();
	
	SvvInternalStack_Push(iterator->path, LINK_AS_OBJECT(element));
	iterator->element = OBJECT_AS_LINK(SvvInternalNothing);
	SvvInternalStringSetIterator_GetNext(iterator);
	return iterator;
};
