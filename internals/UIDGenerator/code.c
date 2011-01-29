#include "internals/basics.h"
#include "internals/UIDGenerator/imports.h"


Object UIDGenerator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("UIDGenerator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct UIDGenerator));
	_self->gid =  8939281001414702080ull;
	Object_SetComparator(_self, &UIDGenerator_Compare);
	Object_SetDestructor(_self, &UIDGenerator_Destroy);
	Object_SetCloner(_self, &UIDGenerator_Clone);
	Object_SetDeepCloner(_self, &UIDGenerator_DeepClone);
	((UIDGenerator) (_self->entity))->_currentUID = _nil;
	_self = UIDGenerator_Init(_self);
	DPOPS ("UIDGenerator: Create ended.")
	return _self;
}

Object UIDGenerator_Init(Object _self)
{
	DPUSHS ("UIDGenerator: Init begined.")
	Object_SetCloning(&(((UIDGenerator) (_self->entity))->_currentUID), NumberFactory_FromLong(_numberFactory, 0));
	Object toReturn = _self;
	DPOPS ("UIDGenerator: Init ended.")
	return toReturn;
}

Object UIDGenerator_Clone(Object _self)
{
	DPUSHS ("UIDGenerator: Clone begined.")
	Object _toReturn;
	_toReturn = UIDGenerator_Create();
	Object_SetCloning(&(((UIDGenerator) (_toReturn->entity))->_currentUID), (((UIDGenerator) (_self->entity))->_currentUID));
	Object toReturn = _toReturn;
	DPOPS ("UIDGenerator: Clone ended.")
	return toReturn;
}

Object UIDGenerator_DeepClone(Object _self)
{
	DPUSHS ("UIDGenerator: DeepClone begined.")
	Object _toReturn;
	_toReturn = UIDGenerator_Create();
	Object_SetCloning(&(((UIDGenerator) (_toReturn->entity))->_currentUID), (((UIDGenerator) (_self->entity))->_currentUID));
	Object toReturn = _toReturn;
	DPOPS ("UIDGenerator: DeepClone ended.")
	return toReturn;
}

Object UIDGenerator_Destroy(Object _self)
{
	DPUSHS ("UIDGenerator: Destroy begined.")
	Object_Release((((UIDGenerator) (_self->entity))->_currentUID));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("UIDGenerator: Destroy ended.")
	return toReturn;
}

Object UIDGenerator_Compare(Object _self, Object _uidGenerator)
{
	DPUSHS ("UIDGenerator: Compare begined.")
	Object toReturn = Object_Compare(Object_Hash(_self), Object_Hash(_uidGenerator));
	DPOPS ("UIDGenerator: Compare ended.")
	return toReturn;
}

Object UIDGenerator_GenerateUID(Object _self)
{
	DPUSHS ("UIDGenerator: GenerateUID begined.")
	Object def = StringFactory_FromNumber(_stringFactory, (((UIDGenerator) (_self->entity))->_currentUID));
	Number_Inc((((UIDGenerator) (_self->entity))->_currentUID));
	DPOPS ("UIDGenerator: GenerateUID ended.")
	return def;
}
