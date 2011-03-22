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

Object ExternalNumberManipulator_CreateUIDNumberFromUIDObject(Object _self, Object _uid)
{
	DPUSHS ("ExternalNumberManipulator: CreateUIDNumberFromUIDObject begined.")
	ASSERT_C ( "ExternalNumberManipulator:CreateUIDNumberFromUIDObject --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:CreateUIDNumberFromUIDObject --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "+=", 2));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "+=", 2), StringFactory_FromUTF8(_stringFactory, "+=", 2), StringFactory_FromUTF8(_stringFactory, "+=", 2), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "-=", 2));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "-=", 2), StringFactory_FromUTF8(_stringFactory, "-=", 2), StringFactory_FromUTF8(_stringFactory, "-=", 2), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "*=", 2));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "*=", 2), StringFactory_FromUTF8(_stringFactory, "*=", 2), StringFactory_FromUTF8(_stringFactory, "*=", 2), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "/=", 2));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "/=", 2), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "/=", 2));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "/=", 2), StringFactory_FromUTF8(_stringFactory, "/=", 2), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Инкремент", 18));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Инкремент", 18), StringFactory_FromUTF8(_stringFactory, "Инкремент", 18), StringFactory_FromUTF8(_stringFactory, "Инкремент", 18), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Декремент", 18));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Декремент", 18), StringFactory_FromUTF8(_stringFactory, "Декремент", 18), StringFactory_FromUTF8(_stringFactory, "Декремент", 18), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Модуль", 12));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Модуль", 12), StringFactory_FromUTF8(_stringFactory, "Модуль", 12), StringFactory_FromUTF8(_stringFactory, "Модуль", 12), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Условие", 14)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20), StringFactory_FromUTF8(_stringFactory, "Опвестить", 18), StringFactory_FromUTF8(_stringFactory, "Оповестить", 20), _messageSlot);
	Object _object;
	_object = Machine_UIDToObject((((ExternalNumberManipulator) (_self->entity))->_machine), _uid);
	ListMap_ObjectSetJob(_object, _job);
	Object toReturn = _uid;
	DPOPS ("ExternalNumberManipulator: CreateUIDNumberFromUIDObject ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SimpleNumber(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SimpleNumber begined.")
	ASSERT_C ( "ExternalNumberManipulator:SimpleNumber --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SimpleNumber --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_message);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Число", 10), Object_TempClone(_number));
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
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _message;
	_message = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_message);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Строка", 12), StringFactory_FromNumber(_stringFactory, _number));
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
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "+=", 2));
	Object _requestArgument;
	_requestArgument = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Machine_DefineFieldHelper((((ExternalNumberManipulator) (_self->entity))->_machine), ListMap_MessageSender(_request), StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38), ListMap_ObjectFields(_jobToProcessThisEvent));
	Object _name;
	_name = Object_TempClone(_requestArgument);
	List_Concatenate(_name, StringFactory_FromUTF8(_stringFactory, "Запрос для +=", 22));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateReplyMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_jobToProcessThisEvent, _name, _name, _name, _messageSlot);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &AddInPlaceSimple), _name);
	Object _request2;
	_request2 = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request2);
	ListMap_MessageSetRequest(_request2, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request2, _requestArgument);
	Processor_SendMessage(_processor, _request2);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: AddInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_AddInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: AddInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:AddInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:AddInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	Number_AddInPlace(_number, ListMap_NumberAt(_request, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _receiver;
	_receiver = ListMap_ObjectFieldUID(_job, StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "+=", 2));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: AddInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SubInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SubInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:SubInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SubInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "-=", 2));
	Object _requestArgument;
	_requestArgument = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Machine_DefineFieldHelper((((ExternalNumberManipulator) (_self->entity))->_machine), ListMap_MessageSender(_request), StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38), ListMap_ObjectFields(_jobToProcessThisEvent));
	Object _name;
	_name = Object_TempClone(_requestArgument);
	List_Concatenate(_name, StringFactory_FromUTF8(_stringFactory, "Запрос для -=", 22));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateReplyMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_jobToProcessThisEvent, _name, _name, _name, _messageSlot);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &SubInPlaceSimple), _name);
	Object _request2;
	_request2 = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request2);
	ListMap_MessageSetRequest(_request2, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request2, _requestArgument);
	Processor_SendMessage(_processor, _request2);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SubInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_SubInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: SubInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:SubInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:SubInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	Number_SubInPlace(_number, ListMap_NumberAt(_request, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _receiver;
	_receiver = ListMap_ObjectFieldUID(_job, StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "-=", 2));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: SubInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_MulInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: MulInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:MulInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:MulInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "*=", 2));
	Object _requestArgument;
	_requestArgument = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Machine_DefineFieldHelper((((ExternalNumberManipulator) (_self->entity))->_machine), ListMap_MessageSender(_request), StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38), ListMap_ObjectFields(_jobToProcessThisEvent));
	Object _name;
	_name = Object_TempClone(_requestArgument);
	List_Concatenate(_name, StringFactory_FromUTF8(_stringFactory, "Запрос для *=", 22));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateReplyMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_jobToProcessThisEvent, _name, _name, _name, _messageSlot);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &MulInPlaceSimple), _name);
	Object _request2;
	_request2 = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request2);
	ListMap_MessageSetRequest(_request2, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request2, _requestArgument);
	Processor_SendMessage(_processor, _request2);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: MulInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_MulInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: MulInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:MulInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:MulInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	Number_MulInPlace(_number, ListMap_NumberAt(_request, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _receiver;
	_receiver = ListMap_ObjectFieldUID(_job, StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "*=", 2));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: MulInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_DivInPlace(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: DivInPlace begined.")
	ASSERT_C ( "ExternalNumberManipulator:DivInPlace --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:DivInPlace --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_processor), StringFactory_FromUTF8(_stringFactory, "/=", 2));
	Object _requestArgument;
	_requestArgument = ListMap_ListAt(_request, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	Object _jobToProcessThisEvent;
	_jobToProcessThisEvent = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Machine_DefineFieldHelper((((ExternalNumberManipulator) (_self->entity))->_machine), ListMap_MessageSender(_request), StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38), ListMap_ObjectFields(_jobToProcessThisEvent));
	Object _name;
	_name = Object_TempClone(_requestArgument);
	List_Concatenate(_name, StringFactory_FromUTF8(_stringFactory, "Запрос для /=", 22));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateReplyMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_jobToProcessThisEvent, _name, _name, _name, _messageSlot);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &DivInPlaceSimple), _name);
	Object _request2;
	_request2 = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request2);
	ListMap_MessageSetRequest(_request2, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	ListMap_MessageSetReceiver(_request2, _requestArgument);
	Processor_SendMessage(_processor, _request2);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: DivInPlace ended.")
	return toReturn;
}

Object ExternalNumberManipulator_DivInPlaceSimple(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: DivInPlaceSimple begined.")
	ASSERT_C ( "ExternalNumberManipulator:DivInPlaceSimple --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:DivInPlaceSimple --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Значение простым числом", 44));
	Number_DivInPlace(_number, ListMap_NumberAt(_request, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _receiver;
	_receiver = ListMap_ObjectFieldUID(_job, StringFactory_FromUTF8(_stringFactory, "Перед кем отчетность", 38));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetTypeReply(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "/=", 2));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: DivInPlaceSimple ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Increment(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Increment begined.")
	ASSERT_C ( "ExternalNumberManipulator:Increment --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Increment --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_Inc(_number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Инкремент", 18));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Increment ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Decrement(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Decrement begined.")
	ASSERT_C ( "ExternalNumberManipulator:Decrement --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Decrement --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
	Number_Dec(_number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Декремент", 18));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Decrement ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Absolute(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Absolute begined.")
	ASSERT_C ( "ExternalNumberManipulator:Absolute --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Absolute --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _number;
	_number = Number_Abs(ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10)));
	Object _cloneUID;
	_cloneUID = ExternalObjectManipulator_CloneUIDObjectInternalRoutine((((ExternalMachineManipulator) ((((Machine) ((((ExternalNumberManipulator) (_self->entity))->_machine)->entity))->_machineManipulator)->entity))->_object), (((Processor) (_processor->entity))->_contextUID));
	Object _clone;
	_clone = Machine_UIDToObject((((ExternalNumberManipulator) (_self->entity))->_machine), _cloneUID);
	ListMap_Add(ListMap_ObjectProperties(_clone), StringFactory_FromUTF8(_stringFactory, "Число", 10), _number);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _cloneUID);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Модуль", 12));
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Absolute ended.")
	return toReturn;
}

Object ExternalNumberManipulator_Notify(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: Notify begined.")
	ASSERT_C ( "ExternalNumberManipulator:Notify --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:Notify --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _notifications;
	_notifications = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Оповещения", 20));
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _request;
	_request = ListMap_JobMessageInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Оповестить", 20));
	List_PushBack(_notifications, _request);
	ExternalNumberManipulator_CheckForNotifications(_self, _processor);
	Object toReturn = _self;
	DPOPS ("ExternalNumberManipulator: Notify ended.")
	return toReturn;
}

Object ExternalNumberManipulator_CheckForNotifications(Object _self, Object _processor)
{
	DPUSHS ("ExternalNumberManipulator: CheckForNotifications begined.")
	ASSERT_C ( "ExternalNumberManipulator:CheckForNotifications --- Checking for correct object type failed.", _self->gid ==  3782552814704636928ull )
	ASSERT_C ( "ExternalNumberManipulator:CheckForNotifications --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _object;
	_object = Processor_ContextObject(_processor);
	Object _notifications;
	_notifications = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Оповещения", 20));
	Object _currentValue;
	_currentValue = ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Число", 10));
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
			_valuesValue = ListMap_ObjectAt(ListMap_ObjectProperty(_object, StringFactory_FromUTF8(_stringFactory, "Значения на оповещения", 42)), _value);
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
			_shouldNotify = _true;
		}
		else
		{
			Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное условие на оповещение: ", 67));
			Console_WriteLnString(_console, _condition);
			ListIterator_ThisRemove(_notificationsIterator);
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
			ListIterator_Prev(_notificationsIterator);
		}
		ListIterator_Next(_notificationsIterator);
	}
}
