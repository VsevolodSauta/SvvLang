#include "internals/basics.h"
#include "internals/Runtime/imports.h"


Object Runtime_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Runtime: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Runtime));
	_self->gid =  5367970674748323840ull;
	Object_SetComparator(_self, &Runtime_Compare);
	Object_SetDestructor(_self, &Runtime_Destroy);
	Object_SetCloner(_self, &Runtime_Clone);
	Object_SetDeepCloner(_self, &Runtime_DeepClone);
	((Runtime) (_self->entity))->_placeHolder = _nil;
	_self = Runtime_Init(_self);
	DPOPS ("Runtime: Create ended.")
	return _self;
}

Object Runtime_Init(Object _self)
{
	DPUSHS ("Runtime: Init begined.")
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
	_console = Console_Create();
	_json = JSON_Create();
	Object toReturn = _self;
	DPOPS ("Runtime: Init ended.")
	return toReturn;
}

Object Runtime_Destroy(Object _self)
{
	DPUSHS ("Runtime: Destroy begined.")
	Object_Release(_autoreleasePool);
	Object_Release(_console);
	Object_Release(_json);
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Runtime: Destroy ended.")
	return toReturn;
}

Object Runtime_Clone(Object _self)
{
	DPUSHS ("Runtime: Clone begined.")
	Object toReturn = _self;
	DPOPS ("Runtime: Clone ended.")
	return toReturn;
}

Object Runtime_DeepClone(Object _self)
{
	DPUSHS ("Runtime: DeepClone begined.")
	Object toReturn = _self;
	DPOPS ("Runtime: DeepClone ended.")
	return toReturn;
}

Object Runtime_Compare(Object _self, Object _runtime)
{
	DPUSHS ("Runtime: Compare begined.")
	Object toReturn = _equal;
	DPOPS ("Runtime: Compare ended.")
	return toReturn;
}
