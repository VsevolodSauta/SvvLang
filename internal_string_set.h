#pragma once

#include "internal_actions.h"
#include "internal_object.h"
#include "internal_stack.h"
#include "internal_list.h"
#include "internal_map.h"
#include "internal_string.h"

typedef struct SvvInternalStringSetNode {
	struct SvvInternalStringSetNode*	parent;
	SvvInternalMap				next_char;
	int					flags;
} *SvvInternalStringSetNode;

typedef struct SvvInternalStringSet {
	SvvInternalStringSetNode	root;
} *SvvInternalStringSet;

typedef struct SvvInternalStringSetIteratorPathElement {
	SvvInternalString		string;
	SvvInternalStringSetNode	node;
} *SvvInternalStringSetIteratorPathElement;

typedef struct SvvInternalStringSetIterator {
	SvvInternalStack				path;
	SvvInternalStringSetIteratorPathElement		element;
} *SvvInternalStringSetIterator;


SvvInternalCreator(SvvInternalStringSetNode);
SvvInternalAction(SvvInternalStringSetNode, GetNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringSetNode, GetCreatingNodeForData, SvvInternalStringSetNode, SvvInternalStringIterator Iterator);
SvvInternalAction(SvvInternalStringSetNode, CleanSubTree, void);
SvvInternalAction(SvvInternalStringSetNode, IsSet, int);
SvvInternalAction(SvvInternalStringSetNode, Set, void);
SvvInternalAction(SvvInternalStringSetNode, UnSet, void);
SvvInternalAction(SvvInternalStringSetNode, Destroy, void);

SvvInternalCreator(SvvInternalStringSetIteratorPathElement);
SvvInternalAction(SvvInternalStringSetIteratorPathElement, Destroy, void);
SvvInternalAction(SvvInternalStringSetIteratorPathElement, Clone, SvvInternalStringSetIteratorPathElement);

SvvInternalCreator(SvvInternalStringSetIterator);
SvvInternalAction(SvvInternalStringSetIterator, GetNext, void);
SvvInternalAction(SvvInternalStringSetIterator, EndReached, int);
SvvInternalAction(SvvInternalStringSetIterator, GetData, SvvInternalString);
SvvInternalAction(SvvInternalStringSetIterator, Destroy, void);
SvvInternalAction(SvvInternalStringSetIterator, Clone, SvvInternalStringSetIterator);

SvvInternalCreator(SvvInternalStringSet);
SvvInternalAction(SvvInternalStringSet, Destroy, void);
SvvInternalAction(SvvInternalStringSet, Add, void, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, Remove, void, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, Clean, void);
SvvInternalAction(SvvInternalStringSet, Exists, int, SvvInternalString String);
SvvInternalAction(SvvInternalStringSet, GetList, SvvInternalList);
SvvInternalAction(SvvInternalStringSet, AddList, void, SvvInternalList List);
SvvInternalAction(SvvInternalStringSet, GetIterator, SvvInternalStringSetIterator);
