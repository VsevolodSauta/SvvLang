#include "internals/basics.h"
#include "internals/string_set/node.h"

#include "internals/map/interface.h"
#include "internals/string/interface.h"

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

