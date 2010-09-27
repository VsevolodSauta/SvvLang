#include "internals/basics.h"
#include "internals/Queue/imports.h"

Object Queue_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct Queue));
	Object_SetComparator(toReturn, &Queue_Compare);
	Object_SetDestructor(toReturn, &Queue_Destroy);
	Object_SetCloner(toReturn, &Queue_Clone);
	toReturn = Queue_Init(toReturn);
	return toReturn;
}


Object Queue_Init(Object self)
{
	(((Queue) (self->entity))->list) = List_Create();
	return self;
}

Object Queue_Push(Object self, Object object)
{
	List_PushBack((((Queue) (self->entity))->list), object);
	return self;
}

Object Queue_Pop(Object self)
{
	return List_PopFront((((Queue) (self->entity))->list));
}

Object Queue_Peek(Object self)
{
	return List_PeekFront((((Queue) (self->entity))->list));
}

Object Queue_Compare(Object self, Object queue)
{
	return Object_Compare(Object_Hash((((Queue) (self->entity))->list)), Object_Hash((((Queue) (queue->entity))->list)));
}

Object Queue_Destroy(Object self)
{
	List_Destroy((((Queue) (self->entity))->list));
	return Object_Destroy(self);
}

Object Queue_GetList(Object self)
{
	return Object_TempClone((((Queue) (self->entity))->list));
}

Object Queue_Clone(Object self)
{
	Object toReturn;
	toReturn = Queue_Create();
	Object_Release((((Queue) (toReturn->entity))->list));
	(((Queue) (toReturn->entity))->list) = Object_Clone((((Queue) (self->entity))->list));
	return toReturn;
}

