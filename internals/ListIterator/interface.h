typedef struct ListIterator {
	Object _list;
	Object _node;
	Object _system;
} *ListIterator;

Object ListIterator_Create(void);
Object ListIterator_Compare(Object _self, Object _iterator);
Object ListIterator_Destroy(Object _self);
Object ListIterator_Clone(Object _self);
Object ListIterator_InitWithListAndNode(Object _self, Object _list, Object _node);
Object ListIterator_SystemInitWithListAndNode(Object _self, Object _list, Object _node);
Object ListIterator_ResetNode(Object _self, Object _node);
Object ListIterator_Hide(Object _self);
Object ListIterator_Next(Object _self);
Object ListIterator_Prev(Object _self);
Object ListIterator_ToBegin(Object _self);
Object ListIterator_ToEnd(Object _self);
Object ListIterator_ToPosition(Object _self, Object _position);
Object ListIterator_FromPositionToPosition(Object _self, Object _positionFrom, Object _positionTo);
Object ListIterator_SearchForward(Object _self, Object _object);
Object ListIterator_SearchBackward(Object _self, Object _object);
Object ListIterator_SearchForwardOffset(Object _self, Object _object);
Object ListIterator_ThisRemove(Object _self);
Object ListIterator_PrevRemove(Object _self);
Object ListIterator_NextRemove(Object _self);
Object ListIterator_ThisData(Object _self);
Object ListIterator_NextData(Object _self);
Object ListIterator_PrevData(Object _self);
Object ListIterator_LogicData(Object _self);
Object ListIterator_NumberData(Object _self);
Object ListIterator_ListData(Object _self);
Object ListIterator_ListMapData(Object _self);
Object ListIterator_CharData(Object _self);
Object ListIterator_ThisSetData(Object _self, Object _object);
Object ListIterator_PrevSetData(Object _self, Object _object);
Object ListIterator_NextSetData(Object _self, Object _object);
Object ListIterator_AddAfter(Object _self, Object _object);
Object ListIterator_AddBefore(Object _self, Object _object);
Object ListIterator_ThisBegin(Object _self);
Object ListIterator_ThisEnd(Object _self);
Object ListIterator_PrevBegin(Object _self);
Object ListIterator_NextEnd(Object _self);
Object ListIterator_AddListBefore(Object _self, Object _list);
Object ListIterator_AddListAfter(Object _self, Object _list);
Object ListIterator_RemoveCount(Object _self, Object _count);
Object ListIterator_StringSkipSpace(Object _self);
Object ListIterator_StringSkipWhiteSpace(Object _self);
