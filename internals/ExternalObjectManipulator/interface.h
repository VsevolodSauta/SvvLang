typedef struct ExternalObjectManipulator {
	Object _machine;
} *ExternalObjectManipulator;

Object ExternalObjectManipulator_Create(void);
Object ExternalObjectManipulator_Init(Object _self);
Object ExternalObjectManipulator_Clone(Object _self);
Object ExternalObjectManipulator_Destroy(Object _self);
Object ExternalObjectManipulator_Compare(Object _self, Object _manipulator);
Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine);
Object ExternalObjectManipulator_CreateUID(Object _self);
Object ExternalObjectManipulator_CloneUID(Object _self, Object _uid);
Object ExternalObjectManipulator_SetBasicMethodWithNameForUID(Object _self, Object _method, Object _name, Object _uid);
Object ExternalObjectManipulator_SetMethodWithNameForUID(Object _self, Object _methodBody, Object _name, Object _uid);
