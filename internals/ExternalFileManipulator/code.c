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
	Object toReturn = _equal;
	DPOPS ("ExternalFileManipulator: Compare ended.")
	return toReturn;
}

Object ExternalFileManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalFileManipulator: SetMachine begined.")
	ASSERT_C ( "ExternalFileManipulator:SetMachine --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	(((ExternalFileManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalFileManipulator_CreateUIDFileFromUIDObject(Object _self, Object _uid)
{
	DPUSHS ("ExternalFileManipulator: CreateUIDFileFromUIDObject begined.")
	ASSERT_C ( "ExternalFileManipulator:CreateUIDFileFromUIDObject --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _object;
	_object = Machine_UIDToObject((((ExternalFileManipulator) (_self->entity))->_machine), _uid);
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_AssociateUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Ассоциировать имя файла", 44));
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_OpenForReadingUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Открыть файл для чтения", 43));
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_OpenForWritingUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Открыть файл для записи", 43));
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_CloseUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23));
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_ReadStringUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31));
	ListMap_ObjectSetBasicMethod(_object, _self, MethodFactory_FromPointer(_methodFactory, &ExternalFileManipulator_WriteStringUIDFileBasicMethod), StringFactory_FromUTF8(_stringFactory, "Записать строку", 29));
	Object _job;
	_job = ExternalEntitiesFactory_CreateEmptyJob(_entitiesFactory);
	ListMap_ObjectSetJob(_object, _job, StringFactory_FromUTF8(_stringFactory, "Основная работа файла", 40));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Ассоциировать", 26));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциирование файла", 39), StringFactory_FromUTF8(_stringFactory, "Ассоциировать имя фала", 42), StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46), _messageSlot);
	Object toReturn = _uid;
	DPOPS ("ExternalFileManipulator: CreateUIDFileFromUIDObject ended.")
	return toReturn;
}

Object ExternalFileManipulator_AssociateUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: AssociateUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:AssociateUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	ListMap_Add(ListMap_ObjectProperties(_fileObject), StringFactory_FromUTF8(_stringFactory, "Имя файла", 17), ListMap_JobFieldInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17), StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46)));
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Чтение", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для чтения", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл для чтения", 43), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для чтения", 65), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Открыть", 14));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Доступ", 12), StringFactory_FromUTF8(_stringFactory, "Запись", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Открытие файла для записи", 47), StringFactory_FromUTF8(_stringFactory, "Открыть файл для записи", 43), StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла для записи", 65), _messageSlot);
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на ассоциирование", 46));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: AssociateUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_OpenForReadingUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: OpenForReadingUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:OpenForReadingUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = File_Create();
	File_OpenForReading(_file, ListMap_ObjectProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_ObjectSetProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8), _file);
	Object_Release(_file);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Прочитать", 18));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект чтения", 25), StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Чтение строки", 25), StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31), StringFactory_FromUTF8(_stringFactory, "Запрос для чтения строки", 45), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Закрыть", 14));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие", 16), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие", 34), _messageSlot);
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциировать", 26));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открыть для чтения", 34));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открыть для записи", 34));
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла", 45));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: OpenForReadingUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_OpenForWritingUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: OpenForWritingUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:OpenForWritingUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = File_Create();
	File_OpenForAppending(_file, ListMap_ObjectProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Имя файла", 17)));
	ListMap_ObjectSetProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8), _file);
	Object_Release(_file);
	Object _messageSlot;
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Записать", 16));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionEquality(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Объект записи", 25), StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	ListMap_MessageSlotSetCondition(_messageSlot, ExternalEntitiesFactory_CreateConditionPresence(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Строка", 12)));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Запись строки", 25), StringFactory_FromUTF8(_stringFactory, "Записать строку", 29), StringFactory_FromUTF8(_stringFactory, "Запрос для записи строки", 45), _messageSlot);
	_messageSlot = ExternalEntitiesFactory_CreateRequestMessageSlot(_entitiesFactory, StringFactory_FromUTF8(_stringFactory, "Закрыть", 14));
	ListMap_JobCreateStageWithNameMethodMessageSlotNameAndEntity(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие файла", 27), StringFactory_FromUTF8(_stringFactory, "Закрыть файл", 23), StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие", 34), _messageSlot);
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Ассоциировать", 26));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открыть для чтения", 34));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Открыть для записи", 34));
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на открытие файла", 45));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: OpenForWritingUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_CloseUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: CloseUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:CloseUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = ListMap_ObjectProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	File_Close(_file);
	ListMap_ObjectSetProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8), _nil);
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
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Записать строку", 29));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Прочитать строку", 31));
	ListMap_JobRemoveStageAndMessageSlots(_job, StringFactory_FromUTF8(_stringFactory, "Закрытие файла", 27));
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос на закрытие файла", 45));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: CloseUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_WriteStringUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: WriteStringUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:WriteStringUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _job;
	_job = Processor_ContextJob(_processor);
	Object _file;
	_file = ListMap_ObjectProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	File_WriteNakedString(_file, ListMap_JobFieldInMessageSlot(_job, StringFactory_FromUTF8(_stringFactory, "Строка", 12), StringFactory_FromUTF8(_stringFactory, "Запрос для записи строки", 45)));
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос для записи строки", 45));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: WriteStringUIDFileBasicMethod ended.")
	return toReturn;
}

Object ExternalFileManipulator_ReadStringUIDFileBasicMethod(Object _self, Object _processor)
{
	DPUSHS ("ExternalFileManipulator: ReadStringUIDFileBasicMethod begined.")
	ASSERT_C ( "ExternalFileManipulator:ReadStringUIDFileBasicMethod --- Checking for correct object type failed.", _self->gid ==  6719891516697860096ull )
	Object _fileObject;
	_fileObject = Processor_ContextObject(_processor);
	Object _file;
	_file = ListMap_ObjectProperty(_fileObject, StringFactory_FromUTF8(_stringFactory, "Файл", 8));
	Object _string;
	_string = File_ReadString(_file);
	Object _reply;
	_reply = ListMap_Create();
	ListMap_MessageSetReplySuccess(_reply);
	ListMap_Add(_reply, StringFactory_FromUTF8(_stringFactory, "Строка", 12), _string);
	Processor_SendReplyForMessage(_processor, _reply, StringFactory_FromUTF8(_stringFactory, "Запрос для чтения строки", 45));
	Object_Release(_reply);
	Object toReturn = _self;
	DPOPS ("ExternalFileManipulator: ReadStringUIDFileBasicMethod ended.")
	return toReturn;
}
