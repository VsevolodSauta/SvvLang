#include "internals/actions.h"
#include "internals/char/interface.h"

SvvInternalAction(SvvInternalChar, LengthInBytes, int)
{
	if((Receiver.bytes[0] & 0xE0) == 0xE0)
	{
		if(Receiver.bytes[0] & 0x10)
		{
			return 4;
		} else {
			return 3;
		};
	} else {
		if((Receiver.bytes[0] & 0xC0) == 0xC0)
		{
			return 2;
		} else {
			return 1;
		};
	};
};

SvvInternalAction(SvvInternalChar, CharFromPtr, SvvInternalChar, void* Ptr)
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
