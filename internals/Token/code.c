#include "internals/basics.h"
#include "internals/Token/imports.h"


Object Token_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Token));
	toReturn->gid =  3556384321805904384ull;
	Object_SetComparator(toReturn, &Token_Compare);
	Object_SetDestructor(toReturn, &Token_Destroy);
	Object_SetCloner(toReturn, &Token_Clone);
	((Token) (toReturn->entity))->_typeQualifier = _nil;
	((Token) (toReturn->entity))->_entity = _nil;
	toReturn = Token_Init(toReturn);
	return toReturn;
}

Object Token_Init(Object _self)
{
	Object_SetRetaining(&(((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 0));
	return _self;
}

Object Token_Compare(Object _self, Object _token)
{
	Object _candidate;
	_candidate = Object_Compare((((Token) (_self->entity))->_typeQualifier), (((Token) (_token->entity))->_typeQualifier));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) == _equal)) != _false)
	{
		if((Token_HasNil(_self)) != _false)
		{
			return _equal;
		}
		if((Token_HasNumber(_self)) != _false)
		{
			return Object_Compare((((Token) (_self->entity))->_entity), (((Token) (_token->entity))->_entity));
		}
		if((Token_HasString(_self)) != _false)
		{
			return Object_Compare((((Token) (_self->entity))->_entity), (((Token) (_token->entity))->_entity));
		}
		if((Token_HasObject(_self)) != _false)
		{
			return Object_Compare((((Token) (_self->entity))->_entity), (((Token) (_token->entity))->_entity));
		}
		return _equal;
	}
	else
	{
		return _candidate;
	}
}

Object Token_Destroy(Object _self)
{
	Object_Release((((Token) (_self->entity))->_typeQualifier));
	return Object_Destroy(_self);
}

Object Token_HasNil(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 0)) == _equal);
}

Object Token_HasNumber(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 1)) == _equal);
}

Object Token_HasString(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 2)) == _equal);
}

Object Token_HasObject(Object _self)
{
	return LogicFactory_FromLong(_logicFactory, Object_Compare((((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 100)) == _equal);
}

Object Token_SetNil(Object _self)
{
	Object_SetRetaining(&(((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 0));
	Object_SetRetaining(&(((Token) (_self->entity))->_entity), _nil);
	return _self;
}

Object Token_SetNumber(Object _self, Object _number)
{
	Object_SetRetaining(&(((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 1));
	Object_SetRetaining(&(((Token) (_self->entity))->_entity), _number);
	return _self;
}

Object Token_SetString(Object _self, Object _string)
{
	Object_SetRetaining(&(((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 2));
	Object_SetRetaining(&(((Token) (_self->entity))->_entity), _string);
	return _self;
}

Object Token_SetObject(Object _self, Object _object)
{
	Object_SetRetaining(&(((Token) (_self->entity))->_typeQualifier), NumberFactory_FromLong(_numberFactory, 100));
	Object_SetRetaining(&(((Token) (_self->entity))->_entity), _object);
	return _self;
}
