#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"
#include "internal_map.h"
#include "internal_allocator.h"
#include "internal_globals.h"
#include "internal_nothing.h"

// SvvInternalMapNode

#define INITED_FLAG 1

SvvInternalCreator(SvvInternalMapNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalMapNode)));
};

SvvInternalAction(SvvInternalMapNode, Init, void, SvvInternalObject Key, SvvInternalObject Value)
{
	Receiver->key = Key;
	Receiver->value = Value;
	Receiver->left = SvvInternalMapNode_Create();
	Receiver->right = SvvInternalMapNode_Create();
	SvvInternalMapNode_DeInit(Receiver->left);
	SvvInternalMapNode_DeInit(Receiver->right);
	Receiver->left->parent = Receiver->right->parent = Receiver;
	Receiver->flags |= INITED_FLAG;
};

SvvInternalAction(SvvInternalMapNode, GetNodeForKey, SvvInternalMapNode, SvvInternalObject Key)
{
	int comparation_result;
	while(SvvInternalMapNode_Inited(Receiver) && (comparation_result = SvvInternalObject_Compare(Key, Receiver->key) != 0))
	{
		if(comparation_result > 0)
		{
			Receiver = Receiver->right;
		} else {
			Receiver = Receiver->left;
		};
	};
	return Receiver;
};

SvvInternalAction(SvvInternalMapNode, Remove, void)
{
	while(1)
	{
		int children = (SvvInternalMapNode_Inited(Receiver->left) << 2) + SvvInternalMapNode_Inited(Receiver->right);
		SvvInternalMapNode node_to_delete;
	
		switch(children)
		{
			case 0:
				SvvInternalMapNode_DeInit(Receiver);
				SvvInternalMapNode_Destroy(Receiver->right);
				SvvInternalMapNode_Destroy(Receiver->left);
				return;
			case 1:
				node_to_delete = Receiver->right;
				SvvInternalMapNode_Destroy(Receiver->left);
			
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;


				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				SvvInternalMapNode_Destroy(node_to_delete);
				return;
			case 2:
				node_to_delete = Receiver->left;
				SvvInternalMapNode_Destroy(Receiver->right);
				
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
				SvvInternalMapNode_Destroy(node_to_delete);
				return;
			case 3:
				node_to_delete = Receiver->left;
				while(SvvInternalMapNode_Inited(node_to_delete->right))
				{
					node_to_delete = node_to_delete->right;
				};

				Receiver->key = node_to_delete->key;
				Receiver->value = node_to_delete->value;
		};
		Receiver = node_to_delete;
	};
};

SvvInternalAction(SvvInternalMapNode, CleanSubTree, void)
{
	if(SvvInternalMapNode_Inited(Receiver))
	{
		SvvInternalMapNode_CleanSubTree(Receiver->left);
		SvvInternalMapNode_CleanSubTree(Receiver->right);
	};
	SvvInternalMapNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalMapNode, DeInit, void)
{
	Receiver->flags &= ~INITED_FLAG;
};

SvvInternalAction(SvvInternalMapNode, Inited, int)
{
	return (Receiver->flags & INITED_FLAG) != 0;
};

SvvInternalAction(SvvInternalMapNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalMapNode, GetValue, SvvInternalObject)
{
	return Receiver->value;
};

SvvInternalAction(SvvInternalMapNode, GetKey, SvvInternalObject)
{
	return Receiver->key;
};

// SvvInternalMap

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


// SvvInternalMapIterator

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

