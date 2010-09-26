#pragma once

typedef unsigned int UnicodeCode;
typedef const UnicodeCode UnicodeCodeTable[2];

#define TABLE(name, begin, end) extern UnicodeCodeTable name ##_Table
#include "internals/char/tables.h"
#undef TABLE

Routine(UnicodeCode, IsASCII, int);

Routine(UnicodeCode, IsLatin, int);
Routine(UnicodeCode, IsCyrillic, int);

Routine(UnicodeCode, IsDigit, int);
Routine(UnicodeCode, IsHexDigit, int);
Routine(UnicodeCode, IsBasicPunctOrSym, int);
Routine(UnicodeCode, IsBasicControl, int);
