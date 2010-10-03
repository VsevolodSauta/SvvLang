#include "internals/basics.h"
#include "internals/Machine/imports.h"


Object Machine_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Machine));
	toReturn->gid =  6547848715907434496ull;
	Object_SetComparator(toReturn, &Machine_Compare);
	Object_SetDestructor(toReturn, &Machine_Destroy);
	Object_SetCloner(toReturn, &Machine_Clone);
	((Machine) (toReturn->entity))->_placeHolder = _nil;
	toReturn = Machine_Init(toReturn);
	return toReturn;
}

Object Machine_Init(Object _self)
{
	_allocator = Allocator_Create();
	_nothing = _null = _nil = Undestroyable_Create();
	_less = Undestroyable_Create();
	_greater = Undestroyable_Create();
	_equal = Undestroyable_Create();
	_uncomparableLess = Undestroyable_Create();
	_uncomparableGreater = Undestroyable_Create();
	_true = _yes = Undestroyable_Create();
	_false = _no = Undestroyable_Create();
	_stringFactory = Undestroyable_Create();
	_numberFactory = Undestroyable_Create();
	_logicFactory = Undestroyable_Create();
	_autoreleasePool = AutoreleasePool_Create();
	return _self;
}

Object Machine_Destroy(Object _self)
{
	return Object_Destroy(_self);
}

Object Machine_Clone(Object _self)
{
	return _self;
}

Object Machine_Compare(Object _self, Object _machine)
{
	return _equal;
}
