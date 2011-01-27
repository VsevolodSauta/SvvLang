typedef struct Machine {
	Object _objectsByUIDs;
	Object _uidGenerator;
	Object _globalContext;
	Object _processor;
	Object _scheduler;
} *Machine;

Object Machine_Create(void);
Object Machine_Init(Object _self);
Object Machine_LoadApplication(Object _self, Object _applicationName);
Object Machine_ObjectByUID(Object _self, Object _uid);
Object Machine_SetObjectByUID(Object _self, Object _object, Object _uid);
Object Machine_GetUID(Object _self);
Object Machine_RestorePreviousState(Object _self);
Object Machine_Schedule(Object _self, Object _uid);
Object Machine_Run(Object _self);
Object Machine_Destroy(Object _self);
Object Machine_Clone(Object _self);
Object Machine_DeepClone(Object _self);
Object Machine_Compare(Object _self, Object _machine);
