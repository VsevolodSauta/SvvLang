#include "internals/basics.h"
#include "internals/string_on_uarray/interface.h"
#include "internals/char/interface.h"

SvvInternalCreator(SvvInternalStringIterator)
{
	return OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalStringIterator)));
};

SvvInternalAction(SvvInternalStringIterator, EndReached, int)
{
	return Receiver->flags & FLAG_ITERATOR_END_REACHED;
};

SvvInternalAction(SvvInternalStringIterator, BeginReached, int)
{
	return Receiver->flags & FLAG_ITERATOR_BEGIN_REACHED;
};

SvvInternalAction(SvvInternalStringIterator, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalStringIterator, GetNext, void)
{
	// Next exists.
	if(Receiver->flags & FLAG_ITERATOR_BEGIN_REACHED)
	{
		Receiver->user_position = 0;
		Receiver->real_position = 0;
		Receiver->flags &= ~FLAG_ITERATOR_BEGIN_REACHED;
	} else {
		if(Receiver->real_position == Receiver->object->length)
		{
			Receiver->flags |= FLAG_ITERATOR_END_REACHED;
		} else {
			Receiver->user_position++;
			Receiver->real_position += char_GetLengthInBytes(SvvInternalUArray_ByteGetAt(Receiver->object->data, Receiver->real_position));
		};
	};
};

SvvInternalAction(SvvInternalStringIterator, GetPrev, void)
{
	// Previous exists.
	if(Receiver->flags & FLAG_ITERATOR_END_REACHED)
	{
		Receiver->user_position = Receiver->object->length - 1;
		Receiver->real_position = SvvInternalUArray_CharGetBeginningFromPosition(Receiver->object->data, 
							SvvInternalUArray_GetSize(Receiver->object->data) - 1);
		Receiver->flags &= ~FLAG_ITERATOR_END_REACHED;
	} else {
		if(Receiver->user_position == 0)
		{
			Receiver->flags |= FLAG_ITERATOR_BEGIN_REACHED;
		} else {
			Receiver->user_position--;
			Receiver->real_position = SvvInternalUArray_CharGetBeginningFromPosition(Receiver->object->data, Receiver->real_position - 1);
			Receiver->real_position += char_GetLengthInBytes(SvvInternalUArray_ByteGetAt(Receiver->object->data, Receiver->real_position));
		};
	};
};

SvvInternalAction(SvvInternalStringIterator, GetString, SvvInternalString)
{
	return Receiver->object;
};

SvvInternalAction(SvvInternalStringIterator, CharGet, SvvInternalChar)
{
	return SvvInternalUArray_CharGetAt(Receiver->object->data, Receiver->real_position);
};

SvvInternalAction(SvvInternalStringIterator, CharSet, void, SvvInternalChar Char)
{
	SvvInternalUArray_CharSetAt(Receiver->object->data, Receiver->real_position, Char);
};

SvvInternalAction(SvvInternalStringIterator, GetPosition, int)
{
	return Receiver->user_position;
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
	iterator->user_position = Receiver->user_position;
	iterator->real_position = Receiver->real_position;
	return iterator;
};

