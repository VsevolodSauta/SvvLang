#include "internals/basics.h"
#include "internals/ListMap/imports.h"


Object ListMap_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListMap: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListMap));
	_self->gid =  2108332898258556672ull;
	Object_SetComparator(_self, &ListMap_Compare);
	Object_SetDestructor(_self, &ListMap_Destroy);
	Object_SetCloner(_self, &ListMap_Clone);
	Object_SetDeepCloner(_self, &ListMap_DeepClone);
	((ListMap) (_self->entity))->_root = _nil;
	_self = ListMap_Init(_self);
	DPOPS ("ListMap: Create ended.")
	return _self;
}

Object ListMap_Init(Object _self)
{
	DPUSHS ("ListMap: Init begined.")
	(((ListMap) (_self->entity))->_root) = ListMapNode_Create();
	Object toReturn = _self;
	DPOPS ("ListMap: Init ended.")
	return toReturn;
}

Object ListMap_Compare(Object _self, Object _listSet)
{
	DPUSHS ("ListMap: Compare begined.")
	Object toReturn = Object_Compare((((ListMap) (_self->entity))->_root), (((ListMap) (_listSet->entity))->_root));
	DPOPS ("ListMap: Compare ended.")
	return toReturn;
}

Object ListMap_Destroy(Object _self)
{
	DPUSHS ("ListMap: Destroy begined.")
	Object_Release((((ListMap) (_self->entity))->_root));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListMap: Destroy ended.")
	return toReturn;
}

Object ListMap_Clone(Object _self)
{
	DPUSHS ("ListMap: Clone begined.")
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Release((((ListMap) (_toReturn->entity))->_root));
	(((ListMap) (_toReturn->entity))->_root) = Object_Clone((((ListMap) (_self->entity))->_root));
	Object toReturn = _toReturn;
	DPOPS ("ListMap: Clone ended.")
	return toReturn;
}

Object ListMap_DeepClone(Object _self)
{
	DPUSHS ("ListMap: DeepClone begined.")
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Release((((ListMap) (_toReturn->entity))->_root));
	(((ListMap) (_toReturn->entity))->_root) = Object_DeepClone((((ListMap) (_self->entity))->_root));
	Object toReturn = _toReturn;
	DPOPS ("ListMap: DeepClone ended.")
	return toReturn;
}

Object ListMap_Empty(Object _self)
{
	DPUSHS ("ListMap: Empty begined.")
	Object toReturn = Logic_And(Logic_Not((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_mapped)), Map_Empty((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_nextMap)));
	DPOPS ("ListMap: Empty ended.")
	return toReturn;
}

Object ListMap_Add(Object _self, Object _list, Object _object)
{
	DPUSHS ("ListMap: Add begined.")
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
	Object toReturn = _self;
	DPOPS ("ListMap: Add ended.")
	return toReturn;
}

Object ListMap_AddListMap(Object _self, Object _listMap)
{
	DPUSHS ("ListMap: AddListMap begined.")
	ListMapNode_MergeRecursiveStrong((((ListMap) (_self->entity))->_root), (((ListMap) (_listMap->entity))->_root));
	Object toReturn = _self;
	DPOPS ("ListMap: AddListMap ended.")
	return toReturn;
}

Object ListMap_Remove(Object _self, Object _list)
{
	DPUSHS ("ListMap: Remove begined.")
	ListMap_RemoveKeyWithConfirmation(_self, _list);
	Object toReturn = _self;
	DPOPS ("ListMap: Remove ended.")
	return toReturn;
}

Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list)
{
	DPUSHS ("ListMap: RemoveKeyWithConfirmation begined.")
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
			Object toReturn = _false;
			DPOPS ("ListMap: RemoveKeyWithConfirmation ended.")
			return toReturn;
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
	Object toReturn = _true;
	DPOPS ("ListMap: RemoveKeyWithConfirmation ended.")
	return toReturn;
}

Object ListMap_ObjectAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: ObjectAt begined.")
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
			Object toReturn = _nil;
			DPOPS ("ListMap: ObjectAt ended.")
			return toReturn;
		}
		ListIterator_Next(_iterator);
	}
	if(((((ListMapNode) (_node->entity))->_mapped)) != _false)
	{
		Object toReturn = (((ListMapNode) (_node->entity))->_mapping);
		DPOPS ("ListMap: ObjectAt ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = _nil;
		DPOPS ("ListMap: ObjectAt ended.")
		return toReturn;
	}
}

Object ListMap_Contains(Object _self, Object _list)
{
	DPUSHS ("ListMap: Contains begined.")
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
			Object toReturn = _false;
			DPOPS ("ListMap: Contains ended.")
			return toReturn;
		}
		ListIterator_Next(_iterator);
	}
	Object toReturn = (((ListMapNode) (_node->entity))->_mapped);
	DPOPS ("ListMap: Contains ended.")
	return toReturn;
}

Object ListMap_ListMapAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: ListMapAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: ListMapAt ended.")
	return toReturn;
}

Object ListMap_ListAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: ListAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: ListAt ended.")
	return toReturn;
}

Object ListMap_QueueAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: QueueAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: QueueAt ended.")
	return toReturn;
}

Object ListMap_LogicAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: LogicAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: LogicAt ended.")
	return toReturn;
}

Object ListMap_NumberAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: NumberAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: NumberAt ended.")
	return toReturn;
}

Object ListMap_SynonimAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: SynonimAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: SynonimAt ended.")
	return toReturn;
}

Object ListMap_MethodAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: MethodAt begined.")
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: MethodAt ended.")
	return toReturn;
}

Object ListMap_First(Object _self)
{
	DPUSHS ("ListMap: First begined.")
	Object _iterator;
	_iterator = ListMapIterator_Create();
	ListMapIterator_SetListMap(_iterator, _self);
	ListMapIterator_ToBegin(_iterator);
	Object toReturn = Object_Autorelease(_iterator);
	DPOPS ("ListMap: First ended.")
	return toReturn;
}

Object ListMap_Last(Object _self)
{
	DPUSHS ("ListMap: Last begined.")
	Object _iterator;
	_iterator = ListMapIterator_Create();
	ListMapIterator_SetListMap(_iterator, _self);
	ListMapIterator_ToEnd(_iterator);
	Object toReturn = Object_Autorelease(_iterator);
	DPOPS ("ListMap: Last ended.")
	return toReturn;
}

Object ListMap_DumpKeys(Object _self)
{
	DPUSHS ("ListMap: DumpKeys begined.")
	Object _iterator;
	_iterator = ListMap_First(_self);
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		Console_WriteLnString(_console, ListMapIterator_ThisKey(_iterator));
		ListMapIterator_Next(_iterator);
	}
	Object toReturn = _self;
	DPOPS ("ListMap: DumpKeys ended.")
	return toReturn;
}
