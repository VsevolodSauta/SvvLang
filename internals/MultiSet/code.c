#include "internals/basics.h"
#include "internals/MultiSet/imports.h"


Object MultiSet_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(allocator, sizeof(struct MultiSet));
	toReturn->gid =  8253887558225682432;
	Object_SetComparator(toReturn, &MultiSet_Compare);
	Object_SetDestructor(toReturn, &MultiSet_Destroy);
	Object_SetCloner(toReturn, &MultiSet_Clone);
	toReturn = MultiSet_Init(toReturn);
	return toReturn;
}

Object MultiSet_Init(Object self)
{
	(((MultiSet) (self->entity))->list) = List_Create();
	return self;
}

Object MultiSet_Destroy(Object self)
{
	Object_Release((((MultiSet) (self->entity))->list));
	return Object_Destroy((((MultiSet) (self->entity))->list));
}

Object MultiSet_Clone(Object self)
{
	Object toReturn;
	toReturn = MultiSet_Create();
	Object_Release((((MultiSet) (toReturn->entity))->list));
	(((MultiSet) (toReturn->entity))->list) = Object_Clone((((MultiSet) (self->entity))->list));
	return toReturn;
}

Object MultiSet_Compare(Object self, Object multiset)
{
	return Object_Compare(List_Sort(Object_TempClone((((MultiSet) (self->entity))->list))), List_Sort(Object_TempClone((((MultiSet) (multiset->entity))->list))));
}

Object MultiSet_Push(Object self, Object object)
{
	List_PushBack((((MultiSet) (self->entity))->list), object);
	return self;
}

Object MultiSet_Contains(Object self, Object object)
{
	return List_Contains((((MultiSet) (self->entity))->list), object);
}

Object MultiSet_RemoveOnce(Object self, Object object)
{
	List_RemoveFirst((((MultiSet) (self->entity))->list), object);
	return self;
}

Object MultiSet_RemoveEvery(Object self, Object object)
{
	List_RemoveEvery((((MultiSet) (self->entity))->list), object);
	return self;
}
