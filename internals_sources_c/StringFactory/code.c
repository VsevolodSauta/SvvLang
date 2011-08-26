#include "internals/basics.h"
#include "internals/StringFactory/interface.h"
#include "internals/StringFactory/encoding.h"
#include "internals/Char/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Number/interface.h"
#include "internals/Logic/interface.h"
#include "internals/Undestroyable/interface.h"
#include "internals/SuperClass/interface.h"

Object StringFactory_Create()
{
	return Undestroyable_Create();
}

Object StringFactory_FromUTF8(Object _self, char* string, int length)
{
	DPUSHS ("String Factory: Creating string.")
	Object toReturn = List_Create();
	int i;
	int offset = 0;
	for(i = 0; i < length;)
	{
		int additionalOffset = UTF8GetLengthOfChar(string + offset);
		long code = UTF8GetCode(string + offset, additionalOffset);
		offset += additionalOffset;
		Object _char = Char_Create();
		Object _number = NumberFactory_FromLong(_numberFactory, code);
		Char_SetCode(_char, _number);
		List_PushBack(toReturn, _char);
		Object_Release(_char);
		i += additionalOffset;
	}
	Object_Autorelease(toReturn);
	DPOPS ("String Factory: String created.")
	return toReturn;
};

Object StringFactory_FromCUTF8(Object _self, char* string)
{
	DPUSHS ("String Factory: Creating string.")
	Object toReturn = List_Create();
	int offset = 0;
	while(1)
	{
		int additionalOffset = UTF8GetLengthOfChar(string + offset);
		long code = UTF8GetCode(string + offset, additionalOffset);
		offset += additionalOffset;
		if(code == 0) break;
		Object _char = Char_Create();
		Object _number = NumberFactory_FromLong(_numberFactory, code);
		Char_SetCode(_char, _number);
		List_PushBack(toReturn, _char);
		Object_Release(_char);
	}
	Object_Autorelease(toReturn);
	DPOPS ("String Factory: String created.")
	return toReturn;
};

int StringFactory_GetUTF8String(Object _self, Object string, char* buffer, int bufferLength)
{
	DPUSHS ("String Factory: Getting UTF8 array from string.")
	Object iterator = List_First(string);
	int position = 0;
	while(ListIterator_ThisEnd(iterator) == _false)
	{
		Object _char = ListIterator_ThisData(iterator);
		Object _number = Char_GetCode(_char);
		long code = Number_GetLong(_number);
		int charLength = UTF8GetLengthOfCode(code);
		if(charLength == -1)
		{
			DPOPS ("String Factory: UTF8 array from string got (with error).")
			return -1;
		}
		if(charLength + position >= bufferLength)
		{
			DPOPS ("String Factory: UTF8 array from string got (with error).")
			return -1;
		}
		UTF8PutChar(buffer + position, code, charLength);
		position += charLength;
		ListIterator_Next(iterator);
	}
	buffer[position] = 0;
	DPOPS ("String Factory: UTF8 array from string got.")
	return position;
}

Object StringFactory_FromNumber(Object _self, Object number)
{
	DPUSHS ("String Factory: Creating string from number.")
	Object toReturn = List_Create();
	Object iterator = List_First(toReturn);
	Object_Autorelease(toReturn);
	long _long = Number_GetLong(number);
	if(_long == 0)
	{
		Object _char = Char_Create();
		Char_SetCode(_char, NumberFactory_FromLong(_numberFactory, '0'));
		List_PushBack(toReturn, _char);
		Object_Release(_char);
	}
	if(_long < 0)
	{
		Object _char = Char_Create();
		Object _code = NumberFactory_FromLong(_numberFactory, '-');
		Char_SetCode(_char, _code);
		ListIterator_AddBefore(iterator, _char);
		Object_Release(_char);
		_long = -_long;
	}
	ListIterator_Prev(iterator);
	while(_long > 0)
	{
		Object _char = Char_Create();
		Object _code = NumberFactory_FromLong(_numberFactory, (_long % 10) + '0');
		_long /= 10;
		Char_SetCode(_char, _code);
		ListIterator_AddAfter(iterator, _char);
		Object_Release(_char);
	}
	DPOPS ("String Factory: String from number created.")
	return toReturn;
}

void StringFactory_InitializeClass()
{
}

Object _stringFactory;
