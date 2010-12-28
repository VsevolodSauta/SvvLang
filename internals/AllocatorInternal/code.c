#include "internals/basics.h"

#define POOL_SIZE		(256 * 1048576)

typedef struct AllocatorNode {
	long			size;
	struct AllocatorNode*	parent;
	struct AllocatorNode*	left;
	struct AllocatorNode*	right;
	struct AllocatorNode*	prev;
	struct AllocatorNode*	next;
	long			flags;
} *AllocatorNode;

static AllocatorNode allocatorData;

// Strategy: Best Fit

Object Allocator_Create()
{
	allocatorData = sbrk(POOL_SIZE);
	AllocatorNode right = allocatorData + 1;
	right->size = POOL_SIZE - 2 * sizeof(struct AllocatorNode);
	right->left = NULL;
	right->right = NULL;
	right->next = NULL;
	right->prev = allocatorData;
	right->parent = allocatorData;
	allocatorData->left = NULL;
	allocatorData->right = right;
	allocatorData->next = right;
	allocatorData->prev = NULL;
	allocatorData->size = 0;
	return NULL;
}

static inline int IsInUse(AllocatorNode node)
{
	return (node == NULL) || (node->flags & 0x1);
}

static inline void Use(AllocatorNode node)
{
	node->flags |= 0x1;
}

static inline void Free(AllocatorNode node)
{
	node->flags &= ~0x1;
}

static inline int IsLeftSon(AllocatorNode node)
{
	return node->parent->left == node;
}

static inline int IsRightSon(AllocatorNode node)
{
	return node->parent->right == node;
}

static AllocatorNode FindBestFitNode(int size)
{
	AllocatorNode node = allocatorData;
	AllocatorNode greaterNode = NULL;
	while(1)
	{
		if(node->size == size) return node;
		if(node->size < size)
		{
			if(IsInUse(node->right)) {
				if(greaterNode != NULL)
				{
					return greaterNode;
					node = greaterNode;
				} else {
					IMPOSSIBLE();
					return NULL;
				}
			}
			node = node->right;
		} else {
			if(IsInUse(node->left)) return node;
			greaterNode = node;
			node = node->left;
		}
	}
}

static void AddNode(AllocatorNode nodeToAdd)
{
	Free(nodeToAdd);
	nodeToAdd->left = nodeToAdd->right = NULL;
	AllocatorNode nodeParent = allocatorData;
	while(1)
	{
		if(nodeParent->size <= nodeToAdd->size)
		{
			if(IsInUse(nodeParent->right))
			{
				nodeParent->right = nodeToAdd;
				nodeToAdd->parent = nodeParent;
				break;
			}
			nodeParent = nodeParent->right;
		} else {
			if(IsInUse(nodeParent->left))
			{
				nodeParent->left = nodeToAdd;
				nodeToAdd->parent = nodeParent;
				break;
			}
			nodeParent = nodeParent->left;
		}
	}
}

static void RemoveNode(AllocatorNode nodeToRemove)
{
	AllocatorNode node = nodeToRemove;
	Use(nodeToRemove);
	switch(IsInUse(node->left) + (IsInUse(node->right) << 1)) {
		case 0:
			node = node->left;
			while(!IsInUse(node->right)) node = node->right;
			if(IsRightSon(node))
			{
				if(IsInUse(node->left))
				{
					node->parent->right = NULL;
				} else {
					node->left->parent = node->parent;
					node->parent->right = node->left;
				}
				node->parent = nodeToRemove->parent;
				if(IsLeftSon(nodeToRemove))
				{
					nodeToRemove->parent->left = node;
				} else {
					nodeToRemove->parent->right = node;
				}
				node->left = nodeToRemove->left;
				node->right = nodeToRemove->right;
				node->left->parent = node->right->parent = node;
			} else {
				node->parent = nodeToRemove->parent;
				if(IsLeftSon(nodeToRemove))
				{
					nodeToRemove->parent->left = node;
				} else {
					nodeToRemove->parent->right = node;
				}
				node->right = nodeToRemove->right;
				node->right->parent = node;
			}
			return;
		case 1:
			if(IsLeftSon(node))
			{
				node->parent->left = node->right;
			} else {
				node->parent->right = node->right;
			}
			node->right->parent = node->parent;
			return;
		case 2:
			if(IsLeftSon(node))
			{
				node->parent->left = node->left;
			} else {
				node->parent->right = node->left;
			}
			node->left->parent = node->parent;
			return;
		case 3:
		default:
			return;
	}
}

void* Allocator_New(Object receiver, int size)
{
	size = (size + 0x1F) & ~0x1F;
	AllocatorNode node = FindBestFitNode(size);
	
	if(node->size > size + sizeof(struct AllocatorNode))
	{
		AllocatorNode nodeToAdd = (AllocatorNode) (((char*) node) + size + sizeof(struct AllocatorNode));
		nodeToAdd->prev = node;
		nodeToAdd->next = node->next;
		nodeToAdd->prev->next = nodeToAdd;
		if(nodeToAdd->next != NULL)
		{
			nodeToAdd->next->prev = nodeToAdd;
		}
		nodeToAdd->size = node->size - sizeof(struct AllocatorNode) - size;
		node->size = size;
		AddNode(nodeToAdd);
	}
	RemoveNode(node);
	return (node + 1);
}

void*  Allocator_Resize(Object receiver, void* toResize, int size)
{
	IMPOSSIBLE();
	return NULL;
}

Object Allocator_Delete(Object receiver, void* toDelete)
{
	if(toDelete == NULL)
		return receiver;
	AllocatorNode node = ((AllocatorNode) toDelete) - 1;
	if((node->prev != allocatorData) && !IsInUse(node->prev))
	{
		RemoveNode(node->prev);
		node->prev->size += node->size + sizeof(struct AllocatorNode);
		node = node->prev;
	}
	if((node->next != NULL) && !IsInUse(node->next))
	{
		RemoveNode(node->next);
		node->size += node->next->size + sizeof(struct AllocatorNode);
	}
	AddNode(node);
	return receiver;
}

void*  Allocator_GetUndeletable(Object receiver)
{
	return NULL;
}

#ifdef MEMORY_DEBUG
int Allocator_GetFreed();
int Allocator_GetResized();
int Allocator_GetAllocated();
#endif

Object _nil;
Object _nothing;
Object _null;
Object _allocator;
