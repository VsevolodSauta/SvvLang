#include "internal_actions.h"
#include "internal_char.h"

SvvInternalAction(SvvInternalChar, LengthInBytes, int)
{
	if((Receiver & 0xE0) == 0xE0)
	{
		if(Receiver & 0x10)
		{
			return 4;
		} else {
			return 3;
		};
	} else {
		if((Receiver & 0xC0) == 0xC0)
		{
			return 2;
		} else {
			return 1;
		};
	};
};

SvvInternalAction(SvvInternalAction, CharFromPtr, SvvInternalChar, void* Ptr)
{
	SvvInternalChar *Buffer = Ptr;
	SvvInternalChar ch = *Buffer;
	int i, len = SvvInternalChar_LengthInBytes(ch);

	for(i = sizeof(SvvInternalChar) - 1; i >= len; i--)
	{
		ch.bytes[i] = 0;
	};
	
	return ch;
};