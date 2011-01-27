typedef struct MultiSet {
	Object _list;
} *MultiSet;

Object MultiSet_Create(void);
Object MultiSet_Init(Object _self);
Object MultiSet_Destroy(Object _self);
Object MultiSet_Clone(Object _self);
Object MultiSet_DeepClone(Object _self);
Object MultiSet_Compare(Object _self, Object _multiset);
Object MultiSet_Push(Object _self, Object _object);
Object MultiSet_Contains(Object _self, Object _object);
Object MultiSet_RemoveOnce(Object _self, Object _object);
Object MultiSet_RemoveEvery(Object _self, Object _object);
Object MultiSet_Empty(Object _self);
