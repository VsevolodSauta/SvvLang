// #include "internals/Object/interface.h"
#include "internals/basics.h"

#define POOL_SIZE		(256 * 1048576)

typedef struct AllocatorNode {
	long	size;
	void*	next;
} *AllocatorNode;

static AllocatorNode allocatorData;
static int allocationSize;


// Strategy: First Fit

Object Allocator_Create()
{
	allocationSize = POOL_SIZE;
	allocatorData = sbrk(POOL_SIZE);
	allocatorData->next = NULL;
	allocatorData->size = allocationSize - sizeof(struct AllocatorNode);
	return NULL;
}

void*  Allocator_New(Object receiver, int size)
{
	size = (size + 0x1F) & ~0x1F;
	AllocatorNode node = allocatorData;
	AllocatorNode prevNode = NULL;
	while(node->size < size)
	{
		if(node->next != NULL)
		{
			prevNode = node;
			node = node->next;
		} else {
			IMPOSSIBLE();
		}
	}
	if(allocatorData->size > size + sizeof(struct AllocatorNode))
	{
		AllocatorNode nextNode = (AllocatorNode) (((char*) node) + size + sizeof(struct AllocatorNode));
		nextNode->size = node->size - sizeof(struct AllocatorNode) - size;
		nextNode->next = node->next;
		node->size = size;
		if(prevNode != NULL)
		{
			prevNode->next = nextNode;
		} else {
			allocatorData = nextNode;
		}
	} else {
		if(prevNode != NULL)
		{
			prevNode->next = node->next;
		} else {
			allocatorData = node->next;
		}
	}
	return (node + 1);
}

void*  Allocator_Resize(Object receiver, void* toResize, int size)
{
	IMPOSSIBLE();
	return NULL;
}

Object Allocator_Delete(Object receiver, void* toDelete)
{
	AllocatorNode node = ((AllocatorNode) toDelete) - 1;
	node->next = allocatorData;
	allocatorData = node;
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
