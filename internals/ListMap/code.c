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

Object ListMap_Empty(Object _self)
{
	return Logic_And(Logic_Not((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_mapped)), Map_Empty((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_nextMap)));
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
			Object_Release(_next);
			_node = _next;
		}
		ListIterator_Next(_iterator);
	}
	(((ListMapNode) (_node->entity))->_mapped) = _true;
	Object_SetRetaining(&(((ListMapNode) (_node->entity))->_mapping), _object);
	return _self;
}

Object ListMap_Remove(Object _self, Object _list)
{
	ListMap_RemoveKeyWithConfirmation(_self, _list);
	return _self;
}

Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list)
{
	Object _stack;
	_stack = Stack_Create();
	Object _iterator;
	_iterator = List_First(_list);
	Object _node;
	_node = (((ListMap) (_self->entity))->_root);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Map_ContainsKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator))) != _false)
		{
			Stack_Push(_stack, _node);
			_node = Map_GetValueForKey((((ListMapNode) (_node->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
		else
		{
			Object_Release(_stack);
			return _false;
		}
		ListIterator_Next(_iterator);
	}
	Stack_Push(_stack, _node);
	(((ListMapNode) (_node->entity))->_mapped) = _false;
	Object_SetRetaining(&(((ListMapNode) (_node->entity))->_mapping), _nil);
	while((Logic_And(Logic_Not(Stack_Empty(_stack)), Logic_Not(ListIterator_PrevBegin(_iterator)))) != _false)
	{
		_node = Stack_Pop(_stack);
		ListIterator_Prev(_iterator);
		if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(Map_Size((((ListMapNode) (_node->entity))->_nextMap)), NumberFactory_FromLong(_numberFactory, 0)) != _equal), (((ListMapNode) (_node->entity))->_mapped))) != _false)
		{
			break;
		}
		else
		{
			Object_Release(_node);
			Object _parent;
			_parent = Stack_Peek(_stack);
			Map_RemoveKey((((ListMapNode) (_parent->entity))->_nextMap), ListIterator_ThisData(_iterator));
		}
	}
	Object_Release(_stack);
	return _true;
}

Object ListMap_ObjectAt(Object _self, Object _list)
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

Object ListMap_ListMapAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}

Object ListMap_ListAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}

Object ListMap_QueueAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}

Object ListMap_LogicAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}

Object ListMap_NumberAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}

Object ListMap_SynonimAt(Object _self, Object _list)
{
	return ListMap_ObjectAt(_self, _list);
}
