#include "internal_object.h"
#include "internal_globals.h"

int main(void)
{
	SvvInternalObject obj = INT_AS_OBJECT(1);
	SvvInternalObject obj1 = INT_AS_OBJECT(1);
	return SvvInternalObject_Compare(obj, obj1);
};