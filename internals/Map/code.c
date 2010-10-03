#include "internals/basics.h"
#include "internals/Map/imports.h"


Object Map_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Map));
	toReturn->gid =  7784561639000363008ull;
	Object_SetComparator(toReturn, &Map_Compare);
	Object_SetDestructor(toReturn, &Map_Destroy);
	Object_SetCloner(toReturn, &Map_Clone);
	((Map) (toReturn->entity))->_keys = _nil;
	((Map) (toReturn->entity))->_values = _nil;
	toReturn = Map_Init(toReturn);
	return toReturn;
}

Object Map_Init(Object _self)
{
	Object_SetReleasing(&(((Map) (_self->entity))->_keys), List_Create());
	Object_SetReleasing(&(((Map) (_self->entity))->_values), List_Create());
	return _self;
}

Object Map_Destroy(Object _self)
{
	Object_Release((((Map) (_self->entity))->_keys));
	Object_Release((((Map) (_self->entity))->_values));
	return Object_Destroy(_self);
}

Object Map_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = Map_Create();
	Object_SetReleasing(&(((Map) (_toReturn->entity))->_keys), Object_Clone((((Map) (_self->entity))->_keys)));
	Object_SetReleasing(&(((Map) (_toReturn->entity))->_values), Object_Clone((((Map) (_self->entity))->_values)));
	return _toReturn;
}

Object Map_Compare(Object _self, Object _map)
{
	Object _candidate;
	_candidate = Object_Compare((((Map) (_self->entity))->_keys), (((Map) (_map->entity))->_keys));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		return _candidate;
	}
	return Object_Compare((((Map) (_self->entity))->_values), (((Map) (_map->entity))->_values));
}

Object Map_Add(Object _self, Object _key, Object _value)
{
	Object _keysIterator;
	_keysIterator = List_First((((Map) (_self->entity))->_keys));
	Object _valuesIterator;
	_valuesIterator = List_First((((Map) (_self->entity))->_values));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _less)) != _false)
		{
			ListIterator_Next(_keysIterator);
			ListIterator_Next(_valuesIterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _greater)) != _false)
		{
			break;
		}
		else
		{
			ListIterator_ThisSetData(_valuesIterator, _value);
			return _self;
		}
	}
	ListIterator_AddBefore(_keysIterator, _key);
	ListIterator_AddBefore(_valuesIterator, _value);
	return _self;
}

Object Map_RemoveKey(Object _self, Object _key)
{
	Object _keysIterator;
	_keysIterator = List_First((((Map) (_self->entity))->_keys));
	Object _valuesIterator;
	_valuesIterator = List_First((((Map) (_self->entity))->_values));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _less)) != _false)
		{
			ListIterator_Next(_keysIterator);
			ListIterator_Next(_valuesIterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _greater)) != _false)
		{
			break;
		}
		else
		{
			ListIterator_ThisRemove(_valuesIterator);
			ListIterator_ThisRemove(_keysIterator);
			break;
		}
	}
	return _self;
}

Object Map_RemoveKeyConfirming(Object _self, Object _key)
{
	Object _keysIterator;
	_keysIterator = List_First((((Map) (_self->entity))->_keys));
	Object _valuesIterator;
	_valuesIterator = List_First((((Map) (_self->entity))->_values));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _less)) != _false)
		{
			ListIterator_Next(_keysIterator);
			ListIterator_Next(_valuesIterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _greater)) != _false)
		{
			break;
		}
		else
		{
			ListIterator_ThisRemove(_valuesIterator);
			ListIterator_ThisRemove(_keysIterator);
			return _true;
		}
	}
	return _false;
}

Object Map_ContainsKey(Object _self, Object _key)
{
	Object _keysIterator;
	_keysIterator = List_First((((Map) (_self->entity))->_keys));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _less)) != _false)
		{
			ListIterator_Next(_keysIterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _greater)) != _false)
		{
			break;
		}
		else
		{
			return _true;
		}
	}
	return _false;
}

Object Map_GetValueForKey(Object _self, Object _key)
{
	Object _keysIterator;
	_keysIterator = List_First((((Map) (_self->entity))->_keys));
	Object _valuesIterator;
	_valuesIterator = List_First((((Map) (_self->entity))->_values));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _less)) != _false)
		{
			ListIterator_Next(_keysIterator);
			ListIterator_Next(_valuesIterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_keysIterator), _key) == _greater)) != _false)
		{
			break;
		}
		else
		{
			return ListIterator_ThisData(_keysIterator);
		}
	}
	return _nil;
}
