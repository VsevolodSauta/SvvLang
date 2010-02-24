#pragma once

#include "internal_actions.h"

typedef struct {
	char bytes[4];
} SvvInternalChar;

SvvInternalAction(SvvInternalChar, LengthInBytes, int);
SvvInternalAction(SvvInternalChar, CharFromPtr, SvvInternalChar, void*);