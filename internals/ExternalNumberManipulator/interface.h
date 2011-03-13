typedef struct ExternalNumberManipulator {
	Object _machine;
} *ExternalNumberManipulator;

Object ExternalNumberManipulator_Create(void);
Object ExternalNumberManipulator_Init(Object _self);
Object ExternalNumberManipulator_Clone(Object _self);
Object ExternalNumberManipulator_DeepClone(Object _self);
Object ExternalNumberManipulator_Destroy(Object _self);
Object ExternalNumberManipulator_Compare(Object _self, Object _manipulator);
Object ExternalNumberManipulator_SetMachine(Object _self, Object _machine);
Object ExternalNumberManipulator_CreateUIDNumberFromUIDObject(Object _self, Object _uid);
Object ExternalNumberManipulator_SimpleNumber(Object _self, Object _processor);
Object ExternalNumberManipulator_SimpleString(Object _self, Object _processor);
Object ExternalNumberManipulator_AddInPlace(Object _self, Object _processor);
Object ExternalNumberManipulator_AddInPlaceSimple(Object _self, Object _processor);
Object ExternalNumberManipulator_SubInPlace(Object _self, Object _processor);
Object ExternalNumberManipulator_SubInPlaceSimple(Object _self, Object _processor);
Object ExternalNumberManipulator_MulInPlace(Object _self, Object _processor);
Object ExternalNumberManipulator_MulInPlaceSimple(Object _self, Object _processor);
Object ExternalNumberManipulator_DivInPlace(Object _self, Object _processor);
Object ExternalNumberManipulator_DivInPlaceSimple(Object _self, Object _processor);
Object ExternalNumberManipulator_Increment(Object _self, Object _processor);
Object ExternalNumberManipulator_Decrement(Object _self, Object _processor);
Object ExternalNumberManipulator_Absolute(Object _self, Object _processor);
