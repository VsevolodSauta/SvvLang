#include "internals/basics.h"
#include "internals/ListMap/imports.h"


Object ListMap_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct ListMap));
	toReturn->gid =  2108332898258556672ull;
	Object_SetComparator(toReturn, &ListMap_Compare);
	Object_SetDestructor(toReturn, &ListMap_Destroy);
	Object_SetCloner(toReturn, &ListMap_Clone);
	((ListMap) (toReturn->entity))->_root = _nil;
	toReturn = ListMap_Init(toReturn);
	return toReturn;
}

Object ListMap_Init(Object _self)
{
	(((ListMap) (_self->entity))->_root) = ListMapNode_Create();
	return _self;
}

Object ListMap_Compare(Object _self, Object _listSet)
{
	return Object_Compare((((ListMap) (_self->entity))->_root), (((ListMap) (_listSet->entity))->_root));
}

Object ListMap_Destroy(Object _self)
{
	Object_Release((((ListMap) (_self->entity))->_root));
	return Object_Destroy(_self);
}

Object ListMap_Clone(Object _self)
{
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Release((((ListMap) (_toReturn->entity))->_root));
	(((ListMap) (_toReturn->entity))->_root) = Object_Clone((((ListMap) (_self->entity))->_root));
	return _toReturn;
}

Object ListMap_Add(Object _self, Object _list, Object _object)
{
	Object _iterator;
	_iterator = List_First(_list);
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			Object _next;
			_next = ListMapNode_Create();
			Map_Add((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator), _next);
			_node = _next;
		}
		ListIterator_Next(_iterator);
	}
	(((ListMapNode) (_node->entity))->_mapped) = _true;
	Object_SetRetaining(&(((ListMapNode) (_node->entity))->_mapping), _object);
	return _self;
}

Object ListMap_RemoveKey(Object _self, Object _list)
{
	Object _iterator;
	_iterator = List_First(_list);
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			return _self;
		}
		ListIterator_Next(_iterator);
	}
	(((ListMapNode) (_node->entity))->_mapped) = _false;
	Object_SetRetaining(&(((ListMapNode) (_node->entity))->_mapping), _nil);
	return _self;
}

Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list)
{
	Object _iterator;
	_iterator = List_First(_list);
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			return _false;
		}
		ListIterator_Next(_iterator);
	}
	(((ListMapNode) (_node->entity))->_mapped) = _false;
	Object_SetRetaining(&(((ListMapNode) (_node->entity))->_mapping), _nil);
	return _true;
}

Object ListMap_GetAt(Object _self, Object _list)
{
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	Object _iterator;
	_iterator = List_First(_list);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			return _nil;
		}
		ListIterator_Next(_iterator);
	}
	if(((((ListMapNode) (_node->entity))->_mapped)) != _false)
	{
		return (((ListMapNode) (_node->entity))->_mapping);
	}
	else
	{
		return _nil;
	}
}

Object ListMap_Contains(Object _self, Object _list)
{
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	Object _iterator;
	_iterator = List_First(_list);
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			return _false;
		}
		ListIterator_Next(_iterator);
	}
	return (((ListMapNode) (_node->entity))->_mapped);
}
