typedef struct ExternalObjectManipulator {
	Object _machine;
} *ExternalObjectManipulator;

Object ExternalObjectManipulator_Create(void);
Object ExternalObjectManipulator_Init(Object _self);
Object ExternalObjectManipulator_Clone(Object _self);
Object ExternalObjectManipulator_Destroy(Object _self);
Object ExternalObjectManipulator_Compare(Object _self);
Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine);
Object ExternalObjectManipulator_ObjectCreate(Object _self);
Object ExternalObjectManipulator_ObjectClone(Object _self, Object _uid);
Object ExternalObjectManipulator_SetBasicMethodForObjectWithName(Object _self, Object _methodAdress, Object _uid, Object _name);
Object ExternalObjectManipulator_SetMethodForObjectWithName(Object _self, Object _methodBody, Object _uid, Object _name);
