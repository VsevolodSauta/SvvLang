#include "internals/actions.h"
#include "internals/char/interface.h"
#include "internals/number/interface.h"
#include "internals/char/unicode.h"

SvvInternalAction(SvvInternalChar, GetLengthInBytes, int)
{
	return char_GetLengthInBytes(Receiver.bytes[0]);
};

SvvInternalAction(SvvInternalChar, CharFromPtr, SvvInternalChar, void* Ptr)
{
	SvvInternalChar *Buffer = Ptr;
	SvvInternalChar ch = *Buffer;
	int i, len = SvvInternalChar_GetLengthInBytes(ch);

	for(i = sizeof(SvvInternalChar) - 1; i >= len; i--)
	{
		ch.bytes[i] = 0;
	};
	
	return ch;
};

SvvInternalAction(SvvInternalChar, GetCode, int)
{
	int length = SvvInternalChar_GetLengthInBytes(Receiver);
	if(length > 0)
	{
		int to_return = ~(-(1 << (8 - length))) & Receiver.bytes[0];
		int i;
		
		for(i = 1; i < length; i++)
		{
			to_return <<= 6;
			to_return |= Receiver.bytes[i] & 0x3F;
		};

		return to_return;
	} else {
		if(length == 0)
		{
			return Receiver.bytes[0];
		} else {
			return -1;
		};
	};
};

SvvInternalAction(SvvInternalChar, Compare, int, SvvInternalChar Char)
{
	// TODO: Optimize.
	int code0 = SvvInternalChar_GetCode(Receiver);
	int code1 = SvvInternalChar_GetCode(Char);

	if(code0 > code1)
		return 1;
	if(code0 < code1)
		return -1;
	return 0;
};

