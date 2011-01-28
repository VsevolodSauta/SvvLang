#include "internals/basics.h"
#include "internals/Char/imports.h"


Object Char_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Char: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Char));
	_self->gid =  6707630545906071552ull;
	Object_SetComparator(_self, &Char_Compare);
	Object_SetDestructor(_self, &Char_Destroy);
	Object_SetCloner(_self, &Char_Clone);
	Object_SetDeepCloner(_self, &Char_DeepClone);
	((Char) (_self->entity))->_code = _nil;
	_self = Char_Init(_self);
	DPOPS ("Char: Create ended.")
	return _self;
}

Object Char_Init(Object _self)
{
	DPUSHS ("Char: Init begined.")
	Object_SetCloning(&(((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 0));
	Object toReturn = _self;
	DPOPS ("Char: Init ended.")
	return toReturn;
}

Object Char_Compare(Object _self, Object _char)
{
	DPUSHS ("Char: Compare begined.")
	Object toReturn = Object_Compare((((Char) (_self->entity))->_code), (((Char) (_char->entity))->_code));
	DPOPS ("Char: Compare ended.")
	return toReturn;
}

Object Char_Destroy(Object _self)
{
	DPUSHS ("Char: Destroy begined.")
	Object_Release((((Char) (_self->entity))->_code));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Char: Destroy ended.")
	return toReturn;
}

Object Char_Clone(Object _self)
{
	DPUSHS ("Char: Clone begined.")
	Object _toReturn;
	_toReturn = Char_Create();
	Char_SetCode(_toReturn, (((Char) (_self->entity))->_code));
	Object toReturn = _toReturn;
	DPOPS ("Char: Clone ended.")
	return toReturn;
}

Object Char_DeepClone(Object _self)
{
	DPUSHS ("Char: DeepClone begined.")
	Object _toReturn;
	_toReturn = Char_Create();
	Char_SetCode(_toReturn, (((Char) (_self->entity))->_code));
	Object toReturn = _toReturn;
	DPOPS ("Char: DeepClone ended.")
	return toReturn;
}

Object Char_SetCode(Object _self, Object _code)
{
	DPUSHS ("Char: SetCode begined.")
	Number_Set((((Char) (_self->entity))->_code), _code);
	Object toReturn = _self;
	DPOPS ("Char: SetCode ended.")
	return toReturn;
}

Object Char_GetCode(Object _self)
{
	DPUSHS ("Char: GetCode begined.")
	Object toReturn = Object_TempClone((((Char) (_self->entity))->_code));
	DPOPS ("Char: GetCode ended.")
	return toReturn;
}

Object Char_GetMutableCode(Object _self)
{
	DPUSHS ("Char: GetMutableCode begined.")
	Object toReturn = (((Char) (_self->entity))->_code);
	DPOPS ("Char: GetMutableCode ended.")
	return toReturn;
}

Object Char_IsSpace(Object _self)
{
	DPUSHS ("Char: IsSpace begined.")
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 32)) == _equal);
	DPOPS ("Char: IsSpace ended.")
	return toReturn;
}

Object Char_IsWhiteSpace(Object _self)
{
	DPUSHS ("Char: IsWhiteSpace begined.")
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 32)) != _greater);
	DPOPS ("Char: IsWhiteSpace ended.")
	return toReturn;
}

Object Char_IsDigit(Object _self)
{
	DPUSHS ("Char: IsDigit begined.")
	Object toReturn = Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 48)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 58)) == _less));
	DPOPS ("Char: IsDigit ended.")
	return toReturn;
}

Object Char_IsHexDigit(Object _self)
{
	DPUSHS ("Char: IsHexDigit begined.")
	Object toReturn = Logic_Or(Char_IsDigit(_self), Logic_Or(Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 97)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 102)) != _greater)), Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 65)) != _less), LogicFactory_FromLong(_logicFactory, Object_Compare((((Char) (_self->entity))->_code), NumberFactory_FromLong(_numberFactory, 70)) != _greater))));
	DPOPS ("Char: IsHexDigit ended.")
	return toReturn;
}
