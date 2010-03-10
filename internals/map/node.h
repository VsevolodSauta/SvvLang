#pragma once

#include "internals/basics.h"

typedef struct SvvInternalMapNode {
	struct SvvInternalMapNode*	left;
	struct SvvInternalMapNode*	right;
	struct SvvInternalMapNode*	parent;
	SvvInternalObject		key;
	SvvInternalObject		value;
	int				flags;
} *SvvInternalMapNode;

SvvInternalCreator(SvvInternalMapNode);
SvvInternalAction(SvvInternalMapNode, Init, void, SvvInternalObject Key, SvvInternalObject Value);
SvvInternalAction(SvvInternalMapNode, GetNodeForKey, SvvInternalMapNode, SvvInternalObject Key);
SvvInternalAction(SvvInternalMapNode, Remove, void);
SvvInternalAction(SvvInternalMapNode, CleanSubTree, void);
SvvInternalAction(SvvInternalMapNode, DeInit, void);
SvvInternalAction(SvvInternalMapNode, Inited, int);
SvvInternalAction(SvvInternalMapNode, Destroy, void);
SvvInternalAction(SvvInternalMapNode, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalMapNode, GetValue, SvvInternalObject);
SvvInternalAction(SvvInternalMapNode, SetValue, void, SvvInternalObject Object);


