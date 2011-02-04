#include "internals/basics.h"
#include "internals/MapIterator/imports.h"


Object MapIterator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("MapIterator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct MapIterator));
	_self->gid =  2171829371942269696ull;
	Object_SetComparator(_self, &MapIterator_Compare);
	Object_SetDestructor(_self, &MapIterator_Destroy);
	Object_SetCloner(_self, &MapIterator_Clone);
	Object_SetDeepCloner(_self, &MapIterator_DeepClone);
	((MapIterator) (_self->entity))->_map = _nil;
	((MapIterator) (_self->entity))->_keysIterator = _nil;
	((MapIterator) (_self->entity))->_valuesIterator = _nil;
	DPOPS ("MapIterator: Create ended.")
	return _self;
}

Object MapIterator_SetMap(Object _self, Object _map)
{
	DPUSHS ("MapIterator: SetMap begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object_SetRetaining(&(((MapIterator) (_self->entity))->_map), _map);
	Object toReturn = _self;
	DPOPS ("MapIterator: SetMap ended.")
	return toReturn;
}

Object MapIterator_ToBegin(Object _self)
{
	DPUSHS ("MapIterator: ToBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object_SetRetaining(&(((MapIterator) (_self->entity))->_keysIterator), List_First((((Map) ((((MapIterator) (_self->entity))->_map)->entity))->_keys)));
	Object_SetRetaining(&(((MapIterator) (_self->entity))->_valuesIterator), List_First((((Map) ((((MapIterator) (_self->entity))->_map)->entity))->_values)));
	Object toReturn = _self;
	DPOPS ("MapIterator: ToBegin ended.")
	return toReturn;
}

Object MapIterator_ToEnd(Object _self)
{
	DPUSHS ("MapIterator: ToEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object_SetRetaining(&(((MapIterator) (_self->entity))->_keysIterator), List_Last((((Map) ((((MapIterator) (_self->entity))->_map)->entity))->_keys)));
	Object_SetRetaining(&(((MapIterator) (_self->entity))->_valuesIterator), List_Last((((Map) ((((MapIterator) (_self->entity))->_map)->entity))->_values)));
	Object toReturn = _self;
	DPOPS ("MapIterator: ToEnd ended.")
	return toReturn;
}

Object MapIterator_Next(Object _self)
{
	DPUSHS ("MapIterator: Next begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	ListIterator_Next((((MapIterator) (_self->entity))->_keysIterator));
	ListIterator_Next((((MapIterator) (_self->entity))->_valuesIterator));
	Object toReturn = _self;
	DPOPS ("MapIterator: Next ended.")
	return toReturn;
}

Object MapIterator_Prev(Object _self)
{
	DPUSHS ("MapIterator: Prev begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	ListIterator_Prev((((MapIterator) (_self->entity))->_keysIterator));
	ListIterator_Prev((((MapIterator) (_self->entity))->_valuesIterator));
	Object toReturn = _self;
	DPOPS ("MapIterator: Prev ended.")
	return toReturn;
}

Object MapIterator_ThisEnd(Object _self)
{
	DPUSHS ("MapIterator: ThisEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_ThisEnd((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: ThisEnd ended.")
	return toReturn;
}

Object MapIterator_ThisBegin(Object _self)
{
	DPUSHS ("MapIterator: ThisBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_ThisBegin((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: ThisBegin ended.")
	return toReturn;
}

Object MapIterator_PrevBegin(Object _self)
{
	DPUSHS ("MapIterator: PrevBegin begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_PrevBegin((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: PrevBegin ended.")
	return toReturn;
}

Object MapIterator_NextEnd(Object _self)
{
	DPUSHS ("MapIterator: NextEnd begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_NextEnd((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: NextEnd ended.")
	return toReturn;
}

Object MapIterator_ThisKey(Object _self)
{
	DPUSHS ("MapIterator: ThisKey begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_ThisData((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: ThisKey ended.")
	return toReturn;
}

Object MapIterator_NextKey(Object _self)
{
	DPUSHS ("MapIterator: NextKey begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_NextData((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: NextKey ended.")
	return toReturn;
}

Object MapIterator_PrevKey(Object _self)
{
	DPUSHS ("MapIterator: PrevKey begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_PrevData((((MapIterator) (_self->entity))->_keysIterator));
	DPOPS ("MapIterator: PrevKey ended.")
	return toReturn;
}

Object MapIterator_ThisValue(Object _self)
{
	DPUSHS ("MapIterator: ThisValue begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_ThisData((((MapIterator) (_self->entity))->_valuesIterator));
	DPOPS ("MapIterator: ThisValue ended.")
	return toReturn;
}

Object MapIterator_NextValue(Object _self)
{
	DPUSHS ("MapIterator: NextValue begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_NextData((((MapIterator) (_self->entity))->_valuesIterator));
	DPOPS ("MapIterator: NextValue ended.")
	return toReturn;
}

Object MapIterator_PrevValue(Object _self)
{
	DPUSHS ("MapIterator: PrevValue begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object toReturn = ListIterator_PrevData((((MapIterator) (_self->entity))->_valuesIterator));
	DPOPS ("MapIterator: PrevValue ended.")
	return toReturn;
}

Object MapIterator_Compare(Object _self, Object _mapIterator)
{
	DPUSHS ("MapIterator: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object _candidate;
	_candidate = Object_Compare((((MapIterator) (_self->entity))->_keysIterator), (((MapIterator) (_mapIterator->entity))->_keysIterator));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) == _equal)) != _false)
	{
		_candidate = Object_Compare((((MapIterator) (_self->entity))->_valuesIterator), (((MapIterator) (_mapIterator->entity))->_valuesIterator));
	}
	Object toReturn = _candidate;
	DPOPS ("MapIterator: Compare ended.")
	return toReturn;
}

Object MapIterator_Clone(Object _self)
{
	DPUSHS ("MapIterator: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object _toReturn;
	_toReturn = MapIterator_Create();
	Object_SetRetaining(&(((MapIterator) (_toReturn->entity))->_map), (((MapIterator) (_self->entity))->_map));
	Object_SetReleasing(&(((MapIterator) (_toReturn->entity))->_keysIterator), Object_Clone((((MapIterator) (_self->entity))->_keysIterator)));
	Object_SetReleasing(&(((MapIterator) (_toReturn->entity))->_valuesIterator), Object_Clone((((MapIterator) (_self->entity))->_valuesIterator)));
	Object toReturn = _toReturn;
	DPOPS ("MapIterator: Clone ended.")
	return toReturn;
}

Object MapIterator_DeepClone(Object _self)
{
	DPUSHS ("MapIterator: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object _toReturn;
	_toReturn = MapIterator_Create();
	Object_SetRetaining(&(((MapIterator) (_toReturn->entity))->_map), (((MapIterator) (_self->entity))->_map));
	Object_SetRetaining(&(((MapIterator) (_toReturn->entity))->_keysIterator), Object_DeepClone((((MapIterator) (_self->entity))->_keysIterator)));
	Object_SetRetaining(&(((MapIterator) (_toReturn->entity))->_valuesIterator), Object_DeepClone((((MapIterator) (_self->entity))->_valuesIterator)));
	Object toReturn = _toReturn;
	DPOPS ("MapIterator: DeepClone ended.")
	return toReturn;
}

Object MapIterator_Destroy(Object _self)
{
	DPUSHS ("MapIterator: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  2171829371942269696ulll )
	Object_Release((((MapIterator) (_self->entity))->_keysIterator));
	Object_Release((((MapIterator) (_self->entity))->_valuesIterator));
	Object_Release((((MapIterator) (_self->entity))->_map));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("MapIterator: Destroy ended.")
	return toReturn;
}
