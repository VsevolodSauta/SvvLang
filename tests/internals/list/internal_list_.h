#include "internal_list.h"
#include "internal_object.h"

SvvInternalAction(SvvInternalList, AddAfterPosition, void, int Position, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, RemoveFirst, void, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetIteratorFromPosition, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, GetCreatingIteratorFromPosition, SvvInternalListIterator, int Position); // O(n)
SvvInternalAction(SvvInternalList, Search, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, SearchPositions, SvvInternalList, SvvInternalObject Object); // O(n)
SvvInternalAction(SvvInternalList, GetSublistBetweenPositions, SvvInternalList, int PositionFrom, int PositionTo); // O(n)
SvvInternalAction(SvvInternalList, GetSublistBetweenIterators, SvvInternalList, SvvInternalListIterator PositionFrom, SvvInternalListIterator PositionTo); // O(n)
SvvInternalAction(SvvInternalList, Clean, void);
SvvInternalAction(SvvInternalList, Clone, SvvInternalList);

SvvInternalAction(SvvInternalListIterator, ToPosition, void, int Position); // O(n)
SvvInternalAction(SvvInternalListIterator, FromPositionToPosition, void, int PositionFrom, int PositionTo); // O(n)
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
