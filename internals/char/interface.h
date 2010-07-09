#pragma once

#include "internals/actions.h"

typedef struct {
	char bytes[4];
} SvvInternalChar;

SvvInternalAction(SvvInternalChar, LengthInBytes, int);
SvvInternalAction(SvvInternalChar, CharFromPtr, SvvInternalChar, void*);

static inline SvvInternalAction(char, GetLengthInBytes, int)
{
	if((Receiver & 0xFE) == 0xFC) return 6;
	if((Receiver & 0xFC) == 0xF8) return 5;
	if((Receiver & 0xF8) == 0xF0) return 4;
	if((Receiver & 0xF0) == 0xE0) return 3;
	if((Receiver & 0xE0) == 0xC0) return 2;
	if((Receiver & 0xC0) == 0x80) return 0;
	if((Receiver & 0x80) == 0x00) return 1;
	return -1;
};
