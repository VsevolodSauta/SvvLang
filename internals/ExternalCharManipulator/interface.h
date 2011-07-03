typedef struct ExternalCharManipulator {
	Object _machine;
} *ExternalCharManipulator;

Object ExternalCharManipulator_Create(void);
Object ExternalCharManipulator_Init(Object _self);
Object ExternalCharManipulator_Clone(Object _self);
Object ExternalCharManipulator_DeepClone(Object _self);
Object ExternalCharManipulator_Destroy(Object _self);
Object ExternalCharManipulator_Compare(Object _self, Object _manipulator);
Object ExternalCharManipulator_SetMachine(Object _self, Object _machine);
Object ExternalCharManipulator_CreateUIDCharFromUIDActor(Object _self, Object _uid);
Object ExternalCharManipulator_CodeSimpleNumberReceived(Object _self, Object _processor);
Object ExternalCharManipulator_SetCode(Object _self, Object _processor);
Object ExternalCharManipulator_GetCode(Object _self, Object _processor);
