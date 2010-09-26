#include "internals/basics.h"
#include "internals/string_on_uarray/interface.h"

SvvInternalAction(SvvInternalString, GetRealPositionFromUserPosition, int, int Position)
{
	int i, result;
	for(i = 0, result = 0; i < Position; i++){
		result += char_GetLengthInBytes(SvvInternalUArray_ByteGetAt(Receiver->data, result));
	};
	return result;
};

SvvInternalCreator(SvvInternalString)
{
	SvvInternalString string = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalString)));
	string->length = 0;
	string->data = SvvInternalUArray_Create();
	return string;
};

SvvInternalAction(SvvInternalString, Destroy, void)
{
	SvvInternalUArray_Destroy(Receiver->data);
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String)
{
	Receiver->length += String->length;
	SvvInternalUArray_Concatenate(Receiver->data, String->data);
};

SvvInternalAction(SvvInternalString, CharGetAt, SvvInternalChar, int Position)
{
	return SvvInternalUArray_CharGetAt(Receiver->data, SvvInternalString_GetRealPositionFromUserPosition(Receiver, Position));
};

SvvInternalAction(SvvInternalString, CharSetAt, void, int Position, SvvInternalChar Char)
{
	SvvInternalUArray_CharSetAt(Receiver->data, SvvInternalString_GetRealPositionFromUserPosition(Receiver, Position), Char);
};

SvvInternalAction(SvvInternalString, GetSubStringFromTo, SvvInternalString, int PositionFrom, int PositionTo)
{
	SvvInternalString string = SvvInternalString_Create();
	int from_real_position = SvvInternalString_GetRealPositionFromUserPosition(Receiver, PositionFrom);
	int to_real_position = SvvInternalString_GetRealPositionFromUserPosition(Receiver, PositionTo);
	SvvInternalUArray array = SvvInternalUArray_ByteGetSubArrayBetweenPositions(Receiver->data, from_real_position, to_real_position);
	SvvInternalUArray_Destroy(string->data);
	string->data = array;
	string->length = PositionFrom - PositionTo;
	
	return string;
};

SvvInternalAction(SvvInternalString, RemoveFromTo, void, int PositionFrom, int PositionTo)
{
	int from_real_position = SvvInternalString_GetRealPositionFromUserPosition(Receiver, PositionFrom);
	int to_real_position = SvvInternalString_GetRealPositionFromUserPosition(Receiver, PositionTo);
	
	SvvInternalUArray_ByteShiftLeftFromBy(Receiver->data, to_real_position, to_real_position - from_real_position);
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
	SvvInternalUArray_Destroy(string->data);
	string->data = SvvInternalUArray_Clone(Receiver->data);
	return string;
};

SvvInternalAction(SvvInternalString, CharAppend, void, SvvInternalChar Char)
{
	int real_size = SvvInternalUArray_GetSize(Receiver->data);
	Receiver->length++;
	SvvInternalUArray_ByteSetAt(Receiver->data, real_size, 0);
	SvvInternalUArray_CharSetAt(Receiver->data, real_size, Char);
};

SvvInternalAction(SvvInternalString, GetUArray, SvvInternalUArray)
{
	return SvvInternalUArray_Clone(Receiver->data);
};

SvvInternalAction(SvvInternalString, GetFirst, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver;
	if(Receiver->length == 0)
	{
		iterator->flags = FLAG_ITERATOR_END_REACHED | FLAG_ITERATOR_BEGIN_REACHED;
	} else {
		iterator->user_position = 0;
		iterator->real_position = 0;
	};
	return iterator;
};

SvvInternalAction(SvvInternalString, GetLast, SvvInternalStringIterator)
{
	SvvInternalStringIterator iterator = SvvInternalStringIterator_Create();
	iterator->object = Receiver;
	if(Receiver->length == 0)
	{
		iterator->flags = FLAG_ITERATOR_END_REACHED | FLAG_ITERATOR_BEGIN_REACHED;
	} else {
		iterator->real_position = SvvInternalUArray_GetSize(Receiver->data) - 1;
		iterator->real_position = SvvInternalUArray_CharGetBeginningFromPosition(Receiver->data, iterator->real_position);
		iterator->user_position = Receiver->length - 1;
	};
	return iterator;
};
