#include "internals/basics.h"
#include "internals/Char/imports.h"


Object Char_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Char));
	toReturn->gid =  6707630545906071552ull;
	Object_SetComparator(toReturn, &Char_Compare);
	Object_SetDestructor(toReturn, &Char_Destroy);
	Object_SetCloner(toReturn, &Char_Clone);
	toReturn = Char_Init(toReturn);
	return toReturn;
}

Object Char_Init(Object _self)
{
	(((Char) (_self->entity))->_code) = Object_Retain(NumberFactory_FromLong(_numberFactory, 0));
	return _self;
}

Object Char_Compare(Object _self, Object _char)
{
	return Object_Compare((((Char) (_self->entity))->_code), (((Char) (_char->entity))->_code));
}

Object Char_Destroy(Object _self)
{
	Object_Release((((Char) (_self->entity))->_code));
	return Object_Destroy(_self);
}

Object Char_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = Char_Create();
	Char_SetCode(_toReturn, (((Char) (_self->entity))->_code));
	return _toReturn;
}

Object Char_SetCode(Object _self, Object _code)
{
	Number_Set((((Char) (_self->entity))->_code), _code);
	return _self;
}

Object Char_GetCode(Object _self)
{
	return Object_TempClone((((Char) (_self->entity))->_code));
}
