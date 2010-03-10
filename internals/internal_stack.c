#include "internal_actions.h"
#include "internal_object.h"
#include "internal_list.h"
#include "internal_stack.h"

SvvInternalCreator(SvvInternalStack)
{
	return SvvInternalList_Create();
};

SvvInternalAction(SvvInternalStack, Destroy, void)
{
	SvvInternalList_Destroy(Receiver);
};

SvvInternalAction(SvvInternalStack, Push, void, SvvInternalObject Object)
{
	SvvInternalList_PushBack(Receiver, Object);
};

SvvInternalAction(SvvInternalStack, Pop, SvvInternalObject)
{
	SvvInternalListIterator iterator = SvvInternalList_GetLast(Receiver);
	SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
	SvvInternalListIterator_Remove(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return object;
};

SvvInternalAction(SvvInternalStack, Peek, SvvInternalObject)
{
	SvvInternalListIterator iterator = SvvInternalList_GetLast(Receiver);
	SvvInternalObject object = SvvInternalListIterator_GetData(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return object;
};

SvvInternalAction(SvvInternalStack, Clean, void)
{
	SvvInternalList_Clean(Receiver);
};

SvvInternalAction(SvvInternalStack, IsEmpty, int)
{
	SvvInternalListIterator iterator = SvvInternalList_GetFirst(Receiver);
	int result = SvvInternalListIterator_EndReached(iterator);
	SvvInternalListIterator_Destroy(iterator);
	return result;
};

SvvInternalAction(SvvInternalStack, Clone, SvvInternalStack)
{
	return SvvInternalList_Clone(Receiver);
};
