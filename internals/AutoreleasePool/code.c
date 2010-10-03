#include "internals/basics.h"
#include "internals/AutoreleasePool/imports.h"


Object AutoreleasePool_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct AutoreleasePool));
	toReturn->gid =  6558146264612776960ull;
	Object_SetComparator(toReturn, &AutoreleasePool_Compare);
	Object_SetDestructor(toReturn, &AutoreleasePool_Destroy);
	Object_SetCloner(toReturn, &AutoreleasePool_Clone);
	((AutoreleasePool) (toReturn->entity))->_stack = _nil;
	toReturn = AutoreleasePool_Init(toReturn);
	return toReturn;
}

Object AutoreleasePool_Init(Object _self)
{
	Object_SetReleasing(&(((AutoreleasePool) (_self->entity))->_stack), Stack_Create());
	return _self;
}

Object AutoreleasePool_PushFrame(Object _self)
{
	Stack_Push((((AutoreleasePool) (_self->entity))->_stack), MultiSet_Create());
	return _self;
}

Object AutoreleasePool_PopFrame(Object _self, Object _object)
{
	Object_Release(Stack_Pop((((AutoreleasePool) (_self->entity))->_stack)));
	return _self;
}

Object AutoreleasePool_Add(Object _self, Object _object)
{
	MultiSet_Push(Stack_Peek((((AutoreleasePool) (_self->entity))->_stack)), _object);
	Object_Release(_object);
	return _self;
}

Object AutoreleasePool_Destroy(Object _self)
{
	Object_Release((((AutoreleasePool) (_self->entity))->_stack));
	return Object_Destroy(_self);
}

Object AutoreleasePool_Compare(Object _self, Object _autoreleasePool)
{
	return Object_Compare((((AutoreleasePool) (_self->entity))->_stack), (((AutoreleasePool) (_autoreleasePool->entity))->_stack));
}

Object AutoreleasePool_Clone(Object _self)
{
	return _self;
}
