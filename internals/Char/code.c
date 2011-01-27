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
	Object_SetDeepCloner(toReturn, &Char_DeepClone);
	((Char) (toReturn->entity))->_code = _nil;
	toReturn = Char_Init(toReturn);
	return toReturn;
}

Object Char_Init(Object _self)
{
	Object_SetCloning(&(((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 0));
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

Object Char_DeepClone(Object _self)
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

Object Char_GetMutableCode(Object _self)
{
	return (((Char) (_self->entity))->_code);
}

Object Char_IsSpace(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 32)) == _equal);
}

Object Char_IsWhiteSpace(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 32)) != _greater);
}

Object Char_IsDigit(Object _self)
{
	return Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 48)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 58)) == _less));
}

Object Char_IsHexDigit(Object _self)
{
	return Logic_Or(Char_IsDigit(_self), Logic_Or(Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 97)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 102)) != _greater)), Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 65)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 70)) != _greater))));
}
