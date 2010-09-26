#pragma once

#include "internals/basics.h"
#include "internals/injection/interface.h"
#include "internals/string/interface.h"

typedef struct SvvInternalStringMapNode {
	struct SvvInternalStringMapNode*	parent;
	SvvInternalInjection			next_char;
	SvvInternalObject			value;
	int					flags;
} *SvvInternalStringMapNode;

SvvInternalCreator(SvvInternalStringMapNode);
SvvInternalAction(SvvInternalStringMapNode, GetNodeForData, SvvInternalStringMapNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringMapNode, GetCreatingNodeForData, SvvInternalStringMapNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringMapNode, CleanSubTree, void);
SvvInternalAction(SvvInternalStringMapNode, IsMapped, int);
SvvInternalAction(SvvInternalStringMapNode, Map, void, SvvInternalObject Value);
SvvInternalAction(SvvInternalStringMapNode, UnMap, void);
SvvInternalAction(SvvInternalStringMapNode, Destroy, void);
SvvInternalAction(SvvInternalStringMapNode, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalStringMapNode, SetValue, void, SvvInternalObject Object);
