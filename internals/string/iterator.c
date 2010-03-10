#include "internals/basics.h"
#include "internals/string/interface.h"

#include "internals/list/interface.h"

SvvInternalCreator(SvvInternalStringIterator)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringIterator)));
};

SvvInternalAction(SvvInternalStringIterator, EndReached, int)
{
	return SvvInternalListIterator_EndReached(Receiver->iterator);
};

SvvInternalAction(SvvInternalStringIterator, BeginReached, int)
{
	return SvvInternalListIterator_BeginReached(Receiver->iterator);
};

SvvInternalAction(SvvInternalStringIterator, Destroy, void)
{
	SvvInternalListIterator_Destroy(Receiver->iterator);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringIterator, GetNext, void)
{
	SvvInternalListIterator_GetNext(Receiver->iterator);
	Receiver->position++;
};

SvvInternalAction(SvvInternalStringIterator, GetPrev, void)
{
	SvvInternalListIterator_GetPrev(Receiver->iterator);
	Receiver->position--;

};

SvvInternalAction(SvvInternalStringIterator, GetString, SvvInternalString)
{
	return Receiver->object;
};

SvvInternalAction(SvvInternalStringIterator, GetChar, SvvInternalChar)
{
	return OBJECT_AS_CHAR(SvvInternalListIterator_GetData(Receiver->iterator));
};

SvvInternalAction(SvvInternalStringIterator, SetChar, void, SvvInternalChar Char)
{
	SvvInternalListIterator_SetData(Receiver->iterator, CHAR_AS_OBJECT(Char));
};

SvvInternalAction(SvvInternalStringIterator, GetPosition, int)
{
	return Receiver->position;
};

SvvInternalAction(SvvInternalStringIterator, SetPosition, void, int Position)
{
	while(SvvInternalStringIterator_GetPosition(Receiver) > Position)
	{
		SvvInternalStringIterator_GetNext(Receiver);
	};
	while(SvvInternalStringIterator_GetPosition(Receiver) < Position)
	{
		SvvInternalStringIterator_GetPrev(Receiver);
	};
};

SvvInternalAction(SvvInternalStringIterator, Clone, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver->object;
	iterator->iterator = SvvInternalListIterator_Clone(Receiver->iterator);
	iterator->position = Receiver->position;
	return iterator;
};
