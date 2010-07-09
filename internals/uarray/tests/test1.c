#include "../interface.h"
#include "internals/uarray/interface.h"
#include "internals/debugger.h"

int main(void)
{
	SvvInternalUArray array = SvvInternalUArray_Create();
	SvvInternalUArray_ByteSetAt(array, 0, 0);
	DEBUG("SvvInternalUArray_GetSize(array) == %i\n", SvvInternalUArray_GetSize(array));
	TEST("Length testing", SvvInternalUArray_GetSize(array) == 1);
	SvvInternalUArray_ByteSetAt(array, 10, 0);
	DEBUG("SvvInternalUArray_GetSize(array) == %i\n", SvvInternalUArray_GetSize(array));
	TEST("Length testing", SvvInternalUArray_GetSize(array) == 11);
	SvvInternalUArray_Destroy(array);
	return 0;
};
