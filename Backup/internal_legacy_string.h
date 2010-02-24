#pragma once

#include "internal_actions.h"
#include "internal_char.h"

typedef struct {
	char* data;
	int size;
	int actual_size;
	int length;
} *SvvInternalString;

SvvInternalCreator(SvvInternalString);
SvvInternalAction(SvvInternalString, Delete, void);
SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String);
SvvInternalAction(SvvInternalString, GetAt, SvvInternalChar, int Position);
SvvInternalAction(SvvInternalString, SubString, SvvInternalString, int Position1, int Position2);
SvvInternalAction(SvvInternalString, Remove, void, int Position1, int Position2);
SvvInternalAction(SvvInternalString, GetLength, int);
SvvInternalAction(SvvInternalString, SetSize, void, int Size);
