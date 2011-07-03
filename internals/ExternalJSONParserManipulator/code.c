#include "internals/basics.h"
#include "internals/ExternalJSONParserManipulator/imports.h"


Object ExternalJSONParserManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalJSONParserManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalJSONParserManipulator));
	_self->gid =  6195725569809723392ull;
	Object_SetComparator(_self, &ExternalJSONParserManipulator_Compare);
	Object_SetDestructor(_self, &ExternalJSONParserManipulator_Destroy);
	Object_SetCloner(_self, &ExternalJSONParserManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalJSONParserManipulator_DeepClone);
	((ExternalJSONParserManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalJSONParserManipulator_Init(_self);
	DPOPS ("ExternalJSONParserManipulator: Create ended.")
	return _self;
}

Object ExternalJSONParserManipulator_Init(Object _self)
{
	DPUSHS ("ExternalJSONParserManipulator: Init begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:Init --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	Object toReturn = _self;
	DPOPS ("ExternalJSONParserManipulator: Init ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalJSONParserManipulator: Clone begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalJSONParserManipulator: Clone ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalJSONParserManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalJSONParserManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalJSONParserManipulator: Destroy begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalJSONParserManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalJSONParserManipulator: Compare begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  6195725569809723392ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalJSONParserManipulator: Compare ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalJSONParserManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalJSONParserManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalJSONParserManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_CreateUIDJSONParserFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalJSONParserManipulator: CreateUIDJSONParserFromUIDActor begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:CreateUIDJSONParserFromUIDActor --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:CreateUIDJSONParserFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalJSONParserManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Создать объект из простой строки", 60), _self, MethodFactory_FromPointer(_methodFactory, &ExternalJSONParserManipulator_CreateEntityFromSimpleString), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Простая строка", 27)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalJSONParserManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Создать объект из строки", 45), _self, MethodFactory_FromPointer(_methodFactory, &ExternalJSONParserManipulator_CreateEntityFromString), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Код", 6)));
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalJSONParserManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа создателя", 48));
	Object toReturn = _uid;
	DPOPS ("ExternalJSONParserManipulator: CreateUIDJSONParserFromUIDActor ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_InternalCreateEntityFromSimpleString(Object _self, Object _processor, Object _simpleString, Object _reply)
{
	DPUSHS ("ExternalJSONParserManipulator: InternalCreateEntityFromSimpleString begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:InternalCreateEntityFromSimpleString --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:InternalCreateEntityFromSimpleString --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalJSONParserManipulator:InternalCreateEntityFromSimpleString --- Checking for correct parameter type failed at parameter _simpleString.", _simpleString->gid ==  3732711262168886272ull || _simpleString == _nil )
	ASSERT_C ( "ExternalJSONParserManipulator:InternalCreateEntityFromSimpleString --- Checking for correct parameter type failed at parameter _reply.", _reply->gid ==  2108332898258556672ull || _reply == _nil )
	ListMap_MessageSetTypeReply(_reply);
	Object _result;
	_result = JSONParser_ParseString(_jsonParser, _simpleString);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_result, (((JSONParser) (_jsonParser->entity))->_error)) == _equal)) != _false)
	{
		ListMap_MessageSetReplyFail(_reply);
		Processor_SendMessage(_processor, _reply);
	}
	else
	{
		ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Объект", 12), ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalJSONParserManipulator) (_self->entity))->_machine)), _result));
		ListMap_MessageSetReplySuccess(_reply);
		Processor_SendMessage(_processor, _reply);
	}
	Object toReturn = _self;
	DPOPS ("ExternalJSONParserManipulator: InternalCreateEntityFromSimpleString ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_CreateEntityFromSimpleString(Object _self, Object _processor)
{
	DPUSHS ("ExternalJSONParserManipulator: CreateEntityFromSimpleString begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:CreateEntityFromSimpleString --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:CreateEntityFromSimpleString --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Создать объект из простой строки", 60));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "Создать объект из простой строки", 60));
	Object toReturn = ExternalJSONParserManipulator_InternalCreateEntityFromSimpleString(_self, _processor, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Простая строка", 27)), _reply);
	DPOPS ("ExternalJSONParserManipulator: CreateEntityFromSimpleString ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_CreateEntityFromString(Object _self, Object _processor)
{
	DPUSHS ("ExternalJSONParserManipulator: CreateEntityFromString begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:CreateEntityFromString --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:CreateEntityFromString --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Создать объект из строки", 45));
	Object _stringUID;
	_stringUID = ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Строка", 12));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46));
	ListMap_MessageSetReceiver(_request, _stringUID);
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ActorSetProperty(_job, ListMap_MessageSender(_message), StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), _self, MethodFactory_FromPointer(_methodFactory, &ExternalJSONParserManipulator_SimpleStringReceived), _job);
	Processor_AddJobWithName(_processor, _job, Machine_GenerateUID((((ExternalJSONParserManipulator) (_self->entity))->_machine)));
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalJSONParserManipulator: CreateEntityFromString ended.")
	return toReturn;
}

Object ExternalJSONParserManipulator_SimpleStringReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalJSONParserManipulator: SimpleStringReceived begined.")
	ASSERT_C ( "ExternalJSONParserManipulator:SimpleStringReceived --- Checking for correct object type failed.", _self->gid ==  6195725569809723392ull )
	ASSERT_C ( "ExternalJSONParserManipulator:SimpleStringReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReceiver(_reply, ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Заказчик", 16)));
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "Создать объект из строки", 45));
	Object def = ExternalJSONParserManipulator_InternalCreateEntityFromSimpleString(_self, _processor, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), StringFactory_FromUTF8(_stringFactory, "Значение", 16)), _reply);
	Processor_FinishThisJob(_processor);
	DPOPS ("ExternalJSONParserManipulator: SimpleStringReceived ended.")
	return def;
}
