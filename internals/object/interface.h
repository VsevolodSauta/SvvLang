#pragma once

#include "internals/actions.h"
#include "internals/char/interface.h"

#define OBJECT_ID_NOTHING 0
#define OBJECT_ID_LINK 1
#define OBJECT_ID_INT 2
#define OBJECT_ID_CHAR 4


typedef struct {
	long			id;
	union {
		void*		ptr_data;
		long int	int_data;
		SvvInternalChar	char_data;
	};
} SvvInternalObject;

inline static SvvInternalObject LINK_AS_OBJECT(void* Link) 
{
	SvvInternalObject to_return;
	
	to_return.id = OBJECT_ID_LINK;
	to_return.ptr_data = Link;
	
	return to_return;
};

inline static SvvInternalObject INT_AS_OBJECT(long int Integer)
{
	SvvInternalObject to_return;
	
	to_return.id = OBJECT_ID_INT;
	to_return.int_data = Integer;
	
	return to_return;
};

inline static SvvInternalObject CHAR_AS_OBJECT(SvvInternalChar Char)
{
	SvvInternalObject to_return;
	
	to_return.id = OBJECT_ID_CHAR;
	to_return.char_data = Char;
	
	return to_return;
};

inline static void* OBJECT_AS_LINK(SvvInternalObject Object)
{
	return Object.ptr_data;
};

inline static long int OBJECT_AS_INT(SvvInternalObject Object)
{
	return Object.int_data;
};

inline static SvvInternalChar OBJECT_AS_CHAR(SvvInternalObject Object)
{
	return Object.char_data;
};

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object);
