#pragma once

#include "internals/basics.h"
#include "internals/map/interface.h"
#include "internals/string/interface.h"

typedef struct SvvInternalStringSetNode {
	struct SvvInternalStringSetNode*	parent;
	SvvInternalMap				next_char;
	int					flags;
} *SvvInternalStringSetNode;

SvvInternalCreator(SvvInternalStringSetNode);
SvvInternalAction(SvvInternalStringSetNode, GetNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringSetNode, GetCreatingNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringSetNode, CleanSubTree, void);
SvvInternalAction(SvvInternalStringSetNode, IsSet, int);
SvvInternalAction(SvvInternalStringSetNode, Set, void);
SvvInternalAction(SvvInternalStringSetNode, UnSet, void);
SvvInternalAction(SvvInternalStringSetNode, Destroy, void);

