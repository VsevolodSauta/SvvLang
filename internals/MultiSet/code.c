#include "internals/basics.h"
#include "internals/MultiSet/imports.h"


Object MultiSet_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("MultiSet: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct MultiSet));
	_self->gid =  8253887558225682432ull;
	Object_SetComparator(_self, &MultiSet_Compare);
	Object_SetDestructor(_self, &MultiSet_Destroy);
	Object_SetCloner(_self, &MultiSet_Clone);
	Object_SetDeepCloner(_self, &MultiSet_DeepClone);
	((MultiSet) (_self->entity))->_list = _nil;
	_self = MultiSet_Init(_self);
	DPOPS ("MultiSet: Create ended.")
	return _self;
}

Object MultiSet_Init(Object _self)
{
	DPUSHS ("MultiSet: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object_SetReleasing(&(((MultiSet) (_self->entity))->_list), List_Create());
	Object toReturn = _self;
	DPOPS ("MultiSet: Init ended.")
	return toReturn;
}

Object MultiSet_Destroy(Object _self)
{
	DPUSHS ("MultiSet: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object_Release((((MultiSet) (_self->entity))->_list));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("MultiSet: Destroy ended.")
	return toReturn;
}

Object MultiSet_Clone(Object _self)
{
	DPUSHS ("MultiSet: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object _toReturn;
	_toReturn = MultiSet_Create();
	Object_SetReleasing(&(((MultiSet) (_toReturn->entity))->_list), Object_Clone((((MultiSet) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("MultiSet: Clone ended.")
	return toReturn;
}

Object MultiSet_DeepClone(Object _self)
{
	DPUSHS ("MultiSet: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object _toReturn;
	_toReturn = MultiSet_Create();
	Object_SetRetaining(&(((MultiSet) (_toReturn->entity))->_list), Object_DeepClone((((MultiSet) (_self->entity))->_list)));
	Object toReturn = _toReturn;
	DPOPS ("MultiSet: DeepClone ended.")
	return toReturn;
}

Object MultiSet_Compare(Object _self, Object _multiset)
{
	DPUSHS ("MultiSet: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object toReturn = Object_Compare((((MultiSet) (_self->entity))->_list), (((MultiSet) (_multiset->entity))->_list));
	DPOPS ("MultiSet: Compare ended.")
	return toReturn;
}

Object MultiSet_Push(Object _self, Object _object)
{
	DPUSHS ("MultiSet: Push begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	List_PushSorted((((MultiSet) (_self->entity))->_list), _object);
	Object toReturn = _self;
	DPOPS ("MultiSet: Push ended.")
	return toReturn;
}

Object MultiSet_Contains(Object _self, Object _object)
{
	DPUSHS ("MultiSet: Contains begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object toReturn = List_Contains((((MultiSet) (_self->entity))->_list), _object);
	DPOPS ("MultiSet: Contains ended.")
	return toReturn;
}

Object MultiSet_RemoveOnce(Object _self, Object _object)
{
	DPUSHS ("MultiSet: RemoveOnce begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	List_RemoveFirst((((MultiSet) (_self->entity))->_list), _object);
	Object toReturn = _self;
	DPOPS ("MultiSet: RemoveOnce ended.")
	return toReturn;
}

Object MultiSet_RemoveEvery(Object _self, Object _object)
{
	DPUSHS ("MultiSet: RemoveEvery begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	List_RemoveEvery((((MultiSet) (_self->entity))->_list), _object);
	Object toReturn = _self;
	DPOPS ("MultiSet: RemoveEvery ended.")
	return toReturn;
}

Object MultiSet_Empty(Object _self)
{
	DPUSHS ("MultiSet: Empty begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8253887558225682432ull )
	Object toReturn = List_Empty((((MultiSet) (_self->entity))->_list));
	DPOPS ("MultiSet: Empty ended.")
	return toReturn;
}
