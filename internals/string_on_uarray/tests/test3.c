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
	SvvInternalString_CharSetAt(string, 2, ch);
	ch.bytes[0] = 0;
	SvvInternalString_CharAppend(string, ch);
	
	SvvInternalUArray array = SvvInternalString_GetUArray(string);
	void* buffer = SvvInternalUArray_GetBuffer(array);
	TEST("Testing data", memcmp(buffer, "ababaabcba\0", 11) == 0);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(buffer));
	SvvInternalUArray_Destroy(array);
	SvvInternalString_Destroy(string);
	return 0;
};
