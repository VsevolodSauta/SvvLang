#include "internals/basics.h"
#include "internals/JSON/imports.h"


Object JSON_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("JSON: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct JSON));
	_self->gid =  6371882041780686848ull;
	Object_SetComparator(_self, &JSON_Compare);
	Object_SetDestructor(_self, &JSON_Destroy);
	Object_SetCloner(_self, &JSON_Clone);
	Object_SetDeepCloner(_self, &JSON_DeepClone);
	((JSON) (_self->entity))->_error = _nil;
	_self = JSON_Init(_self);
	DPOPS ("JSON: Create ended.")
	return _self;
}

Object JSON_Init(Object _self)
{
	DPUSHS ("JSON: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	(((JSON) (_self->entity))->_error) = Object_Create();
	Object toReturn = _self;
	DPOPS ("JSON: Init ended.")
	return toReturn;
}

Object JSON_Compare(Object _self, Object _json)
{
	DPUSHS ("JSON: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	Object toReturn = _equal;
	DPOPS ("JSON: Compare ended.")
	return toReturn;
}

Object JSON_Clone(Object _self)
{
	DPUSHS ("JSON: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	Object toReturn = _self;
	DPOPS ("JSON: Clone ended.")
	return toReturn;
}

Object JSON_DeepClone(Object _self)
{
	DPUSHS ("JSON: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	Object toReturn = _self;
	DPOPS ("JSON: DeepClone ended.")
	return toReturn;
}

Object JSON_Destroy(Object _self)
{
	DPUSHS ("JSON: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	Object_Release((((JSON) (_self->entity))->_error));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("JSON: Destroy ended.")
	return toReturn;
}

Object JSON_ParseString(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseString begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) != _equal))) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseString ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object _toReturn;
	_toReturn = List_Create();
	Object_Autorelease(_toReturn);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			Object toReturn = _toReturn;
			DPOPS ("JSON: ParseString ended.")
			return toReturn;
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '\\')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '"'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '\\')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\\'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\t'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'b')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\b'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\f'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '/')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '/'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\n'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'r')) == _equal)) != _false)
			{
				List_PushBack(_toReturn, CharFactory_FromLong(_charFactory, '\r'));
			}
			else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) == _equal)) != _false)
			{
				Object _hexNumberToParse;
				_hexNumberToParse = List_Create();
				ListIterator_Next(_iterator);
				List_PushBack(_hexNumberToParse, ListIterator_ThisData(_iterator));
				ListIterator_Next(_iterator);
				List_PushBack(_hexNumberToParse, ListIterator_ThisData(_iterator));
				ListIterator_Next(_iterator);
				List_PushBack(_hexNumberToParse, ListIterator_ThisData(_iterator));
				ListIterator_Next(_iterator);
				List_PushBack(_hexNumberToParse, ListIterator_ThisData(_iterator));
				Object _char;
				_char = Char_Create();
				Char_SetCode(_char, NumberFactory_FromHexString(_numberFactory, _hexNumberToParse));
				List_PushBack(_toReturn, _char);
				Object_Release(_char);
			}
		}
		else
		{
			List_PushBack(_toReturn, ListIterator_ThisData(_iterator));
		}
		ListIterator_Next(_iterator);
	}
	Object toReturn = (((JSON) (_self->entity))->_error);
	DPOPS ("JSON: ParseString ended.")
	return toReturn;
}

Object JSON_ParseObject(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseObject begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) != _equal))) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseObject ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '}')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			Object toReturn = _toReturn;
			DPOPS ("JSON: ParseObject ended.")
			return toReturn;
		}
		Object _string;
		_string = JSON_ParseString(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_string, (((JSON) (_self->entity))->_error)) == _equal)) != _false)
		{
			break;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ':')) != _equal)) != _false)
		{
			break;
		}
		ListIterator_Next(_iterator);
		Object _value;
		_value = JSON_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, (((JSON) (_self->entity))->_error)) == _equal)) != _false)
		{
			break;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		ListMap_Add(_toReturn, _string, _value);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ',')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '}')) != _equal)) != _false)
		{
			break;
		}
	}
	Object toReturn = (((JSON) (_self->entity))->_error);
	DPOPS ("JSON: ParseObject ended.")
	return toReturn;
}

Object JSON_ParseArray(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseArray begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = List_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) != _equal))) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseArray ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ']')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			Object toReturn = _toReturn;
			DPOPS ("JSON: ParseArray ended.")
			return toReturn;
		}
		Object _value;
		_value = JSON_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, (((JSON) (_self->entity))->_error)) == _equal)) != _false)
		{
			Object toReturn = (((JSON) (_self->entity))->_error);
			DPOPS ("JSON: ParseArray ended.")
			return toReturn;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		List_PushBack(_toReturn, _value);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ',')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ']')) != _equal)) != _false)
		{
			Object toReturn = (((JSON) (_self->entity))->_error);
			DPOPS ("JSON: ParseArray ended.")
			return toReturn;
		}
	}
	Object toReturn = (((JSON) (_self->entity))->_error);
	DPOPS ("JSON: ParseArray ended.")
	return toReturn;
}

Object JSON_ParseValue(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseValue begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseString(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseObject(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseArray(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '-')) == _equal), Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
	{
		Object toReturn = JSON_ParseNumber(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseTrue(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseFalse(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) == _equal)) != _false)
	{
		Object toReturn = JSON_ParseNull(_self, _iterator);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseValue ended.")
		return toReturn;
	}
}

Object JSON_ParseTrue(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseTrue begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'r')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _true;
	DPOPS ("JSON: ParseTrue ended.")
	return toReturn;
}

Object JSON_ParseFalse(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseFalse begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'a')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 's')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _false;
	DPOPS ("JSON: ParseFalse ended.")
	return toReturn;
}

Object JSON_ParseNull(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseNull begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _nil;
	DPOPS ("JSON: ParseNull ended.")
	return toReturn;
}

Object JSON_ParseNumber(Object _self, Object _iterator)
{
	DPUSHS ("JSON: ParseNumber begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  6371882041780686848ull )
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _negative;
	_negative = _false;
	Object _toReturn;
	_toReturn = NumberFactory_FromLong(_numberFactory, 0);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '-')) == _equal)) != _false)
	{
		_negative = _true;
		ListIterator_Next(_iterator);
	}
	if((Logic_Not(Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
	{
		Object toReturn = (((JSON) (_self->entity))->_error);
		DPOPS ("JSON: ParseNumber ended.")
		return toReturn;
	}
	while((Char_IsDigit(ListIterator_CharData(_iterator))) != _false)
	{
		Number_MulInPlace(_toReturn, NumberFactory_FromLong(_numberFactory, 10));
		Number_AddInPlace(_toReturn, Number_Sub(Char_GetCode(ListIterator_CharData(_iterator)), NumberFactory_FromLong(_numberFactory, 48)));
		ListIterator_Next(_iterator);
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '.')) == _equal)) != _false)
	{
		ListIterator_Next(_iterator);
		Object _toDivide;
		_toDivide = NumberFactory_FromLong(_numberFactory, 1);
		while((Char_IsDigit(ListIterator_CharData(_iterator))) != _false)
		{
			Number_MulInPlace(_toDivide, NumberFactory_FromLong(_numberFactory, 10));
			Number_AddInPlace(_toReturn, Number_Div(Number_Sub(Char_GetCode(ListIterator_CharData(_iterator)), NumberFactory_FromLong(_numberFactory, 48)), _toDivide));
			ListIterator_Next(_iterator);
		}
	}
	if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'E')) == _equal), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) == _equal))) != _false)
	{
		ListIterator_Next(_iterator);
		Object _exp;
		_exp = NumberFactory_FromLong(_numberFactory, 0);
		while((Char_IsDigit(ListIterator_CharData(_iterator))) != _false)
		{
			Number_MulInPlace(_exp, NumberFactory_FromLong(_numberFactory, 10));
			Number_AddInPlace(_exp, Number_Sub(Char_GetCode(ListIterator_CharData(_iterator)), NumberFactory_FromLong(_numberFactory, 48)));
			ListIterator_Next(_iterator);
		}
		Number_Mul(_toReturn, Number_Power(NumberFactory_FromLong(_numberFactory, 10), _exp));
	}
	if((_negative) != _false)
	{
		Object toReturn = Number_Inv(_toReturn);
		DPOPS ("JSON: ParseNumber ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = _toReturn;
		DPOPS ("JSON: ParseNumber ended.")
		return toReturn;
	}
}
