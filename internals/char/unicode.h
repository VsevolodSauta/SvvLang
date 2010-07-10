#pragma once

typedef unsigned int SvvInternalUnicodeCode;
typedef const SvvInternalUnicodeCode SvvInternalUnicodeCodeTable[2];

#define TABLE(name, begin, end) extern SvvInternalUnicodeCodeTable name ##_Table
#include "internals/char/tables.h"
#undef TABLE

SvvInternalAction(SvvInternalUnicodeCode, IsASCII, int);

SvvInternalAction(SvvInternalUnicodeCode, IsLatin, int);
SvvInternalAction(SvvInternalUnicodeCode, IsCyrilic, int);

SvvInternalAction(SvvInternalUnicodeCode, IsDigit, int);
SvvInternalAction(SvvInternalUnicodeCode, IsHexDigit, int);
SvvInternalAction(SvvInternalUnicodeCode, IsPunctOrSym, int);
SvvInternalAction(SvvInternalUnicodeCode, IsControl, int);
