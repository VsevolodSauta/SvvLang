#pragma once

#include "internals/basics.h"

typedef struct SvvInternalUArray {
	char*			data;
	int			size;
	int			allocated;
} *SvvInternalUArray;

SvvInternalCreator(SvvInternalUArray); // O(1)
SvvInternalAction(SvvInternalUArray, Destroy, void); // O(n)
SvvInternalAction(SvvInternalUArray, ByteGetAt, char, int Position); // O(1)
SvvInternalAction(SvvInternalUArray, ByteSetAt, void, int Position, char Byte); // O(1)
SvvInternalAction(SvvInternalUArray, ByteShiftRightFromBy, void, int Position, int Quantity); // O(n)
SvvInternalAction(SvvInternalUArray, ByteShiftLeftFromBy, void, int Position, int Quantity); // O(n)
SvvInternalAction(SvvInternalUArray, ByteGetSubArrayBetweenPositions, SvvInternalUArray, int PositionFrom, int PositionTo); // O(n)
SvvInternalAction(SvvInternalUArray, CharGetAt, SvvInternalChar, int Position); // O(1)
SvvInternalAction(SvvInternalUArray, CharSetAt, void, int Position, SvvInternalChar Char); // O(n)
SvvInternalAction(SvvInternalUArray, CharGetBeginningFromPosition, int, int Position); // O(1)
SvvInternalAction(SvvInternalUArray, Clean, void);
SvvInternalAction(SvvInternalUArray, Clone, SvvInternalUArray);
SvvInternalAction(SvvInternalUArray, Sort, void);
SvvInternalAction(SvvInternalUArray, Compare, int, SvvInternalUArray UArray);
SvvInternalAction(SvvInternalUArray, Concatenate, void, SvvInternalUArray UArray);
SvvInternalAction(SvvInternalUArray, SetSize, void, int Size);
SvvInternalAction(SvvInternalUArray, SetSizeToContain, void, int);
SvvInternalAction(SvvInternalUArray, GetSize, int);
SvvInternalAction(SvvInternalUArray, ByteDump, void);
SvvInternalAction(SvvInternalUArray, GetBuffer, void*);