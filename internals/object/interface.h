#pragma once

#include "internals/actions.h"
#include "internals/char/interface.h"

typedef union {
	void*		ptr_data;
	long int	int_data;
	SvvInternalChar	char_data;
} SvvInternalObject;

#define LINK_AS_OBJECT(a) ((SvvInternalObject) (void*) (a))
#define INT_AS_OBJECT(a) ((SvvInternalObject) (long int) (a))
#define CHAR_AS_OBJECT(a) ((SvvInternalObject) (SvvInternalChar) (a))
#define OBJECT_AS_LINK(a) ((a).ptr_data)
#define OBJECT_AS_CHAR(a) ((a).char_data)
#define OBJECT_AS_INT(a) ((a).int_data)

SvvInternalAction(SvvInternalObject, Compare, int, SvvInternalObject Object);
