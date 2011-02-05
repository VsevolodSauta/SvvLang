typedef struct ExternalConsoleManipulator {
	Object _machine;
} *ExternalConsoleManipulator;

Object ExternalConsoleManipulator_Create(void);
Object ExternalConsoleManipulator_Init(Object _self);
Object ExternalConsoleManipulator_Clone(Object _self);
Object ExternalConsoleManipulator_DeepClone(Object _self);
Object ExternalConsoleManipulator_Destroy(Object _self);
Object ExternalConsoleManipulator_Compare(Object _self, Object _consoleManipulator);
Object ExternalConsoleManipulator_SetMachine(Object _self, Object _machine);
Object ExternalConsoleManipulator_CreateUIDConsoleFromUIDObject(Object _self, Object _uid);
Object ExternalConsoleManipulator_WriteUIDConsoleBasicMethod(Object _self, Object _uid, Object _parameters, Object _processor);
