#include "internals/basics.h"
#include "internals/Stack/imports.h"


Object Stack_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct Stack));
	toReturn->gid =  6822298517081180160;
	Object_SetComparator(toReturn, &Stack_Compare);
	Object_SetDestructor(toReturn, &Stack_Destroy);
	Object_SetCloner(toReturn, &Stack_Clone);
	toReturn = Stack_Init(toReturn);
	return toReturn;
}

Object Stack_Init(Object self)
{
	(((Stack) (self->entity))->list) = List_Create();
	return self;
}

Object Stack_Push(Object self, Object object)
{
	List_PushBack((((Stack) (self->entity))->list), object);
	return self;
}

Object Stack_Pop(Object self)
{
	return List_PopBack((((Stack) (self->entity))->list));
}

Object Stack_Peek(Object self)
{
	return List_PeekBack((((Stack) (self->entity))->list));
}

Object Stack_Compare(Object self, Object queue)
{
	return Object_Compare(Object_Hash((((Stack) (self->entity))->list)), Object_Hash((((Stack) (queue->entity))->list)));
}

Object Stack_Destroy(Object self)
{
	List_Destroy((((Stack) (self->entity))->list));
	return Object_Destroy(self);
}

Object Stack_GetList(Object self)
{
	return Object_TempClone((((Stack) (self->entity))->list));
}

Object Stack_Clone(Object self)
{
	Object toReturn;
	toReturn = Stack_Create();
	Object_Release((((Stack) (toReturn->entity))->list));
	(((Stack) (toReturn->entity))->list) = Object_Clone((((Stack) (self->entity))->list));
	return toReturn;
}
