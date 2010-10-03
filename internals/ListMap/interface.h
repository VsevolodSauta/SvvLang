typedef struct ListMap {
	Object _root;
} *ListMap;

Object ListMap_Create(void);
Object ListMap_Init(Object _self);
Object ListMap_Compare(Object _self, Object _listSet);
Object ListMap_Destroy(Object _self);
Object ListMap_Clone(Object _self);
Object ListMap_Add(Object _self, Object _list, Object _object);
Object ListMap_RemoveKey(Object _self, Object _list);
Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list);
Object ListMap_GetAt(Object _self, Object _list);
Object ListMap_Contains(Object _self, Object _list);
