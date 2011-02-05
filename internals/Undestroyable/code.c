#include "internals/basics.h"
#include "internals/Undestroyable/imports.h"


Object Undestroyable_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Undestroyable: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Undestroyable));
	_self->gid =  3814824931964230656ull;
	Object_SetComparator(_self, &Undestroyable_Compare);
	Object_SetDestructor(_self, &Undestroyable_Destroy);
	Object_SetCloner(_self, &Undestroyable_Clone);
	Object_SetDeepCloner(_self, &Undestroyable_DeepClone);
	((Undestroyable) (_self->entity))->_placeHolder = _nil;
	DPOPS ("Undestroyable: Create ended.")
	return _self;
}

Object Undestroyable_Destroy(Object _self)
{
	DPUSHS ("Undestroyable: Destroy begined.")
	ASSERT_C ( "Undestroyable:Destroy --- Checking for correct object type failed.", _self->gid ==  3814824931964230656ull )
	Object toReturn = _self;
	DPOPS ("Undestroyable: Destroy ended.")
	return toReturn;
}

Object Undestroyable_Clone(Object _self)
{
	DPUSHS ("Undestroyable: Clone begined.")
	ASSERT_C ( "Undestroyable:Clone --- Checking for correct object type failed.", _self->gid ==  3814824931964230656ull )
	Object toReturn = _self;
	DPOPS ("Undestroyable: Clone ended.")
	return toReturn;
}

Object Undestroyable_DeepClone(Object _self)
{
	DPUSHS ("Undestroyable: DeepClone begined.")
	ASSERT_C ( "Undestroyable:DeepClone --- Checking for correct object type failed.", _self->gid ==  3814824931964230656ull )
	Object toReturn = _self;
	DPOPS ("Undestroyable: DeepClone ended.")
	return toReturn;
}

Object Undestroyable_Compare(Object _self, Object _undestroyable)
{
	DPUSHS ("Undestroyable: Compare begined.")
	ASSERT_C ( "Undestroyable:Compare --- Checking for correct object type failed.", _self->gid ==  3814824931964230656ull )
	return ( _self < _undestroyable ) ? _less : ( ( _self > _undestroyable ) ? _greater : _equal ) ; 
}
