#include "internals/basics.h"
#include "internals/ExternalFileManipulator/imports.h"


Object ExternalFileManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalFileManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalFileManipulator));
	_self->gid =  6719891516697860096ull;
	Object_SetComparator(_self, &ExternalFileManipulator_Compare);
	Object_SetDestructor(_self, &ExternalFileManipulator_Destroy);
	Object_SetCloner(_self, &ExternalFileManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalFileManipulator_DeepClone);
	((ExternalFileManipulator) (_self->entity))->_machine = _nil;
	_self = ExternalFileManipulator_Init(_self);
	DPOPS ("ExternalFileManipulator: Create ended.")
	return _self;
}

Object ExternalFileManipulator_Init(Object _self)
{
	DPUSHS ("ExternalFileManipulator: Init begined.")
	ASSERT_C ( "ExternalFileManipulator:Init --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: Init ended.")
	return toReturn;
}

Object ExternalFileManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalFileManipulator: Clone begined.")
	ASSERT_C ( "ExternalFileManipulator:Clone --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: Clone ended.")
	return toReturn;
}

Object ExternalFileManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalFileManipulator: DeepClone begined.")
	ASSERT_C ( "ExternalFileManipulator:DeepClone --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalFileManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalFileManipulator: Destroy begined.")
	ASSERT_C ( "ExternalFileManipulator:Destroy --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalFileManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalFileManipulator_Compare(Object _self, Object _consoleManipulator)
{
	DPUSHS ("ExternalFileManipulator: Compare begined.")
	ASSERT_C ( "ExternalFileManipulator:Compare --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:Compare --- Checking for correct parameter type failed at parameter _consoleManipulator.", _consoleManipulator->gid ==  6719891516697860096ull || _consoleManipulator == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalFileManipulator: Compare ended.")
	return toReturn;
}

Object ExternalFileManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalFileManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalFileManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((ExternalFileManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalFileManipulator_CreateUIDFileFromUIDActor(Object _self, Object _uid)
{
	DPUSHS ("ExternalFileManipulator: CreateUIDFileFromUIDActor begined.")
	ASSERT_C ( "ExternalFileManipulator:CreateUIDFileFromUIDActor --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:CreateUIDFileFromUIDActor --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Object _actor;
	_actor = Machine_UIDToActor((((ExternalFileManipulator) (_self->entity))->_machine), _uid);
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_AssociateUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Ассоциировать имя фала", 42));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_OpenForReadingUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Открыть файл для чтения", 43));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_OpenForWritingUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Открыть файл для записи", 43));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_CloseUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_ReadStringUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_WriteStringUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Записать строку", 29));
	ListMap_ActorSetBasicMethod(_actor, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_WriteActorUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Записать объект", 29));
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ActorSetJob(_actor, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа файла", 40));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ассоциировать", 26));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциирование файла", 39), StringFactory_FromUTF8(_stringFactory, "Ассоциировать имя фала", 42), StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46), _messageSlot);
	Object toReturn = _uid;
	DPOPS ("ExternalFileManipulator: CreateUIDFileFromUIDActor ended.")
	return toReturn;
}

Object ExternalFileManipulator_AssociateUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: AssociateUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:AssociateUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:AssociateUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	ListMap_Add(ListMap_ActorProperties(_fileActor), StringFactory_FromUTF8(_stringFactory, "Имя файла", 17), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46), StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Чтение", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для чтения", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл для чтения", 43), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для чтения", 65), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Запись", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для записи", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл для записи", 43), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для записи", 65), _messageSlot);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: AssociateUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_OpenForReadingUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: OpenForReadingUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:OpenForReadingUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:OpenForReadingUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = File_Create();
	File_OpenForReading(_file, ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_ActorSetProperty(_fileActor, _file, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object_Release(_file);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Прочитать", 18));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект чтения", 25), StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Чтение строки", 25), StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31), StringFactory_FromUTF8(_stringFactory, "Запрос для чтения строки", 45), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Закрыть", 14));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие файла", 27), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие файла", 45), _messageSlot);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для чтения", 65));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциирование файла", 39));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для чтения", 47));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для записи", 47));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: OpenForReadingUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_OpenForWritingUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: OpenForWritingUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:OpenForWritingUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:OpenForWritingUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = File_Create();
	File_OpenForAppending(_file, ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_ActorSetProperty(_fileActor, _file, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object_Release(_file);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Записать", 16));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект записи", 25), StringFactory_FromUTF8(_stringFactory, "Простая строка", 27)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Простая строка", 27)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Запись простой строки", 40), StringFactory_FromUTF8(_stringFactory, "Записать простую строку", 44), StringFactory_FromUTF8(_stringFactory, "Запрос для записи простой строки", 60), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Записать", 16));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект записи", 25), StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Запись объекта", 27), StringFactory_FromUTF8(_stringFactory, "Записать объект", 29), StringFactory_FromUTF8(_stringFactory, "Запрос для записи объекта", 47), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Закрыть", 14));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие файла", 27), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие файла", 45), _messageSlot);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для записи", 65));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциирование файла", 39));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для чтения", 47));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для записи", 47));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: OpenForWritingUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_CloseUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: CloseUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:CloseUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:CloseUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	File_Close(_file);
	ListMap_ActorSetProperty(_fileActor, _nil, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Чтение", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для чтения", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для чтения", 65), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Запись", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для записи", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для записи", 65), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ассоциировать", 26));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциирование файла", 39), StringFactory_FromUTF8(_stringFactory, "Ассоциировать имя фала", 42), StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46), _messageSlot);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие файла", 45));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Записать строку", 29));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие файла", 27));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: CloseUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_WriteStringUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: WriteStringUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:WriteStringUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:WriteStringUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	File_WriteNakedString(_file, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Запрос для записи строки", 45), StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос для записи строки", 45));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: WriteStringUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_WriteActorUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: WriteActorUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:WriteActorUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:WriteActorUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	Object _uidToWrite;
	_uidToWrite = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Запрос для записи объекта", 47), StringFactory_FromUTF8(_stringFactory, "Объект", 12));
	ListMap_ActorSetJob(_fileActor, _job, List_ConcatenateRight(StringFactory_FromUTF8(_stringFactory, "Вывод ", 11), _uidToWrite));
	Object _messageSlot;
	_messageSlot = Processor_CreateStageReplyEntityBasicMethodInJob(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_WriteSecondStageUIDFileBasicMethod), _job);
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	Processor_DefineFieldInNameSpaceWithUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16), ListMap_ActorFields(_job), Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Запрос для записи объекта", 47), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22)));
	Object _request;
	_request = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetTypeRequest(_request);
	ListMap_MessageSetRequest(_request, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46));
	ListMap_MessageSetReceiver(_request, _uidToWrite);
	Processor_SendMessage(_processor, _request);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: WriteActorUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_WriteSecondStageUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: WriteSecondStageUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:WriteSecondStageUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:WriteSecondStageUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _file;
	_file = ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	File_WriteNakedString(_file, Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Значение простой строкой", 46), StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_MessageSetRequest(_reply, StringFactory_FromUTF8(_stringFactory, "Запрос для записи объекта", 47));
	ListMap_MessageSetReceiver(_reply, Processor_FieldNameToUID(_processor, StringFactory_FromUTF8(_stringFactory, "Заказчик", 16)));
	Processor_SendMessage(_processor, _reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: WriteSecondStageUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_ReadStringUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: ReadStringUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:ReadStringUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	ASSERT_C ( "ExternalFileManipulator:ReadStringUIDFileBasicMethod --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object _fileActor;
	_fileActor = Processor_ContextActor(_processor);
	Object _file;
	_file = ListMap_ActorProperty(_fileActor, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object _string;
	_string = File_ReadString(_file);
	Object _reply;
	_reply = ExternalEntitiesFactory_CreateEmptyMessage(_entitiesFactory);
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Строка", 12), _string);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос для чтения строки", 45));
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: ReadStringUIDFileBasicMethod ended.")
	return toReturn;
}
