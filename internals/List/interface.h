typedef struct List {
	Object _iterator;
	Object _head;
	Object _tail;
} *List;

Object List_Create(void);
Object List_Init(Object _self);
Object List_Destroy(Object _self);
Object List_Clone(Object _self);
Object List_DeepClone(Object _self);
Object List_Compare(Object _self, Object _list);
Object List_Clean(Object _self);
Object List_PushFront(Object _self, Object _object);
Object List_PushBack(Object _self, Object _object);
Object List_PushSorted(Object _self, Object _object);
Object List_PeekFront(Object _self);
Object List_PeekBack(Object _self);
Object List_PopFront(Object _self);
Object List_PopBack(Object _self);
Object List_RemoveFront(Object _self);
Object List_RemoveBack(Object _self);
Object List_AddAfterPosition(Object _self, Object _position, Object _object);
Object List_AddBeforePosition(Object _self, Object _position, Object _object);
Object List_ObjectAtPosition(Object _self, Object _position);
Object List_ObjectAtPositionIfExists(Object _self, Object _position);
Object List_RemoveObjectAtPosition(Object _self, Object _position);
Object List_ReplaceAtPositionWithObject(Object _self, Object _position, Object _object);
Object List_Contains(Object _self, Object _object);
Object List_RemoveFirst(Object _self, Object _object);
Object List_RemoveFirstWithConfirmation(Object _self, Object _object);
Object List_RemoveLast(Object _self, Object _object);
Object List_RemoveLastWithConfirmation(Object _self, Object _object);
Object List_RemoveEvery(Object _self, Object _object);
Object List_RemoveEveryWithConfirmation(Object _self, Object _object);
Object List_Last(Object _self);
Object List_First(Object _self);
Object List_SystemIterator(Object _self);
Object List_ListMapAtPosition(Object _self, Object _position);
Object List_Search(Object _self, Object _object);
Object List_IteratorFromPosition(Object _self, Object _position);
Object List_CreatingIteratorFromPosition(Object _self, Object _position);
Object List_SearchPositions(Object _self, Object _object);
Object List_SublistBetweenPositions(Object _self, Object _positionFrom, Object _positionTo);
Object List_SublistBetweenIterators(Object _self, Object _positionFrom, Object _positionTo);
Object List_Size(Object _self);
Object List_Empty(Object _self);
Object List_Concatenate(Object _self, Object _list);
Object List_SortInPlace(Object _self);
Object List_PrintLn(Object _self);
