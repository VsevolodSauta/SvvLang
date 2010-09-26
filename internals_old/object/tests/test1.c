#include "internals/object/interface.h"
// #include "internal_globals.h"

int main(void)
{
	SvvInternalObject obj = INT_AS_OBJECT(1);
	SvvInternalObject obj1 = INT_AS_OBJECT(5);
	return !SvvInternalObject_Compare(obj, obj1);
};