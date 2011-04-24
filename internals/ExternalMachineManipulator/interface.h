typedef struct ExternalMachineManipulator {
	Object _machine;
	Object _object;
	Object _console;
	Object _file;
	Object _number;
	Object _list;
} *ExternalMachineManipulator;

Object ExternalMachineManipulator_Create(void);
Object ExternalMachineManipulator_Init(Object _self);
Object ExternalMachineManipulator_Destroy(Object _self);
Object ExternalMachineManipulator_Clone(Object _self);
Object ExternalMachineManipulator_DeepClone(Object _self);
Object ExternalMachineManipulator_Compare(Object _self, Object _machineManipulator);
Object ExternalMachineManipulator_SetMachine(Object _self, Object _machine);
Object ExternalMachineManipulator_CreateAll(Object _self);
