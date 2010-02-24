#include "internal_object.h"
#include "internal_actions.h"
#include "internal_mmu.h"
#include "internal_globals.h"

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object)
{
	return SvvInternalMMU_Compare(SvvDefaultMMU, LINK_AS_OBJECT(&Receiver), LINK_AS_OBJECT(&Object), sizeof(SvvInternalObject));
};
