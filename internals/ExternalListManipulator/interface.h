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
Object ExternalListManipulator_CreateUIDListFromUIDActor(Object _self, Object _uid);
Object ExternalListManipulator_ListWithIntegersInIntervalHandler(Object _self, Object _processor);
Object ExternalListManipulator_ListWithIntegersInInterval(Object _self, Object _processor);
Object ExternalListManipulator_SendToAllResendAnswersHandler(Object _self, Object _processor);
Object ExternalListManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor);
Object ExternalListManipulator_SendToAll(Object _self, Object _processor);
Object ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(Object _self, Object _processor, Object _message, Object _positionUID, Object _method);
Object ExternalListManipulator_PositionReceived(Object _self, Object _processor);
Object ExternalListManipulator_AtGetInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListManipulator_AtGet(Object _self, Object _processor);
Object ExternalListManipulator_AtInsertInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListManipulator_AtInsert(Object _self, Object _processor);
Object ExternalListManipulator_AtReplaceInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListManipulator_AtReplace(Object _self, Object _processor);
Object ExternalListManipulator_AtSendInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListManipulator_AnswerReceived(Object _self, Object _processor);
Object ExternalListManipulator_AtSend(Object _self, Object _processor);
Object ExternalListManipulator_Size(Object _self, Object _processor);
