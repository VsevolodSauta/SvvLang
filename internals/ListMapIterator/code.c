#include "internals/basics.h"
#include "internals/ListMapIterator/imports.h"


Object ListMapIterator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListMapIterator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListMapIterator));
	_self->gid =  3251886107095273472ull;
	Object_SetComparator(_self, &ListMapIterator_Compare);
	Object_SetDestructor(_self, &ListMapIterator_Destroy);
	Object_SetCloner(_self, &ListMapIterator_Clone);
	Object_SetDeepCloner(_self, &ListMapIterator_DeepClone);
	((ListMapIterator) (_self->entity))->_listMap = _nil;
	((ListMapIterator) (_self->entity))->_key = _nil;
	((ListMapIterator) (_self->entity))->_elementStack = _nil;
	((ListMapIterator) (_self->entity))->_thisEnd = _nil;
	((ListMapIterator) (_self->entity))->_thisBegin = _nil;
	_self = ListMapIterator_Init(_self);
	DPOPS ("ListMapIterator: Create ended.")
	return _self;
}

Object ListMapIterator_Init(Object _self)
{
	DPUSHS ("ListMapIterator: Init begined.")
	ASSERT_C ( "ListMapIterator:Init --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	(((ListMapIterator) (_self->entity))->_elementStack) = Stack_Create();
	Object_SetReleasing(&(((ListMapIterator) (_self->entity))->_key), List_Create());
	Object toReturn = _self;
	DPOPS ("ListMapIterator: Init ended.")
	return toReturn;
}

Object ListMapIterator_SetListMap(Object _self, Object _listMap)
{
	DPUSHS ("ListMapIterator: SetListMap begined.")
	ASSERT_C ( "ListMapIterator:SetListMap --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_C ( "ListMapIterator:SetListMap --- Checking for correct parameter type failed at parameter _listMap.", _listMap->gid ==  2108332898258556672ull || _listMap == _nil )
	Object_SetRetaining(&(((ListMapIterator) (_self->entity))->_listMap), _listMap);
	Object toReturn = _self;
	DPOPS ("ListMapIterator: SetListMap ended.")
	return toReturn;
}

Object ListMapIterator_ToBegin(Object _self)
{
	DPUSHS ("ListMapIterator: ToBegin begined.")
	ASSERT_C ( "ListMapIterator:ToBegin --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	List_Clean((((ListMapIterator) (_self->entity))->_key));
	(((ListMapIterator) (_self->entity))->_thisEnd) = _no;
	(((ListMapIterator) (_self->entity))->_thisBegin) = _no;
	Object _element;
	_element = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_element->entity))->_node), (((ListMap) ((((ListMapIterator) (_self->entity))->_listMap)->entity))->_root));
	Object_SetRetaining(&(((ListMapIteratorElement) (_element->entity))->_iterator), MapIterator_Prev(Map_First((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_nextMap))));
	(((ListMapIteratorElement) (_element->entity))->_nextExists) = ListMapIterator_MoreThanOneElementInNode(_self, (((ListMapIteratorElement) (_element->entity))->_node));
	(((ListMapIteratorElement) (_element->entity))->_prevExists) = _no;
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
	Object_Release(_element);
	if(((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapped)) != _false)
	{
		Object toReturn = _self;
		DPOPS ("ListMapIterator: ToBegin ended.")
		return toReturn;
	}
	if((Map_Empty((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_nextMap))) != _false)
	{
		(((ListMapIterator) (_self->entity))->_thisBegin) = _yes;
		(((ListMapIterator) (_self->entity))->_thisEnd) = _yes;
		Object toReturn = _self;
		DPOPS ("ListMapIterator: ToBegin ended.")
		return toReturn;
	}
	while((Logic_Not((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapped))) != _false)
	{
		_element = ListMapIterator_NextAnyWithElement(_self, _element);
	}
	Object toReturn = _self;
	DPOPS ("ListMapIterator: ToBegin ended.")
	return toReturn;
}

Object ListMapIterator_MoreThanOneElementInNode(Object _self, Object _node)
{
	DPUSHS ("ListMapIterator: MoreThanOneElementInNode begined.")
	ASSERT_C ( "ListMapIterator:MoreThanOneElementInNode --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_C ( "ListMapIterator:MoreThanOneElementInNode --- Checking for correct parameter type failed at parameter _node.", _node->gid ==  5883107801261346816ull || _node == _nil )
	if((Logic_And((((ListMapNode) (_node->entity))->_mapped), Logic_Not(Map_Empty((((ListMapNode) (_node->entity))->_nextMap))))) != _false)
	{
		Object toReturn = _true;
		DPOPS ("ListMapIterator: MoreThanOneElementInNode ended.")
		return toReturn;
	}
	Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(Map_Size((((ListMapNode) (_node->entity))->_nextMap)), NumberFactory_FromLong(_numberFactory, 1)) == _greater);
	DPOPS ("ListMapIterator: MoreThanOneElementInNode ended.")
	return toReturn;
}

Object ListMapIterator_Next(Object _self)
{
	DPUSHS ("ListMapIterator: Next begined.")
	ASSERT_C ( "ListMapIterator:Next --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	if(((((ListMapIterator) (_self->entity))->_thisBegin)) != _false)
	{
		if((Logic_Not((((ListMapIterator) (_self->entity))->_thisEnd))) != _false)
		{
			(((ListMapIterator) (_self->entity))->_thisBegin) = _no;
		}
		Object toReturn = _self;
		DPOPS ("ListMapIterator: Next ended.")
		return toReturn;
	}
	Object _element;
	_element = Stack_Pop((((ListMapIterator) (_self->entity))->_elementStack));
	if((Logic_Not((((ListMapIteratorElement) (_element->entity))->_nextExists))) != _false)
	{
		Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
		(((ListMapIterator) (_self->entity))->_thisEnd) = _yes;
		Object toReturn = _self;
		DPOPS ("ListMapIterator: Next ended.")
		return toReturn;
	}
	while((MapIterator_NextEnd((((ListMapIteratorElement) (_element->entity))->_iterator))) != _false)
	{
		_element = Stack_Pop((((ListMapIterator) (_self->entity))->_elementStack));
		List_RemoveBack((((ListMapIterator) (_self->entity))->_key));
	}
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
	_element = ListMapIterator_NextAnyWithElement(_self, _element);
	while((Logic_Not((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapped))) != _false)
	{
		_element = ListMapIterator_NextAnyWithElement(_self, _element);
	}
	Object toReturn = _self;
	DPOPS ("ListMapIterator: Next ended.")
	return toReturn;
}

Object ListMapIterator_NextAnyWithElement(Object _self, Object _element)
{
	DPUSHS ("ListMapIterator: NextAnyWithElement begined.")
	ASSERT_C ( "ListMapIterator:NextAnyWithElement --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_C ( "ListMapIterator:NextAnyWithElement --- Checking for correct parameter type failed at parameter _element.", _element->gid ==  5141019124093965312ull || _element == _nil )
	Object _nextElement;
	_nextElement = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_nextElement->entity))->_node), ListMapIteratorElement_AdvancingValue(_element, Stack_ObjectAtPositionIfExists((((ListMapIterator) (_self->entity))->_elementStack), NumberFactory_FromLong(_numberFactory, 1))));
	Object_SetRetaining(&(((ListMapIteratorElement) (_nextElement->entity))->_iterator), MapIterator_Prev(Map_First((((ListMapNode) ((((ListMapIteratorElement) (_nextElement->entity))->_node)->entity))->_nextMap))));
	(((ListMapIteratorElement) (_nextElement->entity))->_nextExists) = Logic_Or((((ListMapIteratorElement) (_element->entity))->_nextExists), ListMapIterator_MoreThanOneElementInNode(_self, (((ListMapIteratorElement) (_nextElement->entity))->_node)));
	(((ListMapIteratorElement) (_nextElement->entity))->_prevExists) = (((ListMapIteratorElement) (_element->entity))->_prevExists);
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _nextElement);
	Object_Release(_nextElement);
	List_PushBack((((ListMapIterator) (_self->entity))->_key), MapIterator_ThisKey((((ListMapIteratorElement) (_element->entity))->_iterator)));
	Object toReturn = _nextElement;
	DPOPS ("ListMapIterator: NextAnyWithElement ended.")
	return toReturn;
}

Object ListMapIterator_ThisRemoveRight(Object _self)
{
	DPUSHS ("ListMapIterator: ThisRemoveRight begined.")
	ASSERT_C ( "ListMapIterator:ThisRemoveRight --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_Q ( "", LogicFactory_FromLong(_logicFactory, Object_Compare((((ListMapIterator) (_self->entity))->_thisEnd), _true) != _equal) )
	ASSERT_Q ( "", LogicFactory_FromLong(_logicFactory, Object_Compare((((ListMapIterator) (_self->entity))->_thisBegin), _true) != _equal) )
	Object _key;
	_key = (((ListMapIterator) (_self->entity))->_key);
	ListMapIterator_Next(_self);
	ListMap_Remove((((ListMapIterator) (_self->entity))->_listMap), _key);
	Object toReturn = _self;
	DPOPS ("ListMapIterator: ThisRemoveRight ended.")
	return toReturn;
}

Object ListMapIterator_ThisRemoveLeft(Object _self)
{
	DPUSHS ("ListMapIterator: ThisRemoveLeft begined.")
	ASSERT_C ( "ListMapIterator:ThisRemoveLeft --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_Q ( "", LogicFactory_FromLong(_logicFactory, Object_Compare((((ListMapIterator) (_self->entity))->_thisEnd), _true) != _equal) )
	ASSERT_Q ( "", LogicFactory_FromLong(_logicFactory, Object_Compare((((ListMapIterator) (_self->entity))->_thisBegin), _true) != _equal) )
	Object _key;
	_key = (((ListMapIterator) (_self->entity))->_key);
	ListMapIterator_Prev(_self);
	ListMap_Remove((((ListMapIterator) (_self->entity))->_listMap), _key);
	Object toReturn = _self;
	DPOPS ("ListMapIterator: ThisRemoveLeft ended.")
	return toReturn;
}

Object ListMapIterator_ThisKey(Object _self)
{
	DPUSHS ("ListMapIterator: ThisKey begined.")
	ASSERT_C ( "ListMapIterator:ThisKey --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = Object_TempClone((((ListMapIterator) (_self->entity))->_key));
	DPOPS ("ListMapIterator: ThisKey ended.")
	return toReturn;
}

Object ListMapIterator_ThisValue(Object _self)
{
	DPUSHS ("ListMapIterator: ThisValue begined.")
	ASSERT_C ( "ListMapIterator:ThisValue --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object _element;
	_element = Stack_Peek((((ListMapIterator) (_self->entity))->_elementStack));
	Object toReturn = (((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapping);
	DPOPS ("ListMapIterator: ThisValue ended.")
	return toReturn;
}

Object ListMapIterator_ListMapData(Object _self)
{
	DPUSHS ("ListMapIterator: ListMapData begined.")
	ASSERT_C ( "ListMapIterator:ListMapData --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = ListMapIterator_ThisValue(_self);
	DPOPS ("ListMapIterator: ListMapData ended.")
	return toReturn;
}

Object ListMapIterator_ListData(Object _self)
{
	DPUSHS ("ListMapIterator: ListData begined.")
	ASSERT_C ( "ListMapIterator:ListData --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = ListMapIterator_ThisValue(_self);
	DPOPS ("ListMapIterator: ListData ended.")
	return toReturn;
}

Object ListMapIterator_NumberData(Object _self)
{
	DPUSHS ("ListMapIterator: NumberData begined.")
	ASSERT_C ( "ListMapIterator:NumberData --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = ListMapIterator_ThisValue(_self);
	DPOPS ("ListMapIterator: NumberData ended.")
	return toReturn;
}

Object ListMapIterator_LogicData(Object _self)
{
	DPUSHS ("ListMapIterator: LogicData begined.")
	ASSERT_C ( "ListMapIterator:LogicData --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = ListMapIterator_ThisValue(_self);
	DPOPS ("ListMapIterator: LogicData ended.")
	return toReturn;
}

Object ListMapIterator_ToEnd(Object _self)
{
	DPUSHS ("ListMapIterator: ToEnd begined.")
	ASSERT_C ( "ListMapIterator:ToEnd --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	List_Clean((((ListMapIterator) (_self->entity))->_key));
	(((ListMapIterator) (_self->entity))->_thisEnd) = _no;
	(((ListMapIterator) (_self->entity))->_thisBegin) = _no;
	Object _element;
	_element = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_element->entity))->_node), (((ListMap) ((((ListMapIterator) (_self->entity))->_listMap)->entity))->_root));
	Object_SetRetaining(&(((ListMapIteratorElement) (_element->entity))->_iterator), MapIterator_Next(Map_Last((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_nextMap))));
	(((ListMapIteratorElement) (_element->entity))->_prevExists) = ListMapIterator_MoreThanOneElementInNode(_self, (((ListMapIteratorElement) (_element->entity))->_node));
	(((ListMapIteratorElement) (_element->entity))->_nextExists) = _no;
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
	Object_Release(_element);
	if((Map_Empty((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_nextMap))) != _false)
	{
		if((Logic_Not((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapped))) != _false)
		{
			(((ListMapIterator) (_self->entity))->_thisBegin) = _yes;
			(((ListMapIterator) (_self->entity))->_thisEnd) = _yes;
		}
		Object toReturn = _self;
		DPOPS ("ListMapIterator: ToEnd ended.")
		return toReturn;
	}
	while((Logic_Not(MapIterator_ThisBegin((((ListMapIteratorElement) (_element->entity))->_iterator)))) != _false)
	{
		_element = ListMapIterator_PrevAnyWithElement(_self, _element);
	}
	Object toReturn = _self;
	DPOPS ("ListMapIterator: ToEnd ended.")
	return toReturn;
}

Object ListMapIterator_Prev(Object _self)
{
	DPUSHS ("ListMapIterator: Prev begined.")
	ASSERT_C ( "ListMapIterator:Prev --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	if(((((ListMapIterator) (_self->entity))->_thisEnd)) != _false)
	{
		if((Logic_Not((((ListMapIterator) (_self->entity))->_thisBegin))) != _false)
		{
			(((ListMapIterator) (_self->entity))->_thisEnd) = _no;
		}
		Object toReturn = _self;
		DPOPS ("ListMapIterator: Prev ended.")
		return toReturn;
	}
	Object _element;
	_element = Stack_Pop((((ListMapIterator) (_self->entity))->_elementStack));
	if((Logic_Not((((ListMapIteratorElement) (_element->entity))->_prevExists))) != _false)
	{
		Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
		(((ListMapIterator) (_self->entity))->_thisBegin) = _yes;
		Object toReturn = _self;
		DPOPS ("ListMapIterator: Prev ended.")
		return toReturn;
	}
	while((MapIterator_PrevBegin((((ListMapIteratorElement) (_element->entity))->_iterator))) != _false)
	{
		_element = Stack_Pop((((ListMapIterator) (_self->entity))->_elementStack));
		List_RemoveBack((((ListMapIterator) (_self->entity))->_key));
	}
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _element);
	_element = ListMapIterator_PrevAnyWithElement(_self, _element);
	while((Logic_Not((((ListMapNode) ((((ListMapIteratorElement) (_element->entity))->_node)->entity))->_mapped))) != _false)
	{
		_element = ListMapIterator_PrevAnyWithElement(_self, _element);
	}
	Object toReturn = _self;
	DPOPS ("ListMapIterator: Prev ended.")
	return toReturn;
}

Object ListMapIterator_PrevAnyWithElement(Object _self, Object _element)
{
	DPUSHS ("ListMapIterator: PrevAnyWithElement begined.")
	ASSERT_C ( "ListMapIterator:PrevAnyWithElement --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_C ( "ListMapIterator:PrevAnyWithElement --- Checking for correct parameter type failed at parameter _element.", _element->gid ==  5141019124093965312ull || _element == _nil )
	Object _nextElement;
	_nextElement = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_nextElement->entity))->_node), ListMapIteratorElement_ReturningValue(_element, Stack_ObjectAtPositionIfExists((((ListMapIterator) (_self->entity))->_elementStack), NumberFactory_FromLong(_numberFactory, 1))));
	Object_SetRetaining(&(((ListMapIteratorElement) (_nextElement->entity))->_iterator), MapIterator_Next(Map_Last((((ListMapNode) ((((ListMapIteratorElement) (_nextElement->entity))->_node)->entity))->_nextMap))));
	(((ListMapIteratorElement) (_nextElement->entity))->_nextExists) = (((ListMapIteratorElement) (_element->entity))->_nextExists);
	(((ListMapIteratorElement) (_nextElement->entity))->_prevExists) = Logic_Or((((ListMapIteratorElement) (_element->entity))->_prevExists), ListMapIterator_MoreThanOneElementInNode(_self, (((ListMapIteratorElement) (_nextElement->entity))->_node)));
	Stack_Push((((ListMapIterator) (_self->entity))->_elementStack), _nextElement);
	Object_Release(_nextElement);
	List_PushBack((((ListMapIterator) (_self->entity))->_key), MapIterator_ThisKey((((ListMapIteratorElement) (_element->entity))->_iterator)));
	Object toReturn = _nextElement;
	DPOPS ("ListMapIterator: PrevAnyWithElement ended.")
	return toReturn;
}

Object ListMapIterator_ThisEnd(Object _self)
{
	DPUSHS ("ListMapIterator: ThisEnd begined.")
	ASSERT_C ( "ListMapIterator:ThisEnd --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = (((ListMapIterator) (_self->entity))->_thisEnd);
	DPOPS ("ListMapIterator: ThisEnd ended.")
	return toReturn;
}

Object ListMapIterator_ThisBegin(Object _self)
{
	DPUSHS ("ListMapIterator: ThisBegin begined.")
	ASSERT_C ( "ListMapIterator:ThisBegin --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object toReturn = (((ListMapIterator) (_self->entity))->_thisBegin);
	DPOPS ("ListMapIterator: ThisBegin ended.")
	return toReturn;
}

Object ListMapIterator_Compare(Object _self, Object _iterator)
{
	DPUSHS ("ListMapIterator: Compare begined.")
	ASSERT_C ( "ListMapIterator:Compare --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	ASSERT_C ( "ListMapIterator:Compare --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==  3251886107095273472ull || _iterator == _nil )
	Object _candidate;
	_candidate = Object_Compare((((ListMapIterator) (_self->entity))->_listMap), (((ListMapIterator) (_iterator->entity))->_listMap));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) == _equal)) != _false)
	{
		_candidate = Object_Compare((((ListMapIterator) (_self->entity))->_elementStack), (((ListMapIterator) (_iterator->entity))->_elementStack));
	}
	Object toReturn = _candidate;
	DPOPS ("ListMapIterator: Compare ended.")
	return toReturn;
}

Object ListMapIterator_Clone(Object _self)
{
	DPUSHS ("ListMapIterator: Clone begined.")
	ASSERT_C ( "ListMapIterator:Clone --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object _toReturn;
	_toReturn = ListMapIterator_Create();
	Object_SetRetaining(&(((ListMapIterator) (_toReturn->entity))->_listMap), (((ListMapIterator) (_self->entity))->_listMap));
	(((ListMapIterator) (_toReturn->entity))->_elementStack) = Object_DeepClone((((ListMapIterator) (_self->entity))->_elementStack));
	(((ListMapIterator) (_toReturn->entity))->_thisBegin) = (((ListMapIterator) (_self->entity))->_thisBegin);
	(((ListMapIterator) (_toReturn->entity))->_thisEnd) = (((ListMapIterator) (_self->entity))->_thisEnd);
	Object_SetReleasing(&(((ListMapIterator) (_toReturn->entity))->_key), Object_DeepClone((((ListMapIterator) (_self->entity))->_key)));
	Object toReturn = _toReturn;
	DPOPS ("ListMapIterator: Clone ended.")
	return toReturn;
}

Object ListMapIterator_DeepClone(Object _self)
{
	DPUSHS ("ListMapIterator: DeepClone begined.")
	ASSERT_C ( "ListMapIterator:DeepClone --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object _toReturn;
	_toReturn = ListMapIterator_Create();
	Object_SetRetaining(&(((ListMapIterator) (_toReturn->entity))->_listMap), (((ListMapIterator) (_self->entity))->_listMap));
	(((ListMapIterator) (_toReturn->entity))->_elementStack) = Object_DeepClone((((ListMapIterator) (_self->entity))->_elementStack));
	(((ListMapIterator) (_toReturn->entity))->_thisBegin) = (((ListMapIterator) (_self->entity))->_thisBegin);
	(((ListMapIterator) (_toReturn->entity))->_thisEnd) = (((ListMapIterator) (_self->entity))->_thisEnd);
	Object_SetReleasing(&(((ListMapIterator) (_toReturn->entity))->_key), Object_DeepClone((((ListMapIterator) (_self->entity))->_key)));
	Object toReturn = _toReturn;
	DPOPS ("ListMapIterator: DeepClone ended.")
	return toReturn;
}

Object ListMapIterator_Destroy(Object _self)
{
	DPUSHS ("ListMapIterator: Destroy begined.")
	ASSERT_C ( "ListMapIterator:Destroy --- Checking for correct object type failed.", _self->gid ==  3251886107095273472ull )
	Object_Release((((ListMapIterator) (_self->entity))->_listMap));
	Object_Release((((ListMapIterator) (_self->entity))->_elementStack));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListMapIterator: Destroy ended.")
	return toReturn;
}
