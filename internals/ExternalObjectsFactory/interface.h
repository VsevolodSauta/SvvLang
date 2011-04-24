typedef struct ExternalObjectsFactory {
	Object _machine;
} *ExternalObjectsFactory;

Object ExternalObjectsFactory_Create(void);
Object ExternalObjectsFactory_Init(Object _self);
Object ExternalObjectsFactory_Destroy(Object _self);
Object ExternalObjectsFactory_Compare(Object _self, Object _eof);
Object ExternalObjectsFactory_Clone(Object _self);
Object ExternalObjectsFactory_DeepClone(Object _self);
Object ExternalObjectsFactory_SetMachine(Object _self, Object _machine);
Object ExternalObjectsFactory_CreateValue(Object _self, Object _value);
Object ExternalObjectsFactory_CreateNumber(Object _self, Object _number);
Object ExternalObjectsFactory_CreateString(Object _self, Object _string);
Object ExternalObjectsFactory_CreateList(Object _self, Object _list);
Object ExternalObjectsFactory_CreateListMap(Object _self, Object _listMap);
