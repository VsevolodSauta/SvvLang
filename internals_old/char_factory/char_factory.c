#include "internals/basics.h"
#include "internals/char/interface.h"

Action(CharFactory, FromCode, Object code)
{
	Object toReturn = Char_Create();
	Object_Autorelease(toReturn);
	Char_SetCode(toReturn, code);
	return toReturn;
};

Object charFactory;