#include "internals/basics.h"
#include "internals/ExternalListMapManipulator/imports.h"


Object ExternalListMapManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalListMapManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalListMapManipulator));
	_self->gid =  5014739757341874176ull;
	Object_SetComparator(_self, &ExternalListMapManipulator_Compare);
	Object_SetDestructor(_self, &ExternalListMapManipulator_Destroy);
	Object_SetCloner(_self, &ExternalListMapManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalListMapManipulator_DeepClone);
	((ExternalListMapManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalListMapManipulator_Init(_self);
	DPOPS ("ExternalListMapManipulator: Create ended.")
	return _self;
}

Object ExternalListMapManipulator_Init(Object _self)
{
	DPUSHS ("ExternalListMapManipulator: Init begined.")
	ASSERT_C ( "ExternalListMapManipulator:Init --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: Init ended.")
	return toReturn;
}

Object ExternalListMapManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalListMapManipulator: Clone begined.")
	ASSERT_C ( "ExternalListMapManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalListMapManipulator: Clone ended.")
	return toReturn;
}

Object ExternalListMapManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalListMapManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalListMapManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalListMapManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalListMapManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalListMapManipulator: Destroy begined.")
	ASSERT_C ( "ExternalListMapManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalListMapManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalListMapManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalListMapManipulator: Compare begined.")
	ASSERT_C ( "ExternalListMapManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  5014739757341874176ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalListMapManipulator: Compare ended.")
	return toReturn;
}

Object ExternalListMapManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalListMapManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalListMapManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalListMapManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalListMapManipulator_CreateUIDListMapFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalListMapManipulator: CreateUIDListMapFromUIDActor begined.")
	ASSERT_C ( "ExternalListMapManipulator:CreateUIDListMapFromUIDActor --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:CreateUIDListMapFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListMapManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Послать всем объектам", 40), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_SendToAll), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListMapManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Объект на позиции", 32), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtGet), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListMapManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtSend), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListMapManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Добавить объект на позицию", 49), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtInsert), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListMapManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Размер", 12), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_Size), _job);
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalListMapManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа отображение списков", 67));
	Object toReturn = _uid;
	DPOPS ("ExternalListMapManipulator: CreateUIDListMapFromUIDActor ended.")
	return toReturn;
}

Object ExternalListMapManipulator_Size(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: Size begined.")
	ASSERT_C ( "ExternalListMapManipulator:Size --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:Size --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Размер", 12), ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListMapManipulator) (_self->entity))->_machine)), ListMap_Size(ListMap_ActorProperty(Processor_ContextActor(_processor), StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37)))));
	Processor_SendReplyForMessage(_processor, _message, StringFactory_FromUTF8(_stringFactory, "Размер", 12));
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: Size ended.")
	return toReturn;
}

Object ExternalListMapManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(Object _self, Object _processor, Object _message, Object _positionUID, Object _method)
{
	DPUSHS ("ExternalListMapManipulator: InProcessorWithMessageGetPositionAndThenInvokeMethod begined.")
	ASSERT_C ( "ExternalListMapManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListMapManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "ExternalListMapManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _positionUID.", _positionUID->gid ==  3732711262168886272ull || _positionUID == _nil )
	ASSERT_C ( "ExternalListMapManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _method.", _method->gid == 14849865630305968128ull || _method == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ActorSetJob(_actor, _job, Machine_GenerateUID((((ExternalListMapManipulator) (_self->entity))->_machine)));
	ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _message);
	ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _method);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_PositionReceived), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46));
	ListMap_MessageSetReceiver(_request, _positionUID);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: InProcessorWithMessageGetPositionAndThenInvokeMethod ended.")
	return toReturn;
}

Object ExternalListMapManipulator_PositionReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: PositionReceived begined.")
	ASSERT_C ( "ExternalListMapManipulator:PositionReceived --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:PositionReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _method;
	_method = ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Метод", 10));
	Method_Invoke(_method, _self, _processor, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), StringFactory_FromUTF8(_stringFactory, "Значение", 16)), ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	Processor_FinishThisJob(_processor);
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: PositionReceived ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtInsertInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListMapManipulator: AtInsertInternal begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtInsertInternal --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtInsertInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListMapManipulator:AtInsertInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _listMap;
	_listMap = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _listOfActors;
	_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
	ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_listMap), _position) == _less)) != _false)
	{
		ListMap_MessageSetReplyFail(_reply);
	}
	else
	{
		ListMap_MessageSetReplySuccess(_reply);
		Object _value;
		_value = List_ObjectAtPosition(_listMap, _position);
		if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
		{
			_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListMapManipulator) (_self->entity))->_machine)), _value);
		}
		ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Замещенное значение", 37), _value);
		List_ReplaceAtPositionWithObject(_listMap, _position, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
		if((Object_IsNil(ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Простой", 14)))) != _false)
		{
			List_RemoveFirst(_listOfActors, _position);
		}
		else
		{
			List_PushSorted(_listOfActors, _position);
		}
	}
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtInsertInternal ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtInsert(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: AtInsert begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtInsert --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtInsert --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Добавить объект на позицию", 49));
	ExternalListMapManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtInsertInternal));
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtInsert ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtGetInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListMapManipulator: AtGetInternal begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtGetInternal --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtGetInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListMapManipulator:AtGetInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _listMap;
	_listMap = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _listOfActors;
	_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
	ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_listMap), _position) != _greater)) != _false)
	{
		ListMap_MessageSetReplyFail(_reply);
	}
	else
	{
		ListMap_MessageSetReplySuccess(_reply);
		Object _value;
		_value = List_ObjectAtPosition(_listMap, _position);
		if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
		{
			_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListMapManipulator) (_self->entity))->_machine)), _value);
		}
		ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Объект", 12), _value);
	}
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtGetInternal ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtGet(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: AtGet begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtGet --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtGet --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68));
	ExternalListMapManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtGetInternal));
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtGet ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtSendInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListMapManipulator: AtSendInternal begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtSendInternal --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtSendInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListMapManipulator:AtSendInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _listMap;
	_listMap = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _listOfActors;
	_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_Size(_listMap), _position) != _greater)) != _false)
	{
		Object _reply;
		_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetReplyFail(_reply);
		ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
		ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
		Processor_SendMessage(_processor, _reply);
	}
	else
	{
		Object _value;
		_value = ListMap_ObjectAt(_listMap, _position);
		if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
		{
			{
				_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListMapManipulator) (_self->entity))->_machine)), _value);
			}
		}
		Object _job;
		_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
		ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_MessageSender(_message));
		ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Имя ожидаемого сообщения", 46), ListMap_ObjectAt(ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)));
		ListMap_ActorSetJob(Processor_ContextActor(_processor), Machine_GenerateUID((((ExternalListMapManipulator) (_self->entity))->_machine)), _job);
		Object _messageSlot;
		_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, ListMap_ObjectAt(ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AnswerReceived), _job);
		ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _value));
		_message = ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
		ListMap_MessageSetReceiver(_message, _value);
		Processor_SendMessage(_processor, _message);
	}
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtSendInternal ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AnswerReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: AnswerReceived begined.")
	ASSERT_C ( "ExternalListMapManipulator:AnswerReceived --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AnswerReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _receiver;
	_receiver = ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16));
	Object _incapsulatedMessage;
	_incapsulatedMessage = Processor_MessageInMessageSlot(_processor, ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Имя ожидаемого сообщения", 46)));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeReply(_message);
	ListMap_MessageSetRequest(_message, StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68));
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _incapsulatedMessage);
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage(_processor, _message);
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AnswerReceived ended.")
	return toReturn;
}

Object ExternalListMapManipulator_AtSend(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: AtSend begined.")
	ASSERT_C ( "ExternalListMapManipulator:AtSend --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:AtSend --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68));
	ExternalListMapManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_AtSendInternal));
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: AtSend ended.")
	return toReturn;
}

Object ExternalListMapManipulator_SendToAll(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: SendToAll begined.")
	ASSERT_C ( "ExternalListMapManipulator:SendToAll --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:SendToAll --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _request;
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать всем объектам", 40));
	Object _messageToSend;
	_messageToSend = ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _listMap;
	_listMap = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Отображение списков", 37));
	Object _listOfActors;
	_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object _handler;
	_handler = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ActorSetProperty(_handler, ListMap_Size(_listMap), StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	ListMap_ActorSetProperty(_handler, _request, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	ListMap_ActorSetProperty(_handler, StringFactory_FromUTF8(_stringFactory, "Всюду успех", 21), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	Object _actionWithAnswers;
	_actionWithAnswers = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36));
	Object _method;
	_method = _nil;
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Переотправить", 26)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_SendToAllResendAnswersHandler);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Ответить в общем", 30)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListMapManipulator_SendToAllAnswerInCommonHandler);
	}
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, ListMap_MessageRequest(_messageToSend), _self, _method, _handler);
	ListMap_ActorSetJob(_actor, _handler, Machine_GenerateUID((((ExternalListMapManipulator) (_self->entity))->_machine)));
	Object _iteratorInListMap;
	_iteratorInListMap = ListMap_First(_listMap);
	while((Logic_Not(ListMapIterator_ThisEnd(_iteratorInListMap))) != _false)
	{
		Object _receiver;
		_receiver = _nil;
		if((List_Contains(_listOfActors, ListMapIterator_ThisKey(_iteratorInListMap))) != _false)
		{
			_receiver = ListMapIterator_ThisValue(_iteratorInListMap);
		}
		else
		{
			_receiver = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListMapManipulator) (_self->entity))->_machine)), ListMapIterator_ThisValue(_iteratorInListMap));
		}
		Object _messageToSend2;
		_messageToSend2 = Object_DeepClone(_messageToSend);
		ListMap_MessageSetReceiver(_messageToSend2, _receiver);
		Processor_SendMessage(_processor, _messageToSend2);
		ListMapIterator_Next(_iteratorInListMap);
	}
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: SendToAll ended.")
	return toReturn;
}

Object ExternalListMapManipulator_SendToAllResendAnswersHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: SendToAllResendAnswersHandler begined.")
	ASSERT_C ( "ExternalListMapManipulator:SendToAllResendAnswersHandler --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:SendToAllResendAnswersHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _answersRemained;
	_answersRemained = ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	Object _request;
	_request = ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	Object _receiver;
	_receiver = ListMap_MessageSender(_request);
	Object _incapsulatedMessage;
	_incapsulatedMessage = Processor_MessageInMessageSlot(_processor, ListMap_MessageRequest(ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18))));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReceiver(_message, _receiver);
	ListMap_MessageSetTypeNotification(_message);
	ListMap_MessageSetRequest(_message, ListMap_MessageRequest(_request));
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _incapsulatedMessage);
	Processor_SendMessage(_processor, _message);
	Number_Dec(_answersRemained);
	if((ListMap_MessageReplyIsFail(_incapsulatedMessage)) != _false)
	{
		ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Неудача", 14), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_answersRemained, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
	{
		Object _summaryAnswer;
		_summaryAnswer = Object_TempDeepClone(_request);
		ListMap_MessageSetTypeReply(_summaryAnswer);
		ListMap_MessageSetReplySuccess(_summaryAnswer);
		ListMap_Add(_summaryAnswer, StringFactory_FromUTF8(_stringFactory, "Отчет", 10), ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24)));
		ListMap_MessageSetReceiver(_summaryAnswer, _receiver);
		Processor_SendMessage(_processor, _summaryAnswer);
		Processor_FinishThisJob(_processor);
	}
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: SendToAllResendAnswersHandler ended.")
	return toReturn;
}

Object ExternalListMapManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListMapManipulator: SendToAllAnswerInCommonHandler begined.")
	ASSERT_C ( "ExternalListMapManipulator:SendToAllAnswerInCommonHandler --- Checking for correct object type failed.", _self->gid ==  5014739757341874176ull )
	ASSERT_C ( "ExternalListMapManipulator:SendToAllAnswerInCommonHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _answersRemained;
	_answersRemained = ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	Object _request;
	_request = ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	Object _receiver;
	_receiver = ListMap_MessageSender(_request);
	Number_Dec(_answersRemained);
	if((ListMap_MessageReplyIsFail(Processor_MessageInMessageSlot(_processor, ListMap_MessageRequest(ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)))))) != _false)
	{
		ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Неудача", 14), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_answersRemained, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
	{
		Object _summaryAnswer;
		_summaryAnswer = Object_TempDeepClone(_request);
		ListMap_MessageSetTypeReply(_summaryAnswer);
		ListMap_MessageSetReplySuccess(_summaryAnswer);
		ListMap_Add(_summaryAnswer, StringFactory_FromUTF8(_stringFactory, "Отчет", 10), ListMap_ActorProperty(_job, StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24)));
		ListMap_MessageSetReceiver(_summaryAnswer, _receiver);
		Processor_SendMessage(_processor, _summaryAnswer);
		Processor_FinishThisJob(_processor);
	}
	Object toReturn = _self;
	DPOPS ("ExternalListMapManipulator: SendToAllAnswerInCommonHandler ended.")
	return toReturn;
}
