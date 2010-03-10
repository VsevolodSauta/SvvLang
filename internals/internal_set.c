#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"
#include "internal_set.h"
#include "internal_allocator.h"
#include "internal_globals.h"
#include "internal_nothing.h"

// SvvInternalSetNode

#define INITED_FLAG 1

SvvInternalCreator(SvvInternalSetNode)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalSetNode)));
};

SvvInternalAction(SvvInternalSetNode, Init, void, SvvInternalObject Object)
{
	Receiver->data = Object;
	Receiver->left = SvvInternalSetNode_Create();
	Receiver->right = SvvInternalSetNode_Create();
	SvvInternalSetNode_DeInit(Receiver->left);
	SvvInternalSetNode_DeInit(Receiver->right);
	Receiver->left->parent = Receiver->right->parent = Receiver;
	Receiver->flags |= INITED_FLAG;
};

SvvInternalAction(SvvInternalSetNode, GetNodeForData, SvvInternalSetNode, SvvInternalObject Object)
{
	int comparation_result;
	while(SvvInternalSetNode_Inited(Receiver) && (comparation_result = SvvInternalObject_Compare(Object, Receiver->data) != 0))
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

SvvInternalAction(SvvInternalSetNode, Remove, void)
{
	while(1)
	{
		int children = (SvvInternalSetNode_Inited(Receiver->left) << 2) + SvvInternalSetNode_Inited(Receiver->right);
		SvvInternalSetNode node_to_delete;
		
		switch(children)
		{
			case 0:
				SvvInternalSetNode_DeInit(Receiver);
				SvvInternalSetNode_Destroy(Receiver->right);
				SvvInternalSetNode_Destroy(Receiver->left);
				return;
			case 1:
				node_to_delete = Receiver->right;
				SvvInternalSetNode_Destroy(Receiver->left);
				
				Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;
				
				Receiver->data = node_to_delete->data;
				SvvInternalSetNode_Destroy(node_to_delete);
				return;
			case 2:
				node_to_delete = Receiver->left;
				SvvInternalSetNode_Destroy(Receiver->right);
				
			Receiver->right = node_to_delete->right;
				Receiver->left = node_to_delete->left;
				Receiver->left->parent = Receiver->right->parent = Receiver;
				
				Receiver->data = node_to_delete->data;
				SvvInternalSetNode_Destroy(node_to_delete);
				return;
			case 3:
				node_to_delete = Receiver->left;
				while(SvvInternalSetNode_Inited(node_to_delete->right))
				{
					node_to_delete = node_to_delete->right;
				};
				Receiver->data = node_to_delete->data;
		};
	};
};

SvvInternalAction(SvvInternalSetNode, CleanSubTree, void)
{
	if(SvvInternalSetNode_Inited(Receiver))
	{
		SvvInternalSetNode_CleanSubTree(Receiver->left);
		SvvInternalSetNode_CleanSubTree(Receiver->right);
	};
	SvvInternalSetNode_Destroy(Receiver);
};

SvvInternalAction(SvvInternalSetNode, DeInit, void)
{
	Receiver->flags &= ~INITED_FLAG;
};

SvvInternalAction(SvvInternalSetNode, Inited, int)
{
	return (Receiver->flags & INITED_FLAG) != 0;
};

SvvInternalAction(SvvInternalSetNode, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalSetNode, GetData, SvvInternalObject)
{
	return Receiver->data;
};

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


// SvvInternalSetIterator

SvvInternalCreator(SvvInternalSetIterator)
{
	SvvInternalSetIterator iterator = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalSetIterator)));
	iterator->path = SvvInternalStack_Create();
	return iterator;
};

SvvInternalAction(SvvInternalSetIterator, AddCurrentNodeChildren, void)
{
	if(SvvInternalSetNode_Inited(Receiver->node->right))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->right));
	};
	if(SvvInternalSetNode_Inited(Receiver->node->left))
	{
		SvvInternalStack_Push(Receiver->path, LINK_AS_OBJECT(Receiver->node->left));
	};

};

SvvInternalAction(SvvInternalSetIterator, GetNext, void)
{
	if(SvvInternalStack_IsEmpty(Receiver->path))
	{
		Receiver->node = OBJECT_AS_LINK(SvvInternalNothing);
	} else {
		Receiver->node = OBJECT_AS_LINK(SvvInternalStack_Pop(Receiver->path));
		SvvInternalSetIterator_AddCurrentNodeChildren(Receiver);
	};
};

SvvInternalAction(SvvInternalSetIterator, EndReached, int)
{
	return IS_NOTHING(Receiver->node);
};

SvvInternalAction(SvvInternalSetIterator, GetData, SvvInternalObject)
{
	return Receiver->node->data;
};

SvvInternalAction(SvvInternalSetIterator, Destroy, void)
{
	SvvInternalStack_Destroy(Receiver->path);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalSetIterator, Clone, SvvInternalSetIterator)
{
	SvvInternalSetIterator iterator = SvvInternalSetIterator_Create();
	iterator->path = SvvInternalStack_Clone(Receiver->path);
	iterator->node = Receiver->node;
	return iterator;
};

