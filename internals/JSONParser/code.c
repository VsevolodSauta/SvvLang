#include "internals/basics.h"
#include "internals/JSONParser/imports.h"


Object JSONParser_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("JSONParser: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct JSONParser));
	_self->gid =   932129127216689152ull;
	Object_SetComparator(_self, &JSONParser_Compare);
	Object_SetDestructor(_self, &JSONParser_Destroy);
	Object_SetCloner(_self, &JSONParser_Clone);
	Object_SetDeepCloner(_self, &JSONParser_DeepClone);
	((JSONParser) (_self->entity))->_error = _nil;
	_self = JSONParser_Init(_self);
	DPOPS ("JSONParser: Create ended.")
	return _self;
}

Object JSONParser_Init(Object _self)
{
	DPUSHS ("JSONParser: Init begined.")
	ASSERT_C ( "JSONParser:Init --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	(((JSONParser) (_self->entity))->_error) = Object_Create();
	Object toReturn = _self;
	DPOPS ("JSONParser: Init ended.")
	return toReturn;
}

Object JSONParser_Compare(Object _self, Object _jsonParser)
{
	DPUSHS ("JSONParser: Compare begined.")
	ASSERT_C ( "JSONParser:Compare --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:Compare --- Checking for correct parameter type failed at parameter _jsonParser.", _jsonParser->gid ==   932129127216689152ull || _jsonParser == _nil )
	Object toReturn = _equal;
	DPOPS ("JSONParser: Compare ended.")
	return toReturn;
}

Object JSONParser_Clone(Object _self)
{
	DPUSHS ("JSONParser: Clone begined.")
	ASSERT_C ( "JSONParser:Clone --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	Object toReturn = _self;
	DPOPS ("JSONParser: Clone ended.")
	return toReturn;
}

Object JSONParser_DeepClone(Object _self)
{
	DPUSHS ("JSONParser: DeepClone begined.")
	ASSERT_C ( "JSONParser:DeepClone --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	Object toReturn = _self;
	DPOPS ("JSONParser: DeepClone ended.")
	return toReturn;
}

Object JSONParser_Destroy(Object _self)
{
	DPUSHS ("JSONParser: Destroy begined.")
	ASSERT_C ( "JSONParser:Destroy --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	Object_Release((((JSONParser) (_self->entity))->_error));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("JSONParser: Destroy ended.")
	return toReturn;
}

Object JSONParser_ParseString(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseString begined.")
	ASSERT_C ( "JSONParser:ParseString --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseString --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) != _equal))) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseString ended.")
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
			DPOPS ("JSONParser: ParseString ended.")
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
	Object toReturn = (((JSONParser) (_self->entity))->_error);
	DPOPS ("JSONParser: ParseString ended.")
	return toReturn;
}

Object JSONParser_ParseObject(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseObject begined.")
	ASSERT_C ( "JSONParser:ParseObject --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseObject --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) != _equal))) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseObject ended.")
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
			DPOPS ("JSONParser: ParseObject ended.")
			return toReturn;
		}
		Object _string;
		_string = JSONParser_ParseString(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_string, (((JSONParser) (_self->entity))->_error)) == _equal)) != _false)
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
		_value = JSONParser_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, (((JSONParser) (_self->entity))->_error)) == _equal)) != _false)
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
	Object toReturn = (((JSONParser) (_self->entity))->_error);
	DPOPS ("JSONParser: ParseObject ended.")
	return toReturn;
}

Object JSONParser_ParseArray(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseArray begined.")
	ASSERT_C ( "JSONParser:ParseArray --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseArray --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = List_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) != _equal))) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseArray ended.")
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
			DPOPS ("JSONParser: ParseArray ended.")
			return toReturn;
		}
		Object _value;
		_value = JSONParser_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, (((JSONParser) (_self->entity))->_error)) == _equal)) != _false)
		{
			Object toReturn = (((JSONParser) (_self->entity))->_error);
			DPOPS ("JSONParser: ParseArray ended.")
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
			Object toReturn = (((JSONParser) (_self->entity))->_error);
			DPOPS ("JSONParser: ParseArray ended.")
			return toReturn;
		}
	}
	Object toReturn = (((JSONParser) (_self->entity))->_error);
	DPOPS ("JSONParser: ParseArray ended.")
	return toReturn;
}

Object JSONParser_ParseValue(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseValue begined.")
	ASSERT_C ( "JSONParser:ParseValue --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseValue --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseString(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseObject(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseArray(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '-')) == _equal), Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
	{
		Object toReturn = JSONParser_ParseNumber(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseTrue(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseFalse(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) == _equal)) != _false)
	{
		Object toReturn = JSONParser_ParseNull(_self, _iterator);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseValue ended.")
		return toReturn;
	}
}

Object JSONParser_ParseTrue(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseTrue begined.")
	ASSERT_C ( "JSONParser:ParseTrue --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseTrue --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'r')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseTrue ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _true;
	DPOPS ("JSONParser: ParseTrue ended.")
	return toReturn;
}

Object JSONParser_ParseFalse(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseFalse begined.")
	ASSERT_C ( "JSONParser:ParseFalse --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseFalse --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'a')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 's')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseFalse ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _false;
	DPOPS ("JSONParser: ParseFalse ended.")
	return toReturn;
}

Object JSONParser_ParseNull(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseNull begined.")
	ASSERT_C ( "JSONParser:ParseNull --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseNull --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNull ended.")
		return toReturn;
	}
	ListIterator_Next(_iterator);
	Object toReturn = _nil;
	DPOPS ("JSONParser: ParseNull ended.")
	return toReturn;
}

Object JSONParser_ParseNumber(Object _self, Object _iterator)
{
	DPUSHS ("JSONParser: ParseNumber begined.")
	ASSERT_C ( "JSONParser:ParseNumber --- Checking for correct object type failed.", _self->gid ==   932129127216689152ull )
	ASSERT_C ( "JSONParser:ParseNumber --- Checking for correct parameter type failed at parameter _iterator.", _iterator->gid ==   807984642922801280ull || _iterator == _nil )
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
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNumber ended.")
		return toReturn;
	}
	if((Logic_Not(Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
	{
		Object toReturn = (((JSONParser) (_self->entity))->_error);
		DPOPS ("JSONParser: ParseNumber ended.")
		return toReturn;
	}
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		if((Logic_Not(Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
		{
			break;
		}
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
		DPOPS ("JSONParser: ParseNumber ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = _toReturn;
		DPOPS ("JSONParser: ParseNumber ended.")
		return toReturn;
	}
}
