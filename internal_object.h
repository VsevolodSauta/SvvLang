#pragma once

#include "internal_char.h"
#include "internal_actions.h"

typedef union {
	void* ptr_data;
	int int_data;
	SvvInternalChar char_data;
} SvvInternalObject;

#define LINK_AS_OBJECT(a) ((SvvInternalObject) (void*) (a))
#define INT_AS_OBJECT(a) ((SvvInternalObject) (int) (a))
#define CHAR_AS_OBJECT(a) ((SvvInternalObject) (SvvInternalChar) (a))
#define OBJECT_AS_LINK(a) ((a).ptr_data)
#define OBJECT_AS_CHAR(a) ((a).char_data)
#define OBJECT_AS_INT(a) ((a).int_data)

#if 0
#warning sizeof(SvvInternalObject)
#warning sizeof(SvvInternalChar)
#warning sizeof(int)
#endif

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object);
