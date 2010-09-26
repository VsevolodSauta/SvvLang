#include "internals/basics.h"
#include "internals/string/interface.h"
#include "internals/list/interface.h"

SvvInternalCreator(SvvInternalString)
{
	SvvInternalString string = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalString)));
	string->length = 0;
	string->data = SvvInternalList_Create();
	return string;
};

SvvInternalAction(SvvInternalString, Destroy, void)
{
	SvvInternalList_Destroy(Receiver->data);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String)
{
	SvvInternalListIterator iterator = SvvInternalList_GetLast(Receiver->data);
	SvvInternalListIterator_AddListAfter(iterator, String->data);
	Receiver->length += String->length;
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalString, CharGetAt, SvvInternalChar, int Position)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIteratorFromPosition(Receiver->data, Position);
	SvvInternalChar to_return = OBJECT_AS_CHAR(SvvInternalListIterator_GetData(iterator));
	SvvInternalListIterator_Destroy(iterator);
	return to_return;
};

SvvInternalAction(SvvInternalString, SetAt, void, int Position, SvvInternalChar Char)
{
	SvvInternalListIterator iterator = SvvInternalList_GetIteratorFromPosition(Receiver->data, Position);
	SvvInternalListIterator_SetData(iterator, CHAR_AS_OBJECT(Char));
	SvvInternalListIterator_Destroy(iterator);
};

SvvInternalAction(SvvInternalString, SubString, SvvInternalString, int PositionFrom, int PositionTo)
{
	SvvInternalString string = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalString*)));
	string->length = PositionTo - PositionFrom;
	string->data = SvvInternalList_GetSublistBetweenPositions(Receiver->data, PositionFrom, PositionTo);
	return string;
};

SvvInternalAction(SvvInternalString, Remove, void, int PositionFrom, int PositionTo)
{
	SvvInternalListIterator_RemoveCount(SvvInternalList_GetIteratorFromPosition(Receiver->data, PositionFrom), PositionTo - PositionFrom);
	Receiver->length -= PositionTo - PositionFrom;
};

SvvInternalAction(SvvInternalString, GetLength, int)
{
	return Receiver->length;
};

SvvInternalAction(SvvInternalString, Clone, SvvInternalString)
{
	SvvInternalString string = SvvInternalString_Create();
	string->length = Receiver->length;
	string->data = SvvInternalList_Clone(Receiver->data);
	return string;
};

SvvInternalAction(SvvInternalString, CharAppend, void, SvvInternalChar Char)
{
	Receiver->length++;
	SvvInternalList_PushBack(Receiver->data, CHAR_AS_OBJECT(Char));
};




SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver;
	iterator->position = 0;
	iterator->iterator = SvvInternalList_GetFirst(Receiver->data);
	return iterator;
};

SvvInternalAction(SvvInternalString, GetLast, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver;
	iterator->position = Receiver->length - 1;
	iterator->iterator = SvvInternalList_GetLast(Receiver->data);
	return iterator;
};

