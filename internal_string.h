#pragma once

#include "internal_actions.h"
#include "internal_char.h"
#include "internal_list.h"

typedef struct {
	SvvInternalList data;
	int length;
} *SvvInternalString;

typedef struct {
	SvvInternalString object;
	SvvInternalListIterator iterator;
	int position;
} *SvvInternalStringIterator;

SvvInternalCreator(SvvInternalString);
SvvInternalAction(SvvInternalString, Delete, void);
SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String);
SvvInternalAction(SvvInternalString, GetAt, SvvInternalChar, int Position);
SvvInternalAction(SvvInternalString, SetAt, void, int Position, SvvInternalChar);
SvvInternalAction(SvvInternalString, SubString, SvvInternalString, int PositionFrom, int PositionTo);
SvvInternalAction(SvvInternalString, Remove, void, int PositionFrom, int PositionTo);
SvvInternalAction(SvvInternalString, GetLength, int);

SvvInternalCreator(SvvInternalStringIterator);
SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator);
SvvInternalAction(SvvInternalStringIterator, Destroy, void);
SvvInternalAction(SvvInternalStringIterator, GetNext, void);
SvvInternalAction(SvvInternalStringIterator, GetPrev, void);
SvvInternalAction(SvvInternalStringIterator, GetString, SvvInternalString);
SvvInternalAction(SvvInternalStringIterator, GetChar, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, SetChar, void, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, GetPosition, int);
SvvInternalAction(SvvInternalStringIterator, SetPosition, void, int);
