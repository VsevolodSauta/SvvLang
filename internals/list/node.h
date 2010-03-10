#pragma once

#include "internals/basics.h"

typedef struct SvvInternalListNode {
	struct SvvInternalListNode*	next;
	struct SvvInternalListNode*	prev;
	SvvInternalObject		data;
} *SvvInternalListNode;

SvvInternalCreator(SvvInternalListNode);
SvvInternalAction(SvvInternalListNode, Destroy, void);
