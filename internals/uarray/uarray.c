#include "internals/basics.h"
#include "internals/uarray/interface.h"
#include "internals/uarray/utility.h"
#include <string.h>

SvvInternalCreator(SvvInternalUArray)
{
	SvvInternalUArray array = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(struct SvvInternalUArray)));
	array->size = 0;
	array->data = OBJECT_AS_LINK(SvvInternalNothing);
	SvvInternalUArray_Shrink(array);
	return array;
};

SvvInternalAction(SvvInternalUArray, Destroy, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver->data));
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalUArray, ByteGetAt, char, int Position)
{
	return *BYTE_PTR(Receiver, Position);
};

SvvInternalAction(SvvInternalUArray, ByteSetAt, void, int Position, char Byte)
{
	SvvInternalUArray_SetSizeToContain(Receiver, Position * sizeof(char));
	*BYTE_PTR(Receiver, Position) = Byte;
};
SvvInternalAction(SvvInternalUArray, ByteShiftRightFromBy, void, int Position, int Quantity)
{
	SvvInternalUArray_SetSize(Receiver, (Receiver->size + Quantity) * sizeof(char));
	memmove(BYTE_PTR(Receiver, Position + Quantity), BYTE_PTR(Receiver, Position), (Receiver->size - Position) * sizeof(char));
};


SvvInternalAction(SvvInternalUArray, ByteShiftLeftFromBy, void, int Position, int Quantity)
{
	memmove(BYTE_PTR(Receiver, Position - Quantity), BYTE_PTR(Receiver, Position), (Receiver->size - Position) * sizeof(char));
};

SvvInternalAction(SvvInternalUArray, ByteGetSubArrayBetweenPositions, SvvInternalUArray, int PositionFrom, int PositionTo)
{
	SvvInternalUArray array = SvvInternalUArray_Create();
	SvvInternalUArray_SetSize(array, (PositionTo - PositionFrom) * sizeof(char));
	memcpy(BYTE_PTR(array, 0), BYTE_PTR(Receiver, PositionFrom), (PositionTo - PositionFrom) * sizeof(char));
	return array;
};

SvvInternalAction(SvvInternalUArray, CharGetAt, SvvInternalChar, int Position)
{
	// Position points to char beginning.
	SvvInternalChar char_to_return;
	int char_length = char_GetLengthInBytes(*BYTE_PTR(Receiver, Position));
	int i;
	for(i = 0; i < char_length; i++)
	{
		char_to_return.bytes[i] = *BYTE_PTR(Receiver, Position + i);
	};
	return char_to_return;
};

SvvInternalAction(SvvInternalUArray, CharSetAt, void, int Position, SvvInternalChar Char)
{
	int current_char_length = char_GetLengthInBytes(*BYTE_PTR(Receiver, Position));
	int setting_char_length = char_GetLengthInBytes(Char.bytes[0]);
	int i;
	
	if(current_char_length != setting_char_length)
		SvvInternalUArray_ByteShiftRightFromBy(Receiver, Position + current_char_length, setting_char_length - current_char_length);
	
	for(i = 0; i < setting_char_length; i++)
	{
		SvvInternalUArray_ByteSetAt(Receiver, Position + i, Char.bytes[i]);
	};
};

SvvInternalAction(SvvInternalUArray, CharGetBeginningFromPosition, int, int Position)
{
	while(char_GetLengthInBytes(*BYTE_PTR(Receiver, Position)) == 0)
	{
		Position--;
	};
	return Position;
};

SvvInternalAction(SvvInternalUArray, Clean, void)
{
	SvvInternalUArray_SetSize(Receiver, 0);
};

SvvInternalAction(SvvInternalUArray, Clone, SvvInternalUArray)
{
	SvvInternalUArray array = SvvInternalUArray_Create();
	SvvInternalUArray_SetSize(array, Receiver->size);
	memcpy(array->data, Receiver->data, Receiver->size);
	return array;
};

SvvInternalAction(SvvInternalUArray, Concatenate, void, SvvInternalUArray UArray)
{
	int prev_size = Receiver->size;
	SvvInternalUArray_SetSize(Receiver, Receiver->size + UArray->size);
	memcpy(BYTE_PTR(Receiver, prev_size), BYTE_PTR(UArray, 0), UArray->size);
};

SvvInternalAction(SvvInternalUArray, Sort, void)
{
	// Not implemented yet!
};

SvvInternalAction(SvvInternalUArray, Compare, int, SvvInternalUArray Array)
{
	int comparation_result = memcmp(Receiver->data, Array->data, min(Receiver->size, Array->size));
	if(comparation_result)
	{
		return comparation_result;
	} else {
		return (Receiver->size >= Array->size) - (Array->size >= Receiver->size);
	};
};

SvvInternalAction(SvvInternalUArray, SetSize, void, int Size)
{
	Receiver->size = Size;
	SvvInternalUArray_Shrink(Receiver);
};

SvvInternalAction(SvvInternalUArray, GetSize, int)
{
	return Receiver->size;
};

SvvInternalAction(SvvInternalUArray, SetSizeToContain, void, int Position)
{
	if(Position >= Receiver->size)
	{
		SvvInternalUArray_SetSize(Receiver, Position + 1);
	};
};

SvvInternalAction(SvvInternalUArray, ByteDump, void)
{
	int i;
	for(i = 0; i < Receiver->size; i++)
	{
		DEBUG("%c", *BYTE_PTR(Receiver, i));
	};
	DEBUG("\n");
};

SvvInternalAction(SvvInternalUArray, GetBuffer, void*)
{
	void* to_return = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, Receiver->size));
	memcpy(to_return, Receiver->data, Receiver->size);
	return to_return;
};