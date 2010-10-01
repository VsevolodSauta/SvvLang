#include "internals/basics.h"
#include "internals/MultiSet/imports.h"


Object MultiSet_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct MultiSet));
	toReturn->gid =  8253887558225682432ull;
	Object_SetComparator(toReturn, &MultiSet_Compare);
	Object_SetDestructor(toReturn, &MultiSet_Destroy);
	Object_SetCloner(toReturn, &MultiSet_Clone);
	toReturn = MultiSet_Init(toReturn);
	return toReturn;
}

Object MultiSet_Init(Object _self)
{
	(((MultiSet) (_self->entity))->_list) = List_Create();
	return _self;
}

Object MultiSet_Destroy(Object _self)
{
	Object_Release((((MultiSet) (_self->entity))->_list));
	return Object_Destroy((((MultiSet) (_self->entity))->_list));
}

Object MultiSet_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = MultiSet_Create();
	Object_Release((((MultiSet) (_toReturn->entity))->_list));
	(((MultiSet) (_toReturn->entity))->_list) = Object_Clone((((MultiSet) (_self->entity))->_list));
	return _toReturn;
}

Object MultiSet_Compare(Object _self, Object _multiset)
{
	return Object_Compare((((MultiSet) (_self->entity))->_list), (((MultiSet) (_multiset->entity))->_list));
}

Object MultiSet_Push(Object _self, Object _object)
{
	List_PushSorted((((MultiSet) (_self->entity))->_list), _object);
	return _self;
}

Object MultiSet_Contains(Object _self, Object _object)
{
	return List_Contains((((MultiSet) (_self->entity))->_list), _object);
}

Object MultiSet_RemoveOnce(Object _self, Object _object)
{
	List_RemoveFirst((((MultiSet) (_self->entity))->_list), _object);
	return _self;
}

Object MultiSet_RemoveEvery(Object _self, Object _object)
{
	List_RemoveEvery((((MultiSet) (_self->entity))->_list), _object);
	return _self;
}
