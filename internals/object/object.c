#include "internals/actions.h"
#include "internals/object/interface.h"
#include "internals/mmu/interface.h"

#include "internals/globals.h"

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object)
{
	return SvvInternalMMU_Compare(SvvDefaultMMU, LINK_AS_OBJECT(&Receiver), LINK_AS_OBJECT(&Object), sizeof(SvvInternalObject));
};
