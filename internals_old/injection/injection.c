#include "internals/basics.h"
#include "internals/injection/interface.h"
#include "internals/injection/node.h"

SvvInternalCreator(SvvInternalInjection)
{
	SvvInternalInjection set = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalInjection)));
	set->root1 = SvvInternalInjectionNode_Create();
	set->root2 = SvvInternalInjectionNode_Create();
	set->capacity = 0;
	SvvInternalInjectionNode_DeInit(set->root1);
	SvvInternalInjectionNode_DeInit(set->root2);
	return set;
};

SvvInternalAction(SvvInternalInjection, Destroy, void)
{
	SvvInternalInjectionNode_CleanSubTree(Receiver->root1);
	SvvInternalInjectionNode_CleanSubTree(Receiver->root2);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalInjection, Add, void, SvvInternalObject Key, SvvInternalObject Value)
{
	SvvInternalInjectionNode node1 = SvvInternalInjectionNode_GetNodeForKey(Receiver->root1, Key);
	SvvInternalInjectionNode node2 = SvvInternalInjectionNode_GetNodeForKey(Receiver->root2, Value);
	SvvInternalInjectionNode node3;
	
	int inited_state = (SvvInternalInjectionNode_Inited(node1) << 1) ^ SvvInternalInjectionNode_Inited(node2);
	switch(inited_state)
	{
		case 0:
			SvvInternalInjectionNode_Init(node1, Key, node2);
			SvvInternalInjectionNode_Init(node2, Value, node1);
			Receiver->capacity++;
			break;
		case 1:
			node3 = SvvInternalInjectionNode_GetValue(node2);
			SvvInternalInjectionNode_Remove(node3);
			SvvInternalInjectionNode_Init(node1, Key, node2);
			SvvInternalInjectionNode_SetValue(node2, node1);
			break;
		case 2:
			node3 = SvvInternalInjectionNode_GetValue(node1);
			SvvInternalInjectionNode_Remove(node3);
			SvvInternalInjectionNode_Init(node2, Value, node1);
			SvvInternalInjectionNode_SetValue(node1, node2);
			break;			
		case 3:
			node3 = SvvInternalInjectionNode_GetValue(node1);
			if(SvvInternalObject_Compare(SvvInternalInjectionNode_GetKey(node3), Value) == 0)
			{
				break;
			};
			SvvInternalInjectionNode_Remove(SvvInternalInjectionNode_GetValue(node1));
			SvvInternalInjectionNode_Remove(SvvInternalInjectionNode_GetValue(node2));
			SvvInternalInjectionNode_SetValue(node1, node2);
			SvvInternalInjectionNode_SetValue(node2, node1);
			Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalInjection, RemoveKey, void, SvvInternalObject Key)
{
	SvvInternalInjectionNode node = SvvInternalInjectionNode_GetNodeForKey(Receiver->root1, Key);
	if(SvvInternalInjectionNode_Inited(node))
	{
		SvvInternalInjectionNode_Remove(SvvInternalInjectionNode_GetValue(node));
		SvvInternalInjectionNode_Remove(node);
		Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalInjection, RemoveValue, void, SvvInternalObject Value)
{
	SvvInternalInjectionNode node = SvvInternalInjectionNode_GetNodeForKey(Receiver->root2, Value);
	if(SvvInternalInjectionNode_Inited(node))
	{
		SvvInternalInjectionNode_Remove(SvvInternalInjectionNode_GetValue(node));
		SvvInternalInjectionNode_Remove(node);
		Receiver->capacity--;
	};
};

SvvInternalAction(SvvInternalInjection, Clean, void)
{
	SvvInternalInjectionNode_CleanSubTree(Receiver->root1);
	SvvInternalInjectionNode_CleanSubTree(Receiver->root2);
	Receiver->root1 = SvvInternalInjectionNode_Create();
	Receiver->root2 = SvvInternalInjectionNode_Create();
	Receiver->capacity = 0;
	SvvInternalInjectionNode_DeInit(Receiver->root1);
	SvvInternalInjectionNode_DeInit(Receiver->root2);
};

SvvInternalAction(SvvInternalInjection, ExistsKey, int, SvvInternalObject Key)
{
	SvvInternalInjectionNode node = SvvInternalInjectionNode_GetNodeForKey(Receiver->root1, Key);
	return SvvInternalInjectionNode_Inited(node);
};

SvvInternalAction(SvvInternalInjection, ExistsValue, int, SvvInternalObject Value)
{
	SvvInternalInjectionNode node = SvvInternalInjectionNode_GetNodeForKey(Receiver->root2, Value);
	return SvvInternalInjectionNode_Inited(node);
};

SvvInternalAction(SvvInternalInjection, GetValue, SvvInternalObject, SvvInternalObject Key)
{
	SvvInternalInjectionNode node = SvvInternalInjectionNode_GetNodeForKey(Receiver->root1, Key);
	return SvvInternalInjectionNode_GetKey(SvvInternalInjectionNode_GetValue(node));
};

SvvInternalAction(SvvInternalInjection, GetList, SvvInternalList)
{
	SvvInternalList list = SvvInternalList_Create();
	SvvInternalObject object;
	SvvInternalInjectionIterator iterator = SvvInternalInjection_GetIterator(Receiver);
	while(!SvvInternalInjectionIterator_EndReached(iterator))
	{
		object = SvvInternalInjectionIterator_GetKey(iterator);
		SvvInternalList_PushBack(list, object);
		object = SvvInternalInjectionIterator_GetValue(iterator);
		SvvInternalList_PushBack(list, object);
		SvvInternalInjectionIterator_GetNext(iterator);
	};
	SvvInternalInjectionIterator_Destroy(iterator);
	return list;
};

SvvInternalAction(SvvInternalInjection, AddList, void, SvvInternalList List)
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
		SvvInternalInjection_Add(Receiver, key, value);
	};
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalInjection, GetIterator, SvvInternalInjectionIterator)
{
	SvvInternalInjectionIterator iterator = SvvInternalInjectionIterator_Create();
	if(SvvInternalInjectionNode_Inited(Receiver->root1))
	{
		iterator->node = Receiver->root1;
		SvvInternalInjectionIterator_AddCurrentNodeChildren(iterator);
	};
	
	return iterator;
};

SvvInternalAction(SvvInternalInjection, GetCapacity, int)
{
	return Receiver->capacity;
};
