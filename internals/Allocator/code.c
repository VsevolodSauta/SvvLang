#include "internals/basics.h"

#define POOL_SIZE		(256 * 1048576)
#define ALLOCATION_UNIT_SIZE	0x100000
#define ALLOCATION_BASE		(void*) 0x10000000

typedef struct AllocatorNode {
	long			size;
	struct AllocatorNode*	parent;
	struct AllocatorNode*	left;
	struct AllocatorNode*	right;
	struct AllocatorNode*	prev;
	struct AllocatorNode*	next;
	long			flags;
} *AllocatorNode;

typedef struct Allocator {
	AllocatorNode allocatorData;
	AllocatorNode allocatorData2;
	int fd;
	int allocatedMem;
#if MEMORY_DEBUG
	int allocated;
	int freed;
	int resized;
#endif
} *Allocator;

// Strategy: Best Fit
// Utility

static inline void memcpy(char* dest, char* src, int size)
{
	int i = size / sizeof(long);
	while(i)
	{
		i--;
		((long*) dest)[i] = ((long*) src)[i];
	}
	i = size % sizeof(long);
	while(i)
	{
		i--;
		dest[i] = src[i];
	}
}

static inline void* AllocateSpace(Allocator _self, int size)
{
	if(_self->fd == 0)
	{
		_self->fd = OSfileOpen("memory", 0x42, 0666);
	}
	OSfileTruncate(_self->fd, _self->allocatedMem + size);
	void* mapped = OSmappingMap(ALLOCATION_BASE, size, 0x07, 0x01, _self->fd, _self->allocatedMem);
	_self->allocatedMem += size;
	return mapped;
}

static inline int IsInUse(Allocator _self, AllocatorNode node)
{
	return (node == NULL) || (node->flags & 0x1);
}

static inline void Use(Allocator _self, AllocatorNode node)
{
	node->flags |= 0x1;
}

static inline void Free(Allocator _self, AllocatorNode node)
{
	node->flags &= ~0x1;
}

static inline int IsLeftSon(Allocator _self, AllocatorNode node)
{
	return node->parent->left == node;
}

static inline int IsRightSon(Allocator _self, AllocatorNode node)
{
	return node->parent->right == node;
}

static void AddNode(Allocator _self, AllocatorNode nodeToAdd)
{
	Free(_self, nodeToAdd);
	nodeToAdd->left = nodeToAdd->right = NULL;
	AllocatorNode nodeParent = _self->allocatorData;
	while(1)
	{
		if(nodeParent->size <= nodeToAdd->size)
		{
			if(IsInUse(_self, nodeParent->right))
			{
				nodeParent->right = nodeToAdd;
				nodeToAdd->parent = nodeParent;
				break;
			}
			nodeParent = nodeParent->right;
		} else {
			if(IsInUse(_self, nodeParent->left))
			{
				nodeParent->left = nodeToAdd;
				nodeToAdd->parent = nodeParent;
				break;
			}
			nodeParent = nodeParent->left;
		}
	}
}

static void RemoveNode(Allocator _self, AllocatorNode nodeToRemove)
{
	AllocatorNode node = nodeToRemove;
	Use(_self, nodeToRemove);
	switch(IsInUse(_self, node->left) + (IsInUse(_self, node->right) << 1)) {
		case 0:
			node = node->left;
			while(!IsInUse(_self, node->right)) node = node->right;
			if(IsRightSon(_self, node))
			{
				if(IsInUse(_self, node->left))
				{
					node->parent->right = NULL;
				} else {
					node->left->parent = node->parent;
					node->parent->right = node->left;
				}
				node->parent = nodeToRemove->parent;
				if(IsLeftSon(_self, nodeToRemove))
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
				if(IsLeftSon(_self, nodeToRemove))
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
			if(IsLeftSon(_self, node))
			{
				node->parent->left = node->right;
			} else {
				node->parent->right = node->right;
			}
			node->right->parent = node->parent;
			return;
		case 2:
			if(IsLeftSon(_self, node))
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

static AllocatorNode FindBestFitNode(Allocator _self, int size)
{
	AllocatorNode node = _self->allocatorData;
	AllocatorNode greaterNode = NULL;
	while(1)
	{
		if(node->size == size) return node;
		if(node->size < size)
		{
			if(IsInUse(_self, node->right)) {
				if(greaterNode != NULL)
				{
					return greaterNode;
					node = greaterNode;
				} else {
					DMSG("Untested feature.");
					node = AllocateSpace(_self, ALLOCATION_UNIT_SIZE);
					node->size = ALLOCATION_UNIT_SIZE;
					node->next = NULL;
					node->prev = _self->allocatorData2;
					_self->allocatorData2 = node;
					AddNode(_self, node);
					return node;
				}
			}
			node = node->right;
		} else {
			if(IsInUse(_self, node->left)) return node;
			greaterNode = node;
			node = node->left;
		}
	}
}

// Internal implementations

static inline void* Allocator_InternalNew(Allocator _self, int size)
{
#if MEMORY_DEBUG
	_self->allocated++;
#endif
	size = (size + 0x1F) & ~0x1F;
	AllocatorNode node = FindBestFitNode(_self, size);
	
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
		AddNode(_self, nodeToAdd);
	}
	RemoveNode(_self, node);
	return (node + 1);
}

#if RESIZE_AVAILABLE
static inline void*  Allocator_InternalResize(Allocator _self, void* toResize, int size)
{
#if MEMORY_DEBUG
	_self->resized++;
#endif
	IMPOSSIBLE();
	return NULL;
}
#endif

static inline void Allocator_InternalDelete(Allocator _self, void* toDelete)
{
#if MEMORY_DEBUG
	_self->freed++;
#endif
	if(toDelete == NULL)
		return;
	AllocatorNode node = ((AllocatorNode) toDelete) - 1;
	if((node->prev != _self->allocatorData) && !IsInUse(_self, node->prev))
	{
		RemoveNode(_self, node->prev);
		node->prev->size += node->size + sizeof(struct AllocatorNode);
		node = node->prev;
	}
	if((node->next != NULL) && !IsInUse(_self, node->next))
	{
		RemoveNode(_self, node->next);
		node->size += node->next->size + sizeof(struct AllocatorNode);
	}
	AddNode(_self, node);
}

static inline void*  Allocator_InternalGetUndeletable(Allocator _self)
{
	return NULL;
}

#if MEMORY_DEBUG
static inline int Allocator_InternalGetFreed(Allocator _self)
{
	return _self->freed;
}

static inline int Allocator_InternalGetResized(Allocator _self)
{
	return _self->resized;
}

static inline int Allocator_InternalGetAllocated(Allocator _self)
{
	return _self->allocated;
}
#endif


// Interfaces implementations

Object Allocator_Create()
{
	struct Allocator allocatorEntity;
	allocatorEntity.fd = 0;
#if MEMORY_DEBUG
	allocatorEntity.allocated = 0;
	allocatorEntity.resized = 0;
	allocatorEntity.freed = 0;
#endif
	allocatorEntity.allocatedMem = 0;
	allocatorEntity.allocatorData = AllocateSpace(&allocatorEntity, POOL_SIZE);
	allocatorEntity.allocatorData2 = allocatorEntity.allocatorData + 1;
	allocatorEntity.allocatorData2->size = POOL_SIZE - 2 * sizeof(struct AllocatorNode);
	allocatorEntity.allocatorData2->left = NULL;
	allocatorEntity.allocatorData2->right = NULL;
	allocatorEntity.allocatorData2->next = NULL;
	allocatorEntity.allocatorData2->prev = allocatorEntity.allocatorData;
	allocatorEntity.allocatorData2->parent = allocatorEntity.allocatorData;
	allocatorEntity.allocatorData2->flags = 0;
	allocatorEntity.allocatorData->left = NULL;
	allocatorEntity.allocatorData->right = allocatorEntity.allocatorData2;
	allocatorEntity.allocatorData->next = allocatorEntity.allocatorData2;
	allocatorEntity.allocatorData->prev = NULL;
	allocatorEntity.allocatorData->size = 0;
	allocatorEntity.allocatorData->flags = 0;
	Object earlyAllocator = Allocator_InternalNew(&allocatorEntity, sizeof(struct Object));
	earlyAllocator->entity = Allocator_InternalNew(&allocatorEntity, sizeof(struct Allocator));
	memcpy(earlyAllocator->entity, &allocatorEntity, sizeof(allocatorEntity));
	_allocator = earlyAllocator;
	Object allocator = Object_Create();
	allocator->entity = earlyAllocator->entity;
	_allocator = allocator;
	Allocator_Delete(_allocator, earlyAllocator);
	return _allocator;
}

void Allocator_Restore()
{
	struct Allocator allocatorEntity;
	allocatorEntity.fd = 0;
#if MEMORY_DEBUG
	allocatorEntity.allocated = 0;
	allocatorEntity.resized = 0;
	allocatorEntity.freed = 0;
#endif
	allocatorEntity.allocatedMem = 0;
	allocatorEntity.allocatorData = AllocateSpace(&allocatorEntity, POOL_SIZE);
}

void* Allocator_New(Object _self, int size)
{
	return Allocator_InternalNew(_self->entity, size);
}

#if RESIZE_AVAILABLE
void*  Allocator_Resize(Object _self, void* toResize, int size)
{
	return Allocator_InternalResize(_self->entity, toResize, size);
}
#endif

Object Allocator_Delete(Object _self, void* toDelete)
{
	Allocator_InternalDelete(_self->entity, toDelete);
	return _self;
}

void*  Allocator_GetUndeletable(Object _self)
{
	return Allocator_InternalGetUndeletable(_self->entity);
}

#if MEMORY_DEBUG
int Allocator_GetFreed(Object _self)
{
	return Allocator_InternalGetFreed(_self->entity);
}

int Allocator_GetResized(Object _self)
{
	return Allocator_InternalGetResized(_self->entity);
}

int Allocator_GetAllocated(Object _self)
{
	return Allocator_InternalGetAllocated(_self->entity);
}
#endif

Object _nil;
Object _nothing;
Object _null;
Object _allocator;
