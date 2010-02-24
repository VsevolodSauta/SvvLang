#include "internal_config.h"
#include "internal_actions.h"
#include "internal_string.h"
#include "internal_char.h"
#include "internal_allocator.h"
#include "internal_globals.h"
#include "internal_mmu.h"

SvvInternalCreator(SvvInternalString)
{
	SvvInternalString string = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, sizeof(SvvInternalString*)));
	string->data = OBJECT_AS_LINK(SvvInternalAllocator_New(SvvDefaultAllocator, 1 << CONFIG_INTERNAL_STRING_GRANULARITY));
	string->data[0] = 0;
	string->length = 0;
	string->size = 1 << CONFIG_INTERNAL_STRING_GRANULARITY;
	string->actual_size = 1;
	return string;
};

SvvInternalAction(SvvInternalString, Delete, void)
{
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver->data));
	SvvInternalAllocator_Delete(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver));
};

SvvInternalAction(SvvInternalString, Concatenate, void, SvvInternalString String)
{
	SvvInternalString_SetSize(Receiver, String->actual_size + Receiver->actual_size);
	SvvInternalMMU_Copy(SvvDefaultMMU, LINK_AS_OBJECT(Receiver->data + Receiver->actual_size), LINK_AS_OBJECT(String->data), String->actual_size);
};

SvvInternalAction(SvvInternalString, GetAt, SvvInternalChar, int Position)
{
	SvvInternalChar ch;
	int position = get_position_from_symbol_number(Position);
	
	SvvInternalMMU_Copy(SvvDefaultMMU, CHAR_AS_OBJECT(ch), LINK_AS_OBJECT(Receiver->data + position), 
		SvvInternalChar_LengthInBytes(SvvInternalChar_CharFromPtr(SvvInternalNothing.char_data, Receiver->data + position)));
	
	return ch;
};

SvvInternalAction(SvvInternalString, SubString, SvvInternalString, int Position1, int Position2)
{
	SvvInternalString string = SvvInternalString_Create(SvvInternalNothing);
// TODO: Optimization.
	string->length = Position2 - Position1 + 1;
	Position1 = get_position_from_symbol_number(Position1);
	Position2 = get_position_from_symbol_number(Position2 + 1);
	SvvInternalString_SetSize(string, Position2 - Position1 + 1);
	
	string->actual_size = Position2 - Position1 + 1;
	SvvInternalMMU_Copy(SvvDefaultMMU, LINK_AS_OBJECT(string->data), LINK_AS_OBJECT(Receiver->data + Position1), Position2 - Position1);
	string->data[string->actual_size] = 0;
	
	return string;
};

SvvInternalAction(SvvInternalString, Remove, void, int Position1, int Position2)
{
// TODO: Optimization.
	Position2++;
	Receiver->length -= Position2 - Position1;
	Position1 = get_position_from_symbol_number(Position1);
	Position2 = get_position_from_symbol_number(Position2);
	SvvInternalMMU_Copy(SvvDefaultMMU, LINK_AS_OBJECT(Receiver->data + Position1), LINK_AS_OBJECT(Receiver->data + Position2), 
		Receiver->actual_size - Position2);
	
	Receiver->actual_size -= Position2 - Position1;
};

SvvInternalAction(SvvInternalString, GetLength, int)
{
	return Receiver->length;
};

SvvInternalAction(SvvInternalString, SetSize, void, int Size)
{
	if(Receiver->size < Size)
	{
		Receiver->size = ((Size + 15) >> CONFIG_INTERNAL_STRING_GRANULARITY) << CONFIG_INTERNAL_STRING_GRANULARITY;
		SvvInternalAllocator_Resize(SvvDefaultAllocator, LINK_AS_OBJECT(Receiver->data), Receiver->size);
	};
};

// Utils

int get_position_from_symbol_number(SvvInternalString Receiver, int Position)
{
	int position = 0, symbols = 0;
	while(symbols < Position)
	{
		position += SvvInternalChar_LengthInBytes(SvvInternalChar_CharFromPtr(SvvInternalNothing.char_data, Receiver->data + position));
		symbols++;
	};
	
	return position;
};
