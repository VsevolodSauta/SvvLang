#include "internal_config.h"
#include "internal_globals.h"
#include "internal_actions.h"
#include "internal_object.h"
#include "internal_mmu.h"
#include "internal_list.h"

#define AS_ENTRY(a) ((SvvInternalStringMapEntry) (a))

SvvInternalCreator(SvvInternalStringSet)
{
	return SvvInternalList_Create();
};

SvvInternalAction(SvvInternalStringSet, Destroy, void)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIterator(Receiver);
	while(!IS_NOTHING(iterator))
	{
		if(!IS_NOTHING(AS_ENTRY(SvvInternalListIterator_GetData(iterator))->son))
			SvvInternalStringSet_Destroy(AS_ENTRY(SvvInternalListIterator_GetData(iterator))->son);
		SvvInternalAllocator_Delete(SvvDefaultAllocator, SvvInternaListIterator_GetData(iterator));
		SvvInternalListIterator_GetNext(iterator);
	};
	SvvInternalList_Destroy(Receiver);
};

SvvInternalAction(SvvInternalStringSet, Add, void, SvvInternalString String)
{
	
};

SvvInternalAction(SvvInternalStringSet, Remove, void, SvvInternalString String)
{
};

SvvInternalAction(SvvInternalStringSet, Exists, int, SvvInternalString String)
{
};

SvvInternalAction(SvvInternalStringSet, GetList, SvvInternalList)
{
};
