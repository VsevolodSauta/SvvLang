#include "internals/basics.h"

#if MEMORY_DEBUG
static int allocated;
static int resized;
static int freed;

struct AllocatorObject {
	int size;
	void* ptr;
};

static struct AllocatorObject objects[10000];
static int position;

int Allocator_GetAllocated()
{
	return allocated;
}

int Allocator_GetFreed()
{
	return freed;
}

int Allocator_GetResized()
{
	return resized;
}
#endif

Object Allocator_Create()
{
	return Undestroyable_Create();
}

void* Allocator_New(Object _self, int size)
{
#if MEMORY_DEBUG
	allocated++;
	objects[position].ptr = malloc(size);
	objects[position].size = size;
	if(size == sizeof(struct Object))
	{
		DMSGS("Allocator: Creating object %p.", objects[position].ptr);
	}
	return objects[position++].ptr;
#else
	return malloc(size);
#endif
}

void* Allocator_Resize(Object _self, void* toResize, int size)
{
#if MEMORY_DEBUG
	resized++;
#endif
	return realloc(toResize, size);
}

Object Allocator_Delete(Object _self, void* toDelete)
{
#if MEMORY_DEBUG
	int i;
	for(i = 0; i < position; i++)
	{
		if(objects[i].ptr == toDelete)
		{
			objects[i] = objects[position - 1];
			break;
		}
	}
	if(position == i)
	{
		IMPOSSIBLE();
	}
	if(objects[i].size == sizeof(struct Object))
	{
		DMSGS("Allocator: Destroying object %p", objects[i].ptr);
	}
	position--;
	freed++;
#endif
	free(toDelete);
	return _nothing;
}

void Allocator_Dump()
{
#if MEMORY_DEBUG
	int i = 0;
	for(i = 0; i < position; i++)
	{
		if(objects[i].size == sizeof(struct Object))
		{
			DMSG("Allocator: Object %p of type %lld was not destroyed. Links quantity is %ld.", 
				objects[i].ptr, ((Object) objects[i].ptr)->gid, ((Object) objects[i].ptr)->links);
		}
	}
#endif
}

void* Allocator_GetUndeletable(Object _self)
{
	return NULL;
}

Object _allocator;
Object _nothing;
Object _nil;
Object _null;
