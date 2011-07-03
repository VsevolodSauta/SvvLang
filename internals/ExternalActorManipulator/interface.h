typedef struct ExternalActorManipulator {
	Object _machine;
	Object _actorMasterCopy;
} *ExternalActorManipulator;

Object ExternalActorManipulator_Create(void);
Object ExternalActorManipulator_Init(Object _self);
Object ExternalActorManipulator_Clone(Object _self);
Object ExternalActorManipulator_DeepClone(Object _self);
Object ExternalActorManipulator_Destroy(Object _self);
Object ExternalActorManipulator_Compare(Object _self, Object _manipulator);
Object ExternalActorManipulator_SetMachine(Object _self, Object _machine);
Object ExternalActorManipulator_CreateUIDActor(Object _self);
Object ExternalActorManipulator_CloneUIDActorInternalRoutine(Object _self, Object _uid);
Object ExternalActorManipulator_DoUIDActorBasicMethod(Object _self, Object _processor);
Object ExternalActorManipulator_CloneUIDActorBasicMethod(Object _self, Object _processor);
