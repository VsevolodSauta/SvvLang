#include "internals/basics.h"
#include "internals/string_map/node.h"

#include "internals/injection/interface.h"
#include "internals/string/interface.h"

#define MAPPED_FLAG 1

SvvInternalCreator(SvvInternalStringMapNode)
{
	SvvInternalStringMapNode node = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringMapNode)));
	node->next_char = SvvInternalInjection_Create();
	node->flags = 0;
	return node;
};

SvvInternalAction(SvvInternalStringMapNode, IsMapped, int)
{
	return (Receiver->flags & MAPPED_FLAG) != 0;
};

SvvInternalAction(SvvInternalStringMapNode, Map, void, SvvInternalObject Value)
{
	Receiver->flags |= MAPPED_FLAG;
	SvvInternalStringMapNode_SetValue(Receiver, Value);
};

SvvInternalAction(SvvInternalStringMapNode, GetValue, SvvInternalObject)
{
	return Receiver->value;
};

SvvInternalAction(SvvInternalStringMapNode, SetValue, void, SvvInternalObject Value)
{
	Receiver->value = Value;
};


SvvInternalAction(SvvInternalStringMapNode, UnMap, void)
{
	Receiver->flags &= ~MAPPED_FLAG;
	while((!SvvInternalStringMapNode_IsMapped(Receiver)) && (SvvInternalInjection_GetCapacity(Receiver->next_char) == 0))
	{
		SvvInternalStringMapNode node = Receiver->parent;
		if(!IS_NOTHING(node))
		{
			SvvInternalStringMapNode_Destroy(Receiver);
			SvvInternalInjection_RemoveValue(node->next_char, LINK_AS_OBJECT(Receiver));
		};
		Receiver = node;
	};
};


SvvInternalAction(SvvInternalStringMapNode, GetNodeForData, SvvInternalStringMapNode, SvvInternalStringIterator Iterator)
{
	while(!SvvInternalStringIterator_EndReached(Iterator))
	{
		SvvInternalChar current_char = SvvInternalStringIterator_CharGet(Iterator);
		SvvInternalStringIterator_GetNext(Iterator);
		if(SvvInternalInjection_ExistsKey(Receiver->next_char, CHAR_AS_OBJECT(current_char)))
		{
			Receiver = OBJECT_AS_LINK(SvvInternalInjection_GetValue(Receiver->next_char, CHAR_AS_OBJECT(current_char)));
		} else {
			return OBJECT_AS_LINK(SvvInternalNothing);
		};
	};
	return Receiver;
};


SvvInternalAction(SvvInternalStringMapNode, GetCreatingNodeForData, SvvInternalStringMapNode, SvvInternalStringIterator Iterator)
{
	while(!SvvInternalStringIterator_EndReached(Iterator))
	{
		SvvInternalChar current_char = SvvInternalStringIterator_CharGet(Iterator);
		SvvInternalStringIterator_GetNext(Iterator);
		if(SvvInternalInjection_ExistsKey(Receiver->next_char, CHAR_AS_OBJECT(current_char)))
		{
			Receiver = OBJECT_AS_LINK(SvvInternalInjection_GetValue(Receiver->next_char, CHAR_AS_OBJECT(current_char)));
		} else {
			SvvInternalStringMapNode node = SvvInternalStringMapNode_Create();
			SvvInternalInjection_Add(Receiver->next_char, CHAR_AS_OBJECT(current_char), LINK_AS_OBJECT(node));
			Receiver = node;
		};
	};
	return Receiver;
};


SvvInternalAction(SvvInternalStringMapNode, CleanSubTree, void)
{
	SvvInternalInjectionIterator iterator = SvvInternalInjection_GetIterator(Receiver->next_char);
	while(!SvvInternalInjectionIterator_EndReached(iterator))
	{
		SvvInternalStringMapNode_CleanSubTree(OBJECT_AS_LINK(SvvInternalInjectionIterator_GetValue(iterator)));
		SvvInternalInjectionIterator_GetNext(iterator);
	};
	SvvInternalInjectionIterator_Destroy(iterator);
	SvvInternalInjection_Destroy(Receiver->next_char);
	SvvInternalStringMapNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalStringMapNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

