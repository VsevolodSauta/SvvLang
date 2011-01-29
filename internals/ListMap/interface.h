typedef struct ListMap {
	Object _root;
} *ListMap;

Object ListMap_Create(void);
Object ListMap_Init(Object _self);
Object ListMap_Compare(Object _self, Object _listSet);
Object ListMap_Destroy(Object _self);
Object ListMap_Clone(Object _self);
Object ListMap_DeepClone(Object _self);
Object ListMap_Empty(Object _self);
Object ListMap_Add(Object _self, Object _list, Object _object);
Object ListMap_AddListMap(Object _self, Object _listMap);
Object ListMap_Remove(Object _self, Object _list);
Object ListMap_RemoveKeyWithConfirmation(Object _self, Object _list);
Object ListMap_ObjectAt(Object _self, Object _list);
Object ListMap_Contains(Object _self, Object _list);
Object ListMap_ListMapAt(Object _self, Object _list);
Object ListMap_ListAt(Object _self, Object _list);
Object ListMap_QueueAt(Object _self, Object _list);
Object ListMap_LogicAt(Object _self, Object _list);
Object ListMap_NumberAt(Object _self, Object _list);
Object ListMap_SynonimAt(Object _self, Object _list);
Object ListMap_MethodAt(Object _self, Object _list);
Object ListMap_First(Object _self);
Object ListMap_Last(Object _self);
Object ListMap_DumpKeys(Object _self);
