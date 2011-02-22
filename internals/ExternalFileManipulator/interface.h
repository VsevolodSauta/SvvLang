typedef struct ExternalFileManipulator {
	Object _machine;
} *ExternalFileManipulator;

Object ExternalFileManipulator_Create(void);
Object ExternalFileManipulator_Init(Object _self);
Object ExternalFileManipulator_Clone(Object _self);
Object ExternalFileManipulator_DeepClone(Object _self);
Object ExternalFileManipulator_Destroy(Object _self);
Object ExternalFileManipulator_Compare(Object _self, Object _consoleManipulator);
Object ExternalFileManipulator_SetMachine(Object _self, Object _machine);
Object ExternalFileManipulator_CreateUIDFileFromUIDObject(Object _self, Object _uid);
Object ExternalFileManipulator_AssociateUIDFileBasicMethod(Object _self, Object _processor);
Object ExternalFileManipulator_OpenForReadingUIDFileBasicMethod(Object _self, Object _processor);
Object ExternalFileManipulator_OpenForWritingUIDFileBasicMethod(Object _self, Object _processor);
Object ExternalFileManipulator_CloseUIDFileBasicMethod(Object _self, Object _processor);
Object ExternalFileManipulator_WriteStringUIDFileBasicMethod(Object _self, Object _processor);
Object ExternalFileManipulator_ReadStringUIDFileBasicMethod(Object _self, Object _processor);
