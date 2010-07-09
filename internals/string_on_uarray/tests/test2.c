#include "../interface.h"
#include "internals/uarray/interface.h"
#include "internals/debugger.h"

int main(void)
{
	SvvInternalString string = SvvInternalString_Create();
	SvvInternalChar ch;
	
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 'a';
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 'b';
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 'c';
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 'b';
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 'a';
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	SvvInternalString_Concatenate(string, string);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	SvvInternalString_CharSetAt(string, 2, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	ch.bytes[0] = 0;
	SvvInternalString_CharAppend(string, ch);
	DEBUG("Real UArray size: %i\n", SvvInternalUArray_GetSize(string->data));
	TEST("Testing UArray size", SvvInternalUArray_GetSize(string->data) == 11);
	SvvInternalString_Destroy(string);
	return 0;
};
