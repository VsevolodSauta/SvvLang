#pragma once

#include "internals/basics.h"

typedef struct SvvInternalSetNode {
	struct SvvInternalSetNode*	left;
	struct SvvInternalSetNode*	right;
	struct SvvInternalSetNode*	parent;
	SvvInternalObject		data;
	int				flags;
} *SvvInternalSetNode;

SvvInternalCreator(SvvInternalSetNode);
SvvInternalAction(SvvInternalSetNode, Init, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSetNode, GetNodeForData, SvvInternalSetNode, SvvInternalObject Object);
SvvInternalAction(SvvInternalSetNode, Remove, void);
SvvInternalAction(SvvInternalSetNode, CleanSubTree, void);
SvvInternalAction(SvvInternalSetNode, DeInit, void);
SvvInternalAction(SvvInternalSetNode, Inited, int);
SvvInternalAction(SvvInternalSetNode, Destroy, void);
SvvInternalAction(SvvInternalSetNode, GetData, SvvInternalObject);

