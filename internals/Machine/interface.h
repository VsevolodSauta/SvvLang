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
