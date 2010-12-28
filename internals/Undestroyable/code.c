#include "internals/basics.h"

Object Undestroyable_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Undestroyable));
	toReturn->gid =  3814824931964230656ull;
	Object_SetComparator(toReturn, &Undestroyable_Compare);
	Object_SetDestructor(toReturn, &Undestroyable_Destroy);
	Object_SetCloner(toReturn, &Undestroyable_Clone);
	((Undestroyable) (toReturn->entity))->_placeHolder = _nil;
	return toReturn;
}

Object Undestroyable_Destroy(Object _self)
{
	return _self;
}

Object Undestroyable_Clone(Object _self)
{
	return _self;
}

Object Undestroyable_Compare(Object _self, Object _undestroyable)
{
	return (_self == _undestroyable) ? _equal :
		(_self > _undestroyable) ? _greater : _less;
}
