#include "internals/basics.h"
#include "internals/ExternalListManipulator/imports.h"


Object ExternalListManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalListManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalListManipulator));
	_self->gid =  3902231640652582912ull;
	Object_SetComparator(_self, &ExternalListManipulator_Compare);
	Object_SetDestructor(_self, &ExternalListManipulator_Destroy);
	Object_SetCloner(_self, &ExternalListManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalListManipulator_DeepClone);
	((ExternalListManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalListManipulator_Init(_self);
	DPOPS ("ExternalListManipulator: Create ended.")
	return _self;
}

Object ExternalListManipulator_Init(Object _self)
{
	DPUSHS ("ExternalListManipulator: Init begined.")
	ASSERT_C ( "ExternalListManipulator:Init --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: Init ended.")
	return toReturn;
}

Object ExternalListManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalListManipulator: Clone begined.")
	ASSERT_C ( "ExternalListManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalListManipulator: Clone ended.")
	return toReturn;
}

Object ExternalListManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalListManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalListManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalListManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalListManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalListManipulator: Destroy begined.")
	ASSERT_C ( "ExternalListManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalListManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalListManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalListManipulator: Compare begined.")
	ASSERT_C ( "ExternalListManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:Compare --- Checking for correct parameter type failed at parameter _manipulator.", _manipulator->gid ==  3902231640652582912ull || _manipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalListManipulator: Compare ended.")
	return toReturn;
}

Object ExternalListManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalListManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalListManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalListManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalListManipulator_CreateUIDListFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalListManipulator: CreateUIDListFromUIDActor begined.")
	ASSERT_C ( "ExternalListManipulator:CreateUIDListFromUIDActor --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:CreateUIDListFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Создать список с целыми числами на интервале", 82), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_ListWithIntegersInInterval), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Послать всем объектам", 40), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAll), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Объект на позиции", 32), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtGet), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtSend), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Заменить объект на позиции", 49), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtReplace), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Добавить объект на позицию", 49), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtInsert), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Размер", 12), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_Size), _job);
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalListManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа списка", 42));
	Object toReturn = _uid;
	DPOPS ("ExternalListManipulator: CreateUIDListFromUIDActor ended.")
	return toReturn;
}

Object ExternalListManipulator_ListWithIntegersInIntervalHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: ListWithIntegersInIntervalHandler begined.")
	ASSERT_C ( "ExternalListManipulator:ListWithIntegersInIntervalHandler --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:ListWithIntegersInIntervalHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _leftAnswer;
	_leftAnswer = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от левой границы", 68));
	Object _rightAnswer;
	_rightAnswer = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от правой границы", 70));
	Object _list;
	_list = ExternalEntitiesFactory_CreateEmptyList(_entitiesFactory);
	Object _cur;
	_cur = Number_Add(ListMap_NumberAt(_leftAnswer, StringFactory_FromUTF8(_stringFactory, "Значение", 16)), NumberFactory_FromLong(_numberFactory, 1));
	Object _right;
	_right = ListMap_NumberAt(_rightAnswer, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_cur, _right) == _less)) != _false)
	{
		List_PushBack(_list, Object_TempClone(_cur));
		Number_Inc(_cur);
	}
	Object _uid;
	_uid = ExternalActorsFactory_CreateList(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), _list);
	Object _reply;
	_reply = Object_TempDeepClone(ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Сообщение заказа", 31)));
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_reply));
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Список", 12), _uid);
	Processor_SendMessage(_processor, _reply);
	Processor_FinishThisJob(_processor);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: ListWithIntegersInIntervalHandler ended.")
	return toReturn;
}

Object ExternalListManipulator_ListWithIntegersInInterval(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: ListWithIntegersInInterval begined.")
	ASSERT_C ( "ExternalListManipulator:ListWithIntegersInInterval --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:ListWithIntegersInInterval --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _request;
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Создать список с целыми числами на интервале", 82));
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _leftElement;
	_leftElement = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25));
	Object _rightElement;
	_rightElement = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27));
	Object _handler;
	_handler = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _handlerName;
	_handlerName = Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine));
	ListMap_ActorSetJob(_actor, _handler, _handlerName);
	Object _stage;
	_stage = ExternalEntitiesFactory_CreateEmptyJobStage(_entitiesFactory);
	ListMap_StageSetMethod(_stage, StringFactory_FromUTF8(_stringFactory, "Единственный метод", 35));
	ListMap_JobSetStage(_handler, _stage, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37));
	Object _messageSlotForLeft;
	_messageSlotForLeft = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	ListMap_MessageSlotSetCondition(_messageSlotForLeft, ExternalEntitiesFactory_CreateConditionEqualityWithField(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), StringFactory_FromUTF8(_stringFactory, "Левая граница", 25)));
	ListMap_MessageSlotSetCondition(_messageSlotForLeft, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	ListMap_JobSetMessageSlot(_handler, _messageSlotForLeft, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от левой границы", 68));
	Processor_AttachToStageMessageSlotInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37), StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от левой границы", 68), _handlerName);
	Object _messageSlotForRight;
	_messageSlotForRight = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	ListMap_MessageSlotSetCondition(_messageSlotForRight, ExternalEntitiesFactory_CreateConditionEqualityWithField(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), StringFactory_FromUTF8(_stringFactory, "Правая граница", 27)));
	ListMap_MessageSlotSetCondition(_messageSlotForRight, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	ListMap_JobSetMessageSlot(_handler, _messageSlotForRight, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от правой границы", 70));
	Processor_AttachToStageMessageSlotInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37), StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от правой границы", 70), _handlerName);
	ListMap_ActorSetBasicMethod(_handler, _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_ListWithIntegersInIntervalHandler), StringFactory_FromUTF8(_stringFactory, "Единственный метод", 35));
	ListMap_ActorSetProperty(_handler, _request, StringFactory_FromUTF8(_stringFactory, "Сообщение заказа", 31));
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25), ListMap_ActorFields(_handler), _leftElement);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27), ListMap_ActorFields(_handler), _rightElement);
	Object _msg;
	_msg = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_msg);
	ListMap_MessageSetRequest(_msg, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_msg, _leftElement);
	Processor_SendMessage(_processor, _msg);
	_msg = Object_TempDeepClone(_msg);
	ListMap_MessageSetReceiver(_msg, _rightElement);
	Processor_SendMessage(_processor, _msg);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: ListWithIntegersInInterval ended.")
	return toReturn;
}

Object ExternalListManipulator_SendToAllResendAnswersHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: SendToAllResendAnswersHandler begined.")
	ASSERT_C ( "ExternalListManipulator:SendToAllResendAnswersHandler --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SendToAllResendAnswersHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
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
	DPOPS ("ExternalListManipulator: SendToAllResendAnswersHandler ended.")
	return toReturn;
}

Object ExternalListManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: SendToAllAnswerInCommonHandler begined.")
	ASSERT_C ( "ExternalListManipulator:SendToAllAnswerInCommonHandler --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SendToAllAnswerInCommonHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
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
	DPOPS ("ExternalListManipulator: SendToAllAnswerInCommonHandler ended.")
	return toReturn;
}

Object ExternalListManipulator_SendToAll(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: SendToAll begined.")
	ASSERT_C ( "ExternalListManipulator:SendToAll --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SendToAll --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _request;
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать всем объектам", 40));
	Object _messageToSend;
	_messageToSend = ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _handler;
	_handler = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _actionWithAnswers;
	_actionWithAnswers = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36));
	Object _method;
	_method = _nil;
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Переотправить", 26)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAllResendAnswersHandler);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Ответить в общем", 30)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAllAnswerInCommonHandler);
	}
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, ListMap_MessageRequest(_messageToSend), _self, _method, _handler);
	ListMap_ActorSetJob(_actor, _handler, Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine)));
	Object _list;
	_list = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Object _listOfActors;
	_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object _iteratorInList;
	_iteratorInList = List_First(_list);
	Object _iteratorInListOfActors;
	_iteratorInListOfActors = List_First(_listOfActors);
	Object _position;
	_position = NumberFactory_FromLong(_numberFactory, 0);
	while((Logic_Not(ListIterator_ThisEnd(_iteratorInList))) != _false)
	{
		Object _data;
		_data = ListIterator_ThisData(_iteratorInList);
		Object _flag;
		_flag = _true;
		Object _receiver;
		_receiver = _nil;
		if((Logic_Not(ListIterator_ThisEnd(_iteratorInListOfActors))) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, ListIterator_NumberData(_iteratorInListOfActors)) == _equal)) != _false)
			{
				_flag = _false;
				_receiver = _data;
				ListIterator_Next(_iteratorInListOfActors);
			}
		}
		if((_flag) != _false)
		{
			_receiver = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), _data);
		}
		Object _messageToSend2;
		_messageToSend2 = Object_TempDeepClone(_messageToSend);
		ListMap_MessageSetReceiver(_messageToSend2, _receiver);
		Processor_SendMessage(_processor, _messageToSend2);
		ListIterator_Next(_iteratorInList);
		Number_Inc(_position);
	}
	ListMap_ActorSetProperty(_handler, _position, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	ListMap_ActorSetProperty(_handler, _request, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	ListMap_ActorSetProperty(_handler, StringFactory_FromUTF8(_stringFactory, "Всюду успех", 21), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: SendToAll ended.")
	return toReturn;
}

Object ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(Object _self, Object _processor, Object _message, Object _positionUID, Object _method)
{
	DPUSHS ("ExternalListManipulator: InProcessorWithMessageGetPositionAndThenInvokeMethod begined.")
	ASSERT_C ( "ExternalListManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "ExternalListManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _positionUID.", _positionUID->gid ==  3732711262168886272ull || _positionUID == _nil )
	ASSERT_C ( "ExternalListManipulator:InProcessorWithMessageGetPositionAndThenInvokeMethod --- Checking for correct parameter type failed at parameter _method.", _method->gid == 14849865630305968128ull || _method == _nil )
	Object _actor;
	_actor = Processor_ContextActor(_processor);
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ActorSetJob(_actor, _job, Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine)));
	ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _message);
	ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _method);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_PositionReceived), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request, _positionUID);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: InProcessorWithMessageGetPositionAndThenInvokeMethod ended.")
	return toReturn;
}

Object ExternalListManipulator_PositionReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: PositionReceived begined.")
	ASSERT_C ( "ExternalListManipulator:PositionReceived --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:PositionReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _method;
	_method = ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Метод", 10));
	Method_Invoke(_method, _self, _processor, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение", 16)), ListMap_ActorProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	Processor_FinishThisJob(_processor);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: PositionReceived ended.")
	return toReturn;
}

Object ExternalListManipulator_AtGetInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListManipulator: AtGetInternal begined.")
	ASSERT_C ( "ExternalListManipulator:AtGetInternal --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtGetInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListManipulator:AtGetInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	if((LogicFactory_FromLong(_logicFactory, _position->gid == 15425740279749906432ull)) != _false)
	{
		Object _actor;
		_actor = Processor_ContextActor(_processor);
		Object _list;
		_list = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список", 12));
		Object _listOfActors;
		_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
		Object _reply;
		_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
		ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_list), _position) != _greater)) != _false)
		{
			ListMap_MessageSetReplyFail(_reply);
		}
		else
		{
			ListMap_MessageSetReplySuccess(_reply);
			Object _value;
			_value = List_ObjectAtPosition(_list, _position);
			if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
			{
				_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), _value);
			}
			ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Объект", 12), _value);
		}
		Processor_SendMessage(_processor, _reply);
	}
	else
	{
		ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, _position, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtGetInternal));
	}
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtGetInternal ended.")
	return toReturn;
}

Object ExternalListManipulator_AtGet(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: AtGet begined.")
	ASSERT_C ( "ExternalListManipulator:AtGet --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtGet --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Объект на позиции", 32));
	ExternalListManipulator_AtGetInternal(_self, _processor, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), _message);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtGet ended.")
	return toReturn;
}

Object ExternalListManipulator_AtInsertInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListManipulator: AtInsertInternal begined.")
	ASSERT_C ( "ExternalListManipulator:AtInsertInternal --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtInsertInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListManipulator:AtInsertInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	if((LogicFactory_FromLong(_logicFactory, _position->gid == 15425740279749906432ull)) != _false)
	{
		Object _actor;
		_actor = Processor_ContextActor(_processor);
		Object _list;
		_list = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список", 12));
		Object _listOfActors;
		_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
		Object _reply;
		_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
		ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_list), _position) == _less)) != _false)
		{
			ListMap_MessageSetReplyFail(_reply);
		}
		else
		{
			ListMap_MessageSetReplySuccess(_reply);
			Object _iterator;
			_iterator = List_First(_listOfActors);
			while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
			{
				if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListIterator_NumberData(_iterator), _position) != _less)) != _false)
				{
					Number_Inc(ListIterator_NumberData(_iterator));
				}
				ListIterator_Next(_iterator);
			}
			List_AddBeforePosition(_list, _position, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
			if((Logic_Not(Object_IsNil(ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Простой", 14))))) != _false)
			{
				List_PushSorted(_listOfActors, _position);
			}
		}
		Processor_SendMessage(_processor, _reply);
	}
	else
	{
		ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, _position, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtInsertInternal));
	}
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtInsertInternal ended.")
	return toReturn;
}

Object ExternalListManipulator_AtInsert(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: AtInsert begined.")
	ASSERT_C ( "ExternalListManipulator:AtInsert --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtInsert --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Добавить объект на позицию", 49));
	ExternalListManipulator_AtInsertInternal(_self, _processor, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), _message);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtInsert ended.")
	return toReturn;
}

Object ExternalListManipulator_AtReplaceInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListManipulator: AtReplaceInternal begined.")
	ASSERT_C ( "ExternalListManipulator:AtReplaceInternal --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtReplaceInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListManipulator:AtReplaceInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	if((LogicFactory_FromLong(_logicFactory, _position->gid == 15425740279749906432ull)) != _false)
	{
		Object _actor;
		_actor = Processor_ContextActor(_processor);
		Object _list;
		_list = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список", 12));
		Object _listOfActors;
		_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
		Object _reply;
		_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
		ListMap_MessageSetRequest(_reply, ListMap_MessageRequest(_message));
		ListMap_MessageSetReceiver(_reply, ListMap_MessageSender(_message));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_list), _position) != _greater)) != _false)
		{
			ListMap_MessageSetReplyFail(_reply);
		}
		else
		{
			ListMap_MessageSetReplySuccess(_reply);
			Object _value;
			_value = List_ObjectAtPosition(_list, _position);
			if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
			{
				_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), _value);
			}
			ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Замещенный объект", 33), _value);
			List_ReplaceAtPositionWithObject(_list, _position, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
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
	}
	else
	{
		ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, _position, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtReplaceInternal));
	}
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtReplaceInternal ended.")
	return toReturn;
}

Object ExternalListManipulator_AtReplace(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: AtReplace begined.")
	ASSERT_C ( "ExternalListManipulator:AtReplace --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtReplace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Заменить объект на позиции", 49));
	ExternalListManipulator_AtReplaceInternal(_self, _processor, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), _message);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtReplace ended.")
	return toReturn;
}

Object ExternalListManipulator_AtSendInternal(Object _self, Object _processor, Object _position, Object _message)
{
	DPUSHS ("ExternalListManipulator: AtSendInternal begined.")
	ASSERT_C ( "ExternalListManipulator:AtSendInternal --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtSendInternal --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	ASSERT_C ( "ExternalListManipulator:AtSendInternal --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	if((LogicFactory_FromLong(_logicFactory, _position->gid == 15425740279749906432ull)) != _false)
	{
		Object _actor;
		_actor = Processor_ContextActor(_processor);
		Object _list;
		_list = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список", 12));
		Object _listOfActors;
		_listOfActors = ListMap_ActorProperty(_actor, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(List_Size(_list), _position) != _greater)) != _false)
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
			_value = List_ObjectAtPosition(_list, _position);
			if((Logic_Not(List_Contains(_listOfActors, _position))) != _false)
			{
				_value = ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), _value);
			}
			Object _job;
			_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
			ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_MessageSender(_message));
			ListMap_ActorSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Имя ожидаемого сообщения", 46), ListMap_ObjectAt(ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)));
			ListMap_ActorSetJob(Processor_ContextActor(_processor), Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine)), _job);
			Object _messageSlot;
			_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, ListMap_ObjectAt(ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AnswerReceived), _job);
			ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _value));
			_message = ListMap_ListMapAt(_message, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
			ListMap_MessageSetReceiver(_message, _value);
		}
		Processor_SendMessage(_processor, _message);
	}
	else
	{
		ExternalListManipulator_InProcessorWithMessageGetPositionAndThenInvokeMethod(_self, _processor, _message, _position, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_AtSendInternal));
	}
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtSendInternal ended.")
	return toReturn;
}

Object ExternalListManipulator_AnswerReceived(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: AnswerReceived begined.")
	ASSERT_C ( "ExternalListManipulator:AnswerReceived --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AnswerReceived --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
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
	DPOPS ("ExternalListManipulator: AnswerReceived ended.")
	return toReturn;
}

Object ExternalListManipulator_AtSend(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: AtSend begined.")
	ASSERT_C ( "ExternalListManipulator:AtSend --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:AtSend --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту на позиции", 68));
	ExternalListManipulator_AtSendInternal(_self, _processor, ListMap_ObjectAt(_message, StringFactory_FromUTF8(_stringFactory, "Позиция", 14)), _message);
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: AtSend ended.")
	return toReturn;
}

Object ExternalListManipulator_Size(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: Size begined.")
	ASSERT_C ( "ExternalListManipulator:Size --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:Size --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Размер", 12), ExternalActorsFactory_CreateActorFromObject(Machine_ActorsFactory((((ExternalListManipulator) (_self->entity))->_machine)), List_Size(ListMap_ActorProperty(Processor_ContextActor(_processor), StringFactory_FromUTF8(_stringFactory, "Список", 12)))));
	Processor_SendReplyForMessage(_processor, _message, StringFactory_FromUTF8(_stringFactory, "Размер", 12));
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: Size ended.")
	return toReturn;
}
