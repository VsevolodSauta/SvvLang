#pragma once

#include "internal_actions.h"
#include "internal_object.h"

typedef struct SvvInternalListNode {
	struct SvvInternalListNode*	next;
	struct SvvInternalListNode*	prev;
	SvvInternalObject		data;
} *SvvInternalListNode;

typedef struct SvvInternalList {
	SvvInternalListNode		head;
	SvvInternalListNode		tail;
} *SvvInternalList;

typedef struct SvvInternalListIterator {
	SvvInternalListNode	data;
	SvvInternalList		list;
} *SvvInternalListIterator;

SvvInternalCreator(SvvInternalListNode);
SvvInternalAction(SvvInternalListNode, Destroy, void);

SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
SvvInternalAction(SvvInternalList, PushBack, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, PushFront, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalList, AddAfterPosition, void, int Position, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, RemoveFirst, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, GetIteratorFromPosition, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, GetCreatingIteratorFromPosition, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, GetFirst, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, Search, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, SearchPositions, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int PositionFrom, int PositionTo); // O(n)
SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator PositionFrom, SvvInternalListIterator PositionTo); // O(n)
SvvInternalAction(SvvInternalList, Clean, void);
SvvInternalAction(SvvInternalList, Clone, SvvInternalList);

SvvInternalAction(SvvInternalListIterator, GetNext, void); // O(1)
SvvInternalAction(SvvInternalListIterator, GetPrev, void); // O(1)
SvvInternalAction(SvvInternalListIterator, ToPosition, void, int Position); // O(n)
SvvInternalAction(SvvInternalListIterator, FromPositionToPosition, void, int PositionFrom, int PositionTo); // O(n)
SvvInternalAction(SvvInternalListIterator, BeginReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, EndReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, GetData, SvvInternalObject); // O(1)
SvvInternalAction(SvvInternalListIterator, SetData, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, SearchFirst, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalListIterator, SearchFirstPosition, int, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalListIterator, Remove, void); // O(1)
SvvInternalAction(SvvInternalListIterator, Destroy, void); // O(1)
SvvInternalAction(SvvInternalListIterator, Clone, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalListIterator, AddAfter, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, AddBefore, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, Compare, int, SvvInternalListIterator Iterator);
SvvInternalAction(SvvInternalListIterator, AddListBefore, void, SvvInternalList list); // O(n)
SvvInternalAction(SvvInternalListIterator, AddListAfter, void, SvvInternalList list); // O(n)
SvvInternalAction(SvvInternalListIterator, RemoveCount, void, int Count);
SvvInternalCreator(SvvInternalListIterator); // O(1)
