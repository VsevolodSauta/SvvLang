#pragma once

#include "internals/basics.h"
#include "internals/set/node.h"

#include "internals/stack/interface.h"
#include "internals/list/interface.h"

typedef struct SvvInternalSet {
	SvvInternalSetNode		root;
	int				capacity;
} *SvvInternalSet;

typedef struct SvvInternalSetIterator {
	SvvInternalStack		path;
	SvvInternalSetNode		node;
} *SvvInternalSetIterator;

SvvInternalCreator(SvvInternalSetIterator);
SvvInternalAction(SvvInternalSetIterator, GetNext, void);
SvvInternalAction(SvvInternalSetIterator, EndReached, int);
SvvInternalAction(SvvInternalSetIterator, GetData, SvvInternalObject);
SvvInternalAction(SvvInternalSetIterator, Destroy, void);
SvvInternalAction(SvvInternalSetIterator, Clone, SvvInternalSetIterator);
SvvInternalAction(SvvInternalSetIterator, AddCurrentNodeChildren, void);

SvvInternalCreator(SvvInternalSet);
SvvInternalAction(SvvInternalSet, Destroy, void);
SvvInternalAction(SvvInternalSet, Add, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Remove, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Clean, void);
SvvInternalAction(SvvInternalSet, Exists, int, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalSet, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalSet, GetIterator, SvvInternalSetIterator);
SvvInternalAction(SvvInternalSet, GetCapacity, int);
SvvInternalAction(SvvInternalSet, Dump, void);
