#include "internals/basics.h"
#include "internals/ListMapNode/imports.h"


Object ListMapNode_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct ListMapNode));
	toReturn->gid =  5883107801261346816ull;
	Object_SetComparator(toReturn, &ListMapNode_Compare);
	Object_SetDestructor(toReturn, &ListMapNode_Destroy);
	Object_SetCloner(toReturn, &ListMapNode_Clone);
	Object_SetDeepCloner(toReturn, &ListMapNode_DeepClone);
	((ListMapNode) (toReturn->entity))->_nextMap = _nil;
	((ListMapNode) (toReturn->entity))->_mapped = _nil;
	((ListMapNode) (toReturn->entity))->_mapping = _nil;
	toReturn = ListMapNode_Init(toReturn);
	return toReturn;
}

Object ListMapNode_Init(Object _self)
{
	Object_SetReleasing(&(((ListMapNode) (_self->entity))->_nextMap), Map_Create());
	Object_SetRetaining(&(((ListMapNode) (_self->entity))->_mapping), _nil);
	(((ListMapNode) (_self->entity))->_mapped) = _false;
	return _self;
}

Object ListMapNode_Destroy(Object _self)
{
	Object_Release((((ListMapNode) (_self->entity))->_nextMap));
	Object_Release((((ListMapNode) (_self->entity))->_mapping));
	return Object_Destroy(_self);
}

Object ListMapNode_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = ListMapNode_Create();
	Object_SetReleasing(&(((ListMapNode) (_toReturn->entity))->_nextMap), Object_Clone((((ListMapNode) (_self->entity))->_nextMap)));
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_mapping), (((ListMapNode) (_self->entity))->_mapping));
	(((ListMapNode) (_toReturn->entity))->_mapped) = (((ListMapNode) (_self->entity))->_mapped);
	return _toReturn;
}

Object ListMapNode_DeepClone(Object _self)
{
	Object _toReturn;
	_toReturn = ListMapNode_Create();
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_nextMap), Object_DeepClone((((ListMapNode) (_self->entity))->_nextMap)));
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_mapping), Object_DeepClone((((ListMapNode) (_self->entity))->_mapping)));
	(((ListMapNode) (_toReturn->entity))->_mapped) = (((ListMapNode) (_self->entity))->_mapped);
	return _toReturn;
}

Object ListMapNode_Compare(Object _self, Object _listMapNode)
{
	Object _candidate;
	_candidate = Object_Compare((((ListMapNode) (_self->entity))->_mapped), (((ListMapNode) (_listMapNode->entity))->_mapped));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		return _candidate;
	}
	if(((((ListMapNode) (_self->entity))->_mapped)) != _false)
	{
		_candidate = Object_Compare((((ListMapNode) (_self->entity))->_mapping), (((ListMapNode) (_listMapNode->entity))->_mapping));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
		{
			return _candidate;
		}
	}
	return Object_Compare((((ListMapNode) (_self->entity))->_nextMap), (((ListMapNode) (_listMapNode->entity))->_nextMap));
}

Object ListMapNode_MergeRecursiveStrong(Object _self, Object _listMapNode)
{
	if(((((ListMapNode) (_listMapNode->entity))->_mapped)) != _false)
	{
		(((ListMapNode) (_self->entity))->_mapped) = _true;
		Object_SetRetaining(&(((ListMapNode) (_self->entity))->_mapping), (((ListMapNode) (_listMapNode->entity))->_mapping));
	}
	Object _keysIterator;
	_keysIterator = List_First((((Map) ((((ListMapNode) (_listMapNode->entity))->_nextMap)->entity))->_keys));
	while((Logic_Not(ListIterator_ThisEnd(_keysIterator))) != _false)
	{
		Object _key;
		_key = ListIterator_CharData(_keysIterator);
		Object _value;
		_value = Map_GetValueForKey((((ListMapNode) (_self->entity))->_nextMap), _key);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
		{
			_value = ListMapNode_Create();
			Map_Add((((ListMapNode) (_self->entity))->_nextMap), _key, _value);
			Object_Release(_value);
		}
		ListMapNode_MergeRecursiveStrong(_value, Map_GetValueForKey((((ListMapNode) (_listMapNode->entity))->_nextMap), _key));
	}
	return _self;
}
