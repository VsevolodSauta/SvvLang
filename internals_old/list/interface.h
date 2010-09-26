#pragma once

#include "internals/actions.h"
#include "internals/object/interface.h"

typedef struct List {
	Object		head;
	Object		tail;
	Object		iterator;
} *List;

typedef struct ListIterator {
	Object		node;
	Object		list;
} *ListIterator;

Action(ListIterator, ToBegin); // O(1)
Action(ListIterator, ToEnd); // O(1)
Action(ListIterator, Hide); // O(1)
Action(ListIterator, Next); // O(1)
Action(ListIterator, Prev); // O(1)
Action(ListIterator, ToPosition, Object position); // O(n)
Action(ListIterator, FromPositionToPosition, Object positionFrom, Object positionTo); // O(n)
Action(ListIterator, ThisBegin); // O(1)
Action(ListIterator, PrevBegin); // O(1)
Action(ListIterator, ThisEnd); // O(1)
Action(ListIterator, NextEnd); // O(1)

Action(ListIterator, ThisData); // O(1)
Action(ListIterator, PrevData); // O(1)
Action(ListIterator, NextData); // O(1)

Action(ListIterator, ThisSetData, Object object); // O(1)
Action(ListIterator, PrevSetData, Object object); // O(1)
Action(ListIterator, NextSetData, Object object); // O(1)

Action(ListIterator, SearchFirst, Object object); // O(n)
Action(ListIterator, SearchFirstPosition, Object object); // O(n)
Action(ListIterator, ThisRemove); // O(1)
Action(ListIterator, NextRemove); // O(1)
Action(ListIterator, PrevRemove); // O(1)
Action(ListIterator, Clone); // O(1)
Action(ListIterator, AddAfter, Object object); // O(1)
Action(ListIterator, AddBefore, Object object); // O(1)
Action(ListIterator, Compare, Object iterator);
Action(ListIterator, AddListBefore, Object list); // O(n)
Action(ListIterator, AddListAfter, Object list); // O(n)
Action(ListIterator, RemoveCount, Object count);

Action(ListIterator, InitWithListAndNode, Object list, Object node);
Creator(ListIterator); // O(1)

Creator(List); // O(1)
Action(List, PushBack, Object object); // O(1)
Action(List, PushFront, Object object); // O(1)
Action(List, AddAfterPosition, Object position, Object object); // O(n)
Action(List, RemoveFirst, Object Object); // O(n)
Action(List, SublistBetweenPositions, Object positionFrom, Object positionTo); // O(n)
Action(List, Clean);
Action(List, Clone);
Action(List, Sort);
Action(List, Dump);
Action(List, Size);
Action(List, DataFromPosition, Object position);
Action(List, Concatenate, Object list);

Action(List, Last); // O(1)
Action(List, IteratorFromPosition, Object position); // O(n)
Action(List, CreatingIteratorFromPosition, Object position); // O(n)
Action(List, First); // O(1)
Action(List, Search, Object object); // O(n)
Action(List, SearchPositions, Object object); // O(n)
Action(List, SublistBetweenIterators, Object positionFrom, Object positionTo); // O(n)
