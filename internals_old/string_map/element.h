#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"
#include "internals/string_map/node.h"


typedef struct SvvInternalStringMapIteratorElement {
	SvvInternalString		string;
	SvvInternalStringMapNode	node;
} *SvvInternalStringMapIteratorElement;

SvvInternalCreator(SvvInternalStringMapIteratorElement);
SvvInternalAction(SvvInternalStringMapIteratorElement, Destroy, void);
SvvInternalAction(SvvInternalStringMapIteratorElement, Clone, SvvInternalStringMapIteratorElement);

