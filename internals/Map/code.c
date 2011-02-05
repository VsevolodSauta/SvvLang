#include "internals/basics.h"
#include "internals/Map/imports.h"


Object Map_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Map: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Map));
	_self->gid =  7784561639000363008ull;
	Object_SetComparator(_self, &Map_Compare);
	Object_SetDestructor(_self, &Map_Destroy);
	Object_SetCloner(_self, &Map_Clone);
	Object_SetDeepCloner(_self, &Map_DeepClone);
	((Map) (_self->entity))->_keys = _nil;
	((Map) (_self->entity))->_values = _nil;
	_self = Map_Init(_self);
	DPOPS ("Map: Create ended.")
	return _self;
}

Object Map_Init(Object _self)
{
	DPUSHS ("Map: Init begined.")
	ASSERT_C ( "Map:Init --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object_SetReleasing(&(((Map) (_self->entity))->_keys), List_Create());
	Object_SetReleasing(&(((Map) (_self->entity))->_values), List_Create());
	Object toReturn = _self;
	DPOPS ("Map: Init ended.")
	return toReturn;
}

Object Map_Destroy(Object _self)
{
	DPUSHS ("Map: Destroy begined.")
	ASSERT_C ( "Map:Destroy --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object_Release((((Map) (_self->entity))->_keys));
	Object_Release((((Map) (_self->entity))->_values));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Map: Destroy ended.")
	return toReturn;
}

Object Map_Clone(Object _self)
{
	DPUSHS ("Map: Clone begined.")
	ASSERT_C ( "Map:Clone --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object _toReturn;
	_toReturn = Map_Create();
	Object_SetReleasing(&(((Map) (_toReturn->entity))->_keys), Object_Clone((((Map) (_self->entity))->_keys)));
	Object_SetReleasing(&(((Map) (_toReturn->entity))->_values), Object_Clone((((Map) (_self->entity))->_values)));
	Object toReturn = _toReturn;
	DPOPS ("Map: Clone ended.")
	return toReturn;
}

Object Map_DeepClone(Object _self)
{
	DPUSHS ("Map: DeepClone begined.")
	ASSERT_C ( "Map:DeepClone --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object _toReturn;
	_toReturn = Map_Create();
	Object_SetRetaining(&(((Map) (_toReturn->entity))->_keys), Object_DeepClone((((Map) (_self->entity))->_keys)));
	Object_SetRetaining(&(((Map) (_toReturn->entity))->_values), Object_DeepClone((((Map) (_self->entity))->_values)));
	Object toReturn = _toReturn;
	DPOPS ("Map: DeepClone ended.")
	return toReturn;
}

Object Map_Compare(Object _self, Object _map)
{
	DPUSHS ("Map: Compare begined.")
	ASSERT_C ( "Map:Compare --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object _candidate;
	_candidate = Object_Compare((((Map) (_self->entity))->_keys), (((Map) (_map->entity))->_keys));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Map: Compare ended.")
		return toReturn;
	}
	Object toReturn = Object_Compare((((Map) (_self->entity))->_values), (((Map) (_map->entity))->_values));
	DPOPS ("Map: Compare ended.")
	return toReturn;
}

Object Map_Empty(Object _self)
{
	DPUSHS ("Map: Empty begined.")
	ASSERT_C ( "Map:Empty --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object toReturn = List_Empty((((Map) (_self->entity))->_keys));
	DPOPS ("Map: Empty ended.")
	return toReturn;
}

Object Map_Size(Object _self)
{
	DPUSHS ("Map: Size begined.")
	ASSERT_C ( "Map:Size --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object toReturn = List_Size((((Map) (_self->entity))->_keys));
	DPOPS ("Map: Size ended.")
	return toReturn;
}

Object Map_Add(Object _self, Object _key, Object _value)
{
	DPUSHS ("Map: Add begined.")
	ASSERT_C ( "Map:Add --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
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
			Object toReturn = _self;
			DPOPS ("Map: Add ended.")
			return toReturn;
		}
	}
	ListIterator_AddBefore(_keysIterator, _key);
	ListIterator_AddBefore(_valuesIterator, _value);
	Object toReturn = _self;
	DPOPS ("Map: Add ended.")
	return toReturn;
}

Object Map_RemoveKey(Object _self, Object _key)
{
	DPUSHS ("Map: RemoveKey begined.")
	ASSERT_C ( "Map:RemoveKey --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
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
	Object toReturn = _self;
	DPOPS ("Map: RemoveKey ended.")
	return toReturn;
}

Object Map_RemoveKeyConfirming(Object _self, Object _key)
{
	DPUSHS ("Map: RemoveKeyConfirming begined.")
	ASSERT_C ( "Map:RemoveKeyConfirming --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
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
			Object toReturn = _true;
			DPOPS ("Map: RemoveKeyConfirming ended.")
			return toReturn;
		}
	}
	Object toReturn = _false;
	DPOPS ("Map: RemoveKeyConfirming ended.")
	return toReturn;
}

Object Map_ContainsKey(Object _self, Object _key)
{
	DPUSHS ("Map: ContainsKey begined.")
	ASSERT_C ( "Map:ContainsKey --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
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
			Object toReturn = _true;
			DPOPS ("Map: ContainsKey ended.")
			return toReturn;
		}
	}
	Object toReturn = _false;
	DPOPS ("Map: ContainsKey ended.")
	return toReturn;
}

Object Map_GetValueForKey(Object _self, Object _key)
{
	DPUSHS ("Map: GetValueForKey begined.")
	ASSERT_C ( "Map:GetValueForKey --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
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
			Object toReturn = ListIterator_ThisData(_valuesIterator);
			DPOPS ("Map: GetValueForKey ended.")
			return toReturn;
		}
	}
	Object toReturn = _nil;
	DPOPS ("Map: GetValueForKey ended.")
	return toReturn;
}

Object Map_First(Object _self)
{
	DPUSHS ("Map: First begined.")
	ASSERT_C ( "Map:First --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object _iterator;
	_iterator = MapIterator_Create();
	MapIterator_SetMap(_iterator, _self);
	MapIterator_ToBegin(_iterator);
	Object toReturn = Object_Autorelease(_iterator);
	DPOPS ("Map: First ended.")
	return toReturn;
}

Object Map_Last(Object _self)
{
	DPUSHS ("Map: Last begined.")
	ASSERT_C ( "Map:Last --- Checking for correct object type failed.", _self->gid ==  7784561639000363008ull )
	Object _iterator;
	_iterator = MapIterator_Create();
	MapIterator_SetMap(_iterator, _self);
	MapIterator_ToEnd(_iterator);
	Object toReturn = Object_Autorelease(_iterator);
	DPOPS ("Map: Last ended.")
	return toReturn;
}
