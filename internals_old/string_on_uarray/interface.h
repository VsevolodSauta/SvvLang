#pragma once

#include "internals/basics.h"
#include "internals/uarray/interface.h"

typedef struct SvvInternalString {
	SvvInternalUArray data;
	int length;
} *SvvInternalString;

typedef struct SvvInternalStringIterator {
	SvvInternalString object;
	int user_position;
	int real_position;
	int flags;
} *SvvInternalStringIterator;

SvvInternalCreator(SvvInternalStringIterator);
SvvInternalAction(SvvInternalStringIterator, EndReached, int);
SvvInternalAction(SvvInternalStringIterator, BeginReached, int);
SvvInternalAction(SvvInternalStringIterator, Destroy, void);
SvvInternalAction(SvvInternalStringIterator, GetNext, void);
SvvInternalAction(SvvInternalStringIterator, GetPrev, void);
SvvInternalAction(SvvInternalStringIterator, GetString, SvvInternalString);
SvvInternalAction(SvvInternalStringIterator, CharGet, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, CharSet, void, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, GetPosition, int);
SvvInternalAction(SvvInternalStringIterator, SetPosition, void, int);
SvvInternalAction(SvvInternalStringIterator, Clone, SvvInternalStringIterator);

SvvInternalCreator(SvvInternalString);
SvvInternalAction(SvvInternalString, Destroy, void);
SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String);
SvvInternalAction(SvvInternalString, CharGetAt, SvvInternalChar, int Position);
SvvInternalAction(SvvInternalString, CharSetAt, void, int Position, SvvInternalChar);
SvvInternalAction(SvvInternalString, GetSubString, SvvInternalString, int PositionFrom, int PositionTo);
SvvInternalAction(SvvInternalString, RemoveFromTo, void, int PositionFrom, int PositionTo);
SvvInternalAction(SvvInternalString, GetLength, int);
SvvInternalAction(SvvInternalString, Clone, SvvInternalString);
SvvInternalAction(SvvInternalString, CharAppend, void, SvvInternalChar);

SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator);
SvvInternalAction(SvvInternalString, GetLast, SvvInternalStringIterator);

SvvInternalAction(SvvInternalString, GetUArray, SvvInternalUArray);
