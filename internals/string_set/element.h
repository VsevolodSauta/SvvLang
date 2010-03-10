#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"
#include "internals/string_set/node.h"


typedef struct SvvInternalStringSetIteratorElement {
	SvvInternalString		string;
	SvvInternalStringSetNode	node;
} *SvvInternalStringSetIteratorElement;

SvvInternalCreator(SvvInternalStringSetIteratorElement);
SvvInternalAction(SvvInternalStringSetIteratorElement, Destroy, void);
SvvInternalAction(SvvInternalStringSetIteratorElement, Clone, SvvInternalStringSetIteratorElement);

