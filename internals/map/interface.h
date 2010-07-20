#pragma once

#include "internals/basics.h"
#include "internals/map/node.h"

#include "internals/stack/interface.h"
#include "internals/list/interface.h"

typedef struct SvvInternalMap {
	SvvInternalMapNode		root;
	int				capacity;
} *SvvInternalMap;

typedef struct SvvInternalMapIterator {
	SvvInternalStack		path;
	SvvInternalMapNode		node;
} *SvvInternalMapIterator;

SvvInternalCreator(SvvInternalMap);
SvvInternalAction(SvvInternalMap, Destroy, void);
SvvInternalAction(SvvInternalMap, Add, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalMap, RemoveKey, void, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, Clean, void);
SvvInternalAction(SvvInternalMap, ExistsKey, int, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, GetValue, SvvInternalObject, SvvInternalObject Key);
SvvInternalAction(SvvInternalMap, GetList, SvvInternalList);
SvvInternalAction(SvvInternalMap, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalMap, GetIterator, SvvInternalMapIterator);
SvvInternalAction(SvvInternalMap, GetCapacity, int);

SvvInternalCreator(SvvInternalMapIterator);
SvvInternalAction(SvvInternalMapIterator, GetNext, void);
SvvInternalAction(SvvInternalMapIterator, EndReached, int);
SvvInternalAction(SvvInternalMapIterator, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalMapIterator, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalMapIterator, Destroy, void);
SvvInternalAction(SvvInternalMapIterator, Clone, SvvInternalMapIterator);
SvvInternalAction(SvvInternalMapIterator, AddCurrentNodeChildren, void);
SvvInternalAction(SvvInternalMapIterator, GetNode, SvvInternalMapNode);

