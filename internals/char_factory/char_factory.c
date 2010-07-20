#include "internals/globals.h"
#include "internals/char_factory/interface.h"

SvvInternalAction(SvvInternalCharFactory, CharGetFromCode, SvvInternalChar, int Code)
{
	SvvInternalChar to_return;
	if(Code < (1 << 7))
	{
		// 0b0XXXXXX
		to_return.bytes[0] = Code;
	} else
	if(Code < (1 << (5 + 6)))
	{
		// 0b110XXXXX 0b10XXXXXX
		to_return.bytes[0] = BITMASK_LEFTMOST(2) | (Code >> (6 * 1));
		to_return.bytes[1] = BITMASK_LEFTMOST(1) | (Code & BITMASK_RIGHTMOST(6));
	} else
	if(Code < (1 << (4 + 6 + 6)))
	{
		// 0b1110XXXX 0b10XXXXXX 0b10XXXXXX
		to_return.bytes[0] = BITMASK_LEFTMOST(3) | (Code >> (6 * 2));
		to_return.bytes[1] = BITMASK_LEFTMOST(1) | ((Code >> (6 * 1)) & BITMASK_RIGHTMOST(6));
		to_return.bytes[2] = BITMASK_LEFTMOST(1) | (Code & BITMASK_RIGHTMOST(6));
	} else
	if(Code < (1 << (3 + 6 + 6 + 6)))
	{
		// 0b11110XXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX
		to_return.bytes[0] = BITMASK_LEFTMOST(4) | (Code >> (6 * 3));
		to_return.bytes[1] = BITMASK_LEFTMOST(1) | ((Code >> (6 * 2)) & BITMASK_RIGHTMOST(6));
		to_return.bytes[2] = BITMASK_LEFTMOST(1) | ((Code >> (6 * 1)) & BITMASK_RIGHTMOST(6));
		to_return.bytes[3] = BITMASK_LEFTMOST(1) | (Code & BITMASK_RIGHTMOST(6));
	}
	return to_return;
};

SvvInternalCharFactory SvvDefaultCharFactory;