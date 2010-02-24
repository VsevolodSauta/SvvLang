#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "interanal_list.h"

typedef struct SvvInternalSetNode {
	struct SvvInternalSetNode*	left;
	struct SvvInternalSetNode*	right;
	struct SvvInternalSetNode*	parent;
	SvvInternalObject		data;
} *SvvInternalSetNode;

typedef struct SvvInternalSet {
	SvvInternalSetNode		root;
} *SvvInternalSet;

SvvInternalCreator(SvvInternalSetNode);

SvvInternalCreator(SvvInternalSet);
SvvInternalAction(SvvInternalSet, Destroy, void);
SvvInternalAction(SvvInternalSet, Add, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Remove, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, Exists, void, SvvInternalObject Object);
SvvInternalAction(SvvInternalSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalSet, AddList, void, SvvInternalList List);
