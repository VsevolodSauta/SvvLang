#pragma once

#include "internals/basics.h"
#include "internals/injection/node.h"

#include "internals/stack/interface.h"
#include "internals/list/interface.h"

typedef struct SvvInternalInjection {
	SvvInternalInjectionNode	root1, root2;
	int				capacity;
} *SvvInternalInjection;

typedef struct SvvInternalInjectionIterator {
	SvvInternalStack		path;
	SvvInternalInjectionNode	node;
} *SvvInternalInjectionIterator;

SvvInternalCreator(SvvInternalInjection);
SvvInternalAction(SvvInternalInjection, Destroy, void);
SvvInternalAction(SvvInternalInjection, Add, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalInjection, RemoveKey, void, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjection, RemoveValue, void, SvvInternalObject Value);
SvvInternalAction(SvvInternalInjection, Clean, void);
SvvInternalAction(SvvInternalInjection, ExistsKey, int, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjection, GetValue, SvvInternalObject, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjection, GetList, SvvInternalList);
SvvInternalAction(SvvInternalInjection, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalInjection, GetIterator, SvvInternalInjectionIterator);
SvvInternalAction(SvvInternalInjection, GetCapacity, int);

SvvInternalCreator(SvvInternalInjectionIterator);
SvvInternalAction(SvvInternalInjectionIterator, GetNext, void);
SvvInternalAction(SvvInternalInjectionIterator, EndReached, int);
SvvInternalAction(SvvInternalInjectionIterator, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalInjectionIterator, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalInjectionIterator, Destroy, void);
SvvInternalAction(SvvInternalInjectionIterator, Clone, SvvInternalInjectionIterator);
SvvInternalAction(SvvInternalInjectionIterator, AddCurrentNodeChildren, void);
SvvInternalAction(SvvInternalInjectionIterator, GetNode, SvvInternalInjectionNode);
