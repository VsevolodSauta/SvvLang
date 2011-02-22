typedef struct ExternalEntitiesFactory {
	Object _placeHolder;
} *ExternalEntitiesFactory;

Object ExternalEntitiesFactory_Create(void);
Object ExternalEntitiesFactory_Clone(Object _self);
Object ExternalEntitiesFactory_DeepClone(Object _self);
Object ExternalEntitiesFactory_Destroy(Object _self);
Object ExternalEntitiesFactory_Compare(Object _self, Object _entitiesFactory);
Object ExternalEntitiesFactory_CreateEmptyListMap(Object _self);
Object ExternalEntitiesFactory_CreateEmptyList(Object _self);
Object ExternalEntitiesFactory_CreateEmptyJob(Object _self);
Object ExternalEntitiesFactory_CreateEmptyMethod(Object _self);
Object ExternalEntitiesFactory_CreateEmptyJobStage(Object _self);
Object ExternalEntitiesFactory_CreateConditionPresence(Object _self, Object _key);
Object ExternalEntitiesFactory_CreateConditionEquality(Object _self, Object _key, Object _value);
Object ExternalEntitiesFactory_CreateEmptyMessageSlot(Object _self);
Object ExternalEntitiesFactory_CreateRequestMessageSlot(Object _self, Object _request);
Object ExternalEntitiesFactory_CreateObject(Object _self);
Object ExternalEntitiesFactory_CreateEmptyFields(Object _self);
Object ExternalEntitiesFactory_CreateEmptyMethods(Object _self);
Object ExternalEntitiesFactory_CreateEmptyJobs(Object _self);
Object ExternalEntitiesFactory_CreateEmptyProperties(Object _self);
