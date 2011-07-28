#pragma once

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

