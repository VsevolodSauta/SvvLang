#include "../interface.h"
#include "internals/uarray/interface.h"
#include "internals/debugger.h"

int main(void)
{
	SvvInternalString string = SvvInternalString_Create();
	SvvInternalChar ch;
	
	ch.bytes[0] = 'a';
	SvvInternalString_CharAppend(string, ch);
	ch.bytes[0] = 'b';
	SvvInternalString_CharAppend(string, ch);
	ch.bytes[0] = 'c';
	SvvInternalString_CharAppend(string, ch);
	ch.bytes[0] = 'b';
	SvvInternalString_CharAppend(string, ch);
	ch.bytes[0] = 'a';
	SvvInternalString_CharAppend(string, ch);
	SvvInternalString_Concatenate(string, string);
	TEST("Length testing", SvvInternalString_GetLength(string) == 10);
	SvvInternalString_Destroy(string);
	return 0;
};
