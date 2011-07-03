#include "internals/basics.h"
#include "internals/ExternalActorManipulator/imports.h"


Object ExternalActorManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalActorManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalActorManipulator));
	_self->gid =  2910355935909677056ull;
	Object_SetComparator(_self, &ExternalActorManipulator_Compare);
	Object_SetDestructor(_self, &ExternalActorManipulator_Destroy);
	Object_SetCloner(_self, &ExternalActorManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalActorManipulator_DeepClone);
	((ExternalActorManipulator) (_self->entity))->_machine = _nil;
	((ExternalActorManipulator) (_self->entity))->_actorMasterCopy = _nil;
	_self = ExternalActorManipulator_Init(_self);
	DPOPS ("ExternalActorManipulator: Create ended.")
	return _self;
}

Object ExternalActorManipulator_Init(Object _self)
{
	DPUSHS ("ExternalActorManipulator: Init begined.")
	ASSERT_C ( "ExternalActorManipulator:Init --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	Object toReturn = _self;
	DPOPS ("ExternalActorManipulator: Init ended.")
	return toReturn;
}

Object ExternalActorManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalActorManipulator: Clone begined.")
	ASSERT_C ( "ExternalActorManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalActorManipulator: Clone ended.")
	return toReturn;
}

Object ExternalActorManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalActorManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalActorManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalActorManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalActorManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalActorManipulator: Destroy begined.")
	ASSERT_C ( "ExternalActorManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	Object_Release((((ExternalActorManipulator) (_self->entity))->_actorMasterCopy));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalActorManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalActorManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalActorManipulator: Compare begined.")
	ASSERT_C ( "ExternalActorManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	ASSERT_C ( "ExternalActorManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  2910355935909677056ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalActorManipulator: Compare ended.")
	return toReturn;
}

Object ExternalActorManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalActorManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalActorManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	ASSERT_C ( "ExternalActorManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalActorManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalActorManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalActorManipulator_CreateUIDActor(Object _self)
{
	DPUSHS ("ExternalActorManipulator: CreateUIDActor begined.")
	ASSERT_C ( "ExternalActorManipulator:CreateUIDActor --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	AutoreleasePool_PushFrame(ThreadManager_AutoreleasePool(_threadManager));
	Object _actor;
	_actor = ExternalEntitiesFactory_CreateEmptyActor(_entitiesFactory);
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalActorManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Клонироваться", 26), _self, MethodFactory_FromPointer(_methodFactory, &ExternalActorManipulator_CloneUIDActorBasicMethod), _job);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа актора", 42));
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalActorManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Выполнить", 18), _self, MethodFactory_FromPointer(_methodFactory, &ExternalActorManipulator_DoUIDActorBasicMethod), _job);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Специализация", 26));
	(((ExternalActorManipulator) (_self->entity))->_actorMasterCopy) = Object_DeepClone(_actor);
	Object _uid;
	_uid = Machine_GenerateUID((((ExternalActorManipulator) (_self->entity))->_machine));
	Machine_SetUIDToActor((((ExternalActorManipulator) (_self->entity))->_machine), _uid, _actor);
	AutoreleasePool_PopFrame(ThreadManager_AutoreleasePool(_threadManager));
	Object toReturn = _uid;
	DPOPS ("ExternalActorManipulator: CreateUIDActor ended.")
	return toReturn;
}

Object ExternalActorManipulator_CloneUIDActorInternalRoutine(Object _self, Object _uid)
{
	DPUSHS ("ExternalActorManipulator: CloneUIDActorInternalRoutine begined.")
	ASSERT_C ( "ExternalActorManipulator:CloneUIDActorInternalRoutine --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	ASSERT_C ( "ExternalActorManipulator:CloneUIDActorInternalRoutine --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalActorManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GenerateUID((((ExternalActorManipulator) (_self->entity))->_machine));
	Object _actorToReturn;
	_actorToReturn = Object_DeepClone((((ExternalActorManipulator) (_self->entity))->_actorMasterCopy));
	ListMap_ActorResetMethodsDestructive(_actorToReturn, Object_TempDeepClone(ListMap_ActorMethods(_actor)));
	ListMap_ActorResetFieldsDestructive(_actorToReturn, Object_TempDeepClone(ListMap_ActorFields(_actor)));
	ListMap_ActorResetJobsDestructive(_actorToReturn, Object_TempDeepClone(ListMap_ActorJobs(_actor)));
	ListMap_ActorRemoveAllIdentifiers(_actorToReturn);
	Machine_SetUIDToActor((((ExternalActorManipulator) (_self->entity))->_machine), _uidToReturn, _actorToReturn);
	Object_Release(_actorToReturn);
	Object toReturn = _uidToReturn;
	DPOPS ("ExternalActorManipulator: CloneUIDActorInternalRoutine ended.")
	return toReturn;
}

Object ExternalActorManipulator_DoUIDActorBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalActorManipulator: DoUIDActorBasicMethod begined.")
	ASSERT_C ( "ExternalActorManipulator:DoUIDActorBasicMethod --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	ASSERT_C ( "ExternalActorManipulator:DoUIDActorBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _tempMethodName;
	_tempMethodName = StringFactory_FromUTF8(_stringFactory, "Специализация, временный метод", 57);
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _methodBody;
	_methodBody = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Тело", 8), StringFactory_FromUTF8(_stringFactory, "Специализация Тип=ЗапросЗапрос=Выполнить_Тело", 86));
	ListMap_ActorSetMethodBody(_job, _methodBody, _tempMethodName);
	Processor_InvokeMethodWithParameters(_processor, _tempMethodName, ExternalEntitiesFactory_CreateEmptyListMap(_entitiesFactory));
	ListMap_Remove(ListMap_ActorMethods(_actor), _tempMethodName);
	Object _replyMessage;
	_replyMessage = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_replyMessage);
	Processor_SendReplyForMessage(_processor, _replyMessage, StringFactory_FromUTF8(_stringFactory, "Специализация Тип=ЗапросЗапрос=Выполнить_Тело", 86));
	Object toReturn = _self;
	DPOPS ("ExternalActorManipulator: DoUIDActorBasicMethod ended.")
	return toReturn;
}

Object ExternalActorManipulator_CloneUIDActorBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalActorManipulator: CloneUIDActorBasicMethod begined.")
	ASSERT_C ( "ExternalActorManipulator:CloneUIDActorBasicMethod --- Checking for correct object type failed.", _self->gid ==  2910355935909677056ull )
	ASSERT_C ( "ExternalActorManipulator:CloneUIDActorBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _uidToReturn;
	_uidToReturn = ExternalActorManipulator_CloneUIDActorInternalRoutine(_self, Processor_ContextActorUID(_processor));
	Object _replyMessage;
	_replyMessage = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_replyMessage);
	ListMap_Add(_replyMessage, StringFactory_FromUTF8(_stringFactory, "Клон", 8), _uidToReturn);
	Processor_SendReplyForMessage(_processor, _replyMessage, StringFactory_FromUTF8(_stringFactory, "Клонирование Тип=ЗапросЗапрос=Клонировать", 79));
	Object toReturn = _self;
	DPOPS ("ExternalActorManipulator: CloneUIDActorBasicMethod ended.")
	return toReturn;
}
