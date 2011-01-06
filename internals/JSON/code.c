#include "internals/basics.h"
#include "internals/JSON/imports.h"


Object JSON_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct JSON));
	toReturn->gid =  6371882041780686848ull;
	Object_SetComparator(toReturn, &JSON_Compare);
	Object_SetDestructor(toReturn, &JSON_Destroy);
	Object_SetCloner(toReturn, &JSON_Clone);
	((JSON) (toReturn->entity))->_null = _nil;
	((JSON) (toReturn->entity))->_true = _nil;
	((JSON) (toReturn->entity))->_false = _nil;
	toReturn = JSON_Init(toReturn);
	return toReturn;
}

Object JSON_Init(Object _self)
{
	_null = Object_Create();
	_true = Object_Create();
	_false = Object_Create();
	return _self;
}

Object JSON_Compare(Object _self, Object _json)
{
	return _equal;
}

Object JSON_Clone(Object _self)
{
	return _self;
}

Object JSON_Destroy(Object _self)
{
	Object_Release(_null);
	Object_Release(_true);
	Object_Release(_false);
	return Object_Destroy(_self);
}

Object JSON_ParseString(Object _self, Object _iterator)
{
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) != _equal))) != _false)
	{
		return _nil;
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
			return _toReturn;
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
	return _nil;
}

Object JSON_ParseObject(Object _self, Object _iterator)
{
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) != _equal))) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '}')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			return _toReturn;
		}
		Object _string;
		_string = JSON_ParseString(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_string, _nil) == _equal)) != _false)
		{
			return _nil;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ':')) != _equal)) != _false)
		{
			return _nil;
		}
		ListIterator_Next(_iterator);
		Object _value;
		_value = JSON_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
		{
			return _nil;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		ListMap_Add(_toReturn, _string, _value);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ',')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '}')) != _equal)) != _false)
		{
			return _nil;
		}
	}
	return _nil;
}

Object JSON_ParseArray(Object _self, Object _iterator)
{
	ListIterator_StringSkipWhiteSpace(_iterator);
	Object _toReturn;
	_toReturn = List_Create();
	Object_Autorelease(_toReturn);
	if((Logic_Or(ListIterator_ThisEnd(_iterator), LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) != _equal))) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
	{
		ListIterator_StringSkipWhiteSpace(_iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ']')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
			return _toReturn;
		}
		Object _value;
		_value = JSON_ParseValue(_self, _iterator);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
		{
			return _nil;
		}
		ListIterator_StringSkipWhiteSpace(_iterator);
		List_PushBack(_toReturn, _value);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ',')) == _equal)) != _false)
		{
			ListIterator_Next(_iterator);
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, ']')) != _equal)) != _false)
		{
			return _nil;
		}
	}
	return _nil;
}

Object JSON_ParseValue(Object _self, Object _iterator)
{
	ListIterator_StringSkipWhiteSpace(_iterator);
	if((ListIterator_ThisEnd(_iterator)) != _false)
	{
		return _nil;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '"')) == _equal)) != _false)
	{
		return JSON_ParseString(_self, _iterator);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '{')) == _equal)) != _false)
	{
		return JSON_ParseObject(_self, _iterator);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '[')) == _equal)) != _false)
	{
		return JSON_ParseArray(_self, _iterator);
	}
	else if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, '-')) == _equal), Char_IsDigit(ListIterator_CharData(_iterator)))) != _false)
	{
		return JSON_ParseNumber(_self, _iterator);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) == _equal)) != _false)
	{
		return JSON_ParseTrue(_self, _iterator);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) == _equal)) != _false)
	{
		return JSON_ParseFalse(_self, _iterator);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) == _equal)) != _false)
	{
		return JSON_ParseNull(_self, _iterator);
	}
	else
	{
		return _nil;
	}
}

Object JSON_ParseTrue(Object _self, Object _iterator)
{
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 't')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'r')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	return (((JSON) (_self->entity))->_true);
}

Object JSON_ParseFalse(Object _self, Object _iterator)
{
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'f')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'a')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 's')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'e')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	return (((JSON) (_self->entity))->_false);
}

Object JSON_ParseNull(Object _self, Object _iterator)
{
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'n')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'u')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_ThisData(_iterator), CharFactory_FromLong(_charFactory, 'l')) != _equal)) != _false)
	{
		return _nil;
	}
	ListIterator_Next(_iterator);
	return (((JSON) (_self->entity))->_null);
}

Object JSON_ParseNumber(Object _self, Object _iterator)
{
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
		return _nil;
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
		return Number_Inv(_toReturn);
	}
	else
	{
		return _toReturn;
	}
}
