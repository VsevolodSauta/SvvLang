#pragma once

#include "internals/object/interface.h"
#include "internals/actions.h"

typedef struct Char {
	Object code;
} *Char;

Creator(Char);
Action(Char, GetCode);
Action(Char, SetCode, Object);

Action(Char, IsASCII);
Action(Char, IsLatin);
Action(Char, IsCyrillic);
Action(Char, IsDigit);
Action(Char, IsHexDigit);
Action(Char, IsBasicPunctOrSym);
Action(Char, IsBasicControl);
