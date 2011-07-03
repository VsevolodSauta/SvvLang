#include "internals/basics.h"
#include "internals/ExternalNumberManipulator/imports.h"


Object ExternalNumberManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalNumberManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalNumberManipulator));
	_self->gid =  3782552814704636928ull;
	Object_SetComparator(_self, &ExternalNumberManipulator_Compare);
	Object_SetDestructor(_self, &ExternalNumberManipulator_Destroy);
	Object_SetCloner(_self, &ExternalNumberManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalNumberManipulator_DeepClone);
	((ExternalNumberManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalNumberManipulator_Init(_self);
	DPOPS ("ExternalNumberManipulator: Create ended.")
	return _self;
}

Object ExternalNumberManipulator_Init(Object _self)
{
	DPUSHS ("ExternalNumberManipulator: Init begined.")
	ASSERT_C ( "ExternalNumberManipulator:Init --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Init ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalNumberManipulator: Clone begined.")
	ASSERT_C ( "ExternalNumberManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalNumberManipulator: Clone ended.")
	return toReturn;
}

Object ExternalNumberManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalNumberManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalNumberManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalNumberManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalNumberManipulator: Destroy begined.")
	ASSERT_C ( "ExternalNumberManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalNumberManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalNumberManipulator: Compare begined.")
	ASSERT_C ( "ExternalNumberManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  3782552814704636928ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalNumberManipulator: Compare ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalNumberManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalNumberManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalNumberManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalNumberManipulator_CreateUIDNumberFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalNumberManipulator: CreateUIDNumberFromUIDActor begined.")
	ASSERT_C ( "ExternalNumberManipulator:CreateUIDNumberFromUIDActor --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:CreateUIDNumberFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_SimpleNumber), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_SimpleString), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "+=", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_AddInPlace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "-=", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_SubInPlace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "*=", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_MulInPlace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "/=", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_DivInPlace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "%=", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_ModInPlace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "++", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_Increment), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "--", 2), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_Decrement), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Модуль", 12), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_Absolute), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Оповестить", 20), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_NotifyRequest), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Условие", 14)));
	_messageSlot = Processor_CreateStageEmptyEntityBasicMethodInJob((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Текущее значение получено", 48), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_CurrentValueReceived), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Текущее значение", 31)));
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalNumberManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа числа", 40));
	Object toReturn = _uid;
	DPOPS ("ExternalNumberManipulator: CreateUIDNumberFromUIDActor ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SimpleNumber(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SimpleNumber begined.")
	ASSERT_C ( "ExternalNumberManipulator:SimpleNumber --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SimpleNumber --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_message);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Значение", 16), Object_TempClone(_number));
	Processor_SendReplyForMessage(_processor, _message, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SimpleNumber ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SimpleString(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SimpleString begined.")
	ASSERT_C ( "ExternalNumberManipulator:SimpleString --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SimpleString --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_message);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Значение", 16), StringFactory_FromNumber(_stringFactory, _number));
	Processor_SendReplyForMessage(_processor, _message, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SimpleString ended.")
	return toReturn;
}

Object ExternalNumberManipulator_AddInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: AddInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:AddInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:AddInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _requestArgument;
	_requestArgument = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "+=", 2), StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_jobToProcessThisEvent), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "+=", 2), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_AddInPlaceSimple), _jobToProcessThisEvent);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _requestArgument));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Processor_AddJobWithName(_processor, _jobToProcessThisEvent, Machine_GenerateUID((((ExternalNumberManipulator) (_self->entity))->_machine)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _requestArgument);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: AddInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_AddInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: AddInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:AddInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:AddInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_AddInPlace(_number, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "+=", 2));
	ListMap_MessageSetReceiver(_reply, _receiver);
	Processor_SendMessage(_processor, _reply);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: AddInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SubInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SubInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:SubInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SubInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _requestArgument;
	_requestArgument = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "-=", 2), StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_jobToProcessThisEvent), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "-=", 2), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_SubInPlaceSimple), _jobToProcessThisEvent);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _requestArgument));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Processor_AddJobWithName(_processor, _jobToProcessThisEvent, Machine_GenerateUID((((ExternalNumberManipulator) (_self->entity))->_machine)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _requestArgument);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SubInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SubInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SubInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:SubInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SubInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_SubInPlace(_number, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "-=", 2));
	ListMap_MessageSetReceiver(_reply, _receiver);
	Processor_SendMessage(_processor, _reply);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SubInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_MulInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: MulInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:MulInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:MulInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _requestArgument;
	_requestArgument = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "*=", 2), StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_jobToProcessThisEvent), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "*=", 2), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_MulInPlaceSimple), _jobToProcessThisEvent);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _requestArgument));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Processor_AddJobWithName(_processor, _jobToProcessThisEvent, Machine_GenerateUID((((ExternalNumberManipulator) (_self->entity))->_machine)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _requestArgument);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: MulInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_MulInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: MulInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:MulInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:MulInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_MulInPlace(_number, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "*=", 2));
	ListMap_MessageSetReceiver(_reply, _receiver);
	Processor_SendMessage(_processor, _reply);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: MulInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_DivInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: DivInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:DivInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:DivInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _requestArgument;
	_requestArgument = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_jobToProcessThisEvent), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_DivInPlaceSimple), _jobToProcessThisEvent);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _requestArgument));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Processor_AddJobWithName(_processor, _jobToProcessThisEvent, Machine_GenerateUID((((ExternalNumberManipulator) (_self->entity))->_machine)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _requestArgument);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: DivInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_DivInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: DivInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:DivInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:DivInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_DivInPlace(_number, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "/=", 2));
	ListMap_MessageSetReceiver(_reply, _receiver);
	Processor_SendMessage(_processor, _reply);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: DivInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_ModInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: ModInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:ModInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:ModInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _requestArgument;
	_requestArgument = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "%=", 2), StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_jobToProcessThisEvent), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "%=", 2), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalNumberManipulator_ModInPlaceSimple), _jobToProcessThisEvent);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _requestArgument));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Processor_AddJobWithName(_processor, _jobToProcessThisEvent, Machine_GenerateUID((((ExternalNumberManipulator) (_self->entity))->_machine)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _requestArgument);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: ModInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_ModInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: ModInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:ModInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:ModInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_ModInPlace(_number, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "%=", 2));
	ListMap_MessageSetReceiver(_reply, _receiver);
	Processor_SendMessage(_processor, _reply);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: ModInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Increment(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Increment begined.")
	ASSERT_C ( "ExternalNumberManipulator:Increment --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Increment --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_Inc(_number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "++", 2));
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Increment ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Decrement(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Decrement begined.")
	ASSERT_C ( "ExternalNumberManipulator:Decrement --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Decrement --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_Dec(_number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "--", 2));
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Decrement ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Absolute(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Absolute begined.")
	ASSERT_C ( "ExternalNumberManipulator:Absolute --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Absolute --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _number;
	_number = Number_Abs(ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _cloneUID;
	_cloneUID = ExternalActorManipulator_CloneUIDActorInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_actor), Processor_ContextActorUID(_processor));
	Object _clone;
	_clone = Machine_UIDToActor((((ExternalNumberManipulator) (_self->entity))->_machine), _cloneUID);
	ListMap_Add(ListMap_ActorProperties(_clone), StringFactory_FromUTF8(_stringFactory, "Число", 10), _number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _cloneUID);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Модуль", 12));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Absolute ended.")
	return toReturn;
}

Object ExternalNumberManipulator_NotifyRequest(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: NotifyRequest begined.")
	ASSERT_C ( "ExternalNumberManipulator:NotifyRequest --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:NotifyRequest --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _request;
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20));
	if((Logic_Not(ListMap_Contains(ListMap_ActorProperties(_actor), StringFactory_FromUTF8(_stringFactory, "Значения при оповещении", 44)))) != _false)
	{
		ListMap_ActorSetProperty(_actor, ExternalEntitiesFactory_CreateEmptyListMap(_entitiesFactory), StringFactory_FromUTF8(_stringFactory, "Значения при оповещении", 44));
	}
	ListMap_ActorAddNotificationRequest(_actor, _request);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Значение", 16)), _nil) != _equal)) != _false)
	{
		Object _msg;
		_msg = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetReceiver(_msg, ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
		ListMap_MessageSetTypeRequest(_msg);
		ListMap_MessageSetRequest(_msg, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20));
		ListMap_Add(_msg, StringFactory_FromUTF8(_stringFactory, "Условие", 14), StringFactory_FromUTF8(_stringFactory, "Значение изменилось", 37));
		Processor_SendMessage(_processor, _msg);
	}
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object _reply;
	_reply = Object_TempDeepClone(_request);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Текущее значение", 31), ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_request));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: NotifyRequest ended.")
	return toReturn;
}

Object ExternalNumberManipulator_CurrentValueReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: CurrentValueReceived begined.")
	ASSERT_C ( "ExternalNumberManipulator:CurrentValueReceived --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:CurrentValueReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _receivedMessage;
	_receivedMessage = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Текущее значение получено", 48));
	ListMap_Add(ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Значения при оповещении", 44)), ListMap_MessageSender(_receivedMessage), ListMap_NumberAt(_receivedMessage, StringFactory_FromUTF8(_stringFactory, "Текущее значение", 31)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_MessageType(_receivedMessage), StringFactory_FromUTF8(_stringFactory, "Оповещение", 20)) == _equal)) != _false)
	{
		Object _request;
		_request = Object_TempDeepClone(_receivedMessage);
		ListMap_MessageSetTypeRequest(_request);
		ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20));
		ListMap_MessageSetReceiver(_request, ListMap_MessageSender(_receivedMessage));
		Processor_SendMessage(_processor, _request);
	}
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: CurrentValueReceived ended.")
	return toReturn;
}

Object ExternalNumberManipulator_CheckForNotifications(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: CheckForNotifications begined.")
	ASSERT_C ( "ExternalNumberManipulator:CheckForNotifications --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:CheckForNotifications --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _notifications;
	_notifications = ListMap_ActorNotificationRequests(_actor);
	Object _currentValue;
	_currentValue = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _prevValue;
	_prevValue = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Число (предыдущее значение)", 50));
	Object _notificationsIterator;
	_notificationsIterator = List_First(_notifications);
	while((Logic_Not(ListIterator_ThisEnd(_notificationsIterator))) != _false)
	{
		Object _request;
		_request = ListIterator_ListMapData(_notificationsIterator);
		Object _condition;
		_condition = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Условие", 14));
		Object _value;
		_value = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
		Object _valuesValue;
		_valuesValue = _nil;
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) != _equal)) != _false)
		{
			_valuesValue = ListMap_ObjectAt(ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Значения при оповещении", 44)), _value);
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_valuesValue, _nil) == _equal)) != _false)
			{
				ListIterator_Next(_notificationsIterator);
				continue;
			}
		}
		Object _shouldNotify;
		_shouldNotify = _false;
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_condition, StringFactory_FromUTF8(_stringFactory, ">", 1)) == _equal)) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentValue, _valuesValue) == _greater)) != _false)
			{
				_shouldNotify = _true;
			}
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_condition, StringFactory_FromUTF8(_stringFactory, "<", 1)) == _equal)) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentValue, _valuesValue) == _less)) != _false)
			{
				_shouldNotify = _true;
			}
		}
		else if((Logic_Or(LogicFactory_FromLong(_logicFactory, Object_Compare(_condition, StringFactory_FromUTF8(_stringFactory, "=", 1)) == _equal), LogicFactory_FromLong(_logicFactory, Object_Compare(_condition, StringFactory_FromUTF8(_stringFactory, "==", 2)) == _equal))) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentValue, _valuesValue) == _equal)) != _false)
			{
				_shouldNotify = _true;
			}
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_condition, StringFactory_FromUTF8(_stringFactory, "Значение изменилось", 37)) == _equal)) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_currentValue, _prevValue) != _equal)) != _false)
			{
				_shouldNotify = _true;
			}
		}
		else
		{
			Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное условие на оповещение: ", 67));
			Console_WriteLnString(_console, _condition);
			ListIterator_Prev(_notificationsIterator);
		}
		if((_shouldNotify) != _false)
		{
			Object _notifyMessage;
			_notifyMessage = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
			ListMap_MessageSetTypeNotification(_notifyMessage);
			ListMap_Add(_notifyMessage, StringFactory_FromUTF8(_stringFactory, "Условие", 14), _condition);
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) != _equal)) != _false)
			{
				ListMap_Add(_notifyMessage, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _value);
			}
			ListMap_Add(_notifyMessage, StringFactory_FromUTF8(_stringFactory, "Текущее значение", 31), _currentValue);
			ListMap_MessageSetReceiver(_notifyMessage, ListMap_MessageSender(_request));
			Processor_SendMessage(_processor, _notifyMessage);
			ListIterator_ThisRemove(_notificationsIterator);
		}
		ListIterator_Next(_notificationsIterator);
	}
	ListMap_ActorSetProperty(_actor, Object_TempClone(_currentValue), StringFactory_FromUTF8(_stringFactory, "Число (предыдущее значение)", 50));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: CheckForNotifications ended.")
	return toReturn;
}
