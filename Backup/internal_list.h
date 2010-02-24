#pragma once

#include "internal_actions.h"
#include "internal_object.h"

typedef struct SvvInternalList {
	struct SvvInternalList*	next;
	struct SvvInternalList*	prev;
	struct SvvInternalList* tail;
	struct SvvInternalList* tail;
	SvvInternalObject	data;
} *SvvInternalList;

typedef struct {
	SvvInternalList data;
	SvvInternalList head;
} *SvvInternalListIterator;

SvvInternalCreator(SvvInternalList); // O(1)
SvvInternalAction(SvvInternalList, Destroy, void); // O(n)
SvvInternalAction(SvvInternalList, Append, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, AddAfterPosition, void, int Position, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, RemoveFirst, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetLast, SvvInternalListIterator); // O(n)
SvvInternalAction(SvvInternalList, GetIteratorFromNumber, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, GetCreatingIteratorFromNumber, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, GetIterator, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalList, Search, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, SearchNumbers, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int Position1, int Position2);
SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator Position1, SvvInternalListIterator Position2);

SvvInternalAction(SvvInternalListIterator, GetNext, void); // O(1)
SvvInternalAction(SvvInternalListIterator, GetPrev, void); // O(1)
SvvInternalAction(SvvInternalListIterator, ToPosition, void, int Position); // O(n)
SvvInternalAction(SvvInternalListIterator, BeginReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, EndReached, int); // O(1)
SvvInternalAction(SvvInternalListIterator, GetData, SvvInternalObject); // O(1)
SvvInternalAction(SvvInternalListIterator, SetData, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, SearchFirst, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalListIterator, SearchFirstNumber, int, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalListIterator, Remove, void); // O(1)
SvvInternalAction(SvvInternalListIterator, Destroy, void); // O(1)
SvvInternalAction(SvvInternalListIterator, Clone, SvvInternalListIterator); // O(1)
SvvInternalAction(SvvInternalListIterator, AddAfter, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, AddBefore, void, SvvInternalObject Object); // O(1)
SvvInternalAction(SvvInternalListIterator, Compare, int, SvvInternalListIterator Iterator);
SvvInternalCreator(SvvInternalListIterator); // O(1)
