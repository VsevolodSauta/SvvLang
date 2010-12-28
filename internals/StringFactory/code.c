#include "internals/basics.h"
#include "internals/StringFactory/interface.h"
#include "internals/Char/interface.h"
#include "internals/List/interface.h"
#include "internals/ListIterator/interface.h"
#include "internals/Number/interface.h"
#include <stdio.h>

Object StringFactory_Create()
{
	return Undestroyable_Create();
}

static inline int UTF8GetLengthOfCode(long code)
{
	if(code < 1ull << 7)
		return 1;
	if(code < 1ull << (5 + 6))
		return 2;
	if(code < 1ull << (4 + 6 + 6))
		return 3;
	if(code < 1ull << (3 + 6 + 6 + 6))
		return 4;
	if(code < 1ull << (2 + 6 + 6 + 6 + 6))
		return 5;
	if(code < 1ull << (1 + 6 + 6 + 6 + 6 + 6))
		return 6;
	if(code < 1ull << (0 + 6 + 6 + 6 + 6 + 6 + 6))
		return 7;
	return -1;
}

static inline int UTF8GetLengthOfChar(char* position)
{
	char toInspect = *position;
	if((toInspect & ((1 << 8) - (1 << 7))) == 0)
		return 1;
	if((toInspect & ((1 << 8) - (1 << 5))) == ((1 << 8) - (1 << 6)))
		return 2;
	if((toInspect & ((1 << 8) - (1 << 4))) == ((1 << 8) - (1 << 5)))
		return 3;
	if((toInspect & ((1 << 8) - (1 << 3))) == ((1 << 8) - (1 << 4)))
		return 4;
	if((toInspect & ((1 << 8) - (1 << 2))) == ((1 << 8) - (1 << 3)))
		return 5;
	if((toInspect & ((1 << 8) - (1 << 1))) == ((1 << 8) - (1 << 2)))
		return 6;
	if((toInspect & ((1 << 8) - (1 << 0))) == ((1 << 8) - (1 << 1)))
		return 7;
	return 8;
}

static inline void UTF8PutChar(char* position, int code, int charLength)
{
	if(charLength == 1)
	{
		*position = code;
	} else {
		*position = (code >> ((charLength - 1) * 6)) ^ (0 - (1 << (8 - charLength)));
		int i;
		for(i = 1; i < charLength; i++)
		{
			position[i] = (1 << 7) ^ (((1 << 6) - 1) & (code >> ((charLength - i - 1) * 6)));
		}
	}
}

static inline long UTF8GetCode(char* position, int length)
{
	if(length == 1)
		return *position;
	long toReturn = (unsigned char) (((1 << (7 - length)) - 1) & (*position));
	int i;
	for(i = 1; i < length; i++)
	{
		toReturn <<= 6;
		toReturn += (unsigned char) (position[i] & ((1 << 6) - 1));
	}
	return toReturn;
}

Object StringFactory_FromUTF8(Object _self, char* string, int length)
{
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
	return toReturn;
};

int StringFactory_GetUTF8String(Object _self, Object string, char* buffer, int bufferLength)
{
	Object iterator = List_First(string);
	int position = 0;
	while(ListIterator_ThisEnd(iterator) == _false)
	{
		Object _char = ListIterator_ThisData(iterator);
		Object _number = Char_GetCode(_char);
		long code = Number_GetLong(_number);
		int charLength = UTF8GetLengthOfCode(code);
		if(charLength == -1)
			return -1;
		if(charLength + position >= bufferLength)
			return -1;
		UTF8PutChar(buffer + position, code, charLength);
		position += charLength;
		ListIterator_Next(iterator);
	}
	buffer[position] = 0;
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


Object _stringFactory;
