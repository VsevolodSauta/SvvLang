#pragma once

#include "internals/basics.h"
#include "internals/string_map/element.h"

#include "internals/list/interface.h"
#include "internals/string/interface.h"
#include "internals/stack/interface.h"

typedef struct SvvInternalStringMap {
	SvvInternalStringMapNode	root;
	int				capacity;
} *SvvInternalStringMap;

typedef struct SvvInternalStringMapIterator {
	SvvInternalStack				path;
	SvvInternalStringMapIteratorElement		element;
} *SvvInternalStringMapIterator;

SvvInternalCreator(SvvInternalStringMap);
SvvInternalAction(SvvInternalStringMap, Destroy, void);
SvvInternalAction(SvvInternalStringMap, Add, void, SvvInternalString Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalStringMap, RemoveKey, void, SvvInternalString Key);
SvvInternalAction(SvvInternalStringMap, Clean, void);
SvvInternalAction(SvvInternalStringMap, ExistsKey, int, SvvInternalString Key);
SvvInternalAction(SvvInternalStringMap, GetValue, SvvInternalObject, SvvInternalString Key);
SvvInternalAction(SvvInternalStringMap, GetList, SvvInternalList);
SvvInternalAction(SvvInternalStringMap, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalStringMap, GetIterator, SvvInternalStringMapIterator);
SvvInternalAction(SvvInternalStringMap, GetCapacity, int);

SvvInternalCreator(SvvInternalStringMapIterator);
SvvInternalAction(SvvInternalStringMapIterator, GetNext, void);
SvvInternalAction(SvvInternalStringMapIterator, EndReached, int);
SvvInternalAction(SvvInternalStringMapIterator, GetKey, SvvInternalString);
SvvInternalAction(SvvInternalStringMapIterator, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalStringMapIterator, Destroy, void);
SvvInternalAction(SvvInternalStringMapIterator, Clone, SvvInternalStringMapIterator);
