typedef struct ExternalActorsFactory {
	Object _machine;
} *ExternalActorsFactory;

Object ExternalActorsFactory_Create(void);
Object ExternalActorsFactory_Init(Object _self);
Object ExternalActorsFactory_Destroy(Object _self);
Object ExternalActorsFactory_Compare(Object _self, Object _eof);
Object ExternalActorsFactory_Clone(Object _self);
Object ExternalActorsFactory_DeepClone(Object _self);
Object ExternalActorsFactory_SetMachine(Object _self, Object _machine);
Object ExternalActorsFactory_CreateActorFromObject(Object _self, Object _value);
Object ExternalActorsFactory_CreateNumber(Object _self, Object _number);
Object ExternalActorsFactory_CreateChar(Object _self, Object _char);
Object ExternalActorsFactory_CreateString(Object _self, Object _string);
Object ExternalActorsFactory_CreateList(Object _self, Object _list);
Object ExternalActorsFactory_CreateListMap(Object _self, Object _listMap);
