#include "internals/basics.h"
#include "internals/mmu/interface.h"
#include <string.h>

SvvInternalAction(SvvInternalMMU, Copy, void, SvvInternalObject DestObject, SvvInternalObject SrcObject, int Size)
{
	memcpy(OBJECT_AS_LINK(DestObject), OBJECT_AS_LINK(SrcObject), Size);
};

SvvInternalAction(SvvInternalMMU, Compare, int, SvvInternalObject Object1, SvvInternalObject Object2, int Size)
{
	return memcmp(OBJECT_AS_LINK(Object1), OBJECT_AS_LINK(Object2), Size);
};

SvvInternalMMU SvvDefaultMMU;