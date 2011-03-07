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
	((ListMap) (_self->entity))->_underClonning = _nil;
	_self = ListMap_Init(_self);
	DPOPS ("ListMap: Create ended.")
	return _self;
}

Object ListMap_Init(Object _self)
{
	DPUSHS ("ListMap: Init begined.")
	ASSERT_C ( "ListMap:Init --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	(((ListMap) (_self->entity))->_root) = ListMapNode_Create();
	(((ListMap) (_self->entity))->_underClonning) = _no;
	Object toReturn = _self;
	DPOPS ("ListMap: Init ended.")
	return toReturn;
}

Object ListMap_Compare(Object _self, Object _listMap)
{
	DPUSHS ("ListMap: Compare begined.")
	ASSERT_C ( "ListMap:Compare --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:Compare --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	Object toReturn = Object_Compare((((ListMap) (_self->entity))->_root), (((ListMap) (_listMap->entity))->_root));
	DPOPS ("ListMap: Compare ended.")
	return toReturn;
}

Object ListMap_Destroy(Object _self)
{
	DPUSHS ("ListMap: Destroy begined.")
	ASSERT_C ( "ListMap:Destroy --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object_Release((((ListMap) (_self->entity))->_root));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListMap: Destroy ended.")
	return toReturn;
}

Object ListMap_Clone(Object _self)
{
	DPUSHS ("ListMap: Clone begined.")
	ASSERT_C ( "ListMap:Clone --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	if(((((ListMap) (_self->entity))->_underClonning)) != _false)
	{
		ListMap_DumpKeys(_self);
	}
	ASSERT_Q ( "Under clonning check failed.", Logic_Not((((ListMap) (_self->entity))->_underClonning)) )
	(((ListMap) (_self->entity))->_underClonning) = _yes;
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Release((((ListMap) (_toReturn->entity))->_root));
	(((ListMap) (_toReturn->entity))->_root) = Object_Clone((((ListMap) (_self->entity))->_root));
	(((ListMap) (_self->entity))->_underClonning) = _no;
	Object toReturn = _toReturn;
	DPOPS ("ListMap: Clone ended.")
	return toReturn;
}

Object ListMap_DeepClone(Object _self)
{
	DPUSHS ("ListMap: DeepClone begined.")
	ASSERT_C ( "ListMap:DeepClone --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	if(((((ListMap) (_self->entity))->_underClonning)) != _false)
	{
		ListMap_DumpKeys(_self);
	}
	ASSERT_Q ( "Under clonning check failed.", Logic_Not((((ListMap) (_self->entity))->_underClonning)) )
	(((ListMap) (_self->entity))->_underClonning) = _yes;
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Release((((ListMap) (_toReturn->entity))->_root));
	(((ListMap) (_toReturn->entity))->_root) = Object_DeepClone((((ListMap) (_self->entity))->_root));
	(((ListMap) (_self->entity))->_underClonning) = _no;
	Object toReturn = _toReturn;
	DPOPS ("ListMap: DeepClone ended.")
	return toReturn;
}

Object ListMap_Empty(Object _self)
{
	DPUSHS ("ListMap: Empty begined.")
	ASSERT_C ( "ListMap:Empty --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = Logic_And(Logic_Not((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_mapped)), Map_Empty((((ListMapNode) ((((ListMap) (_self->entity))->_root)->entity))->_nextMap)));
	DPOPS ("ListMap: Empty ended.")
	return toReturn;
}

Object ListMap_Add(Object _self, Object _list, Object _object)
{
	DPUSHS ("ListMap: Add begined.")
	ASSERT_C ( "ListMap:Add --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:Add --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
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
	ASSERT_C ( "ListMap:AddListMap --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:AddListMap --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	ListMapNode_MergeRecursiveStrong((((ListMap) (_self->entity))->_root), (((ListMap) (_listMap->entity))->_root));
	Object toReturn = _self;
	DPOPS ("ListMap: AddListMap ended.")
	return toReturn;
}

Object ListMap_Remove(Object _self, Object _list)
{
	DPUSHS ("ListMap: Remove begined.")
	ASSERT_C ( "ListMap:Remove --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:Remove --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	ListMap_RemoveKeyWithConfirmation(_self, _list);
	Object toReturn = _self;
	DPOPS ("ListMap: Remove ended.")
	return toReturn;
}

Object ListMap_RemoveAll(Object _self)
{
	DPUSHS ("ListMap: RemoveAll begined.")
	ASSERT_C ( "ListMap:RemoveAll --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	(((ListMap) (_self->entity))->_root) = ListMapNode_Create();
	Object toReturn = _self;
	DPOPS ("ListMap: RemoveAll ended.")
	return toReturn;
}

Object ListMap_ResetWithListMapDestructive(Object _self, Object _listMap)
{
	DPUSHS ("ListMap: ResetWithListMapDestructive begined.")
	ASSERT_C ( "ListMap:ResetWithListMapDestructive --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ResetWithListMapDestructive --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	(((ListMap) (_self->entity))->_root) = (((ListMap) (_listMap->entity))->_root);
	(((ListMap) (_listMap->entity))->_root) = ListMapNode_Create();
	Object toReturn = _self;
	DPOPS ("ListMap: ResetWithListMapDestructive ended.")
	return toReturn;
}

Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list)
{
	DPUSHS ("ListMap: RemoveKeyWithConfirmation begined.")
	ASSERT_C ( "ListMap:RemoveKeyWithConfirmation --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:RemoveKeyWithConfirmation --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
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
	ASSERT_C ( "ListMap:ObjectAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
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
	ASSERT_C ( "ListMap:Contains --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:Contains --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
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
	ASSERT_C ( "ListMap:ListMapAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ListMapAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: ListMapAt ended.")
	return toReturn;
}

Object ListMap_ListAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: ListAt begined.")
	ASSERT_C ( "ListMap:ListAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ListAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: ListAt ended.")
	return toReturn;
}

Object ListMap_QueueAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: QueueAt begined.")
	ASSERT_C ( "ListMap:QueueAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:QueueAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: QueueAt ended.")
	return toReturn;
}

Object ListMap_LogicAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: LogicAt begined.")
	ASSERT_C ( "ListMap:LogicAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:LogicAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: LogicAt ended.")
	return toReturn;
}

Object ListMap_NumberAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: NumberAt begined.")
	ASSERT_C ( "ListMap:NumberAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:NumberAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: NumberAt ended.")
	return toReturn;
}

Object ListMap_SynonimAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: SynonimAt begined.")
	ASSERT_C ( "ListMap:SynonimAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:SynonimAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: SynonimAt ended.")
	return toReturn;
}

Object ListMap_MethodAt(Object _self, Object _list)
{
	DPUSHS ("ListMap: MethodAt begined.")
	ASSERT_C ( "ListMap:MethodAt --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MethodAt --- Checking for correct parameter type failed at parameter _list.", _list->gid ==  3732711262168886272ull || _list == _nil )
	Object toReturn = ListMap_ObjectAt(_self, _list);
	DPOPS ("ListMap: MethodAt ended.")
	return toReturn;
}

Object ListMap_First(Object _self)
{
	DPUSHS ("ListMap: First begined.")
	ASSERT_C ( "ListMap:First --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
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
	ASSERT_C ( "ListMap:Last --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
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
	ASSERT_C ( "ListMap:DumpKeys --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
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

Object ListMap_DumpListToListMap(Object _self)
{
	DPUSHS ("ListMap: DumpListToListMap begined.")
	ASSERT_C ( "ListMap:DumpListToListMap --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object _iterator;
	_iterator = ListMap_First(_self);
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "\"", 1));
		Console_WriteString(_console, ListMapIterator_ThisKey(_iterator));
		Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "\":\"", 3));
		Console_WriteString(_console, ListMapIterator_ThisValue(_iterator));
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "\"", 1));
		ListMapIterator_Next(_iterator);
	}
	Object toReturn = _self;
	DPOPS ("ListMap: DumpListToListMap ended.")
	return toReturn;
}

Object ListMap_ObjectMethods(Object _self)
{
	DPUSHS ("ListMap: ObjectMethods begined.")
	ASSERT_C ( "ListMap:ObjectMethods --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	DPOPS ("ListMap: ObjectMethods ended.")
	return toReturn;
}

Object ListMap_ObjectFields(Object _self)
{
	DPUSHS ("ListMap: ObjectFields begined.")
	ASSERT_C ( "ListMap:ObjectFields --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Поля", 8));
	DPOPS ("ListMap: ObjectFields ended.")
	return toReturn;
}

Object ListMap_ObjectJobs(Object _self)
{
	DPUSHS ("ListMap: ObjectJobs begined.")
	ASSERT_C ( "ListMap:ObjectJobs --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Работы", 12));
	DPOPS ("ListMap: ObjectJobs ended.")
	return toReturn;
}

Object ListMap_ObjectProperties(Object _self)
{
	DPUSHS ("ListMap: ObjectProperties begined.")
	ASSERT_C ( "ListMap:ObjectProperties --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Свойства", 16));
	DPOPS ("ListMap: ObjectProperties ended.")
	return toReturn;
}

Object ListMap_ObjectField(Object _self, Object _fieldName)
{
	DPUSHS ("ListMap: ObjectField begined.")
	ASSERT_C ( "ListMap:ObjectField --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object toReturn = ListMap_SynonimAt(ListMap_ObjectFields(_self), _fieldName);
	DPOPS ("ListMap: ObjectField ended.")
	return toReturn;
}

Object ListMap_ObjectFieldUID(Object _self, Object _fieldName)
{
	DPUSHS ("ListMap: ObjectFieldUID begined.")
	ASSERT_C ( "ListMap:ObjectFieldUID --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectFieldUID --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object toReturn = Synonim_GetUID(ListMap_ObjectField(_self, _fieldName));
	DPOPS ("ListMap: ObjectFieldUID ended.")
	return toReturn;
}

Object ListMap_ObjectMethod(Object _self, Object _methodName)
{
	DPUSHS ("ListMap: ObjectMethod begined.")
	ASSERT_C ( "ListMap:ObjectMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	Object toReturn = ListMap_ListMapAt(ListMap_ObjectMethods(_self), _methodName);
	DPOPS ("ListMap: ObjectMethod ended.")
	return toReturn;
}

Object ListMap_ObjectRemoveMethod(Object _self, Object _methodName)
{
	DPUSHS ("ListMap: ObjectRemoveMethod begined.")
	ASSERT_C ( "ListMap:ObjectRemoveMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectRemoveMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ListMap_Remove(ListMap_ObjectMethods(_self), _methodName);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectRemoveMethod ended.")
	return toReturn;
}

Object ListMap_ObjectSetMethod(Object _self, Object _method, Object _methodName)
{
	DPUSHS ("ListMap: ObjectSetMethod begined.")
	ASSERT_C ( "ListMap:ObjectSetMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectSetMethod --- Checking for correct parameter type failed at parameter _method.", _method->gid ==  2108332898258556672ull || _method == _nil )
	ASSERT_C ( "ListMap:ObjectSetMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ListMap_Add(ListMap_ObjectMethods(_self), _methodName, _method);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectSetMethod ended.")
	return toReturn;
}

Object ListMap_ObjectSetMethodBody(Object _self, Object _methodBody, Object _methodName)
{
	DPUSHS ("ListMap: ObjectSetMethodBody begined.")
	ASSERT_C ( "ListMap:ObjectSetMethodBody --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectSetMethodBody --- Checking for correct parameter type failed at parameter _methodBody.", _methodBody->gid ==  3732711262168886272ull || _methodBody == _nil )
	ASSERT_C ( "ListMap:ObjectSetMethodBody --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8), _methodBody);
	ListMap_Add(ListMap_ObjectMethods(_self), _methodName, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectSetMethodBody ended.")
	return toReturn;
}

Object ListMap_ObjectSetBasicMethod(Object _self, Object _entity, Object _basicMethod, Object _methodName)
{
	DPUSHS ("ListMap: ObjectSetBasicMethod begined.")
	ASSERT_C ( "ListMap:ObjectSetBasicMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectSetBasicMethod --- Checking for correct parameter type failed at parameter _basicMethod.", _basicMethod->gid == 14849865630305968128ull || _basicMethod == _nil )
	ASSERT_C ( "ListMap:ObjectSetBasicMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _true);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Сущность", 16), _entity);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый метод", 25), _basicMethod);
	ListMap_Add(ListMap_ObjectMethods(_self), _methodName, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectSetBasicMethod ended.")
	return toReturn;
}

Object ListMap_ObjectSetJob(Object _self, Object _job, Object _jobName)
{
	DPUSHS ("ListMap: ObjectSetJob begined.")
	ASSERT_C ( "ListMap:ObjectSetJob --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectSetJob --- Checking for correct parameter type failed at parameter _job.", _job->gid ==  2108332898258556672ull || _job == _nil )
	ASSERT_C ( "ListMap:ObjectSetJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_Add(ListMap_ObjectJobs(_self), _jobName, _job);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectSetJob ended.")
	return toReturn;
}

Object ListMap_ObjectSetProperty(Object _self, Object _propertyName, Object _value)
{
	DPUSHS ("ListMap: ObjectSetProperty begined.")
	ASSERT_C ( "ListMap:ObjectSetProperty --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectSetProperty --- Checking for correct parameter type failed at parameter _propertyName.", _propertyName->gid ==  3732711262168886272ull || _propertyName == _nil )
	ListMap_Add(ListMap_ObjectProperties(_self), _propertyName, _value);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectSetProperty ended.")
	return toReturn;
}

Object ListMap_ObjectRemoveJob(Object _self, Object _jobName)
{
	DPUSHS ("ListMap: ObjectRemoveJob begined.")
	ASSERT_C ( "ListMap:ObjectRemoveJob --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectRemoveJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_Remove(ListMap_ObjectJobs(_self), _jobName);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectRemoveJob ended.")
	return toReturn;
}

Object ListMap_ObjectResetMethodsDestructive(Object _self, Object _newMethods)
{
	DPUSHS ("ListMap: ObjectResetMethodsDestructive begined.")
	ASSERT_C ( "ListMap:ObjectResetMethodsDestructive --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectResetMethodsDestructive --- Checking for correct parameter type failed at parameter _newMethods.", _newMethods->gid ==  2108332898258556672ull || _newMethods == _nil )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Методы", 12), _newMethods);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectResetMethodsDestructive ended.")
	return toReturn;
}

Object ListMap_ObjectResetFieldsDestructive(Object _self, Object _newFields)
{
	DPUSHS ("ListMap: ObjectResetFieldsDestructive begined.")
	ASSERT_C ( "ListMap:ObjectResetFieldsDestructive --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectResetFieldsDestructive --- Checking for correct parameter type failed at parameter _newFields.", _newFields->gid ==  2108332898258556672ull || _newFields == _nil )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Поля", 8), _newFields);
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectResetFieldsDestructive ended.")
	return toReturn;
}

Object ListMap_ObjectRemoveAllIdentifiers(Object _self)
{
	DPUSHS ("ListMap: ObjectRemoveAllIdentifiers begined.")
	ASSERT_C ( "ListMap:ObjectRemoveAllIdentifiers --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	List_Clean(ListMap_ListAt(ListMap_ObjectProperties(_self), StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28)));
	Object toReturn = _self;
	DPOPS ("ListMap: ObjectRemoveAllIdentifiers ended.")
	return toReturn;
}

Object ListMap_ObjectJob(Object _self, Object _jobName)
{
	DPUSHS ("ListMap: ObjectJob begined.")
	ASSERT_C ( "ListMap:ObjectJob --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object toReturn = ListMap_ListMapAt(ListMap_ObjectJobs(_self), _jobName);
	DPOPS ("ListMap: ObjectJob ended.")
	return toReturn;
}

Object ListMap_ObjectProperty(Object _self, Object _propertyName)
{
	DPUSHS ("ListMap: ObjectProperty begined.")
	ASSERT_C ( "ListMap:ObjectProperty --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:ObjectProperty --- Checking for correct parameter type failed at parameter _propertyName.", _propertyName->gid ==  3732711262168886272ull || _propertyName == _nil )
	Object toReturn = ListMap_ObjectAt(ListMap_ObjectProperties(_self), _propertyName);
	DPOPS ("ListMap: ObjectProperty ended.")
	return toReturn;
}

Object ListMap_JobStages(Object _self)
{
	DPUSHS ("ListMap: JobStages begined.")
	ASSERT_C ( "ListMap:JobStages --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Стадии", 12));
	DPOPS ("ListMap: JobStages ended.")
	return toReturn;
}

Object ListMap_JobMessageSlots(Object _self)
{
	DPUSHS ("ListMap: JobMessageSlots begined.")
	ASSERT_C ( "ListMap:JobMessageSlots --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37));
	DPOPS ("ListMap: JobMessageSlots ended.")
	return toReturn;
}

Object ListMap_JobStage(Object _self, Object _stageName)
{
	DPUSHS ("ListMap: JobStage begined.")
	ASSERT_C ( "ListMap:JobStage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	Object toReturn = ListMap_ListMapAt(ListMap_JobStages(_self), _stageName);
	DPOPS ("ListMap: JobStage ended.")
	return toReturn;
}

Object ListMap_JobFieldInMessageSlot(Object _self, Object _fieldName, Object _messageSlotName)
{
	DPUSHS ("ListMap: JobFieldInMessageSlot begined.")
	ASSERT_C ( "ListMap:JobFieldInMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobFieldInMessageSlot --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "ListMap:JobFieldInMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object toReturn = ListMap_ObjectAt(ListMap_JobMessageInMessageSlot(_self, _messageSlotName), _fieldName);
	DPOPS ("ListMap: JobFieldInMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("ListMap: JobMessageSlot begined.")
	ASSERT_C ( "ListMap:JobMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object toReturn = ListMap_ListMapAt(ListMap_JobMessageSlots(_self), _messageSlotName);
	DPOPS ("ListMap: JobMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobMessageInMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("ListMap: JobMessageInMessageSlot begined.")
	ASSERT_C ( "ListMap:JobMessageInMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobMessageInMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object toReturn = ListMap_MessageSlotMessage(ListMap_JobMessageSlot(_self, _messageSlotName));
	DPOPS ("ListMap: JobMessageInMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobSetStage(Object _self, Object _stage, Object _stageName)
{
	DPUSHS ("ListMap: JobSetStage begined.")
	ASSERT_C ( "ListMap:JobSetStage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobSetStage --- Checking for correct parameter type failed at parameter _stage.", _stage->gid ==  2108332898258556672ull || _stage == _nil )
	ASSERT_C ( "ListMap:JobSetStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ListMap_Add(ListMap_JobStages(_self), _stageName, _stage);
	Object toReturn = _self;
	DPOPS ("ListMap: JobSetStage ended.")
	return toReturn;
}

Object ListMap_JobRemoveStage(Object _self, Object _stageName)
{
	DPUSHS ("ListMap: JobRemoveStage begined.")
	ASSERT_C ( "ListMap:JobRemoveStage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobRemoveStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ListMap_Remove(ListMap_JobStages(_self), _stageName);
	Object toReturn = _self;
	DPOPS ("ListMap: JobRemoveStage ended.")
	return toReturn;
}

Object ListMap_JobRemoveStageAndMessageSlots(Object _self, Object _stageName)
{
	DPUSHS ("ListMap: JobRemoveStageAndMessageSlots begined.")
	ASSERT_C ( "ListMap:JobRemoveStageAndMessageSlots --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobRemoveStageAndMessageSlots --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	Object _stage;
	_stage = ListMap_ListMapAt(ListMap_JobStages(_self), _stageName);
	Object _stageMessageSlotsIterator;
	_stageMessageSlotsIterator = ListMap_StageMessageSlotsIterator(_stage);
	while((Logic_Not(ListIterator_ThisEnd(_stageMessageSlotsIterator))) != _false)
	{
		Object _messageSlotName;
		_messageSlotName = ListIterator_ListData(_stageMessageSlotsIterator);
		ListMap_JobRemoveMessageSlot(_self, _messageSlotName);
		ListIterator_Next(_stageMessageSlotsIterator);
	}
	ListMap_Remove(ListMap_JobStages(_self), _stageName);
	Object toReturn = _self;
	DPOPS ("ListMap: JobRemoveStageAndMessageSlots ended.")
	return toReturn;
}

Object ListMap_JobSetMessageSlot(Object _self, Object _messageSlot, Object _messageSlotName)
{
	DPUSHS ("ListMap: JobSetMessageSlot begined.")
	ASSERT_C ( "ListMap:JobSetMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobSetMessageSlot --- Checking for correct parameter type failed at parameter _messageSlot.", _messageSlot->gid ==  2108332898258556672ull || _messageSlot == _nil )
	ASSERT_C ( "ListMap:JobSetMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ListMap_Add(ListMap_JobMessageSlots(_self), _messageSlotName, _messageSlot);
	Object toReturn = _self;
	DPOPS ("ListMap: JobSetMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobRemoveMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("ListMap: JobRemoveMessageSlot begined.")
	ASSERT_C ( "ListMap:JobRemoveMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobRemoveMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ListMap_Remove(ListMap_JobMessageSlots(_self), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ListMap: JobRemoveMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobMessageSlotsIterator(Object _self)
{
	DPUSHS ("ListMap: JobMessageSlotsIterator begined.")
	ASSERT_C ( "ListMap:JobMessageSlotsIterator --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_First(ListMap_JobMessageSlots(_self));
	DPOPS ("ListMap: JobMessageSlotsIterator ended.")
	return toReturn;
}

Object ListMap_JobStagesIterator(Object _self)
{
	DPUSHS ("ListMap: JobStagesIterator begined.")
	ASSERT_C ( "ListMap:JobStagesIterator --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_First(ListMap_JobStages(_self));
	DPOPS ("ListMap: JobStagesIterator ended.")
	return toReturn;
}

Object ListMap_JobRemoveAllStages(Object _self)
{
	DPUSHS ("ListMap: JobRemoveAllStages begined.")
	ASSERT_C ( "ListMap:JobRemoveAllStages --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ListMap_RemoveAll(ListMap_JobStages(_self));
	Object toReturn = _self;
	DPOPS ("ListMap: JobRemoveAllStages ended.")
	return toReturn;
}

Object ListMap_JobRemoveAllMessageSlots(Object _self)
{
	DPUSHS ("ListMap: JobRemoveAllMessageSlots begined.")
	ASSERT_C ( "ListMap:JobRemoveAllMessageSlots --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ListMap_RemoveAll(ListMap_JobMessageSlots(_self));
	Object toReturn = _self;
	DPOPS ("ListMap: JobRemoveAllMessageSlots ended.")
	return toReturn;
}

Object ListMap_JobCreateStageWithNameMethodRequestMessageSlot(Object _self, Object _stageName, Object _methodName, Object _messageSlotName, Object _messageSlotRequestName)
{
	DPUSHS ("ListMap: JobCreateStageWithNameMethodRequestMessageSlot begined.")
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodRequestMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodRequestMessageSlot --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodRequestMessageSlot --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodRequestMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodRequestMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotRequestName.", _messageSlotRequestName->gid ==  3732711262168886272ull || _messageSlotRequestName == _nil )
	Object _stage;
	_stage = ExternalEntitiesFactory_CreateEmptyJobStage(_entitiesFactory);
	ListMap_StageSetMethod(_stage, _methodName);
	ListMap_StageSetMessageSlot(_stage, _messageSlotName);
	ListMap_StageIncrementMessagesCounter(_stage);
	ListMap_JobSetStage(_self, _stage, _stageName);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	ListMap_MessageSlotSetStage(_messageSlot, _stageName);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Тип", 6), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), _messageSlotRequestName));
	ListMap_JobSetMessageSlot(_self, _messageSlot, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ListMap: JobCreateStageWithNameMethodRequestMessageSlot ended.")
	return toReturn;
}

Object ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(Object _self, Object _stageName, Object _methodName, Object _messageSlotName, Object _messageSlot)
{
	DPUSHS ("ListMap: JobCreateStageWithNameMethodMessageSlotNameAndEntity begined.")
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodMessageSlotNameAndEntity --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodMessageSlotNameAndEntity --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodMessageSlotNameAndEntity --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodMessageSlotNameAndEntity --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "ListMap:JobCreateStageWithNameMethodMessageSlotNameAndEntity --- Checking for correct parameter type failed at parameter _messageSlot.", _messageSlot->gid ==  2108332898258556672ull || _messageSlot == _nil )
	Object _stage;
	_stage = ExternalEntitiesFactory_CreateEmptyJobStage(_entitiesFactory);
	ListMap_StageSetMethod(_stage, _methodName);
	ListMap_StageSetMessageSlot(_stage, _messageSlotName);
	ListMap_StageIncrementMessagesCounter(_stage);
	ListMap_MessageSlotSetStage(_messageSlot, _stageName);
	ListMap_JobSetStage(_self, _stage, _stageName);
	ListMap_JobSetMessageSlot(_self, _messageSlot, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ListMap: JobCreateStageWithNameMethodMessageSlotNameAndEntity ended.")
	return toReturn;
}

Object ListMap_MessageSender(Object _self)
{
	DPUSHS ("ListMap: MessageSender begined.")
	ASSERT_C ( "ListMap:MessageSender --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22));
	DPOPS ("ListMap: MessageSender ended.")
	return toReturn;
}

Object ListMap_MessageReceiver(Object _self)
{
	DPUSHS ("ListMap: MessageReceiver begined.")
	ASSERT_C ( "ListMap:MessageReceiver --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Получатель", 20));
	DPOPS ("ListMap: MessageReceiver ended.")
	return toReturn;
}

Object ListMap_MessageType(Object _self)
{
	DPUSHS ("ListMap: MessageType begined.")
	ASSERT_C ( "ListMap:MessageType --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Тип", 6));
	DPOPS ("ListMap: MessageType ended.")
	return toReturn;
}

Object ListMap_MessageRequest(Object _self)
{
	DPUSHS ("ListMap: MessageRequest begined.")
	ASSERT_C ( "ListMap:MessageRequest --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Запрос", 12));
	DPOPS ("ListMap: MessageRequest ended.")
	return toReturn;
}

Object ListMap_MessageReply(Object _self)
{
	DPUSHS ("ListMap: MessageReply begined.")
	ASSERT_C ( "ListMap:MessageReply --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10));
	DPOPS ("ListMap: MessageReply ended.")
	return toReturn;
}

Object ListMap_MessageSetSender(Object _self, Object _sender)
{
	DPUSHS ("ListMap: MessageSetSender begined.")
	ASSERT_C ( "ListMap:MessageSetSender --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetSender --- Checking for correct parameter type failed at parameter _sender.", _sender->gid ==  3732711262168886272ull || _sender == _nil )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _sender);
	DPOPS ("ListMap: MessageSetSender ended.")
	return toReturn;
}

Object ListMap_MessageSetReceiver(Object _self, Object _receiver)
{
	DPUSHS ("ListMap: MessageSetReceiver begined.")
	ASSERT_C ( "ListMap:MessageSetReceiver --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetReceiver --- Checking for correct parameter type failed at parameter _receiver.", _receiver->gid ==  3732711262168886272ull || _receiver == _nil )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Получатель", 20), _receiver);
	DPOPS ("ListMap: MessageSetReceiver ended.")
	return toReturn;
}

Object ListMap_MessageSetType(Object _self, Object _type)
{
	DPUSHS ("ListMap: MessageSetType begined.")
	ASSERT_C ( "ListMap:MessageSetType --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetType --- Checking for correct parameter type failed at parameter _type.", _type->gid ==  3732711262168886272ull || _type == _nil )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Тип", 6), _type);
	DPOPS ("ListMap: MessageSetType ended.")
	return toReturn;
}

Object ListMap_MessageSetTypeReply(Object _self)
{
	DPUSHS ("ListMap: MessageSetTypeReply begined.")
	ASSERT_C ( "ListMap:MessageSetTypeReply --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_MessageSetType(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10));
	DPOPS ("ListMap: MessageSetTypeReply ended.")
	return toReturn;
}

Object ListMap_MessageSetTypeRequest(Object _self)
{
	DPUSHS ("ListMap: MessageSetTypeRequest begined.")
	ASSERT_C ( "ListMap:MessageSetTypeRequest --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_MessageSetType(_self, StringFactory_FromUTF8(_stringFactory, "Запрос", 12));
	DPOPS ("ListMap: MessageSetTypeRequest ended.")
	return toReturn;
}

Object ListMap_MessageSetRequest(Object _self, Object _reqest)
{
	DPUSHS ("ListMap: MessageSetRequest begined.")
	ASSERT_C ( "ListMap:MessageSetRequest --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetRequest --- Checking for correct parameter type failed at parameter _reqest.", _reqest->gid ==  3732711262168886272ull || _reqest == _nil )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), _reqest);
	DPOPS ("ListMap: MessageSetRequest ended.")
	return toReturn;
}

Object ListMap_MessageSetReply(Object _self, Object _reply)
{
	DPUSHS ("ListMap: MessageSetReply begined.")
	ASSERT_C ( "ListMap:MessageSetReply --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetReply --- Checking for correct parameter type failed at parameter _reply.", _reply->gid ==  3732711262168886272ull || _reply == _nil )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _reply);
	DPOPS ("ListMap: MessageSetReply ended.")
	return toReturn;
}

Object ListMap_MessageSetReplySuccess(Object _self)
{
	DPUSHS ("ListMap: MessageSetReplySuccess begined.")
	ASSERT_C ( "ListMap:MessageSetReplySuccess --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_MessageSetReply(_self, StringFactory_FromUTF8(_stringFactory, "Успех", 10));
	DPOPS ("ListMap: MessageSetReplySuccess ended.")
	return toReturn;
}

Object ListMap_MessageSetReplyFail(Object _self)
{
	DPUSHS ("ListMap: MessageSetReplyFail begined.")
	ASSERT_C ( "ListMap:MessageSetReplyFail --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_MessageSetReply(_self, StringFactory_FromUTF8(_stringFactory, "Неудача", 14));
	DPOPS ("ListMap: MessageSetReplyFail ended.")
	return toReturn;
}

Object ListMap_MessageSetJobNameAndMessageSlotName(Object _self, Object _jobName, Object _messageSlotName)
{
	DPUSHS ("ListMap: MessageSetJobNameAndMessageSlotName begined.")
	ASSERT_C ( "ListMap:MessageSetJobNameAndMessageSlotName --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSetJobNameAndMessageSlotName --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ASSERT_C ( "ListMap:MessageSetJobNameAndMessageSlotName --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object _listmap;
	_listmap = ExternalEntitiesFactory_CreateEmptyListMap(_entitiesFactory);
	ListMap_Add(_listmap, StringFactory_FromUTF8(_stringFactory, "Работа", 12), _jobName);
	ListMap_Add(_listmap, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение", 37), _messageSlotName);
	List_PushBack(ListMap_ListAt(ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Атрибуты", 16)), StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)), _listmap);
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSetJobNameAndMessageSlotName ended.")
	return toReturn;
}

Object ListMap_MessageAttributesMessageSlots(Object _self)
{
	DPUSHS ("ListMap: MessageAttributesMessageSlots begined.")
	ASSERT_C ( "ListMap:MessageAttributesMessageSlots --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(ListMap_ListMapAt(_self, StringFactory_FromUTF8(_stringFactory, "Атрибуты", 16)), StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37));
	DPOPS ("ListMap: MessageAttributesMessageSlots ended.")
	return toReturn;
}

Object ListMap_MessageSlotStages(Object _self)
{
	DPUSHS ("ListMap: MessageSlotStages begined.")
	ASSERT_C ( "ListMap:MessageSlotStages --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Стадии", 12));
	DPOPS ("ListMap: MessageSlotStages ended.")
	return toReturn;
}

Object ListMap_MessageSlotStagesIterator(Object _self)
{
	DPUSHS ("ListMap: MessageSlotStagesIterator begined.")
	ASSERT_C ( "ListMap:MessageSlotStagesIterator --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = List_First(ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Стадии", 12)));
	DPOPS ("ListMap: MessageSlotStagesIterator ended.")
	return toReturn;
}

Object ListMap_MessageSlotMessage(Object _self)
{
	DPUSHS ("ListMap: MessageSlotMessage begined.")
	ASSERT_C ( "ListMap:MessageSlotMessage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = List_PeekFront(ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18)));
	DPOPS ("ListMap: MessageSlotMessage ended.")
	return toReturn;
}

Object ListMap_MessageSlotSetMessage(Object _self, Object _message)
{
	DPUSHS ("ListMap: MessageSlotSetMessage begined.")
	ASSERT_C ( "ListMap:MessageSlotSetMessage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSlotSetMessage --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _list;
	_list = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18));
	List_PushBack(_list, _message);
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotSetMessage ended.")
	return toReturn;
}

Object ListMap_MessageSlotRemoveMessage(Object _self, Object _message)
{
	DPUSHS ("ListMap: MessageSlotRemoveMessage begined.")
	ASSERT_C ( "ListMap:MessageSlotRemoveMessage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSlotRemoveMessage --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _list;
	_list = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_message, _nil) == _equal)) != _false)
	{
		List_RemoveFront(_list);
	}
	else
	{
		List_RemoveFirstExactlySame(_list, _message);
	}
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotRemoveMessage ended.")
	return toReturn;
}

Object ListMap_MessageSlotRemoveAllMessages(Object _self)
{
	DPUSHS ("ListMap: MessageSlotRemoveAllMessages begined.")
	ASSERT_C ( "ListMap:MessageSlotRemoveAllMessages --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object _list;
	_list = List_Create();
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), _list);
	Object_Release(_list);
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotRemoveAllMessages ended.")
	return toReturn;
}

Object ListMap_MessageSlotField(Object _self, Object _fieldName)
{
	DPUSHS ("ListMap: MessageSlotField begined.")
	ASSERT_C ( "ListMap:MessageSlotField --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSlotField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object toReturn = ListMap_ObjectAt(ListMap_MessageSlotMessage(_self), _fieldName);
	DPOPS ("ListMap: MessageSlotField ended.")
	return toReturn;
}

Object ListMap_MessageSlotSetStage(Object _self, Object _stageName)
{
	DPUSHS ("ListMap: MessageSlotSetStage begined.")
	ASSERT_C ( "ListMap:MessageSlotSetStage --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSlotSetStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	List_PushBackIfAbsent(ListMap_MessageSlotStages(_self), _stageName);
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotSetStage ended.")
	return toReturn;
}

Object ListMap_MessageSlotConditions(Object _self)
{
	DPUSHS ("ListMap: MessageSlotConditions begined.")
	ASSERT_C ( "ListMap:MessageSlotConditions --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Метод идентификации", 37));
	DPOPS ("ListMap: MessageSlotConditions ended.")
	return toReturn;
}

Object ListMap_MessageSlotSetCondition(Object _self, Object _condition)
{
	DPUSHS ("ListMap: MessageSlotSetCondition begined.")
	ASSERT_C ( "ListMap:MessageSlotSetCondition --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:MessageSlotSetCondition --- Checking for correct parameter type failed at parameter _condition.", _condition->gid ==  2108332898258556672ull || _condition == _nil )
	List_PushBack(ListMap_MessageSlotConditions(_self), _condition);
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotSetCondition ended.")
	return toReturn;
}

Object ListMap_MessageSlotIsBlocked(Object _self)
{
	DPUSHS ("ListMap: MessageSlotIsBlocked begined.")
	ASSERT_C ( "ListMap:MessageSlotIsBlocked --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Заблокировано", 26)) == _equal);
	DPOPS ("ListMap: MessageSlotIsBlocked ended.")
	return toReturn;
}

Object ListMap_MessageSlotIsClosed(Object _self)
{
	DPUSHS ("ListMap: MessageSlotIsClosed begined.")
	ASSERT_C ( "ListMap:MessageSlotIsClosed --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Закрыто", 14)) == _equal);
	DPOPS ("ListMap: MessageSlotIsClosed ended.")
	return toReturn;
}

Object ListMap_MessageSlotIsOpened(Object _self)
{
	DPUSHS ("ListMap: MessageSlotIsOpened begined.")
	ASSERT_C ( "ListMap:MessageSlotIsOpened --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Открыто", 14)) == _equal);
	DPOPS ("ListMap: MessageSlotIsOpened ended.")
	return toReturn;
}

Object ListMap_MessageSlotBlock(Object _self)
{
	DPUSHS ("ListMap: MessageSlotBlock begined.")
	ASSERT_C ( "ListMap:MessageSlotBlock --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Заблокировано", 26));
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotBlock ended.")
	return toReturn;
}

Object ListMap_MessageSlotOpen(Object _self)
{
	DPUSHS ("ListMap: MessageSlotOpen begined.")
	ASSERT_C ( "ListMap:MessageSlotOpen --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Открыто", 14));
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotOpen ended.")
	return toReturn;
}

Object ListMap_MessageSlotClose(Object _self)
{
	DPUSHS ("ListMap: MessageSlotClose begined.")
	ASSERT_C ( "ListMap:MessageSlotClose --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Закрыто", 14));
	Object toReturn = _self;
	DPOPS ("ListMap: MessageSlotClose ended.")
	return toReturn;
}

Object ListMap_StageContainsMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("ListMap: StageContainsMessageSlot begined.")
	ASSERT_C ( "ListMap:StageContainsMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:StageContainsMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object toReturn = List_Contains(ListMap_StageMessageSlots(_self), _messageSlotName);
	DPOPS ("ListMap: StageContainsMessageSlot ended.")
	return toReturn;
}

Object ListMap_StageSetMethod(Object _self, Object _methodName)
{
	DPUSHS ("ListMap: StageSetMethod begined.")
	ASSERT_C ( "ListMap:StageSetMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:StageSetMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _methodName);
	Object toReturn = _self;
	DPOPS ("ListMap: StageSetMethod ended.")
	return toReturn;
}

Object ListMap_StageSetMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("ListMap: StageSetMessageSlot begined.")
	ASSERT_C ( "ListMap:StageSetMessageSlot --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:StageSetMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	List_PushBackIfAbsent(ListMap_StageMessageSlots(_self), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ListMap: StageSetMessageSlot ended.")
	return toReturn;
}

Object ListMap_StageMessageSlots(Object _self)
{
	DPUSHS ("ListMap: StageMessageSlots begined.")
	ASSERT_C ( "ListMap:StageMessageSlots --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37));
	DPOPS ("ListMap: StageMessageSlots ended.")
	return toReturn;
}

Object ListMap_StageMessageSlotsIterator(Object _self)
{
	DPUSHS ("ListMap: StageMessageSlotsIterator begined.")
	ASSERT_C ( "ListMap:StageMessageSlotsIterator --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = List_First(ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)));
	DPOPS ("ListMap: StageMessageSlotsIterator ended.")
	return toReturn;
}

Object ListMap_StageMethod(Object _self)
{
	DPUSHS ("ListMap: StageMethod begined.")
	ASSERT_C ( "ListMap:StageMethod --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_ListAt(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10));
	DPOPS ("ListMap: StageMethod ended.")
	return toReturn;
}

Object ListMap_StageIncrementMessagesCounter(Object _self)
{
	DPUSHS ("ListMap: StageIncrementMessagesCounter begined.")
	ASSERT_C ( "ListMap:StageIncrementMessagesCounter --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Number_Inc(ListMap_NumberAt(_self, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39)));
	Object toReturn = _self;
	DPOPS ("ListMap: StageIncrementMessagesCounter ended.")
	return toReturn;
}

Object ListMap_StageDecrementMessagesCounter(Object _self)
{
	DPUSHS ("ListMap: StageDecrementMessagesCounter begined.")
	ASSERT_C ( "ListMap:StageDecrementMessagesCounter --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Number_Dec(ListMap_NumberAt(_self, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39)));
	Object toReturn = _self;
	DPOPS ("ListMap: StageDecrementMessagesCounter ended.")
	return toReturn;
}

Object ListMap_StageMessagesCounter(Object _self)
{
	DPUSHS ("ListMap: StageMessagesCounter begined.")
	ASSERT_C ( "ListMap:StageMessagesCounter --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_NumberAt(_self, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39));
	DPOPS ("ListMap: StageMessagesCounter ended.")
	return toReturn;
}

Object ListMap_StageSetMessagesCounter(Object _self, Object _newMessagesCounter)
{
	DPUSHS ("ListMap: StageSetMessagesCounter begined.")
	ASSERT_C ( "ListMap:StageSetMessagesCounter --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	ASSERT_C ( "ListMap:StageSetMessagesCounter --- Checking for correct parameter type failed at parameter _newMessagesCounter.", _newMessagesCounter->gid == 15425740279749906432ull || _newMessagesCounter == _nil )
	ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39), _newMessagesCounter);
	Object toReturn = _self;
	DPOPS ("ListMap: StageSetMessagesCounter ended.")
	return toReturn;
}

Object ListMap_StageSetBlocked(Object _self)
{
	DPUSHS ("ListMap: StageSetBlocked begined.")
	ASSERT_C ( "ListMap:StageSetBlocked --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Заблокировано", 26));
	DPOPS ("ListMap: StageSetBlocked ended.")
	return toReturn;
}

Object ListMap_StageSetReady(Object _self)
{
	DPUSHS ("ListMap: StageSetReady begined.")
	ASSERT_C ( "ListMap:StageSetReady --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Готово", 12));
	DPOPS ("ListMap: StageSetReady ended.")
	return toReturn;
}

Object ListMap_StageSetWaiting(Object _self)
{
	DPUSHS ("ListMap: StageSetWaiting begined.")
	ASSERT_C ( "ListMap:StageSetWaiting --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = ListMap_Add(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Ожидание", 16));
	DPOPS ("ListMap: StageSetWaiting ended.")
	return toReturn;
}

Object ListMap_StageIsWaiting(Object _self)
{
	DPUSHS ("ListMap: StageIsWaiting begined.")
	ASSERT_C ( "ListMap:StageIsWaiting --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Ожидание", 16)) == _equal);
	DPOPS ("ListMap: StageIsWaiting ended.")
	return toReturn;
}

Object ListMap_StageIsReady(Object _self)
{
	DPUSHS ("ListMap: StageIsReady begined.")
	ASSERT_C ( "ListMap:StageIsReady --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Готово", 12)) == _equal);
	DPOPS ("ListMap: StageIsReady ended.")
	return toReturn;
}

Object ListMap_StageIsBlocked(Object _self)
{
	DPUSHS ("ListMap: StageIsBlocked begined.")
	ASSERT_C ( "ListMap:StageIsBlocked --- Checking for correct object type failed.", _self->gid ==  2108332898258556672ull )
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_self, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Заблокировано", 26)) == _equal);
	DPOPS ("ListMap: StageIsBlocked ended.")
	return toReturn;
}
