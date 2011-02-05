#include "internals/basics.h"
#include "internals/ListMapIteratorElement/imports.h"


Object ListMapIteratorElement_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ListMapIteratorElement: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ListMapIteratorElement));
	_self->gid =  5141019124093965312ull;
	Object_SetComparator(_self, &ListMapIteratorElement_Compare);
	Object_SetDestructor(_self, &ListMapIteratorElement_Destroy);
	Object_SetCloner(_self, &ListMapIteratorElement_Clone);
	Object_SetDeepCloner(_self, &ListMapIteratorElement_DeepClone);
	((ListMapIteratorElement) (_self->entity))->_node = _nil;
	((ListMapIteratorElement) (_self->entity))->_iterator = _nil;
	((ListMapIteratorElement) (_self->entity))->_nextExists = _nil;
	((ListMapIteratorElement) (_self->entity))->_prevExists = _nil;
	DPOPS ("ListMapIteratorElement: Create ended.")
	return _self;
}

Object ListMapIteratorElement_AdvancingValue(Object _self, Object _prevElement)
{
	DPUSHS ("ListMapIteratorElement: AdvancingValue begined.")
	ASSERT_C ( "ListMapIteratorElement:AdvancingValue --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	MapIterator_Next((((ListMapIteratorElement) (_self->entity))->_iterator));
	(((ListMapIteratorElement) (_self->entity))->_nextExists) = Logic_Not(MapIterator_NextEnd((((ListMapIteratorElement) (_self->entity))->_iterator)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_prevElement, _nil) != _equal)) != _false)
	{
		(((ListMapIteratorElement) (_self->entity))->_nextExists) = Logic_Or((((ListMapIteratorElement) (_self->entity))->_nextExists), (((ListMapIteratorElement) (_prevElement->entity))->_nextExists));
	}
	(((ListMapIteratorElement) (_self->entity))->_prevExists) = _yes;
	Object toReturn = MapIterator_ThisValue((((ListMapIteratorElement) (_self->entity))->_iterator));
	DPOPS ("ListMapIteratorElement: AdvancingValue ended.")
	return toReturn;
}

Object ListMapIteratorElement_ReturningValue(Object _self, Object _prevElement)
{
	DPUSHS ("ListMapIteratorElement: ReturningValue begined.")
	ASSERT_C ( "ListMapIteratorElement:ReturningValue --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	MapIterator_Prev((((ListMapIteratorElement) (_self->entity))->_iterator));
	(((ListMapIteratorElement) (_self->entity))->_nextExists) = _yes;
	(((ListMapIteratorElement) (_self->entity))->_prevExists) = Logic_Not(MapIterator_PrevBegin((((ListMapIteratorElement) (_self->entity))->_iterator)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_prevElement, _nil) != _equal)) != _false)
	{
		(((ListMapIteratorElement) (_self->entity))->_prevExists) = Logic_Or((((ListMapIteratorElement) (_self->entity))->_prevExists), (((ListMapIteratorElement) (_prevElement->entity))->_prevExists));
	}
	Object toReturn = MapIterator_ThisValue((((ListMapIteratorElement) (_self->entity))->_iterator));
	DPOPS ("ListMapIteratorElement: ReturningValue ended.")
	return toReturn;
}

Object ListMapIteratorElement_Clone(Object _self)
{
	DPUSHS ("ListMapIteratorElement: Clone begined.")
	ASSERT_C ( "ListMapIteratorElement:Clone --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	Object _toReturn;
	_toReturn = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_toReturn->entity))->_node), (((ListMapIteratorElement) (_self->entity))->_node));
	Object_SetReleasing(&(((ListMapIteratorElement) (_toReturn->entity))->_iterator), Object_Clone((((ListMapIteratorElement) (_self->entity))->_iterator)));
	(((ListMapIteratorElement) (_toReturn->entity))->_nextExists) = (((ListMapIteratorElement) (_self->entity))->_nextExists);
	(((ListMapIteratorElement) (_toReturn->entity))->_prevExists) = (((ListMapIteratorElement) (_self->entity))->_prevExists);
	Object toReturn = _toReturn;
	DPOPS ("ListMapIteratorElement: Clone ended.")
	return toReturn;
}

Object ListMapIteratorElement_DeepClone(Object _self)
{
	DPUSHS ("ListMapIteratorElement: DeepClone begined.")
	ASSERT_C ( "ListMapIteratorElement:DeepClone --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	Object _toReturn;
	_toReturn = ListMapIteratorElement_Create();
	Object_SetRetaining(&(((ListMapIteratorElement) (_toReturn->entity))->_node), (((ListMapIteratorElement) (_self->entity))->_node));
	Object_SetRetaining(&(((ListMapIteratorElement) (_toReturn->entity))->_iterator), Object_DeepClone((((ListMapIteratorElement) (_self->entity))->_iterator)));
	(((ListMapIteratorElement) (_toReturn->entity))->_nextExists) = (((ListMapIteratorElement) (_self->entity))->_nextExists);
	(((ListMapIteratorElement) (_toReturn->entity))->_prevExists) = (((ListMapIteratorElement) (_self->entity))->_prevExists);
	Object toReturn = _toReturn;
	DPOPS ("ListMapIteratorElement: DeepClone ended.")
	return toReturn;
}

Object ListMapIteratorElement_Compare(Object _self, Object _element)
{
	DPUSHS ("ListMapIteratorElement: Compare begined.")
	ASSERT_C ( "ListMapIteratorElement:Compare --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	Object _candidate;
	_candidate = Object_Compare((((ListMapIteratorElement) (_self->entity))->_node), (((ListMapIteratorElement) (_element->entity))->_node));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _equal) == _equal)) != _false)
	{
		_candidate = Object_Compare((((ListMapIteratorElement) (_self->entity))->_iterator), (((ListMapIteratorElement) (_element->entity))->_iterator));
	}
	Object toReturn = _candidate;
	DPOPS ("ListMapIteratorElement: Compare ended.")
	return toReturn;
}

Object ListMapIteratorElement_Destroy(Object _self)
{
	DPUSHS ("ListMapIteratorElement: Destroy begined.")
	ASSERT_C ( "ListMapIteratorElement:Destroy --- Checking for correct object type failed.", _self->gid ==  5141019124093965312ull )
	Object_Release((((ListMapIteratorElement) (_self->entity))->_node));
	Object_Release((((ListMapIteratorElement) (_self->entity))->_iterator));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ListMapIteratorElement: Destroy ended.")
	return toReturn;
}
