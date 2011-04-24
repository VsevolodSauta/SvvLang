typedef struct ExternalListManipulator {
	Object _machine;
} *ExternalListManipulator;

Object ExternalListManipulator_Create(void);
Object ExternalListManipulator_Init(Object _self);
Object ExternalListManipulator_Clone(Object _self);
Object ExternalListManipulator_DeepClone(Object _self);
Object ExternalListManipulator_Destroy(Object _self);
Object ExternalListManipulator_Compare(Object _self, Object _manipulator);
Object ExternalListManipulator_SetMachine(Object _self, Object _machine);
Object ExternalListManipulator_CreateUIDListFromUIDObject(Object _self, Object _uid);
Object ExternalListManipulator_ListWithIntegersInIntervalHandler(Object _self, Object _processor);
Object ExternalListManipulator_ListWithIntegersInInterval(Object _self, Object _processor);
Object ExternalListManipulator_SendToAllRedirectAnswersHandler(Object _self, Object _processor);
Object ExternalListManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor);
Object ExternalListManipulator_SendToAll(Object _self, Object _processor);
