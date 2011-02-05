typedef struct Machine {
	Object _objectsByUIDs;
	Object _uidGenerator;
	Object _globalContext;
	Object _processor;
	Object _scheduler;
	Object _machineManipulator;
} *Machine;

Object Machine_Create(void);
Object Machine_Init(Object _self);
Object Machine_LoadUIDWithNameToNamespace(Object _self, Object _objectName, Object _namespace);
Object Machine_ImportUID(Object _self, Object _objectName);
Object Machine_UIDToObject(Object _self, Object _uid);
Object Machine_SetUIDToObject(Object _self, Object _uid, Object _object);
Object Machine_GenerateUID(Object _self);
Object Machine_RestorePreviousState(Object _self);
Object Machine_ScheduleUID(Object _self, Object _uid);
Object Machine_Run(Object _self);
Object Machine_Destroy(Object _self);
Object Machine_Clone(Object _self);
Object Machine_DeepClone(Object _self);
Object Machine_Compare(Object _self, Object _machine);
