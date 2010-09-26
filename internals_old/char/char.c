#include "internals/basics.h"
#include "internals/char/interface.h"
#include "internals/char/unicode.h"

#define CODE(recv) (ENTITY(recv, Char)->code)

#define Char_GID 0x50

DefaultOperations(Char);
DefaultInit(Char,
	CODE(receiver) = Number_Create();
	return receiver;
);
DefaultCreator(Char);

Action(Char, Compare, Object toCompare)
{
	return Object_Compare(CODE(receiver), CODE(toCompare));
}

Action(Char, Destroy)
{
	Object_Release(CODE(receiver));
	return Object_Destroy(receiver);
}

Action(Char, Clone)
{
	Object toReturn = Char_Create();
	Char_SetCode(toReturn, CODE(receiver));
	return toReturn;
}

Action(Char, Code)
{
	return Object_TempClone(CODE(receiver));
}

Action(Char, SetCode, Object code)
{
	Number_Set(CODE(receiver), code);
	return receiver;
}

#define IsSmth(smth) \
	Action(Char, Is ##smth) \
	{ \
		return UnicodeCode_Is ##smth (Number_GetLong(CODE(receiver))) ? true : false; \
	}

IsSmth(ASCII);
IsSmth(Cyrillic);
IsSmth(Latin);
IsSmth(Digit);
IsSmth(HexDigit);
IsSmth(BasicPunctOrSym);
IsSmth(BasicControl);
