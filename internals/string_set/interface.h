#pragma once

#include "internals/basics.h"
#include "internals/string_set/element.h"

#include "internals/list/interface.h"
#include "internals/string/interface.h"
#include "internals/stack/interface.h"

typedef struct SvvInternalStringSet {
	SvvInternalStringSetNode	root;
} *SvvInternalStringSet;

typedef struct SvvInternalStringSetIterator {
	SvvInternalStack				path;
	SvvInternalStringSetIteratorElement		element;
} *SvvInternalStringSetIterator;

SvvInternalCreator(SvvInternalStringSet);
SvvInternalAction(SvvInternalStringSet, Destroy, void);
SvvInternalAction(SvvInternalStringSet, Add, void, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, Remove, void, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, Clean, void);
SvvInternalAction(SvvInternalStringSet, Exists, int, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalStringSet, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalStringSet, GetIterator, SvvInternalStringSetIterator);

SvvInternalCreator(SvvInternalStringSetIterator);
SvvInternalAction(SvvInternalStringSetIterator, GetNext, void);
SvvInternalAction(SvvInternalStringSetIterator, EndReached, int);
SvvInternalAction(SvvInternalStringSetIterator, GetData, SvvInternalString);
SvvInternalAction(SvvInternalStringSetIterator, Destroy, void);
SvvInternalAction(SvvInternalStringSetIterator, Clone, SvvInternalStringSetIterator);

