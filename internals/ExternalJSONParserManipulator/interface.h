typedef struct ExternalJSONParserManipulator {
	Object _machine;
} *ExternalJSONParserManipulator;

Object ExternalJSONParserManipulator_Create(void);
Object ExternalJSONParserManipulator_Init(Object _self);
Object ExternalJSONParserManipulator_Clone(Object _self);
Object ExternalJSONParserManipulator_DeepClone(Object _self);
Object ExternalJSONParserManipulator_Destroy(Object _self);
Object ExternalJSONParserManipulator_Compare(Object _self, Object _manipulator);
Object ExternalJSONParserManipulator_SetMachine(Object _self, Object _machine);
Object ExternalJSONParserManipulator_CreateUIDJSONParserFromUIDActor(Object _self, Object _uid);
Object ExternalJSONParserManipulator_InternalCreateEntityFromSimpleString(Object _self, Object _processor, Object _simpleString, Object _reply);
Object ExternalJSONParserManipulator_CreateEntityFromSimpleString(Object _self, Object _processor);
Object ExternalJSONParserManipulator_CreateEntityFromString(Object _self, Object _processor);
Object ExternalJSONParserManipulator_SimpleStringReceived(Object _self, Object _processor);
