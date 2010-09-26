#include "internals/basics.h"
#include "internals/queue/interface.h"

#include "internals/list/interface.h"

SvvInternalCreator(SvvInternalQueue)
{
	return SvvInternalList_Create();
};

SvvInternalAction(SvvInternalQueue, Destroy, void)
{
	SvvInternalList_Destroy(Receiver);
};

SvvInternalAction(SvvInternalQueue, Push, void, SvvInternalObject Object)
{
	SvvInternalList_PushBack(Receiver, Object);
};

SvvInternalAction(SvvInternalQueue, Pop, SvvInternalObject)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
	SvvInternalListIterator_Remove(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return object;
};

SvvInternalAction(SvvInternalQueue, Peek, SvvInternalObject)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return object;
};

SvvInternalAction(SvvInternalQueue, Clean, void)
{
	SvvInternalList_Clean(Receiver);
};

SvvInternalAction(SvvInternalQueue, Clone, SvvInternalQueue)
{
	return SvvInternalList_Clone(Receiver);
};

SvvInternalAction(SvvInternalQueue, IsEmpty, int)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	int result = SvvInternalListIterator_EndReached(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return result;
};