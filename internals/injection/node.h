#pragma once

#include "internals/basics.h"

typedef struct SvvInternalInjectionNode {
	struct SvvInternalInjectionNode*	left;
	struct SvvInternalInjectionNode*	right;
	struct SvvInternalInjectionNode*	parent;
	struct SvvInternalInjectionNode*	value;
	SvvInternalObject			key;
	int					flags;
} *SvvInternalInjectionNode;

SvvInternalCreator(SvvInternalInjectionNode);
SvvInternalAction(SvvInternalInjectionNode, Init, void, SvvInternalObject Key, SvvInternalInjectionNode Value);
SvvInternalAction(SvvInternalInjectionNode, GetNodeForKey, SvvInternalInjectionNode, SvvInternalObject Key);
SvvInternalAction(SvvInternalInjectionNode, Remove, void);
SvvInternalAction(SvvInternalInjectionNode, CleanSubTree, void);
SvvInternalAction(SvvInternalInjectionNode, DeInit, void);
SvvInternalAction(SvvInternalInjectionNode, Inited, int);
SvvInternalAction(SvvInternalInjectionNode, Destroy, void);
SvvInternalAction(SvvInternalInjectionNode, GetKey, SvvInternalObject);
SvvInternalAction(SvvInternalInjectionNode, GetValue, SvvInternalInjectionNode);
SvvInternalAction(SvvInternalInjectionNode, SetValue, void, SvvInternalInjectionNode Value);

