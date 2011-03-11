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
	ASSERT_C ( "Runtime:Init --- Checking for correct object type failed.", _self->gid ==  5367970674748323840ull )
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
	Object _jsonParser;
	_jsonParser = JSONParser_Create();
	_entitiesFactory = ExternalEntitiesFactory_Create();
	Object toReturn = _self;
	DPOPS ("Runtime: Init ended.")
	return toReturn;
}

Object Runtime_Destroy(Object _self)
{
	DPUSHS ("Runtime: Destroy begined.")
	ASSERT_C ( "Runtime:Destroy --- Checking for correct object type failed.", _self->gid ==  5367970674748323840ull )
	Object_Release(_autoreleasePool);
	Object_Release(_console);
	Object _jsonParser;
	Object_Release(_jsonParser);
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Runtime: Destroy ended.")
	return toReturn;
}

Object Runtime_Clone(Object _self)
{
	DPUSHS ("Runtime: Clone begined.")
	ASSERT_C ( "Runtime:Clone --- Checking for correct object type failed.", _self->gid ==  5367970674748323840ull )
	Object toReturn = _self;
	DPOPS ("Runtime: Clone ended.")
	return toReturn;
}

Object Runtime_DeepClone(Object _self)
{
	DPUSHS ("Runtime: DeepClone begined.")
	ASSERT_C ( "Runtime:DeepClone --- Checking for correct object type failed.", _self->gid ==  5367970674748323840ull )
	Object toReturn = _self;
	DPOPS ("Runtime: DeepClone ended.")
	return toReturn;
}

Object Runtime_Compare(Object _self, Object _runtime)
{
	DPUSHS ("Runtime: Compare begined.")
	ASSERT_C ( "Runtime:Compare --- Checking for correct object type failed.", _self->gid ==  5367970674748323840ull )
	ASSERT_C ( "Runtime:Compare --- Checking for correct parameter type failed at parameter _runtime.", _runtime->gid ==  5367970674748323840ull || _runtime == _nil )
	Object toReturn = _equal;
	DPOPS ("Runtime: Compare ended.")
	return toReturn;
}
