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

Object ExternalListManipulator_CreateUIDListFromUIDObject(Object _self, Object _uid)
{
	DPUSHS ("ExternalListManipulator: CreateUIDListFromUIDObject begined.")
	ASSERT_C ( "ExternalListManipulator:CreateUIDListFromUIDObject --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:CreateUIDListFromUIDObject --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Создать список с целыми числами на интервале", 82), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_ListWithIntegersInInterval), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27)));
	_messageSlot = Processor_CreateStageRequestEntityBasicMethodInJob((((Machine) ((((ExternalListManipulator) (_self->entity))->_machine)->entity))->_fakeProcessor), StringFactory_FromUTF8(_stringFactory, "Послать всем элементам", 42), _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAll), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36)));
	Object _object;
	_object = Machine_UIDToObject((((ExternalListManipulator) (_self->entity))->_machine), _uid);
	ListMap_ObjectSetJob(_object, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа списка", 42));
	Object toReturn = _uid;
	DPOPS ("ExternalListManipulator: CreateUIDListFromUIDObject ended.")
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
	_cur = Number_Add(ListMap_NumberAt(_leftAnswer, StringFactory_FromUTF8(_stringFactory, "Число", 10)), NumberFactory_FromLong(_numberFactory, 1));
	Object _right;
	_right = ListMap_NumberAt(_rightAnswer, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	while((LogicFactory_FromLong(_logicFactory, Object_Compare(_cur, _right) == _less)) != _false)
	{
		List_PushBack(_list, Object_TempClone(_cur));
		Number_Inc(_cur);
	}
	Object _uid;
	_uid = ExternalObjectsFactory_CreateList(_objectsFactory, _list);
	Object _reply;
	_reply = Object_TempDeepClone(ListMap_ObjectProperty(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "Сообщение заказа", 31)));
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
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _leftElement;
	_leftElement = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25));
	Object _rightElement;
	_rightElement = ListMap_ObjectAt(_request, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27));
	Object _handler;
	_handler = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _handlerName;
	_handlerName = Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine));
	ListMap_ObjectSetJob(_object, _handler, _handlerName);
	Object _stage;
	_stage = ExternalEntitiesFactory_CreateEmptyJobStage(_entitiesFactory);
	ListMap_StageSetMethod(_stage, StringFactory_FromUTF8(_stringFactory, "Единственный метод", 35));
	ListMap_JobSetStage(_handler, _stage, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37));
	Object _messageSlotForLeft;
	_messageSlotForLeft = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	ListMap_MessageSlotSetCondition(_messageSlotForLeft, ExternalEntitiesFactory_CreateConditionEqualityWithField(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), StringFactory_FromUTF8(_stringFactory, "Левая граница", 25)));
	ListMap_MessageSlotSetCondition(_messageSlotForLeft, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	ListMap_JobSetMessageSlot(_handler, _messageSlotForLeft, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от левой границы", 68));
	Processor_AttachToStageMessageSlotInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37), StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от левой границы", 68), _handlerName);
	Object _messageSlotForRight;
	_messageSlotForRight = ExternalEntitiesFactory_CreateEmptyMessageSlot(_entitiesFactory);
	ListMap_MessageSlotSetCondition(_messageSlotForRight, ExternalEntitiesFactory_CreateConditionEqualityWithField(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), StringFactory_FromUTF8(_stringFactory, "Правая граница", 27)));
	ListMap_MessageSlotSetCondition(_messageSlotForRight, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	ListMap_JobSetMessageSlot(_handler, _messageSlotForRight, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от правой границы", 70));
	Processor_AttachToStageMessageSlotInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Единственная стадия", 37), StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение от правой границы", 70), _handlerName);
	ListMap_ObjectSetBasicMethod(_handler, _self, MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_ListWithIntegersInIntervalHandler), StringFactory_FromUTF8(_stringFactory, "Единственный метод", 35));
	ListMap_ObjectSetProperty(_handler, _request, StringFactory_FromUTF8(_stringFactory, "Сообщение заказа", 31));
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Левая граница", 25), ListMap_ObjectFields(_handler), _leftElement);
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Правая граница", 27), ListMap_ObjectFields(_handler), _rightElement);
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

Object ExternalListManipulator_SendToAllRedirectAnswersHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: SendToAllRedirectAnswersHandler begined.")
	ASSERT_C ( "ExternalListManipulator:SendToAllRedirectAnswersHandler --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SendToAllRedirectAnswersHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _answersRemained;
	_answersRemained = ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	Object _request;
	_request = ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	Object _receiver;
	_receiver = ListMap_MessageSender(_request);
	Object _msgToRedirect;
	_msgToRedirect = Object_TempDeepClone(Processor_MessageInMessageSlot(_processor, ListMap_MessageRequest(ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)))));
	ListMap_MessageSetReceiver(_msgToRedirect, _receiver);
	ListMap_Add(_msgToRedirect, StringFactory_FromUTF8(_stringFactory, "Исходный отправитель", 39), ListMap_MessageSender(_msgToRedirect));
	Processor_SendMessage(_processor, _msgToRedirect);
	Number_Dec(_answersRemained);
	if((ListMap_MessageReplyIsFail(_msgToRedirect)) != _false)
	{
		ListMap_ObjectSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Неудача", 14), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_answersRemained, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
	{
		Object _summaryAnswer;
		_summaryAnswer = Object_TempDeepClone(_request);
		ListMap_MessageSetTypeReply(_summaryAnswer);
		ListMap_MessageSetReplySuccess(_summaryAnswer);
		ListMap_Add(_summaryAnswer, StringFactory_FromUTF8(_stringFactory, "Отчет", 10), ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24)));
		ListMap_MessageSetReceiver(_summaryAnswer, _receiver);
		Processor_SendMessage(_processor, _summaryAnswer);
		Processor_FinishThisJob(_processor);
	}
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: SendToAllRedirectAnswersHandler ended.")
	return toReturn;
}

Object ExternalListManipulator_SendToAllAnswerInCommonHandler(Object _self, Object _processor)
{
	DPUSHS ("ExternalListManipulator: SendToAllAnswerInCommonHandler begined.")
	ASSERT_C ( "ExternalListManipulator:SendToAllAnswerInCommonHandler --- Checking for correct object type failed.", _self->gid ==  3902231640652582912ull )
	ASSERT_C ( "ExternalListManipulator:SendToAllAnswerInCommonHandler --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _answersRemained;
	_answersRemained = ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	Object _request;
	_request = ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	Object _receiver;
	_receiver = ListMap_MessageSender(_request);
	Number_Dec(_answersRemained);
	if((ListMap_MessageReplyIsFail(Processor_MessageInMessageSlot(_processor, ListMap_MessageRequest(ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)))))) != _false)
	{
		ListMap_ObjectSetProperty(_job, StringFactory_FromUTF8(_stringFactory, "Неудача", 14), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_answersRemained, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
	{
		Object _summaryAnswer;
		_summaryAnswer = Object_TempDeepClone(_request);
		ListMap_MessageSetTypeReply(_summaryAnswer);
		ListMap_MessageSetReplySuccess(_summaryAnswer);
		ListMap_Add(_summaryAnswer, StringFactory_FromUTF8(_stringFactory, "Отчет", 10), ListMap_ObjectProperty(_job, StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24)));
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
	_request = Processor_MessageInMessageSlot(_processor, StringFactory_FromUTF8(_stringFactory, "Послать всем элементам", 42));
	Object _messageToSend;
	_messageToSend = ListMap_ListMapAt(_request, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _handler;
	_handler = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _actionWithAnswers;
	_actionWithAnswers = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Послать всем элементам", 42), StringFactory_FromUTF8(_stringFactory, "Действия с ответами", 36));
	Object _method;
	_method = _nil;
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Перенаправить", 26)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAllRedirectAnswersHandler);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_actionWithAnswers, StringFactory_FromUTF8(_stringFactory, "Ответить в общем", 30)) == _equal)) != _false)
	{
		_method = MethodFactory_FromPointer(_methodFactory, &ExternalListManipulator_SendToAllAnswerInCommonHandler);
	}
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, ListMap_MessageRequest(_messageToSend), _self, _method, _handler);
	ListMap_ObjectSetJob(_object, _handler, Machine_GenerateUID((((ExternalListManipulator) (_self->entity))->_machine)));
	Object _list;
	_list = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	Object _listOfObjects;
	_listOfObjects = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Список объектов", 29));
	Object _iteratorInList;
	_iteratorInList = List_First(_list);
	Object _iteratorInListOfObjects;
	_iteratorInListOfObjects = List_First(_listOfObjects);
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
		if((Logic_Not(ListIterator_ThisEnd(_iteratorInListOfObjects))) != _false)
		{
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, ListIterator_NumberData(_iteratorInListOfObjects)) == _equal)) != _false)
			{
				_flag = _false;
				_receiver = _data;
				ListIterator_Next(_iteratorInListOfObjects);
			}
		}
		if((_flag) != _false)
		{
			_receiver = ExternalObjectsFactory_CreateValue(_objectsFactory, _data);
		}
		Object _messageToSend2;
		_messageToSend2 = Object_TempDeepClone(_messageToSend);
		ListMap_MessageSetReceiver(_messageToSend2, _receiver);
		Processor_SendMessage(_processor, _messageToSend2);
		ListIterator_Next(_iteratorInList);
		Number_Inc(_position);
	}
	ListMap_ObjectSetProperty(_handler, _position, StringFactory_FromUTF8(_stringFactory, "Осталось ответов", 31));
	ListMap_ObjectSetProperty(_handler, _request, StringFactory_FromUTF8(_stringFactory, "Сообщение запроса", 33));
	ListMap_ObjectSetProperty(_handler, StringFactory_FromUTF8(_stringFactory, "Всюду успех", 21), StringFactory_FromUTF8(_stringFactory, "Ответ в общем", 24));
	Object toReturn = _self;
	DPOPS ("ExternalListManipulator: SendToAll ended.")
	return toReturn;
}
