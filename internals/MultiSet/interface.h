typedef struct MultiSet {
	Object list;
} *MultiSet;
Object MultiSet_Create(void);
Object MultiSet_Init(Object self);
Object MultiSet_Destroy(Object self);
Object MultiSet_Clone(Object self);
Object MultiSet_Compare(Object self, Object multiset);
Object MultiSet_Push(Object self, Object object);
Object MultiSet_Contains(Object self, Object object);
Object MultiSet_RemoveOnce(Object self, Object object);
Object MultiSet_RemoveEvery(Object self, Object object);
