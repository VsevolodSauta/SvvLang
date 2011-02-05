typedef struct ExternalObjectManipulator {
	Object _machine;
	Object _objectMasterCopy;
} *ExternalObjectManipulator;

Object ExternalObjectManipulator_Create(void);
Object ExternalObjectManipulator_Init(Object _self);
Object ExternalObjectManipulator_Clone(Object _self);
Object ExternalObjectManipulator_DeepClone(Object _self);
Object ExternalObjectManipulator_Destroy(Object _self);
Object ExternalObjectManipulator_Compare(Object _self, Object _manipulator);
Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine);
Object ExternalObjectManipulator_CreateUIDObject(Object _self);
Object ExternalObjectManipulator_CloneUIDObjectInternalRoutine(Object _self, Object _uid);
Object ExternalObjectManipulator_CloneUIDObjectBasicMethod(Object _self, Object _parameters, Object _processor);
