#include "internals/basics.h"
#include "internals/Processor/imports.h"


Object Processor_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("Processor: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct Processor));
	_self->gid =  8708543990322460672ull;
	Object_SetComparator(_self, &Processor_Compare);
	Object_SetDestructor(_self, &Processor_Destroy);
	Object_SetCloner(_self, &Processor_Clone);
	Object_SetDeepCloner(_self, &Processor_DeepClone);
	((Processor) (_self->entity))->_contextUID = _nil;
	((Processor) (_self->entity))->_contextJobName = _nil;
	((Processor) (_self->entity))->_contextJobStageName = _nil;
	((Processor) (_self->entity))->_machine = _nil;
	((Processor) (_self->entity))->_localNamespaces = _nil;
	((Processor) (_self->entity))->_helperStack = _nil;
	((Processor) (_self->entity))->_processorCodes = _nil;
	_self = Processor_Init(_self);
	DPOPS ("Processor: Create ended.")
	return _self;
}

Object Processor_Clone(Object _self)
{
	DPUSHS ("Processor: Clone begined.")
	ASSERT_C ( "Processor:Clone --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_Create();
	DPOPS ("Processor: Clone ended.")
	return toReturn;
}

Object Processor_DeepClone(Object _self)
{
	DPUSHS ("Processor: DeepClone begined.")
	ASSERT_C ( "Processor:DeepClone --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_Create();
	DPOPS ("Processor: DeepClone ended.")
	return toReturn;
}

Object Processor_Destroy(Object _self)
{
	DPUSHS ("Processor: Destroy begined.")
	ASSERT_C ( "Processor:Destroy --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object_Release((((Processor) (_self->entity))->_contextUID));
	Object_Release((((Processor) (_self->entity))->_contextJobName));
	Object_Release((((Processor) (_self->entity))->_contextJobStageName));
	Object_Release((((Processor) (_self->entity))->_helperStack));
	Object_Release((((Processor) (_self->entity))->_localNamespaces));
	Object_Release((((Processor) (_self->entity))->_processorCodes));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("Processor: Destroy ended.")
	return toReturn;
}

Object Processor_Compare(Object _self, Object _processor)
{
	DPUSHS ("Processor: Compare begined.")
	ASSERT_C ( "Processor:Compare --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:Compare --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	Object toReturn = _equal;
	DPOPS ("Processor: Compare ended.")
	return toReturn;
}

Object Processor_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("Processor: SetMachine begined.")
	ASSERT_C ( "Processor:SetMachine --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:SetMachine --- Checking for correct parameter type failed at parameter _machine.", _machine->gid ==  6547848715907434496ull || _machine == _nil )
	(((Processor) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("Processor: SetMachine ended.")
	return toReturn;
}

Object Processor_ContextObject(Object _self)
{
	DPUSHS ("Processor: ContextObject begined.")
	ASSERT_C ( "Processor:ContextObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Machine_UIDToObject((((Processor) (_self->entity))->_machine), (((Processor) (_self->entity))->_contextUID));
	DPOPS ("Processor: ContextObject ended.")
	return toReturn;
}

Object Processor_ContextJob(Object _self)
{
	DPUSHS ("Processor: ContextJob begined.")
	ASSERT_C ( "Processor:ContextJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = ListMap_ObjectJob(Processor_ContextObject(_self), (((Processor) (_self->entity))->_contextJobName));
	DPOPS ("Processor: ContextJob ended.")
	return toReturn;
}

Object Processor_ContextJobStage(Object _self)
{
	DPUSHS ("Processor: ContextJobStage begined.")
	ASSERT_C ( "Processor:ContextJobStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = ListMap_JobStage(Processor_ContextJob(_self), (((Processor) (_self->entity))->_contextJobStageName));
	DPOPS ("Processor: ContextJobStage ended.")
	return toReturn;
}

Object Processor_Init(Object _self)
{
	DPUSHS ("Processor: Init begined.")
	ASSERT_C ( "Processor:Init --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	(((Processor) (_self->entity))->_localNamespaces) = Stack_Create();
	(((Processor) (_self->entity))->_helperStack) = Stack_Create();
	(((Processor) (_self->entity))->_processorCodes) = ListMap_Create();
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Выполнить", 18), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDo));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Сущность поля сообщения", 44), MethodFactory_FromPointer(_methodFactory, &Processor_CodeEntityFromMessageField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Идентификатор поля", 35), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUIDFromField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущий объект", 27), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddCurrentUIDToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая работа", 27), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddCurrentJobToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая стадия", 27), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddCurrentJobStageToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Список", 12), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddListToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Отображение", 22), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddListMapToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveFromStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в отображение", 59), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddEntityToListMap));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по ключу", 75), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveEntityFromListMapByKey));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по значению", 81), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveEntityFromListMapByValue));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в список", 49), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddEntityToList));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка на позиции", 69), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveEntityFromListByPosition));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка по значению", 71), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveEntityFromListByValue));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в вершину", 51), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddEntityToStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Дублировать вершину", 37), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDuplicateTopInStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Поменять местами вершинные элементы", 67), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSwapTopInStack));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту с идентификатором", 82), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSendMessageToUID));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту из поля", 62), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSendMessageToField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту из поля сообщения", 81), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSendMessageToMessageField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать ответ на сообщение", 49), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSendReplyForMessage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Вызвать метод с параметрами", 51), MethodFactory_FromPointer(_methodFactory, &Processor_CodeInvokeMethod));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Определить метод", 31), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDefineMethod));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить метод с именем", 41), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUnDefineMethod));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить ТВА", 27), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDefineLocalField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле работы", 42), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDefineJobField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле объекта", 44), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDefineObjectField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить глобальное поле", 50), MethodFactory_FromPointer(_methodFactory, &Processor_CodeDefineGlobalField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Присвоить полю идентификатор", 54), MethodFactory_FromPointer(_methodFactory, &Processor_CodeSetField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Перемежить поле прибытия с полем отправления", 83), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUniteField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить поле", 23), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUnDefineField));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить работу", 29), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddJob));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить стадию", 29), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddJobStage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Заблокировать стадию", 39), MethodFactory_FromPointer(_methodFactory, &Processor_CodeBlockStage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Разблокировать стадию", 41), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUnBlockStage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Заблокировать ожидаемое сообщение", 64), MethodFactory_FromPointer(_methodFactory, &Processor_CodeBlockMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Разблокировать ожидаемое сообщение", 66), MethodFactory_FromPointer(_methodFactory, &Processor_CodeUnBlockMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить стадию", 27), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveJobStage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии", 29), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllStages));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить ожидаемые сообщения", 54), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllMessageSlots));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии и ожидаемые сообщения", 70), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllStagesAndMessageSlots));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить ожидаемое сообщение", 54), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAddMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить ожидаемое сообщение", 52), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить стадии ожидаемое сообщение", 71), MethodFactory_FromPointer(_methodFactory, &Processor_CodeAttachToStageMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения текущей стадии для текущей стадии", 96), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllMessagesOfCurrentStageForCurrentStage));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения текущей стадии", 61), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllMessagesOfCurrentStageForAllStages));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения всех разблокированных стадий", 88), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllMessagesOfAllOpenedStages));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученное сообщение", 54), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveMessageInMessageSlot));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученные сообщения", 54), MethodFactory_FromPointer(_methodFactory, &Processor_CodeRemoveAllReceivedMessages));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Завершить текущую работу", 46), MethodFactory_FromPointer(_methodFactory, &Processor_CodeFinishThisJob));
	Object toReturn = _self;
	DPOPS ("Processor: Init ended.")
	return toReturn;
}

Object Processor_Do(Object _self, Object _toDo)
{
	DPUSHS ("Processor: Do begined.")
	ASSERT_C ( "Processor:Do --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:Do --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _method;
	_method = ListMap_MethodAt((((Processor) (_self->entity))->_processorCodes), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: Действие не задано либо отсутствует в системе комманд.", 131));
	}
	else
	{
		Method_Invoke(_method, _self, _toDo);
	}
	Object toReturn = _self;
	DPOPS ("Processor: Do ended.")
	return toReturn;
}

Object Processor_GetNamedEntityFromToDoOrStack(Object _self, Object _entityName, Object _toDo)
{
	DPUSHS ("Processor: GetNamedEntityFromToDoOrStack begined.")
	ASSERT_C ( "Processor:GetNamedEntityFromToDoOrStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:GetNamedEntityFromToDoOrStack --- Checking for correct parameter type failed at parameter _entityName.", _entityName->gid ==  3732711262168886272ull || _entityName == _nil )
	ASSERT_C ( "Processor:GetNamedEntityFromToDoOrStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _object;
	_object = Object_TempClone(ListMap_ObjectAt(_toDo, _entityName));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_object, _nil) == _equal)) != _false)
	{
		_object = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Object toReturn = _object;
	DPOPS ("Processor: GetNamedEntityFromToDoOrStack ended.")
	return toReturn;
}

Object Processor_CodeDo(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDo begined.")
	ASSERT_C ( "Processor:CodeDo --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDo --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _action;
	_action = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Действие", 16), _toDo);
	Processor_Do(_self, _action);
	Object toReturn = _self;
	DPOPS ("Processor: CodeDo ended.")
	return toReturn;
}

Object Processor_CodeEntityFromMessageField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeEntityFromMessageField begined.")
	ASSERT_C ( "Processor:CodeEntityFromMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeEntityFromMessageField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((Processor) (_self->entity))->_helperStack), Processor_EntityFromMessageField(_self, _fieldName, _messageSlotName));
	Object toReturn = _self;
	DPOPS ("Processor: CodeEntityFromMessageField ended.")
	return toReturn;
}

Object Processor_CodeUIDFromField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUIDFromField begined.")
	ASSERT_C ( "Processor:CodeUIDFromField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUIDFromField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((Processor) (_self->entity))->_helperStack), Processor_FieldNameToUID(_self, _fieldName));
	Object toReturn = _self;
	DPOPS ("Processor: CodeUIDFromField ended.")
	return toReturn;
}

Object Processor_CodeAddCurrentUIDToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddCurrentUIDToStack begined.")
	ASSERT_C ( "Processor:CodeAddCurrentUIDToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddCurrentUIDToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextUID));
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddCurrentUIDToStack ended.")
	return toReturn;
}

Object Processor_CodeAddCurrentJobToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddCurrentJobToStack begined.")
	ASSERT_C ( "Processor:CodeAddCurrentJobToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddCurrentJobToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddCurrentJobToStack ended.")
	return toReturn;
}

Object Processor_CodeAddCurrentJobStageToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddCurrentJobStageToStack begined.")
	ASSERT_C ( "Processor:CodeAddCurrentJobStageToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddCurrentJobStageToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobStageName));
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddCurrentJobStageToStack ended.")
	return toReturn;
}

Object Processor_CodeAddListToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddListToStack begined.")
	ASSERT_C ( "Processor:CodeAddListToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddListToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _list;
	_list = List_Create();
	Stack_Push((((Processor) (_self->entity))->_helperStack), _list);
	Object_Release(_list);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddListToStack ended.")
	return toReturn;
}

Object Processor_CodeAddListMapToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddListMapToStack begined.")
	ASSERT_C ( "Processor:CodeAddListMapToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddListMapToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _listMap;
	_listMap = ListMap_Create();
	Stack_Push((((Processor) (_self->entity))->_helperStack), _listMap);
	Object_Release(_listMap);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddListMapToStack ended.")
	return toReturn;
}

Object Processor_CodeRemoveFromStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveFromStack begined.")
	ASSERT_C ( "Processor:CodeRemoveFromStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveFromStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Remove((((Processor) (_self->entity))->_helperStack));
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveFromStack ended.")
	return toReturn;
}

Object Processor_CodeAddEntityToListMap(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddEntityToListMap begined.")
	ASSERT_C ( "Processor:CodeAddEntityToListMap --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddEntityToListMap --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _key;
	_key = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Add(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key, _value);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddEntityToListMap ended.")
	return toReturn;
}

Object Processor_CodeRemoveEntityFromListMapByKey(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveEntityFromListMapByKey begined.")
	ASSERT_C ( "Processor:CodeRemoveEntityFromListMapByKey --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveEntityFromListMapByKey --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _key;
	_key = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Remove(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveEntityFromListMapByKey ended.")
	return toReturn;
}

Object Processor_CodeRemoveEntityFromListMapByValue(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveEntityFromListMapByValue begined.")
	ASSERT_C ( "Processor:CodeRemoveEntityFromListMapByValue --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveEntityFromListMapByValue --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _iterator;
	_iterator = ListMap_First(Stack_Peek((((Processor) (_self->entity))->_helperStack)));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMapIterator_ThisValue(_iterator), _value) == _equal)) != _false)
		{
			ListMapIterator_ThisRemoveRight(_iterator);
			break;
		}
	}
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveEntityFromListMapByValue ended.")
	return toReturn;
}

Object Processor_CodeAddEntityToList(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddEntityToList begined.")
	ASSERT_C ( "Processor:CodeAddEntityToList --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddEntityToList --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _position;
	_position = ListMap_NumberAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Позиция", 14));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _nil) == _equal)) != _false)
	{
		List_PushBack(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _value);
	}
	else
	{
		List_AddBeforePosition(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _position, _value);
	}
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddEntityToList ended.")
	return toReturn;
}

Object Processor_CodeRemoveEntityFromListByPosition(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveEntityFromListByPosition begined.")
	ASSERT_C ( "Processor:CodeRemoveEntityFromListByPosition --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveEntityFromListByPosition --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _position;
	_position = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Позиция", 14), _toDo);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _nil) != _equal)) != _false)
	{
		List_RemoveObjectAtPosition(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _position);
	}
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveEntityFromListByPosition ended.")
	return toReturn;
}

Object Processor_CodeRemoveEntityFromListByValue(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveEntityFromListByValue begined.")
	ASSERT_C ( "Processor:CodeRemoveEntityFromListByValue --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveEntityFromListByValue --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	List_RemoveFirst(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _value);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveEntityFromListByValue ended.")
	return toReturn;
}

Object Processor_CodeAddEntityToStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddEntityToStack begined.")
	ASSERT_C ( "Processor:CodeAddEntityToStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddEntityToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((Processor) (_self->entity))->_helperStack), Object_TempClone(ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16))));
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddEntityToStack ended.")
	return toReturn;
}

Object Processor_CodeDuplicateTopInStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDuplicateTopInStack begined.")
	ASSERT_C ( "Processor:CodeDuplicateTopInStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDuplicateTopInStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((Processor) (_self->entity))->_helperStack), Object_TempClone(Stack_Peek((((Processor) (_self->entity))->_helperStack))));
	Object toReturn = _self;
	DPOPS ("Processor: CodeDuplicateTopInStack ended.")
	return toReturn;
}

Object Processor_CodeSwapTopInStack(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSwapTopInStack begined.")
	ASSERT_C ( "Processor:CodeSwapTopInStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSwapTopInStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _a;
	_a = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	Object _b;
	_b = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	Stack_Push((((Processor) (_self->entity))->_helperStack), _a);
	Stack_Push((((Processor) (_self->entity))->_helperStack), _b);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSwapTopInStack ended.")
	return toReturn;
}

Object Processor_CodeSendMessageToUID(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSendMessageToUID begined.")
	ASSERT_C ( "Processor:CodeSendMessageToUID --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSendMessageToUID --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _receiver;
	_receiver = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Получатель", 20), _toDo);
	Object _message;
	_message = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	ListMap_MessageSetSender(_message, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage(_self, _message);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSendMessageToUID ended.")
	return toReturn;
}

Object Processor_CodeSendMessageToField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSendMessageToField begined.")
	ASSERT_C ( "Processor:CodeSendMessageToField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSendMessageToField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _message;
	_message = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _receiver;
	_receiver = Processor_FieldNameToUID(_self, _fieldName);
	ListMap_MessageSetSender(_message, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage(_self, _message);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSendMessageToField ended.")
	return toReturn;
}

Object Processor_CodeSendMessageToMessageField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSendMessageToMessageField begined.")
	ASSERT_C ( "Processor:CodeSendMessageToMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSendMessageToMessageField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _message;
	_message = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_SendMessageToMessageField(_self, _message, _messageSlotName, _fieldName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSendMessageToMessageField ended.")
	return toReturn;
}

Object Processor_CodeSendReplyForMessage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSendReplyForMessage begined.")
	ASSERT_C ( "Processor:CodeSendReplyForMessage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSendReplyForMessage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _reply;
	_reply = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _toDo);
	Object _messageName;
	_messageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_SendReplyForMessage(_self, _reply, _messageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSendReplyForMessage ended.")
	return toReturn;
}

Object Processor_CodeInvokeMethod(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeInvokeMethod begined.")
	ASSERT_C ( "Processor:CodeInvokeMethod --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeInvokeMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _methodName;
	_methodName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _parameters;
	_parameters = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Параметры", 18), _toDo);
	Processor_InvokeMethodWithParameters(_self, _methodName, _parameters);
	Object toReturn = _self;
	DPOPS ("Processor: CodeInvokeMethod ended.")
	return toReturn;
}

Object Processor_CodeDefineMethod(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDefineMethod begined.")
	ASSERT_C ( "Processor:CodeDefineMethod --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDefineMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _methodName;
	_methodName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _method;
	_method = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _toDo);
	Processor_DefineMethod(_self, _method, _methodName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeDefineMethod ended.")
	return toReturn;
}

Object Processor_CodeUnDefineMethod(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUnDefineMethod begined.")
	ASSERT_C ( "Processor:CodeUnDefineMethod --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUnDefineMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_UnDefineMethod(_self, Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo));
	Object toReturn = _self;
	DPOPS ("Processor: CodeUnDefineMethod ended.")
	return toReturn;
}

Object Processor_CodeDefineLocalField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDefineLocalField begined.")
	ASSERT_C ( "Processor:CodeDefineLocalField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDefineLocalField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, Stack_Peek((((Processor) (_self->entity))->_localNamespaces)));
	DPOPS ("Processor: CodeDefineLocalField ended.")
	return toReturn;
}

Object Processor_CodeDefineJobField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDefineJobField begined.")
	ASSERT_C ( "Processor:CodeDefineJobField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDefineJobField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ObjectFields(Processor_ContextJob(_self)));
	DPOPS ("Processor: CodeDefineJobField ended.")
	return toReturn;
}

Object Processor_CodeDefineObjectField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDefineObjectField begined.")
	ASSERT_C ( "Processor:CodeDefineObjectField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDefineObjectField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ObjectFields(Processor_ContextObject(_self)));
	DPOPS ("Processor: CodeDefineObjectField ended.")
	return toReturn;
}

Object Processor_CodeDefineGlobalField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeDefineGlobalField begined.")
	ASSERT_C ( "Processor:CodeDefineGlobalField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeDefineGlobalField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext));
	DPOPS ("Processor: CodeDefineGlobalField ended.")
	return toReturn;
}

Object Processor_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace)
{
	DPUSHS ("Processor: DefineFieldHelper begined.")
	ASSERT_C ( "Processor:DefineFieldHelper --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:DefineFieldHelper --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	ASSERT_C ( "Processor:DefineFieldHelper --- Checking for correct parameter type failed at parameter _nameSpace.", _nameSpace->gid ==  2108332898258556672ull || _nameSpace == _nil )
	Object _uid;
	_uid = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Processor_DefineFieldInNameSpaceWithUID(_self, _fieldName, _nameSpace, _uid);
	Object toReturn = _self;
	DPOPS ("Processor: DefineFieldHelper ended.")
	return toReturn;
}

Object Processor_CodeSetField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeSetField begined.")
	ASSERT_C ( "Processor:CodeSetField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeSetField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _uid;
	_uid = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Processor_SetField(_self, _fieldName, _uid);
	Object toReturn = _self;
	DPOPS ("Processor: CodeSetField ended.")
	return toReturn;
}

Object Processor_CodeUniteField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUniteField begined.")
	ASSERT_C ( "Processor:CodeUniteField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUniteField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _destinationFieldName;
	_destinationFieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля прибытия", 32), _toDo);
	Object _sourceFieldName;
	_sourceFieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля отправления", 38), _toDo);
	Processor_UniteField(_self, _destinationFieldName, _sourceFieldName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeUniteField ended.")
	return toReturn;
}

Object Processor_CodeUnDefineField(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUnDefineField begined.")
	ASSERT_C ( "Processor:CodeUnDefineField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUnDefineField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _locationType;
	_locationType = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33));
	Processor_UnDefineFieldInNamespace(_self, _fieldName, _locationType);
	Object toReturn = _self;
	DPOPS ("Processor: CodeUnDefineField ended.")
	return toReturn;
}

Object Processor_CodeAddJob(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddJob begined.")
	ASSERT_C ( "Processor:CodeAddJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddJob --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobName;
	_jobName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя работы", 19), _toDo);
	Object _job;
	_job = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Работа", 12), _toDo);
	Processor_AddJobWithName(_self, _job, _jobName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddJob ended.")
	return toReturn;
}

Object Processor_CodeFinishThisJob(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeFinishThisJob begined.")
	ASSERT_C ( "Processor:CodeFinishThisJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeFinishThisJob --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_FinishThisJob(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeFinishThisJob ended.")
	return toReturn;
}

Object Processor_CodeAddJobStage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddJobStage begined.")
	ASSERT_C ( "Processor:CodeAddJobStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddJobStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobStageName;
	_jobStageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _jobStage;
	_jobStage = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Стадия", 12), _toDo);
	Processor_AddJobStage(_self, _jobStage, _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddJobStage ended.")
	return toReturn;
}

Object Processor_CodeAddMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAddMessageSlot begined.")
	ASSERT_C ( "Processor:CodeAddMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAddMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _messageSlot;
	_messageSlot = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Processor_AddMessageSlot(_self, _messageSlot, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAddMessageSlot ended.")
	return toReturn;
}

Object Processor_CodeBlockStage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeBlockStage begined.")
	ASSERT_C ( "Processor:CodeBlockStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeBlockStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_BlockStage(_self, _stageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeBlockStage ended.")
	return toReturn;
}

Object Processor_CodeUnBlockStage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUnBlockStage begined.")
	ASSERT_C ( "Processor:CodeUnBlockStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUnBlockStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_UnBlockStage(_self, _stageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeUnBlockStage ended.")
	return toReturn;
}

Object Processor_CodeBlockMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeBlockMessageSlot begined.")
	ASSERT_C ( "Processor:CodeBlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeBlockMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_BlockMessageSlot(_self, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeBlockMessageSlot ended.")
	return toReturn;
}

Object Processor_CodeUnBlockMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeUnBlockMessageSlot begined.")
	ASSERT_C ( "Processor:CodeUnBlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeUnBlockMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_UnBlockMessageSlot(_self, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeUnBlockMessageSlot ended.")
	return toReturn;
}

Object Processor_CodeRemoveJobStage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveJobStage begined.")
	ASSERT_C ( "Processor:CodeRemoveJobStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveJobStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobStageName;
	_jobStageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_RemoveJobStage(_self, _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveJobStage ended.")
	return toReturn;
}

Object Processor_CodeRemoveMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveMessageSlot begined.")
	ASSERT_C ( "Processor:CodeRemoveMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_RemoveMessageSlot(_self, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveMessageSlot ended.")
	return toReturn;
}

Object Processor_CodeRemoveMessageInMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveMessageInMessageSlot begined.")
	ASSERT_C ( "Processor:CodeRemoveMessageInMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveMessageInMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_RemoveMessageInMessageSlot(_self, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveMessageInMessageSlot ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllMessagesOfCurrentStageForCurrentStage(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllMessagesOfCurrentStageForCurrentStage begined.")
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfCurrentStageForCurrentStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfCurrentStageForCurrentStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfCurrentStageForCurrentStage(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllMessagesOfCurrentStageForCurrentStage ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllMessagesOfCurrentStageForAllStages(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllMessagesOfCurrentStageForAllStages begined.")
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfCurrentStageForAllStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfCurrentStageForAllStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfCurrentStageForAllStages(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllMessagesOfCurrentStageForAllStages ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllMessagesOfAllOpenedStages(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllMessagesOfAllOpenedStages begined.")
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfAllOpenedStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllMessagesOfAllOpenedStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfAllOpenedStages(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllMessagesOfAllOpenedStages ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllReceivedMessages(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllReceivedMessages begined.")
	ASSERT_C ( "Processor:CodeRemoveAllReceivedMessages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllReceivedMessages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllReceivedMessages(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllReceivedMessages ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllStages(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllStages begined.")
	ASSERT_C ( "Processor:CodeRemoveAllStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllStages(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllStages ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllMessageSlots(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllMessageSlots begined.")
	ASSERT_C ( "Processor:CodeRemoveAllMessageSlots --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllMessageSlots --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessageSlots(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllMessageSlots ended.")
	return toReturn;
}

Object Processor_CodeRemoveAllStagesAndMessageSlots(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeRemoveAllStagesAndMessageSlots begined.")
	ASSERT_C ( "Processor:CodeRemoveAllStagesAndMessageSlots --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeRemoveAllStagesAndMessageSlots --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllStagesAndMessageSlots(_self);
	Object toReturn = _self;
	DPOPS ("Processor: CodeRemoveAllStagesAndMessageSlots ended.")
	return toReturn;
}

Object Processor_CodeAttachToStageMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("Processor: CodeAttachToStageMessageSlot begined.")
	ASSERT_C ( "Processor:CodeAttachToStageMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:CodeAttachToStageMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _messageName;
	_messageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_AttachToStageMessageSlot(_self, _stageName, _messageName);
	Object toReturn = _self;
	DPOPS ("Processor: CodeAttachToStageMessageSlot ended.")
	return toReturn;
}

Object Processor_DefineMethod(Object _self, Object _method, Object _methodName)
{
	DPUSHS ("Processor: DefineMethod begined.")
	ASSERT_C ( "Processor:DefineMethod --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:DefineMethod --- Checking for correct parameter type failed at parameter _method.", _method->gid ==  2108332898258556672ull || _method == _nil )
	ASSERT_C ( "Processor:DefineMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ListMap_ObjectSetMethod(Processor_ContextObject(_self), _method, _methodName);
	Object toReturn = _self;
	DPOPS ("Processor: DefineMethod ended.")
	return toReturn;
}

Object Processor_UnDefineMethod(Object _self, Object _methodName)
{
	DPUSHS ("Processor: UnDefineMethod begined.")
	ASSERT_C ( "Processor:UnDefineMethod --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnDefineMethod --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ListMap_ObjectRemoveMethod(Processor_ContextObject(_self), _methodName);
	Object toReturn = _self;
	DPOPS ("Processor: UnDefineMethod ended.")
	return toReturn;
}

Object Processor_DefineFieldInNameSpaceWithUID(Object _self, Object _fieldName, Object _nameSpace, Object _uid)
{
	DPUSHS ("Processor: DefineFieldInNameSpaceWithUID begined.")
	ASSERT_C ( "Processor:DefineFieldInNameSpaceWithUID --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:DefineFieldInNameSpaceWithUID --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Processor:DefineFieldInNameSpaceWithUID --- Checking for correct parameter type failed at parameter _nameSpace.", _nameSpace->gid ==  2108332898258556672ull || _nameSpace == _nil )
	ASSERT_C ( "Processor:DefineFieldInNameSpaceWithUID --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Machine_DefineFieldHelper((((Processor) (_self->entity))->_machine), _uid, _fieldName, _nameSpace);
	Object toReturn = _self;
	DPOPS ("Processor: DefineFieldInNameSpaceWithUID ended.")
	return toReturn;
}

Object Processor_SetField(Object _self, Object _fieldName, Object _uid)
{
	DPUSHS ("Processor: SetField begined.")
	ASSERT_C ( "Processor:SetField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:SetField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Processor:SetField --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	Synonim_SetUID(Processor_FieldNameToSynonim(_self, _fieldName), _uid);
	Object toReturn = _self;
	DPOPS ("Processor: SetField ended.")
	return toReturn;
}

Object Processor_UniteField(Object _self, Object _destinationFieldName, Object _sourceFieldName)
{
	DPUSHS ("Processor: UniteField begined.")
	ASSERT_C ( "Processor:UniteField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UniteField --- Checking for correct parameter type failed at parameter _destinationFieldName.", _destinationFieldName->gid ==  3732711262168886272ull || _destinationFieldName == _nil )
	ASSERT_C ( "Processor:UniteField --- Checking for correct parameter type failed at parameter _sourceFieldName.", _sourceFieldName->gid ==  3732711262168886272ull || _sourceFieldName == _nil )
	Synonim_Unite(Processor_FieldNameToSynonim(_self, _destinationFieldName), Processor_FieldNameToSynonim(_self, _sourceFieldName));
	Object toReturn = _self;
	DPOPS ("Processor: UniteField ended.")
	return toReturn;
}

Object Processor_UnDefineFieldInNamespace(Object _self, Object _fieldName, Object _locationType)
{
	DPUSHS ("Processor: UnDefineFieldInNamespace begined.")
	ASSERT_C ( "Processor:UnDefineFieldInNamespace --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnDefineFieldInNamespace --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Processor:UnDefineFieldInNamespace --- Checking for correct parameter type failed at parameter _locationType.", _locationType->gid ==  3732711262168886272ull || _locationType == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, _nil) == _equal)) != _false)
	{
		_locationType = Processor_FieldNameToNamespaceName(_self, _fieldName);
	}
	Object _place;
	_place = ListMap_Create();
	ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Имя", 6), _fieldName);
	ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), Processor_NamespaceNameToNamespace(_self, _locationType));
	Object _synonim;
	_synonim = Processor_FieldNameToSynonim(_self, _fieldName);
	Synonim_RemoveReference(_synonim, _place);
	Object_Release(_place);
	Object toReturn = _self;
	DPOPS ("Processor: UnDefineFieldInNamespace ended.")
	return toReturn;
}

Object Processor_AddJobWithName(Object _self, Object _job, Object _jobName)
{
	DPUSHS ("Processor: AddJobWithName begined.")
	ASSERT_C ( "Processor:AddJobWithName --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AddJobWithName --- Checking for correct parameter type failed at parameter _job.", _job->gid ==  2108332898258556672ull || _job == _nil )
	ASSERT_C ( "Processor:AddJobWithName --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_ObjectSetJob(Processor_ContextObject(_self), _job, _jobName);
	Object toReturn = _self;
	DPOPS ("Processor: AddJobWithName ended.")
	return toReturn;
}

Object Processor_FinishThisJob(Object _self)
{
	DPUSHS ("Processor: FinishThisJob begined.")
	ASSERT_C ( "Processor:FinishThisJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ListMap_ObjectRemoveJob(Processor_ContextObject(_self), (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: FinishThisJob ended.")
	return toReturn;
}

Object Processor_AddJobStage(Object _self, Object _jobStage, Object _jobStageName)
{
	DPUSHS ("Processor: AddJobStage begined.")
	ASSERT_C ( "Processor:AddJobStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AddJobStage --- Checking for correct parameter type failed at parameter _jobStage.", _jobStage->gid ==  3732711262168886272ull || _jobStage == _nil )
	ASSERT_C ( "Processor:AddJobStage --- Checking for correct parameter type failed at parameter _jobStageName.", _jobStageName->gid ==  3732711262168886272ull || _jobStageName == _nil )
	Processor_AddJobStageInJob(_self, _jobStage, _jobStageName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: AddJobStage ended.")
	return toReturn;
}

Object Processor_BlockStage(Object _self, Object _stageName)
{
	DPUSHS ("Processor: BlockStage begined.")
	ASSERT_C ( "Processor:BlockStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:BlockStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	Processor_BlockStageInJob(_self, _stageName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: BlockStage ended.")
	return toReturn;
}

Object Processor_UnBlockStage(Object _self, Object _stageName)
{
	DPUSHS ("Processor: UnBlockStage begined.")
	ASSERT_C ( "Processor:UnBlockStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnBlockStage --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	Processor_UnBlockStageInJob(_self, _stageName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: UnBlockStage ended.")
	return toReturn;
}

Object Processor_RemoveJobStage(Object _self, Object _jobStageName)
{
	DPUSHS ("Processor: RemoveJobStage begined.")
	ASSERT_C ( "Processor:RemoveJobStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveJobStage --- Checking for correct parameter type failed at parameter _jobStageName.", _jobStageName->gid ==  3732711262168886272ull || _jobStageName == _nil )
	Processor_RemoveJobStageInJob(_self, _jobStageName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveJobStage ended.")
	return toReturn;
}

Object Processor_RemoveAllStages(Object _self)
{
	DPUSHS ("Processor: RemoveAllStages begined.")
	ASSERT_C ( "Processor:RemoveAllStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllStagesInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllStages ended.")
	return toReturn;
}

Object Processor_AddMessageSlot(Object _self, Object _messageSlot, Object _messageSlotName)
{
	DPUSHS ("Processor: AddMessageSlot begined.")
	ASSERT_C ( "Processor:AddMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AddMessageSlot --- Checking for correct parameter type failed at parameter _messageSlot.", _messageSlot->gid ==  3732711262168886272ull || _messageSlot == _nil )
	ASSERT_C ( "Processor:AddMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Processor_AddMessageSlotInJob(_self, _messageSlot, _messageSlotName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: AddMessageSlot ended.")
	return toReturn;
}

Object Processor_BlockMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("Processor: BlockMessageSlot begined.")
	ASSERT_C ( "Processor:BlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:BlockMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Processor_BlockMessageSlotInJob(_self, _messageSlotName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: BlockMessageSlot ended.")
	return toReturn;
}

Object Processor_UnBlockMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("Processor: UnBlockMessageSlot begined.")
	ASSERT_C ( "Processor:UnBlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnBlockMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Processor_UnBlockMessageSlotInJob(_self, _messageSlotName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: UnBlockMessageSlot ended.")
	return toReturn;
}

Object Processor_RemoveMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("Processor: RemoveMessageSlot begined.")
	ASSERT_C ( "Processor:RemoveMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Processor_RemoveMessageSlotInJob(_self, _messageSlotName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveMessageSlot ended.")
	return toReturn;
}

Object Processor_RemoveAllMessageSlots(Object _self)
{
	DPUSHS ("Processor: RemoveAllMessageSlots begined.")
	ASSERT_C ( "Processor:RemoveAllMessageSlots --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllMessageSlotsInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessageSlots ended.")
	return toReturn;
}

Object Processor_AttachToStageMessageSlot(Object _self, Object _stageName, Object _messageName)
{
	DPUSHS ("Processor: AttachToStageMessageSlot begined.")
	ASSERT_C ( "Processor:AttachToStageMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AttachToStageMessageSlot --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "Processor:AttachToStageMessageSlot --- Checking for correct parameter type failed at parameter _messageName.", _messageName->gid ==  3732711262168886272ull || _messageName == _nil )
	Processor_AttachToStageMessageSlotInJob(_self, _stageName, _messageName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: AttachToStageMessageSlot ended.")
	return toReturn;
}

Object Processor_RemoveAllStagesAndMessageSlots(Object _self)
{
	DPUSHS ("Processor: RemoveAllStagesAndMessageSlots begined.")
	ASSERT_C ( "Processor:RemoveAllStagesAndMessageSlots --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllStagesAndMessageSlotsInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllStagesAndMessageSlots ended.")
	return toReturn;
}

Object Processor_RemoveMessageInMessageSlot(Object _self, Object _messageSlotName)
{
	DPUSHS ("Processor: RemoveMessageInMessageSlot begined.")
	ASSERT_C ( "Processor:RemoveMessageInMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveMessageInMessageSlot --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Processor_RemoveMessageInMessageSlotInJob(_self, _messageSlotName, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveMessageInMessageSlot ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfCurrentStageForCurrentStage(Object _self)
{
	DPUSHS ("Processor: RemoveAllMessagesOfCurrentStageForCurrentStage begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForCurrentStage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllMessagesOfCurrentStageForAllStagesInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfCurrentStageForCurrentStage ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfCurrentStageForAllStages(Object _self)
{
	DPUSHS ("Processor: RemoveAllMessagesOfCurrentStageForAllStages begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForAllStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllMessagesOfCurrentStageForAllStagesInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfCurrentStageForAllStages ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfAllOpenedStages(Object _self)
{
	DPUSHS ("Processor: RemoveAllMessagesOfAllOpenedStages begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfAllOpenedStages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllMessagesOfAllOpenedStagesInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfAllOpenedStages ended.")
	return toReturn;
}

Object Processor_RemoveAllReceivedMessages(Object _self)
{
	DPUSHS ("Processor: RemoveAllReceivedMessages begined.")
	ASSERT_C ( "Processor:RemoveAllReceivedMessages --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Processor_RemoveAllReceivedMessagesInJob(_self, (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllReceivedMessages ended.")
	return toReturn;
}

Object Processor_AddJobStageInJob(Object _self, Object _jobStage, Object _jobStageName, Object _jobName)
{
	DPUSHS ("Processor: AddJobStageInJob begined.")
	ASSERT_C ( "Processor:AddJobStageInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AddJobStageInJob --- Checking for correct parameter type failed at parameter _jobStage.", _jobStage->gid ==  3732711262168886272ull || _jobStage == _nil )
	ASSERT_C ( "Processor:AddJobStageInJob --- Checking for correct parameter type failed at parameter _jobStageName.", _jobStageName->gid ==  3732711262168886272ull || _jobStageName == _nil )
	ASSERT_C ( "Processor:AddJobStageInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_JobSetStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _jobStage, _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: AddJobStageInJob ended.")
	return toReturn;
}

Object Processor_BlockStageInJob(Object _self, Object _stageName, Object _jobName)
{
	DPUSHS ("Processor: BlockStageInJob begined.")
	ASSERT_C ( "Processor:BlockStageInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:BlockStageInJob --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "Processor:BlockStageInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_StageSetBlocked(ListMap_JobStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _stageName));
	Object toReturn = _self;
	DPOPS ("Processor: BlockStageInJob ended.")
	return toReturn;
}

Object Processor_UnBlockStageInJob(Object _self, Object _stageName, Object _jobName)
{
	DPUSHS ("Processor: UnBlockStageInJob begined.")
	ASSERT_C ( "Processor:UnBlockStageInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnBlockStageInJob --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "Processor:UnBlockStageInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _stage;
	_stage = ListMap_JobStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _stageName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_StageMessagesCounter(_stage), NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
	{
		ListMap_StageSetReady(_stage);
	}
	else
	{
		ListMap_StageSetWaiting(_stage);
	}
	Object toReturn = _self;
	DPOPS ("Processor: UnBlockStageInJob ended.")
	return toReturn;
}

Object Processor_RemoveJobStageInJob(Object _self, Object _jobStageName, Object _jobName)
{
	DPUSHS ("Processor: RemoveJobStageInJob begined.")
	ASSERT_C ( "Processor:RemoveJobStageInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveJobStageInJob --- Checking for correct parameter type failed at parameter _jobStageName.", _jobStageName->gid ==  3732711262168886272ull || _jobStageName == _nil )
	ASSERT_C ( "Processor:RemoveJobStageInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _iterator;
	_iterator = ListMap_JobMessageSlotsIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMapIterator_ThisValue(_iterator);
		Object _stages;
		_stages = ListMap_MessageSlotStages(_messageSlot);
		List_RemoveFirst(_stages, _jobStageName);
		ListMapIterator_Next(_iterator);
	}
	ListMap_JobRemoveStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveJobStageInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllStagesInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllStagesInJob begined.")
	ASSERT_C ( "Processor:RemoveAllStagesInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllStagesInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_JobRemoveAllStages(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_JobMessageSlotsIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	while((Logic_Not(ListMapIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMapIterator_ListMapData(_messageSlotsIterator);
		List_Clean(ListMap_MessageSlotStages(_messageSlot));
		ListMapIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllStagesInJob ended.")
	return toReturn;
}

Object Processor_AddMessageSlotInJob(Object _self, Object _messageSlot, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: AddMessageSlotInJob begined.")
	ASSERT_C ( "Processor:AddMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AddMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlot.", _messageSlot->gid ==  3732711262168886272ull || _messageSlot == _nil )
	ASSERT_C ( "Processor:AddMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:AddMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_JobSetMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlot, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: AddMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_BlockMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: BlockMessageSlotInJob begined.")
	ASSERT_C ( "Processor:BlockMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:BlockMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:BlockMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_MessageSlotBlock(ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName));
	Object toReturn = _self;
	DPOPS ("Processor: BlockMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_UnBlockMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: UnBlockMessageSlotInJob begined.")
	ASSERT_C ( "Processor:UnBlockMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:UnBlockMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:UnBlockMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_MessageSlotOpen(ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName));
	Object toReturn = _self;
	DPOPS ("Processor: UnBlockMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_RemoveMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: RemoveMessageSlotInJob begined.")
	ASSERT_C ( "Processor:RemoveMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:RemoveMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_JobMessageInMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName), _nil) != _equal)) != _false)
	{
		Object _stagesIterator;
		_stagesIterator = ListMap_JobStagesIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
		while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
		{
			Object _stage;
			_stage = ListMapIterator_ListMapData(_stagesIterator);
			if((List_RemoveFirstWithConfirmation(ListMap_StageMessageSlots(_stage), _messageSlotName)) != _false)
			{
				ListMap_StageDecrementMessagesCounter(_stage);
				if((Logic_And(ListMap_StageIsWaiting(_stage), LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_StageMessagesCounter(_stage), NumberFactory_FromLong(_numberFactory, 0)) == _equal))) != _false)
				{
					ListMap_StageSetReady(_stage);
				}
			}
			ListMapIterator_Next(_stagesIterator);
		}
	}
	else
	{
		Object _stagesIterator;
		_stagesIterator = ListMap_JobStagesIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
		while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
		{
			Object _stage;
			_stage = ListMapIterator_ListMapData(_stagesIterator);
			List_RemoveFirst(ListMap_StageMessageSlots(_stage), _messageSlotName);
			ListMapIterator_Next(_stagesIterator);
		}
	}
	ListMap_JobRemoveMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllMessageSlotsInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllMessageSlotsInJob begined.")
	ASSERT_C ( "Processor:RemoveAllMessageSlotsInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllMessageSlotsInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_JobRemoveAllMessageSlots(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	Object _jobStagesIterator;
	_jobStagesIterator = ListMap_JobStagesIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobStagesIterator))) != _false)
	{
		Object _jobStage;
		_jobStage = ListMapIterator_ThisValue(_jobStagesIterator);
		List_Clean(ListMap_StageMessageSlots(_jobStage));
		ListMap_StageSetMessagesCounter(_jobStage, NumberFactory_FromLong(_numberFactory, 0));
		ListMap_StageSetBlocked(_jobStage);
		ListMapIterator_Next(_jobStagesIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessageSlotsInJob ended.")
	return toReturn;
}

Object Processor_AttachToStageMessageSlotInJob(Object _self, Object _stageName, Object _messageName, Object _jobName)
{
	DPUSHS ("Processor: AttachToStageMessageSlotInJob begined.")
	ASSERT_C ( "Processor:AttachToStageMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:AttachToStageMessageSlotInJob --- Checking for correct parameter type failed at parameter _stageName.", _stageName->gid ==  3732711262168886272ull || _stageName == _nil )
	ASSERT_C ( "Processor:AttachToStageMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageName.", _messageName->gid ==  3732711262168886272ull || _messageName == _nil )
	ASSERT_C ( "Processor:AttachToStageMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _stage;
	_stage = ListMap_JobStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _stageName);
	Object _stagesInMessageSlot;
	_stagesInMessageSlot = ListMap_MessageSlotStages(ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageName));
	if((Logic_Not(List_Contains(_stagesInMessageSlot, _stageName))) != _false)
	{
		Object _messageSlotsInStage;
		_messageSlotsInStage = ListMap_StageMessageSlots(_stage);
		List_PushBack(_stagesInMessageSlot, _stageName);
		List_PushBack(_messageSlotsInStage, _messageName);
		ListMap_StageIncrementMessagesCounter(_stage);
		if((ListMap_StageIsReady(_stage)) != _false)
		{
			ListMap_StageSetWaiting(_stage);
		}
	}
	Object toReturn = _self;
	DPOPS ("Processor: AttachToStageMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllStagesAndMessageSlotsInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllStagesAndMessageSlotsInJob begined.")
	ASSERT_C ( "Processor:RemoveAllStagesAndMessageSlotsInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllStagesAndMessageSlotsInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	ListMap_JobRemoveAllStages(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	ListMap_JobRemoveAllMessageSlots(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllStagesAndMessageSlotsInJob ended.")
	return toReturn;
}

Object Processor_RemoveMessageInMessageSlotInJob(Object _self, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: RemoveMessageInMessageSlotInJob begined.")
	ASSERT_C ( "Processor:RemoveMessageInMessageSlotInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveMessageInMessageSlotInJob --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:RemoveMessageInMessageSlotInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _messageSlot;
	_messageSlot = ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_MessageSlotMessage(_messageSlot), _nil) != _equal)) != _false)
	ListMap_MessageSlotRemoveMessage(_messageSlot, _nil);
	Object _stagesIterator;
	_stagesIterator = ListMap_MessageSlotStagesIterator(_messageSlot);
	while((Logic_Not(ListIterator_ThisEnd(_stagesIterator))) != _false)
	{
		Object _stage;
		_stage = ListMap_JobStage(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), ListIterator_ListData(_stagesIterator));
		ListMap_StageDecrementMessagesCounter(_stage);
		if((ListMap_StageIsReady(_stage)) != _false)
		{
			ListMap_StageSetWaiting(_stage);
		}
		ListIterator_Next(_stagesIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveMessageInMessageSlotInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfCurrentStageForCurrentStageInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllMessagesOfCurrentStageForCurrentStageInJob begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForCurrentStageInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForCurrentStageInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_StageMessageSlotsIterator(Processor_ContextJobStage(_self));
	while((Logic_Not(ListIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlotName;
		_messageSlotName = ListIterator_ListData(_messageSlotsIterator);
		Object _messageSlot;
		_messageSlot = ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName);
		ListMap_MessageSlotRemoveMessage(_messageSlot, _nil);
		ListIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfCurrentStageForCurrentStageInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfCurrentStageForAllStagesInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllMessagesOfCurrentStageForAllStagesInJob begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForAllStagesInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllMessagesOfCurrentStageForAllStagesInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_StageMessageSlotsIterator(Processor_ContextJobStage(_self));
	while((Logic_Not(ListIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlotName;
		_messageSlotName = ListIterator_ListData(_messageSlotsIterator);
		Object _messageSlot;
		_messageSlot = ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), _messageSlotName);
		Object _message;
		_message = ListMap_MessageSlotMessage(_messageSlot);
		Object _messageMessageSlotsIterator;
		_messageMessageSlotsIterator = ListMap_First(ListMap_MessageAttributesMessageSlots(_message));
		while((Logic_Not(ListMapIterator_ThisEnd(_messageMessageSlotsIterator))) != _false)
		{
			Object _messageMessageSlot;
			_messageMessageSlot = ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), ListMapIterator_ListData(_messageMessageSlotsIterator));
			ListMap_MessageSlotRemoveMessage(_messageMessageSlot, _message);
			ListMapIterator_Next(_messageMessageSlotsIterator);
		}
		ListIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfCurrentStageForAllStagesInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllMessagesOfAllOpenedStagesInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllMessagesOfAllOpenedStagesInJob begined.")
	ASSERT_C ( "Processor:RemoveAllMessagesOfAllOpenedStagesInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllMessagesOfAllOpenedStagesInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_StageMessageSlotsIterator(Processor_ContextJobStage(_self));
	while((Logic_Not(ListIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMap_JobMessageSlot(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName), ListIterator_ListData(_messageSlotsIterator));
		if((ListMap_MessageSlotIsOpened(_messageSlot)) != _false)
		{
			ListMap_MessageSlotRemoveAllMessages(_messageSlot);
		}
		ListIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessagesOfAllOpenedStagesInJob ended.")
	return toReturn;
}

Object Processor_RemoveAllReceivedMessagesInJob(Object _self, Object _jobName)
{
	DPUSHS ("Processor: RemoveAllReceivedMessagesInJob begined.")
	ASSERT_C ( "Processor:RemoveAllReceivedMessagesInJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:RemoveAllReceivedMessagesInJob --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_JobMessageSlotsIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	Object _stagesIterator;
	_stagesIterator = ListMap_JobStagesIterator(ListMap_ObjectJob(Processor_ContextObject(_self), _jobName));
	while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
	{
		Object _stage;
		_stage = ListMapIterator_ListMapData(_stagesIterator);
		ListMap_StageSetMessagesCounter(_stage, List_Size(ListMap_StageMessageSlots(_stage)));
		ListMapIterator_Next(_stagesIterator);
	}
	while((Logic_Not(ListMapIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMapIterator_ListMapData(_messageSlotsIterator);
		ListMap_MessageSlotRemoveAllMessages(_messageSlot);
		ListMapIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllReceivedMessagesInJob ended.")
	return toReturn;
}

Object Processor_EntityFromNamedMessageField(Object _self, Object _messageName, Object _fieldName)
{
	DPUSHS ("Processor: EntityFromNamedMessageField begined.")
	ASSERT_C ( "Processor:EntityFromNamedMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:EntityFromNamedMessageField --- Checking for correct parameter type failed at parameter _messageName.", _messageName->gid ==  3732711262168886272ull || _messageName == _nil )
	ASSERT_C ( "Processor:EntityFromNamedMessageField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object toReturn = ListMap_ObjectAt(ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageName), _fieldName);
	DPOPS ("Processor: EntityFromNamedMessageField ended.")
	return toReturn;
}

Object Processor_NamespaceNameToNamespace(Object _self, Object _locationType)
{
	DPUSHS ("Processor: NamespaceNameToNamespace begined.")
	ASSERT_C ( "Processor:NamespaceNameToNamespace --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:NamespaceNameToNamespace --- Checking for correct parameter type failed at parameter _locationType.", _locationType->gid ==  3732711262168886272ull || _locationType == _nil )
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Глобальное поле", 29)) == _equal)) != _false)
	{
		Object toReturn = (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext);
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23)) == _equal)) != _false)
	{
		Object toReturn = ListMap_ObjectFields(Processor_ContextObject(_self));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле работы", 21)) == _equal)) != _false)
	{
		Object toReturn = ListMap_ObjectFields(Processor_ContextJob(_self));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27)) == _equal)) != _false)
	{
		Object toReturn = Stack_Peek((((Processor) (_self->entity))->_localNamespaces));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = _nil;
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
}

Object Processor_FieldNameToNamespaceName(Object _self, Object _fieldName)
{
	DPUSHS ("Processor: FieldNameToNamespaceName begined.")
	ASSERT_C ( "Processor:FieldNameToNamespaceName --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:FieldNameToNamespaceName --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	if((ListMap_Contains(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _fieldName)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	else if((ListMap_Contains(ListMap_ObjectFields(Processor_ContextJob(_self)), _fieldName)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Поле работы", 21);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	else if((ListMap_Contains(ListMap_ObjectFields(Processor_ContextObject(_self)), _fieldName)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	else if((ListMap_Contains((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _fieldName)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Глобальное поле", 29);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	else
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Нет такого поля", 28);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
}

Object Processor_FieldNameToSynonim(Object _self, Object _fieldName)
{
	DPUSHS ("Processor: FieldNameToSynonim begined.")
	ASSERT_C ( "Processor:FieldNameToSynonim --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:FieldNameToSynonim --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object _candidate;
	_candidate = ListMap_SynonimAt(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt(ListMap_ObjectFields(Processor_ContextJob(_self)), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt(ListMap_ObjectFields(Processor_ContextObject(_self)), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "!!!!!!!!! Ошибка! Взятие отсутствующего поля.", 75));
	Object toReturn = _nil;
	DPOPS ("Processor: FieldNameToSynonim ended.")
	return toReturn;
}

Object Processor_FieldNameToSynonimInJobObject(Object _self, Object _fieldName, Object _job, Object _object)
{
	DPUSHS ("Processor: FieldNameToSynonimInJobObject begined.")
	ASSERT_C ( "Processor:FieldNameToSynonimInJobObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:FieldNameToSynonimInJobObject --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Processor:FieldNameToSynonimInJobObject --- Checking for correct parameter type failed at parameter _job.", _job->gid ==  2108332898258556672ull || _job == _nil )
	ASSERT_C ( "Processor:FieldNameToSynonimInJobObject --- Checking for correct parameter type failed at parameter _object.", _object->gid ==  2108332898258556672ull || _object == _nil )
	Object _candidate;
	_candidate = ListMap_SynonimAt(ListMap_ObjectFields(_job), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonimInJobObject ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt(ListMap_ObjectFields(_object), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonimInJobObject ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _fieldName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonimInJobObject ended.")
		return toReturn;
	}
	Object toReturn = _nil;
	DPOPS ("Processor: FieldNameToSynonimInJobObject ended.")
	return toReturn;
}

Object Processor_FieldNameToUID(Object _self, Object _fieldName)
{
	DPUSHS ("Processor: FieldNameToUID begined.")
	ASSERT_C ( "Processor:FieldNameToUID --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:FieldNameToUID --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object toReturn = Synonim_GetUID(Processor_FieldNameToSynonim(_self, _fieldName));
	DPOPS ("Processor: FieldNameToUID ended.")
	return toReturn;
}

Object Processor_EntityFromMessageField(Object _self, Object _fieldName, Object _messageSlotName)
{
	DPUSHS ("Processor: EntityFromMessageField begined.")
	ASSERT_C ( "Processor:EntityFromMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:EntityFromMessageField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	ASSERT_C ( "Processor:EntityFromMessageField --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object toReturn = ListMap_JobFieldInMessageSlot(Processor_ContextJob(_self), _fieldName, _messageSlotName);
	DPOPS ("Processor: EntityFromMessageField ended.")
	return toReturn;
}

Object Processor_SendMessage(Object _self, Object _message)
{
	DPUSHS ("Processor: SendMessage begined.")
	ASSERT_C ( "Processor:SendMessage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:SendMessage --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	Object _uid;
	_uid = ListMap_MessageReceiver(_message);
	Object _receiver;
	_receiver = Machine_UIDToObject((((Processor) (_self->entity))->_machine), _uid);
	Processor_ProcessMessageForObject(_self, _message, _receiver);
	Machine_ScheduleUID((((Processor) (_self->entity))->_machine), _uid);
	Object toReturn = _self;
	DPOPS ("Processor: SendMessage ended.")
	return toReturn;
}

Object Processor_SendMessageToMessageField(Object _self, Object _message, Object _messageSlotName, Object _fieldName)
{
	DPUSHS ("Processor: SendMessageToMessageField begined.")
	ASSERT_C ( "Processor:SendMessageToMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:SendMessageToMessageField --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "Processor:SendMessageToMessageField --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:SendMessageToMessageField --- Checking for correct parameter type failed at parameter _fieldName.", _fieldName->gid ==  3732711262168886272ull || _fieldName == _nil )
	Object _receiver;
	_receiver = ListMap_ObjectAt(ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageSlotName), _fieldName);
	ListMap_MessageSetSender(_message, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage(_self, _message);
	Object toReturn = _self;
	DPOPS ("Processor: SendMessageToMessageField ended.")
	return toReturn;
}

Object Processor_SendReplyForMessage(Object _self, Object _replyMessage, Object _messageSlotName)
{
	DPUSHS ("Processor: SendReplyForMessage begined.")
	ASSERT_C ( "Processor:SendReplyForMessage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:SendReplyForMessage --- Checking for correct parameter type failed at parameter _replyMessage.", _replyMessage->gid ==  2108332898258556672ull || _replyMessage == _nil )
	ASSERT_C ( "Processor:SendReplyForMessage --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	Object _message;
	_message = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageSlotName);
	Object _receiver;
	_receiver = ListMap_MessageSender(_message);
	Object _reqest;
	_reqest = ListMap_MessageRequest(_message);
	_replyMessage = Object_TempDeepClone(_replyMessage);
	ListMap_MessageSetSender(_replyMessage, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_replyMessage, _receiver);
	ListMap_MessageSetRequest(_replyMessage, _reqest);
	ListMap_MessageSetTypeReply(_replyMessage);
	Processor_SendMessage(_self, _replyMessage);
	Object toReturn = _self;
	DPOPS ("Processor: SendReplyForMessage ended.")
	return toReturn;
}

Object Processor_InvokeMethodWithParameters(Object _self, Object _methodName, Object _parameters)
{
	DPUSHS ("Processor: InvokeMethodWithParameters begined.")
	ASSERT_C ( "Processor:InvokeMethodWithParameters --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:InvokeMethodWithParameters --- Checking for correct parameter type failed at parameter _methodName.", _methodName->gid ==  3732711262168886272ull || _methodName == _nil )
	ASSERT_C ( "Processor:InvokeMethodWithParameters --- Checking for correct parameter type failed at parameter _parameters.", _parameters->gid ==  2108332898258556672ull || _parameters == _nil )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _method;
	_method = ListMap_ObjectMethod(Processor_ContextObject(_self), _methodName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "!!!!!!!! Ошибка! Вызов несуществующего метода.", 78));
	}
	else
	{
		Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Процессор вызывает метод: ", 48));
		Console_WriteLnString(_console, _methodName);
		Object _namespace;
		_namespace = ListMap_Create();
		Stack_Push((((Processor) (_self->entity))->_localNamespaces), _namespace);
		ListMap_AddListMap(_namespace, _parameters);
		Object_Release(_namespace);
		if((ListMap_LogicAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14))) != _false)
		{
			Object _basicMethod;
			_basicMethod = ListMap_MethodAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый метод", 25));
			Object _objectEntity;
			_objectEntity = ListMap_ObjectAt(_method, StringFactory_FromUTF8(_stringFactory, "Сущность", 16));
			Method_Invoke(_basicMethod, _objectEntity, _self);
		}
		else
		{
			Object _methodBody;
			_methodBody = ListMap_ListAt(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8));
			Object _iterator;
			_iterator = List_First(_methodBody);
			while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
			{
				Processor_Do(_self, ListIterator_ListMapData(_iterator));
				ListIterator_Next(_iterator);
			}
		}
		Stack_Pop((((Processor) (_self->entity))->_localNamespaces));
	}
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _self;
	DPOPS ("Processor: InvokeMethodWithParameters ended.")
	return toReturn;
}

Object Processor_MessageConfirmsToParameterInJobObject(Object _self, Object _message, Object _parameter, Object _job, Object _object)
{
	DPUSHS ("Processor: MessageConfirmsToParameterInJobObject begined.")
	ASSERT_C ( "Processor:MessageConfirmsToParameterInJobObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:MessageConfirmsToParameterInJobObject --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "Processor:MessageConfirmsToParameterInJobObject --- Checking for correct parameter type failed at parameter _parameter.", _parameter->gid ==  2108332898258556672ull || _parameter == _nil )
	ASSERT_C ( "Processor:MessageConfirmsToParameterInJobObject --- Checking for correct parameter type failed at parameter _job.", _job->gid ==  2108332898258556672ull || _job == _nil )
	ASSERT_C ( "Processor:MessageConfirmsToParameterInJobObject --- Checking for correct parameter type failed at parameter _object.", _object->gid ==  2108332898258556672ull || _object == _nil )
	Object _checkingMethod;
	_checkingMethod = ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Совпадение", 20)) == _equal)) != _false)
	{
		Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Ключ", 8))), ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Значение", 16))) == _equal);
		DPOPS ("Processor: MessageConfirmsToParameterInJobObject ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Совпадение с полем", 34)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = Processor_FieldNameToSynonimInJobObject(_self, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Значение", 16)), _job, _object);
		if((Object_Is(_synonim, _nil)) != _false)
		{
			Object toReturn = _false;
			DPOPS ("Processor: MessageConfirmsToParameterInJobObject ended.")
			return toReturn;
		}
		Object toReturn = LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Ключ", 8))), Synonim_GetUID(_synonim)) == _equal);
		DPOPS ("Processor: MessageConfirmsToParameterInJobObject ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Наличие", 14)) == _equal)) != _false)
	{
		Object toReturn = ListMap_Contains(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Ключ", 8)));
		DPOPS ("Processor: MessageConfirmsToParameterInJobObject ended.")
		return toReturn;
	}
	Object toReturn = _false;
	DPOPS ("Processor: MessageConfirmsToParameterInJobObject ended.")
	return toReturn;
}

Object Processor_TryLinkMessageWithMessageSlotInJobObject(Object _self, Object _message, Object _messageSlot, Object _job, Object _object, Object _messageSlotName, Object _jobName)
{
	DPUSHS ("Processor: TryLinkMessageWithMessageSlotInJobObject begined.")
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _messageSlot.", _messageSlot->gid ==  2108332898258556672ull || _messageSlot == _nil )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _job.", _job->gid ==  2108332898258556672ull || _job == _nil )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _object.", _object->gid ==  2108332898258556672ull || _object == _nil )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _messageSlotName.", _messageSlotName->gid ==  3732711262168886272ull || _messageSlotName == _nil )
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotInJobObject --- Checking for correct parameter type failed at parameter _jobName.", _jobName->gid ==  3732711262168886272ull || _jobName == _nil )
	Object _confirms;
	_confirms = _true;
	Object _parametersIterator;
	_parametersIterator = List_First(ListMap_ListAt(_messageSlot, StringFactory_FromUTF8(_stringFactory, "Метод идентификации", 37)));
	while((Logic_Not(ListIterator_ThisEnd(_parametersIterator))) != _false)
	{
		Object _parameter;
		_parameter = ListIterator_ListMapData(_parametersIterator);
		if((Logic_Not(Processor_MessageConfirmsToParameterInJobObject(_self, _message, _parameter, _job, _object))) != _false)
		{
			_confirms = _false;
			break;
		}
		ListIterator_Next(_parametersIterator);
	}
	if((_confirms) != _false)
	{
		ListMap_MessageSlotSetMessage(_messageSlot, _message);
		ListMap_MessageSetJobNameAndMessageSlotName(_message, _jobName, _messageSlotName);
		Object _waitingStageNamesIterator;
		_waitingStageNamesIterator = List_First(ListMap_MessageSlotStages(_messageSlot));
		while((Logic_Not(ListIterator_ThisEnd(_waitingStageNamesIterator))) != _false)
		{
			Object _jobStage;
			_jobStage = ListMap_ListMapAt(ListMap_JobStages(_job), ListIterator_ListData(_waitingStageNamesIterator));
			ListMap_StageDecrementMessagesCounter(_jobStage);
			if((Logic_And(LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_StageMessagesCounter(_jobStage), NumberFactory_FromLong(_numberFactory, 0)) == _equal), ListMap_StageIsWaiting(_jobStage))) != _false)
			{
				ListMap_StageSetReady(_jobStage);
			}
			ListIterator_Next(_waitingStageNamesIterator);
		}
	}
	Object toReturn = _confirms;
	DPOPS ("Processor: TryLinkMessageWithMessageSlotInJobObject ended.")
	return toReturn;
}

Object Processor_ProcessMessageForObject(Object _self, Object _message, Object _object)
{
	DPUSHS ("Processor: ProcessMessageForObject begined.")
	ASSERT_C ( "Processor:ProcessMessageForObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:ProcessMessageForObject --- Checking for correct parameter type failed at parameter _message.", _message->gid ==  2108332898258556672ull || _message == _nil )
	ASSERT_C ( "Processor:ProcessMessageForObject --- Checking for correct parameter type failed at parameter _object.", _object->gid ==  2108332898258556672ull || _object == _nil )
	Object _assigned;
	_assigned = _false;
	Console_WriteLnString(_console, ListMap_MessageRequest(_message));
	Object _jobsIterator;
	_jobsIterator = ListMap_First(ListMap_ObjectJobs(_object));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobsIterator))) != _false)
	{
		Object _job;
		_job = ListMapIterator_ListMapData(_jobsIterator);
		Object _jobName;
		_jobName = ListMapIterator_ThisKey(_jobsIterator);
		Object _messageSlotsIterator;
		_messageSlotsIterator = ListMap_JobMessageSlotsIterator(_job);
		while((Logic_Not(ListMapIterator_ThisEnd(_messageSlotsIterator))) != _false)
		{
			Object _messageSlot;
			_messageSlot = ListMapIterator_ListMapData(_messageSlotsIterator);
			Object _messageSlotName;
			_messageSlotName = ListMapIterator_ThisKey(_messageSlotsIterator);
			if((ListMap_MessageSlotIsOpened(_messageSlot)) != _false)
			{
				Object _assignedRightNow;
				_assignedRightNow = Processor_TryLinkMessageWithMessageSlotInJobObject(_self, _message, _messageSlot, _job, _object, _messageSlotName, _jobName);
				if((_assignedRightNow) != _false)
				{
					Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, "Сообщение прикреплено к ", 45));
					Console_WriteString(_console, _jobName);
					Console_WriteString(_console, StringFactory_FromUTF8(_stringFactory, ":", 1));
					Console_WriteLnString(_console, _messageSlotName);
				}
				_assigned = Logic_Or(_assignedRightNow, _assigned);
			}
			ListMapIterator_Next(_messageSlotsIterator);
		}
		ListMapIterator_Next(_jobsIterator);
	}
	if((Logic_Not(_assigned)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "!!!!!!!! Ошибка! Сообщение не обработано объектом.", 85));
	}
	Object toReturn = _self;
	DPOPS ("Processor: ProcessMessageForObject ended.")
	return toReturn;
}

Object Processor_ProcessOneJobIfAny(Object _self)
{
	DPUSHS ("Processor: ProcessOneJobIfAny begined.")
	ASSERT_C ( "Processor:ProcessOneJobIfAny --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _jobsIterator;
	_jobsIterator = ListMap_First(ListMap_ObjectJobs(Processor_ContextObject(_self)));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobsIterator))) != _false)
	{
		Object _job;
		_job = ListMapIterator_ListMapData(_jobsIterator);
		Object _jobStagesIterator;
		_jobStagesIterator = ListMap_JobStagesIterator(_job);
		while((Logic_Not(ListMapIterator_ThisEnd(_jobStagesIterator))) != _false)
		{
			Object _jobStage;
			_jobStage = ListMapIterator_ListMapData(_jobStagesIterator);
			if((ListMap_StageIsReady(_jobStage)) != _false)
			{
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStageName), ListMapIterator_ThisKey(_jobStagesIterator));
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobName), ListMapIterator_ThisKey(_jobsIterator));
				Object _emptyParameters;
				_emptyParameters = ListMap_Create();
				Processor_InvokeMethodWithParameters(_self, ListMap_StageMethod(_jobStage), _emptyParameters);
				Object_Release(_emptyParameters);
				if((LogicFactory_FromLong(_logicFactory, Object_Compare(Processor_ContextJob(_self), _nil) != _equal)) != _false)
				{
					Object _messageSlotsIterator;
					_messageSlotsIterator = ListMap_StageMessageSlotsIterator(_jobStage);
					while((Logic_Not(ListIterator_ThisEnd(_messageSlotsIterator))) != _false)
					{
						Object _messageSlotName;
						_messageSlotName = ListIterator_ListData(_messageSlotsIterator);
						Object _messageSlot;
						_messageSlot = ListMap_JobMessageSlot(Processor_ContextJob(_self), _messageSlotName);
						if((LogicFactory_FromLong(_logicFactory, Object_Compare(_messageSlot, _nil) != _equal)) != _false)
						{
							if((Logic_Not(List_Empty(ListMap_MessageSlotMessages(_messageSlot)))) != _false)
							{
								ListMap_MessageSlotRemoveMessage(_messageSlot, _nil);
								if((List_Empty(ListMap_MessageSlotMessages(_messageSlot))) != _false)
								{
									Object _slotStagesIterator;
									_slotStagesIterator = ListMap_MessageSlotStagesIterator(_messageSlot);
									while((Logic_Not(ListIterator_ThisEnd(_slotStagesIterator))) != _false)
									{
										Object _slotStage;
										_slotStage = ListMap_JobStage(Processor_ContextJob(_self), ListIterator_ThisData(_slotStagesIterator));
										if((LogicFactory_FromLong(_logicFactory, Object_Compare(_slotStage, _nil) != _equal)) != _false)
										{
											ListMap_StageIncrementMessagesCounter(_slotStage);
											if((ListMap_StageIsReady(_slotStage)) != _false)
											{
												Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Стадия переведена в состояние ожидания", 72));
												ListMap_StageSetWaiting(_slotStage);
											}
											else
											{
												Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Стадия не была готова.", 40));
											}
										}
										else
										{
											Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Стадия, подписанная да это сообщение, удалена.", 84));
										}
										ListIterator_Next(_slotStagesIterator);
									}
								}
								else
								{
									Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение несет более одного сообщения.", 92));
								}
							}
							else
							{
								Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение не несет реальных сообщений.", 90));
							}
						}
						else
						{
							Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ожидаемое сообщение удалено.", 53));
						}
						ListIterator_Next(_messageSlotsIterator);
					}
				}
				else
				{
					Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Контекстная работа удалена.", 51));
				}
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStageName), _nil);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobName), _nil);
				Object toReturn = _self;
				DPOPS ("Processor: ProcessOneJobIfAny ended.")
				return toReturn;
			}
			ListMapIterator_Next(_jobStagesIterator);
		}
		ListMapIterator_Next(_jobsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: ProcessOneJobIfAny ended.")
	return toReturn;
}

Object Processor_ProcessUID(Object _self, Object _uid)
{
	DPUSHS ("Processor: ProcessUID begined.")
	ASSERT_C ( "Processor:ProcessUID --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ASSERT_C ( "Processor:ProcessUID --- Checking for correct parameter type failed at parameter _uid.", _uid->gid ==  3732711262168886272ull || _uid == _nil )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Stack_Clean((((Processor) (_self->entity))->_helperStack));
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextUID), _uid);
	Processor_ProcessOneJobIfAny(_self);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextUID), _nil);
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _self;
	DPOPS ("Processor: ProcessUID ended.")
	return toReturn;
}
