#include "internals/basics.h"
#include "internals/UIDGenerator/imports.h"


Object UIDGenerator_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct UIDGenerator));
	toReturn->gid =  8939281001414702080ull;
	Object_SetComparator(toReturn, &UIDGenerator_Compare);
	Object_SetDestructor(toReturn, &UIDGenerator_Destroy);
	Object_SetCloner(toReturn, &UIDGenerator_Clone);
	((UIDGenerator) (toReturn->entity))->_currentUID = _nil;
	toReturn = UIDGenerator_Init(toReturn);
	return toReturn;
}

Object UIDGenerator_Init(Object _self)
{
	DPUSHS( "UID Generator: Initing." ) 
	Object_SetCloning(&(((UIDGenerator) (_self->entity))->_currentUID), NumberFactory_FromLong(_numberFactory, 0));
	DPOPS( "UID Generator: Inited." ) 
	return _self;
}

Object UIDGenerator_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = UIDGenerator_Create();
	Object_SetCloning(&(((UIDGenerator) (_toReturn->entity))->_currentUID), (((UIDGenerator) (_self->entity))->_currentUID));
	return _toReturn;
}

Object UIDGenerator_Destroy(Object _self)
{
	Object_Release((((UIDGenerator) (_self->entity))->_currentUID));
	return Object_Destroy(_self);
}

Object UIDGenerator_Compare(Object _self, Object _uidGenerator)
{
	return Object_Compare(Object_Hash(_self), Object_Hash(_uidGenerator));
}

Object UIDGenerator_getUID(Object _self)
{
	DPUSHS( "UID Generator: Generating UID." ) 
	Object def = StringFactory_FromNumber(_stringFactory, (((UIDGenerator) (_self->entity))->_currentUID));
	Number_Inc((((UIDGenerator) (_self->entity))->_currentUID));
	DPOPS( "UID Generator: UID generated." ) 
	return def;
}
