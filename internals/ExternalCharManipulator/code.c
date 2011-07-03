#include "internals/basics.h"
#include "internals/ExternalCharManipulator/imports.h"


Object ExternalCharManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalCharManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalCharManipulator));
	_self->gid =  1458704701250809600ull;
	Object_SetComparator(_self, &ExternalCharManipulator_Compare);
	Object_SetDestructor(_self, &ExternalCharManipulator_Destroy);
	Object_SetCloner(_self, &ExternalCharManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalCharManipulator_DeepClone);
	((ExternalCharManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalCharManipulator_Init(_self);
	DPOPS ("ExternalCharManipulator: Create ended.")
	return _self;
}

Object ExternalCharManipulator_Init(Object _self)
{
	DPUSHS ("ExternalCharManipulator: Init begined.")
	ASSERT_C ( "ExternalCharManipulator:Init --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	Object toReturn = _self;
	DPOPS ("ExternalCharManipulator: Init ended.")
	return toReturn;
}

Object ExternalCharManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalCharManipulator: Clone begined.")
	ASSERT_C ( "ExternalCharManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalCharManipulator: Clone ended.")
	return toReturn;
}

Object ExternalCharManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalCharManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalCharManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalCharManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalCharManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalCharManipulator: Destroy begined.")
	ASSERT_C ( "ExternalCharManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalCharManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalCharManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalCharManipulator: Compare begined.")
	ASSERT_C ( "ExternalCharManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  1458704701250809600ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalCharManipulator: Compare ended.")
	return toReturn;
}

Object ExternalCharManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalCharManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalCharManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalCharManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalCharManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalCharManipulator_CreateUIDCharFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalCharManipulator: CreateUIDCharFromUIDActor begined.")
	ASSERT_C ( "ExternalCharManipulator:CreateUIDCharFromUIDActor --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:CreateUIDCharFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalCharManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Код", 6), _self, MethodFactory_FromPointer(_methodFactory, &ExternalCharManipulator_GetCode), _job);
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalCharManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Установить код", 27), _self, MethodFactory_FromPointer(_methodFactory, &ExternalCharManipulator_SetCode), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Код", 6)));
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalCharManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа символа", 44));
	Object toReturn = _uid;
	DPOPS ("ExternalCharManipulator: CreateUIDCharFromUIDActor ended.")
	return toReturn;
}

Object ExternalCharManipulator_CodeSimpleNumberReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalCharManipulator: CodeSimpleNumberReceived begined.")
	ASSERT_C ( "ExternalCharManipulator:CodeSimpleNumberReceived --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:CodeSimpleNumberReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Char_SetCode(ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Символ", 12)), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение", 16), StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44)));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReceiver(_reply, ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Заказчик", 16)));
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "Установить код", 27));
	Processor_SendMessage(_processor, _reply);
	Processor_FinishThisJob(_processor);
	Object toReturn = _self;
	DPOPS ("ExternalCharManipulator: CodeSimpleNumberReceived ended.")
	return toReturn;
}

Object ExternalCharManipulator_SetCode(Object _self, Object _processor)
{
	DPUSHS ("ExternalCharManipulator: SetCode begined.")
	ASSERT_C ( "ExternalCharManipulator:SetCode --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:SetCode --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _request;
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Установить код", 27));
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _code;
	_code = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Код", 6));
	if((LogicFactory_FromLong(_logicFactory, _code->gid == 15425740279749906432ull)) != _false)
	{
		Char_SetCode(ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Символ", 12)), _code);
		Object _reply;
		_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetReplySuccess(_reply);
		Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Установить код", 27));
	}
	else
	{
		Object _codeRequest;
		_codeRequest = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetReceiver(_codeRequest, _code);
		ListMap_MessageSetTypeRequest(_codeRequest);
		ListMap_MessageSetRequest(_codeRequest, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
		Object _job;
		_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
		ListMap_ActorSetProperty(_job, ListMap_MessageSender(_request), StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
		Object _messageSlot;
		_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalCharManipulator_CodeSimpleNumberReceived), _job);
		Processor_AddJobWithName(_processor, _job, Machine_GenerateUID((((ExternalCharManipulator) (_self->entity))->_machine)));
		Processor_SendMessage(_processor, _codeRequest);
	}
	Object toReturn = _self;
	DPOPS ("ExternalCharManipulator: SetCode ended.")
	return toReturn;
}

Object ExternalCharManipulator_GetCode(Object _self, Object _processor)
{
	DPUSHS ("ExternalCharManipulator: GetCode begined.")
	ASSERT_C ( "ExternalCharManipulator:GetCode --- Checking for correct object type failed.", _self->gid ==  1458704701250809600ull )
	ASSERT_C ( "ExternalCharManipulator:GetCode --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Код", 6), ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalCharManipulator) (_self->entity))->_machine)), Char_GetMutableCode(ListMap_ActorProperty(Processor_ContextActor(_processor), StringFactory_FromUTF8(_stringFactory, "Символ", 12)))));
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Код", 6));
	Object toReturn = _self;
	DPOPS ("ExternalCharManipulator: GetCode ended.")
	return toReturn;
}
