#pragma once

#include "internals/actions.h"
#include "internals/mask_builder.h"
#include "internals/char/unicode.h"

typedef struct {
	char bytes[4];
} SvvInternalChar;

SvvInternalAction(SvvInternalChar, GetLengthInBytes, int);
SvvInternalAction(SvvInternalChar, CharFromPtr, SvvInternalChar, void*);
SvvInternalAction(SvvInternalChar, Compare, int, SvvInternalChar Char);
SvvInternalAction(SvvInternalChar, GetCode, int);

#define IsSomething(smth) \
	static inline SvvInternalAction(SvvInternalChar, Is ##smth, int) \
	{ \
		return SvvInternalUnicodeCode_Is ##smth( \
			SvvInternalChar_GetCode(Receiver) \
		); \
	};


IsSomething(ASCII);
IsSomething(Latin);
IsSomething(Cyrillic);
IsSomething(Digit);
IsSomething(HexDigit);
IsSomething(BasicPunctOrSym);
IsSomething(BasicControl);

#undef IsSomething

SvvInternalRoutine(char, GetLengthInBytes, int)
{
	if((Receiver & BITMASK_TO_LEFT(7)) == 0x00) return 1;
	if((Receiver & BITMASK_TO_LEFT(6)) == BITMASK_TO_LEFT(7)) return 0;
	
	int i;
	for(i = 5; i >= 0; i--)
	{
		if((Receiver & BITMASK_TO_LEFT(i)) == BITMASK_TO_LEFT(i + 1))
		{
			return 7 - i;
		};
	};
	
	return -1;
};

SvvInternalRoutine(char, IsInRange, int, char LeftBound, char RightBound)
{
	return ((Receiver >= LeftBound) && (Receiver <= RightBound));
};


