typedef struct ExternalListMapManipulator {
	Object _machine;
} *ExternalListMapManipulator;

Object ExternalListMapManipulator_Create(void);
Object ExternalListMapManipulator_Init(Object _self);
Object ExternalListMapManipulator_Clone(Object _self);
Object ExternalListMapManipulator_DeepClone(Object _self);
Object ExternalListMapManipulator_Destroy(Object _self);
Object ExternalListMapManipulator_Compare(Object _self, Object _manipulator);
Object ExternalListMapManipulator_SetMachine(Object _self, Object _machine);
Object ExternalListMapManipulator_CreateUIDListMapFromUIDActor(Object _self, Object _uid);
Object ExternalListMapManipulator_Size(Object _self, Object _processor);
Object ExternalListMapManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(Object _self, Object _processor, Object _message, Object _positionUID, Object _method);
Object ExternalListMapManipulator_PositionReceived(Object _self, Object _processor);
Object ExternalListMapManipulator_AtInsertInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListMapManipulator_AtInsert(Object _self, Object _processor);
Object ExternalListMapManipulator_AtGetInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListMapManipulator_AtGet(Object _self, Object _processor);
Object ExternalListMapManipulator_AtSendInternal(Object _self, Object _processor, Object _position, Object _message);
Object ExternalListMapManipulator_AnswerReceived(Object _self, Object _processor);
Object ExternalListMapManipulator_AtSend(Object _self, Object _processor);
Object ExternalListMapManipulator_SendToAll(Object _self, Object _processor);
Object ExternalListMapManipulator_SendToAllResendAnswersHandler(Object _self, Object _processor);
Object ExternalListMapManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor);
