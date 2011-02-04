#include "internals/basics.h"
#include "internals/ListMapNode/imports.h"


Object ListMapNode_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListMapNode: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListMapNode));
	_self->gid =  5883107801261346816ull;
	Object_SetComparator(_self, &ListMapNode_Compare);
	Object_SetDestructor(_self, &ListMapNode_Destroy);
	Object_SetCloner(_self, &ListMapNode_Clone);
	Object_SetDeepCloner(_self, &ListMapNode_DeepClone);
	((ListMapNode) (_self->entity))->_nextMap = _nil;
	((ListMapNode) (_self->entity))->_mapped = _nil;
	((ListMapNode) (_self->entity))->_mapping = _nil;
	_self = ListMapNode_Init(_self);
	DPOPS ("ListMapNode: Create ended.")
	return _self;
}

Object ListMapNode_Init(Object _self)
{
	DPUSHS ("ListMapNode: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
	Object_SetReleasing(&(((ListMapNode) (_self->entity))->_nextMap), Map_Create());
	Object_SetRetaining(&(((ListMapNode) (_self->entity))->_mapping), _nil);
	(((ListMapNode) (_self->entity))->_mapped) = _false;
	Object toReturn = _self;
	DPOPS ("ListMapNode: Init ended.")
	return toReturn;
}

Object ListMapNode_Destroy(Object _self)
{
	DPUSHS ("ListMapNode: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
	Object_Release((((ListMapNode) (_self->entity))->_nextMap));
	Object_Release((((ListMapNode) (_self->entity))->_mapping));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListMapNode: Destroy ended.")
	return toReturn;
}

Object ListMapNode_Clone(Object _self)
{
	DPUSHS ("ListMapNode: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
	Object _toReturn;
	_toReturn = ListMapNode_Create();
	Object_SetReleasing(&(((ListMapNode) (_toReturn->entity))->_nextMap), Object_Clone((((ListMapNode) (_self->entity))->_nextMap)));
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_mapping), (((ListMapNode) (_self->entity))->_mapping));
	(((ListMapNode) (_toReturn->entity))->_mapped) = (((ListMapNode) (_self->entity))->_mapped);
	Object toReturn = _toReturn;
	DPOPS ("ListMapNode: Clone ended.")
	return toReturn;
}

Object ListMapNode_DeepClone(Object _self)
{
	DPUSHS ("ListMapNode: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
	Object _toReturn;
	_toReturn = ListMapNode_Create();
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_nextMap), Object_DeepClone((((ListMapNode) (_self->entity))->_nextMap)));
	Object_SetRetaining(&(((ListMapNode) (_toReturn->entity))->_mapping), Object_DeepClone((((ListMapNode) (_self->entity))->_mapping)));
	(((ListMapNode) (_toReturn->entity))->_mapped) = (((ListMapNode) (_self->entity))->_mapped);
	Object toReturn = _toReturn;
	DPOPS ("ListMapNode: DeepClone ended.")
	return toReturn;
}

Object ListMapNode_Compare(Object _self, Object _listMapNode)
{
	DPUSHS ("ListMapNode: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
	Object _candidate;
	_candidate = Object_Compare((((ListMapNode) (_self->entity))->_mapped), (((ListMapNode) (_listMapNode->entity))->_mapped));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("ListMapNode: Compare ended.")
		return toReturn;
	}
	if(((((ListMapNode) (_self->entity))->_mapped)) != _false)
	{
		_candidate = Object_Compare((((ListMapNode) (_self->entity))->_mapping), (((ListMapNode) (_listMapNode->entity))->_mapping));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) != _equal)) != _false)
		{
			Object toReturn = _candidate;
			DPOPS ("ListMapNode: Compare ended.")
			return toReturn;
		}
	}
	Object toReturn = Object_Compare((((ListMapNode) (_self->entity))->_nextMap), (((ListMapNode) (_listMapNode->entity))->_nextMap));
	DPOPS ("ListMapNode: Compare ended.")
	return toReturn;
}

Object ListMapNode_MergeRecursiveStrong(Object _self, Object _listMapNode)
{
	DPUSHS ("ListMapNode: MergeRecursiveStrong begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  5883107801261346816ulll )
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
	Object toReturn = _self;
	DPOPS ("ListMapNode: MergeRecursiveStrong ended.")
	return toReturn;
}
