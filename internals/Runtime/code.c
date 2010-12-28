#include "internals/basics.h"
#include "internals/Runtime/imports.h"


Object Runtime_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Runtime));
	toReturn->gid =  5367970674748323840ull;
	Object_SetComparator(toReturn, &Runtime_Compare);
	Object_SetDestructor(toReturn, &Runtime_Destroy);
	Object_SetCloner(toReturn, &Runtime_Clone);
	((Runtime) (toReturn->entity))->_placeHolder = _nil;
	toReturn = Runtime_Init(toReturn);
	return toReturn;
}

Object Runtime_Init(Object _self)
{
	_nothing = _null = _nil = Undestroyable_Create();
	_less = Comparation_Create();
	_greater = Comparation_Create();
	_equal = Comparation_Create();
	_uncomparableLess = Comparation_Create();
	_uncomparableGreater = Comparation_Create();
	_true = _yes = Logic_Create();
	_false = _no = Logic_Create();
	_stringFactory = StringFactory_Create();
	_numberFactory = NumberFactory_Create();
	_logicFactory = LogicFactory_Create();
	_autoreleasePool = AutoreleasePool_Create();
	AutoreleasePool_PushFrame(_autoreleasePool);
	return _self;
}

Object Runtime_Destroy(Object _self)
{
	DPUSHS( "Runtime: Destroying." ) 
	Object_Release(_autoreleasePool);
	DPOPS( "Runtime: Destroyed." ) 
	return Object_Destroy(_self);
}

Object Runtime_Clone(Object _self)
{
	return _self;
}

Object Runtime_Compare(Object _self, Object _runtime)
{
	return _equal;
}
