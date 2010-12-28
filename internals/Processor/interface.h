typedef struct Processor {
	Object _contextObject;
	Object _contextJobStage;
	Object _machine;
	Object _localNamespaces;
	Object _helperStack;
} *Processor;

Object Processor_Create(void);
Object Processor_Init(Object _self);
Object Processor_Clone(Object _self);
Object Processor_Destroy(Object _self);
Object Processor_Compare(Object _self, Object _processor);
Object Processor_SetMachine(Object _self, Object _machine);
Object Processor_LocationType(Object _self, Object _objectName);
Object Processor_ResolveName(Object _self, Object _objectName);
Object Processor_SendMessage(Object _self, Object _message);
Object Processor_DoHelper(Object _self, Object _toDo);
Object Processor_Do(Object _self, Object _toDo);
Object Processor_InvokeMethod(Object _self, Object _methodName, Object _parameters);
Object Processor_MessageConfirmsToParameter(Object _self, Object _message, Object _parameter);
Object Processor_TryLinkMessageWithJobStage(Object _self, Object _jobStage, Object _message);
Object Processor_ProcessOneMessage(Object _self);
Object Processor_ProcessOneJobIfAny(Object _self);
Object Processor_ProcessObject(Object _self, Object _object);
