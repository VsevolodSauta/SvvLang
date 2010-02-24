#include "internal_actions.h"
#include "internal_char.h"
#include "internal_list.h"
#include "internal_string.h"
#include "internal_allocator.h"
#include "internal_globals.h"

SvvInternalCreator(SvvInternalString)
{
	SvvInternalString string = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalString*)));
	string->length = 0;
	string->data = SvvInternalList_Create();
	return string;
};

SvvInternalAction(SvvInternalString, Delete, void)
{
	SvvInternalList_Destroy(Receiver->data);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String)
{
	SvvInternalList_AddListAfter(SvvInternalList_GetLast(Receiver->data), String->data);
	Receiver->length += String->length;
};

SvvInternalAction(SvvInternalString, GetAt, SvvInternalChar, int Position)
{
	return OBJECT_AS_CHAR(SvvInternalListIterator_GetData(SvvInternalList_GetIteratorFromPosition(Receiver->data, Position)));
};

SvvInternalAction(SvvInternalString, SetAt, void, int Position, SvvInternalChar Char)
{
	SvvInternalListIterator_SetData(SvvInternalList_GetIteratorFromPosition(Receiver->data, Position), CHAR_AS_OBJECT(Char));
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

SvvInternalCreator(SvvInternalStringIterator)
{
	return SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalStringIterator*));
};

SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver;
	iterator->position = 0;
	iterator->iterator = SvvInternalList_GetFirst(Receiver->data);
	return iterator;
};

SvvInternalAction(SvvInternalStringIterator, Destroy, void)
{
	
};

SvvInternalAction(SvvInternalStringIterator, GetNext, void);
SvvInternalAction(SvvInternalStringIterator, GetPrev, void);
SvvInternalAction(SvvInternalStringIterator, GetString, void);
SvvInternalAction(SvvInternalStringIterator, GetChar, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, SetChar, void, SvvInternalChar);
SvvInternalAction(SvvInternalStringIterator, GetPosition, void);
SvvInternalAction(SvvInternalStringIterator, SetPosition, void);
