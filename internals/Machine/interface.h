typedef struct Machine {
	Object _actorsByUIDs;
	Object _uidGenerator;
	Object _globalContext;
	Object _fakeProcessor;
	Object _processors;
	Object _scheduler;
	Object _machineManipulator;
	Object _totalProcessors;
	Object _actorsFactory;
} *Machine;

Object Machine_Create(void);
Object Machine_Init(Object _self);
Object Machine_Destroy(Object _self);
Object Machine_Clone(Object _self);
Object Machine_DeepClone(Object _self);
Object Machine_Compare(Object _self, Object _machine);
Object Machine_ActorsFactory(Object _self);
Object Machine_LoadActorWithNameToNamespace(Object _self, Object _actorName, Object _namespace);
Object Machine_ImportActor(Object _self, Object _actorName);
Object Machine_RegisterAtGlobalContext(Object _self, Object _uid, Object _name);
Object Machine_UIDToActor(Object _self, Object _uid);
Object Machine_SetUIDToActor(Object _self, Object _uid, Object _actor);
Object Machine_GenerateUID(Object _self);
Object Machine_RestorePreviousState(Object _self);
Object Machine_ScheduleUID(Object _self, Object _uid);
Object Machine_ProcessorFinishedWork(Object _self, Object _processor);
Object Machine_Run(Object _self);
Object Machine_CollectGarbageProcessListMap(Object _self, Object _listMap, Object _notToDeleteList);
Object Machine_CollectGarbageProcessList(Object _self, Object _list, Object _notToDeleteList);
Object Machine_CollectGarbage(Object _self);
