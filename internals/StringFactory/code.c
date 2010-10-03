#include "internals/basics.h"
#include "internals/StringFactory/interface.h"
#include "internals/Char/interface.h"
#include "internals/List/interface.h"
#include "internals/Number/interface.h"

static inline int GetLengthOfByteInUTF8(char* position)
{
	char toInspect = *position;
	if(toInspect & (0 - (1 << 6)) == 0)
		return 1;
	if(toInspect & (0 - (1 << 4)) == (0 - (1 << 5)))
		return 2;
	if(toInspect & (0 - (1 << 3)) == (0 - (1 << 4)))
		return 3;
	if(toInspect & (0 - (1 << 2)) == (0 - (1 << 3)))
		return 4;
	if(toInspect & (0 - (1 << 1)) == (0 - (1 << 2)))
		return 5;
	if(toInspect & (0 - (1 << 0)) == (0 - (1 << 1)))
		return 6;
	return 7;
}

static inline long GetCodeInUTF8(char* position, int length)
{
	if(length == 1)
		return *position;
	int toReturn = ((1 << (7 - length)) - 1) & (*position);
	int i;
	for(i = 1; i < length; i++)
	{
		toReturn <<= 6;
		toReturn += position[i] & ((1 << 6) - 1);
	}
	return toReturn;
}

Object StringFactory_FromUTF8(Object receiver, char* string, int length)
{
	Object toReturn = List_Create();
	int i;
	int offset = 0;
	for(i = 0; i < length; i++)
	{
		int additionalOffset = GetLengthOfByteInUTF8(string + offset);
		long code = GetCodeInUTF8(string + offset, additionalOffset);
		offset += additionalOffset;
		Object _char = Char_Create();
		Object _number = NumberFactory_FromLong(_numberFactory, code);
		Char_SetCode(_char, _number);
		List_PushBack(toReturn, _char);
	}
	return Object_Autorelease(toReturn);
};

Object _stringFactory;
