#include "internals/basics.h"
#include "internals/AutoreleasePool/imports.h"

Object AutoreleasePool_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct AutoreleasePool));
	Object_SetComparator(toReturn, &AutoreleasePool_Compare);
	Object_SetDestructor(toReturn, &AutoreleasePool_Destroy);
	Object_SetCloner(toReturn, &AutoreleasePool_Clone);
	toReturn = AutoreleasePool_Init(toReturn);
	return toReturn;
}


Object AutoreleasePool_Init(Object self)
{
	(((AutoreleasePool) (self->entity))->stack) = Stack_Create();
	return self;
}

Object AutoreleasePool_PushFrame(Object self)
{
	Stack_Push((((AutoreleasePool) (self->entity))->stack), MultiSet_Create());
	return self;
}

Object AutoreleasePool_PopFrame(Object self, Object object)
{
	Object_Release(Stack_Pop((((AutoreleasePool) (self->entity))->stack)));
	return self;
}

Object AutoreleasePool_Add(Object self, Object object)
{
	MultiSet_Push(Stack_Peek((((AutoreleasePool) (self->entity))->stack)), object);
	Object_Release(object);
	return self;
}

Object AutoreleasePool_Destroy(Object self)
{
	Object_Release((((AutoreleasePool) (self->entity))->stack));
	return Object_Destroy(self);
}

Object AutoreleasePool_Compare(Object self, Object autoreleasePool)
{
	return Object_Compare(Object_Hash((((AutoreleasePool) (self->entity))->stack)), Object_Hash((((AutoreleasePool) (autoreleasePool->entity))->stack)));
}

Object AutoreleasePool_Clone(Object self)
{
	return AutoreleasePool_Create();
}

