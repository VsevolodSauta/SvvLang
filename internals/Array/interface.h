#pragma once

#include "internals/Object/interface.h"

typedef struct Array {
	long		size;
	Object		*data;
} *Array;

Object Array_Create();
Object Array_Compare(Object receiver, Object array);
Object Array_Clone(Object receiver);
Object Array_Destroy(Object receiver);

Object Array_SetSize(Object receiver, Object size);
Object Array_GetAt(Object receiver, Object position);
Object Array_PutAt(Object receiver, Object object, Object position);
