#pragma once

#include "internal_actions.h"
#include "internal_char.h"
#include "internal_list.h"

typedef struct SvvInternalString {
	SvvInternalList data;
	int length;
} *SvvInternalString;

typedef struct SvvInternalStringIterator {
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
SvvInternalAction(SvvInternalString, Clone, SvvInternalString);
SvvInternalAction(SvvInternalString, AppendChar, void, SvvInternalChar);

SvvInternalCreator(SvvInternalStringIterator);
SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator);
SvvInternalAction(SvvInternalString, GetLast, SvvInternalStringIterator);
SvvInternalAction(SvvInternalStringIterator, EndReached, int);
SvvInternalAction(SvvInternalStringIterator, BeginReached, int);
SvvInternalAction(SvvInternalStringIterator, Destroy, void);
SvvInternalAction(SvvInternalStringIterator, GetNext, void);
SvvInternalAction(SvvInternalStringIterator, GetPrev, void);
SvvInternalAction(SvvInternalStringIterator, GetString, SvvInternalString);
SvvInternalAction(SvvInternalStringIterator, GetChar, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, SetChar, void, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, GetPosition, int);
SvvInternalAction(SvvInternalStringIterator, SetPosition, void, int);
SvvInternalAction(SvvInternalStringIterator, Clone, SvvInternalStringIterator);
