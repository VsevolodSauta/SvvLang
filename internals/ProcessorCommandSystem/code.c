#include "internals/basics.h"
#include "internals/ProcessorCommandSystem/imports.h"


Object ProcessorCommandSystem_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ProcessorCommandSystem: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ProcessorCommandSystem));
	_self->gid =  3307502136344893952ull;
	Object_SetComparator(_self, &ProcessorCommandSystem_Compare);
	Object_SetDestructor(_self, &ProcessorCommandSystem_Destroy);
	Object_SetCloner(_self, &ProcessorCommandSystem_Clone);
	Object_SetDeepCloner(_self, &ProcessorCommandSystem_DeepClone);
	((ProcessorCommandSystem) (_self->entity))->_helperStack = _nil;
	((ProcessorCommandSystem) (_self->entity))->_processorCodes = _nil;
	((ProcessorCommandSystem) (_self->entity))->_processor = _nil;
	_self = ProcessorCommandSystem_Init(_self);
	DPOPS ("ProcessorCommandSystem: Create ended.")
	return _self;
}

Object ProcessorCommandSystem_Clone(Object _self)
{
	DPUSHS ("ProcessorCommandSystem: Clone begined.")
	ASSERT_C ( "ProcessorCommandSystem:Clone --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	Object toReturn = ProcessorCommandSystem_Create();
	DPOPS ("ProcessorCommandSystem: Clone ended.")
	return toReturn;
}

Object ProcessorCommandSystem_DeepClone(Object _self)
{
	DPUSHS ("ProcessorCommandSystem: DeepClone begined.")
	ASSERT_C ( "ProcessorCommandSystem:DeepClone --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	Object toReturn = ProcessorCommandSystem_Create();
	DPOPS ("ProcessorCommandSystem: DeepClone ended.")
	return toReturn;
}

Object ProcessorCommandSystem_Compare(Object _self, Object _processorCommandSystem)
{
	DPUSHS ("ProcessorCommandSystem: Compare begined.")
	ASSERT_C ( "ProcessorCommandSystem:Compare --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:Compare --- Checking for correct parameter type failed at parameter _processorCommandSystem.", _processorCommandSystem->gid ==  3307502136344893952ull || _processorCommandSystem == _nil )
	Object toReturn = Object_Compare(Object_Hash(_self), Object_Hash(_processorCommandSystem));
	DPOPS ("ProcessorCommandSystem: Compare ended.")
	return toReturn;
}

Object ProcessorCommandSystem_Destroy(Object _self)
{
	DPUSHS ("ProcessorCommandSystem: Destroy begined.")
	ASSERT_C ( "ProcessorCommandSystem:Destroy --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	Object_Release((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	Object_Release((((ProcessorCommandSystem) (_self->entity))->_processorCodes));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ProcessorCommandSystem: Destroy ended.")
	return toReturn;
}

Object ProcessorCommandSystem_SetProcessor(Object _self, Object _processor)
{
	DPUSHS ("ProcessorCommandSystem: SetProcessor begined.")
	ASSERT_C ( "ProcessorCommandSystem:SetProcessor --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:SetProcessor --- Checking for correct parameter type failed at parameter _processor.", _processor->gid ==  8708543990322460672ull || _processor == _nil )
	(((ProcessorCommandSystem) (_self->entity))->_processor) = _processor;
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: SetProcessor ended.")
	return toReturn;
}

Object ProcessorCommandSystem_ContextSwitched(Object _self)
{
	DPUSHS ("ProcessorCommandSystem: ContextSwitched begined.")
	ASSERT_C ( "ProcessorCommandSystem:ContextSwitched --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	Stack_Clean((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: ContextSwitched ended.")
	return toReturn;
}

Object ProcessorCommandSystem_Init(Object _self)
{
	DPUSHS ("ProcessorCommandSystem: Init begined.")
	ASSERT_C ( "ProcessorCommandSystem:Init --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	(((ProcessorCommandSystem) (_self->entity))->_helperStack) = Stack_Create();
	(((ProcessorCommandSystem) (_self->entity))->_processorCodes) = ListMap_Create();
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Выполнить", 18), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDo));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Сущность поля сообщения", 44), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeEntityFromMessageField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Идентификатор поля", 35), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUIDFromField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущий объект", 27), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddCurrentUIDToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая работа", 27), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddCurrentJobToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая стадия", 27), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddCurrentJobStageToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Список", 12), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddListToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Отображение", 22), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddListMapToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveFromStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в отображение", 59), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddEntityToListMap));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по ключу", 75), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveEntityFromListMapByKey));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по значению", 81), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveEntityFromListMapByValue));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в список", 49), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddEntityToList));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка на позиции", 69), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveEntityFromListByPosition));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка по значению", 71), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveEntityFromListByValue));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в вершину", 51), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddEntityToStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Дублировать вершину", 37), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDuplicateTopInStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Поменять местами вершинные элементы", 67), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSwapTopInStack));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту с идентификатором", 82), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSendMessageToUID));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту из поля", 62), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSendMessageToField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту из поля сообщения", 81), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSendMessageToMessageField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать ответ на сообщение", 49), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSendReplyForMessage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Вызвать метод с параметрами", 51), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeInvokeMethod));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Определить метод объекта", 46), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineActorMethod));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Определить метод работы", 44), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineJobMethod));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить метод с именем", 41), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUnDefineMethod));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить ТВА", 27), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineLocalField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле работы", 42), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineJobField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле объекта", 44), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineActorField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить глобальное поле", 50), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeDefineGlobalField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Присвоить полю идентификатор", 54), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeSetField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Перемежить поле прибытия с полем отправления", 83), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUniteField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить поле", 23), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUnDefineField));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить работу", 29), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddJob));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить стадию", 29), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddJobStage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Заблокировать стадию", 39), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeBlockStage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Разблокировать стадию", 41), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUnBlockStage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Заблокировать ожидаемое сообщение", 64), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeBlockMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Разблокировать ожидаемое сообщение", 66), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeUnBlockMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить стадию", 27), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveJobStage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии", 29), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllStages));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить ожидаемые сообщения", 54), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllMessageSlots));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии и ожидаемые сообщения", 70), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllStagesAndMessageSlots));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить ожидаемое сообщение", 54), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAddMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить ожидаемое сообщение", 52), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить стадии ожидаемое сообщение", 71), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeAttachToStageMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения текущей стадии для текущей стадии", 96), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForCurrentStage));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения текущей стадии", 61), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForAllStages));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сообщения всех разблокированных стадий", 88), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllMessagesOfAllOpenedStages));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученное сообщение", 54), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveMessageInMessageSlot));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученные сообщения", 54), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeRemoveAllReceivedMessages));
	ListMap_Add((((ProcessorCommandSystem) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Завершить текущую работу", 46), MethodFactory_FromPointer(_methodFactory, &ProcessorCommandSystem_CodeFinishThisJob));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: Init ended.")
	return toReturn;
}

Object ProcessorCommandSystem_Do(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: Do begined.")
	ASSERT_C ( "ProcessorCommandSystem:Do --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:Do --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _method;
	_method = ListMap_MethodAt((((ProcessorCommandSystem) (_self->entity))->_processorCodes), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: Действие не задано либо отсутствует в системе комманд.", 131));
	}
	else
	{
		Method_Invoke(_method, _self, _toDo);
	}
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: Do ended.")
	return toReturn;
}

Object ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(Object _self, Object _entityName, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: GetNamedEntityFromToDoOrStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:GetNamedEntityFromToDoOrStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:GetNamedEntityFromToDoOrStack --- Checking for correct parameter type failed at parameter _entityName.", _entityName->gid ==  3732711262168886272ull || _entityName == _nil )
	ASSERT_C ( "ProcessorCommandSystem:GetNamedEntityFromToDoOrStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _object;
	_object = Object_TempClone(ListMap_ObjectAt(_toDo, _entityName));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_object, _nil) == _equal)) != _false)
	{
		_object = Stack_Pop((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	}
	Object toReturn = _object;
	DPOPS ("ProcessorCommandSystem: GetNamedEntityFromToDoOrStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDo(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDo begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDo --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDo --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _action;
	_action = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Действие", 16), _toDo);
	ProcessorCommandSystem_Do(_self, _action);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeDo ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeEntityFromMessageField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeEntityFromMessageField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeEntityFromMessageField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeEntityFromMessageField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Processor_EntityFromNamedMessageField((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName, _messageSlotName));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeEntityFromMessageField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUIDFromField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUIDFromField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUIDFromField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUIDFromField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Processor_FieldNameToUID((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUIDFromField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddCurrentUIDToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddCurrentUIDToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentUIDToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentUIDToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Processor_ContextActorUID((((ProcessorCommandSystem) (_self->entity))->_processor)));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddCurrentUIDToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddCurrentJobToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddCurrentJobToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentJobToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentJobToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Processor_ContextJobName((((ProcessorCommandSystem) (_self->entity))->_processor)));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddCurrentJobToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddCurrentJobStageToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddCurrentJobStageToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentJobStageToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddCurrentJobStageToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Processor_ContextJobStageName((((ProcessorCommandSystem) (_self->entity))->_processor)));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddCurrentJobStageToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddListToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddListToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddListToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddListToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _list;
	_list = List_Create();
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), _list);
	Object_Release(_list);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddListToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddListMapToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddListMapToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddListMapToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddListMapToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _listMap;
	_listMap = ListMap_Create();
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), _listMap);
	Object_Release(_listMap);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddListMapToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveFromStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveFromStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveFromStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveFromStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Remove((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveFromStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddEntityToListMap(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddEntityToListMap begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToListMap --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToListMap --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _key;
	_key = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Add(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _key, _value);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddEntityToListMap ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveEntityFromListMapByKey(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveEntityFromListMapByKey begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListMapByKey --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListMapByKey --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _key;
	_key = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Remove(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _key);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveEntityFromListMapByKey ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveEntityFromListMapByValue(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveEntityFromListMapByValue begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListMapByValue --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListMapByValue --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _iterator;
	_iterator = ListMap_First(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMapIterator_ThisValue(_iterator), _value) == _equal)) != _false)
		{
			ListMapIterator_ThisRemoveRight(_iterator);
			break;
		}
	}
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveEntityFromListMapByValue ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddEntityToList(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddEntityToList begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToList --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToList --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _position;
	_position = ListMap_NumberAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Позиция", 14));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _nil) == _equal)) != _false)
	{
		List_PushBack(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _value);
	}
	else
	{
		List_AddBeforePosition(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _position, _value);
	}
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddEntityToList ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveEntityFromListByPosition(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveEntityFromListByPosition begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListByPosition --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListByPosition --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _position;
	_position = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Позиция", 14), _toDo);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _nil) != _equal)) != _false)
	{
		List_RemoveObjectAtPosition(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _position);
	}
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveEntityFromListByPosition ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveEntityFromListByValue(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveEntityFromListByValue begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListByValue --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveEntityFromListByValue --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _value;
	_value = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	List_RemoveFirst(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack)), _value);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveEntityFromListByValue ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddEntityToStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddEntityToStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddEntityToStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Object_TempClone(ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16))));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddEntityToStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDuplicateTopInStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDuplicateTopInStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDuplicateTopInStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDuplicateTopInStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), Object_TempClone(Stack_Peek((((ProcessorCommandSystem) (_self->entity))->_helperStack))));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeDuplicateTopInStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSwapTopInStack(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSwapTopInStack begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSwapTopInStack --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSwapTopInStack --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _a;
	_a = Stack_Pop((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	Object _b;
	_b = Stack_Pop((((ProcessorCommandSystem) (_self->entity))->_helperStack));
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), _a);
	Stack_Push((((ProcessorCommandSystem) (_self->entity))->_helperStack), _b);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSwapTopInStack ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSendMessageToUID(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSendMessageToUID begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToUID --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToUID --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _receiver;
	_receiver = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Получатель", 20), _toDo);
	Object _message;
	_message = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage((((ProcessorCommandSystem) (_self->entity))->_processor), _message);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSendMessageToUID ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSendMessageToField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSendMessageToField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _message;
	_message = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _receiver;
	_receiver = Processor_FieldNameToUID((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName);
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage((((ProcessorCommandSystem) (_self->entity))->_processor), _message);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSendMessageToField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSendMessageToMessageField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSendMessageToMessageField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToMessageField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSendMessageToMessageField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _message;
	_message = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_SendMessageToMessageField((((ProcessorCommandSystem) (_self->entity))->_processor), _message, _messageSlotName, _fieldName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSendMessageToMessageField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSendReplyForMessage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSendReplyForMessage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSendReplyForMessage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSendReplyForMessage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _reply;
	_reply = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _toDo);
	Object _messageName;
	_messageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_SendReplyForMessage((((ProcessorCommandSystem) (_self->entity))->_processor), _reply, _messageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSendReplyForMessage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeInvokeMethod(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeInvokeMethod begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeInvokeMethod --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeInvokeMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _methodName;
	_methodName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _parameters;
	_parameters = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Параметры", 18), _toDo);
	Processor_InvokeMethodWithParameters((((ProcessorCommandSystem) (_self->entity))->_processor), _methodName, _parameters);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeInvokeMethod ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineActorMethod(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineActorMethod begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineActorMethod --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineActorMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _methodName;
	_methodName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _method;
	_method = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _toDo);
	Processor_DefineActorMethod((((ProcessorCommandSystem) (_self->entity))->_processor), _method, _methodName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeDefineActorMethod ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineJobMethod(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineJobMethod begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineJobMethod --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineJobMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _methodName;
	_methodName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _method;
	_method = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _toDo);
	Processor_DefineJobMethod((((ProcessorCommandSystem) (_self->entity))->_processor), _method, _methodName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeDefineJobMethod ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUnDefineMethod(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUnDefineMethod begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUnDefineMethod --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUnDefineMethod --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_UnDefineMethod((((ProcessorCommandSystem) (_self->entity))->_processor), ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUnDefineMethod ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineLocalField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineLocalField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineLocalField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineLocalField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = ProcessorCommandSystem_DefineFieldHelper(_self, _toDo, Stack_Peek((((Processor) ((((ProcessorCommandSystem) (_self->entity))->_processor)->entity))->_localNamespaces)));
	DPOPS ("ProcessorCommandSystem: CodeDefineLocalField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineJobField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineJobField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineJobField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineJobField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = ProcessorCommandSystem_DefineFieldHelper(_self, _toDo, ListMap_ActorFields(Processor_ContextJob((((ProcessorCommandSystem) (_self->entity))->_processor))));
	DPOPS ("ProcessorCommandSystem: CodeDefineJobField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineActorField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineActorField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineActorField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineActorField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = ProcessorCommandSystem_DefineFieldHelper(_self, _toDo, ListMap_ActorFields(Processor_ContextActor((((ProcessorCommandSystem) (_self->entity))->_processor))));
	DPOPS ("ProcessorCommandSystem: CodeDefineActorField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeDefineGlobalField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeDefineGlobalField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineGlobalField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeDefineGlobalField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object toReturn = ProcessorCommandSystem_DefineFieldHelper(_self, _toDo, (((Machine) ((((Processor) ((((ProcessorCommandSystem) (_self->entity))->_processor)->entity))->_machine)->entity))->_globalContext));
	DPOPS ("ProcessorCommandSystem: CodeDefineGlobalField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace)
{
	DPUSHS ("ProcessorCommandSystem: DefineFieldHelper begined.")
	ASSERT_C ( "ProcessorCommandSystem:DefineFieldHelper --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:DefineFieldHelper --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	ASSERT_C ( "ProcessorCommandSystem:DefineFieldHelper --- Checking for correct parameter type failed at parameter _nameSpace.", _nameSpace->gid ==  2108332898258556672ull || _nameSpace == _nil )
	Object _uid;
	_uid = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Processor_DefineFieldInNameSpaceWithUID((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName, _nameSpace, _uid);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: DefineFieldHelper ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeSetField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeSetField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeSetField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeSetField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _uid;
	_uid = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Processor_SetField((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName, _uid);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeSetField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUniteField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUniteField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUniteField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUniteField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _destinationFieldName;
	_destinationFieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля прибытия", 32), _toDo);
	Object _sourceFieldName;
	_sourceFieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля отправления", 38), _toDo);
	Processor_UniteField((((ProcessorCommandSystem) (_self->entity))->_processor), _destinationFieldName, _sourceFieldName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUniteField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUnDefineField(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUnDefineField begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUnDefineField --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUnDefineField --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _fieldName;
	_fieldName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _locationType;
	_locationType = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33));
	Processor_UnDefineFieldInNamespace((((ProcessorCommandSystem) (_self->entity))->_processor), _fieldName, _locationType);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUnDefineField ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddJob(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddJob begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddJob --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddJob --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobName;
	_jobName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя работы", 19), _toDo);
	Object _job;
	_job = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Работа", 12), _toDo);
	Processor_AddJobWithName((((ProcessorCommandSystem) (_self->entity))->_processor), _job, _jobName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddJob ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeFinishThisJob(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeFinishThisJob begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeFinishThisJob --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeFinishThisJob --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_FinishThisJob((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeFinishThisJob ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddJobStage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddJobStage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddJobStage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddJobStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobStageName;
	_jobStageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _jobStage;
	_jobStage = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Стадия", 12), _toDo);
	Processor_AddJobStage((((ProcessorCommandSystem) (_self->entity))->_processor), _jobStage, _jobStageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddJobStage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAddMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAddMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAddMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAddMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _messageSlot;
	_messageSlot = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Processor_AddMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _messageSlot, _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAddMessageSlot ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeBlockStage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeBlockStage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeBlockStage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeBlockStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_BlockStage((((ProcessorCommandSystem) (_self->entity))->_processor), _stageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeBlockStage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUnBlockStage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUnBlockStage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUnBlockStage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUnBlockStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_UnBlockStage((((ProcessorCommandSystem) (_self->entity))->_processor), _stageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUnBlockStage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeBlockMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeBlockMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeBlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeBlockMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_BlockMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeBlockMessageSlot ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeUnBlockMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeUnBlockMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeUnBlockMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeUnBlockMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_UnBlockMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeUnBlockMessageSlot ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveJobStage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveJobStage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveJobStage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveJobStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _jobStageName;
	_jobStageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Processor_RemoveJobStage((((ProcessorCommandSystem) (_self->entity))->_processor), _jobStageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveJobStage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_RemoveMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveMessageSlot ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveMessageInMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveMessageInMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveMessageInMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveMessageInMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _messageSlotName;
	_messageSlotName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_RemoveMessageInMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveMessageInMessageSlot ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForCurrentStage(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfCurrentStageForCurrentStage begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfCurrentStageForCurrentStage --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfCurrentStageForCurrentStage --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfCurrentStageForCurrentStage((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfCurrentStageForCurrentStage ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllMessagesOfCurrentStageForAllStages(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfCurrentStageForAllStages begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfCurrentStageForAllStages --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfCurrentStageForAllStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfCurrentStageForAllStages((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfCurrentStageForAllStages ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllMessagesOfAllOpenedStages(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfAllOpenedStages begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfAllOpenedStages --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessagesOfAllOpenedStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessagesOfAllOpenedStages((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllMessagesOfAllOpenedStages ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllReceivedMessages(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllReceivedMessages begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllReceivedMessages --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllReceivedMessages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllReceivedMessages((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllReceivedMessages ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllStages(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllStages begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllStages --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllStages --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllStages((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllStages ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllMessageSlots(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllMessageSlots begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessageSlots --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllMessageSlots --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllMessageSlots((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllMessageSlots ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeRemoveAllStagesAndMessageSlots(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeRemoveAllStagesAndMessageSlots begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllStagesAndMessageSlots --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeRemoveAllStagesAndMessageSlots --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Processor_RemoveAllStagesAndMessageSlots((((ProcessorCommandSystem) (_self->entity))->_processor));
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeRemoveAllStagesAndMessageSlots ended.")
	return toReturn;
}

Object ProcessorCommandSystem_CodeAttachToStageMessageSlot(Object _self, Object _toDo)
{
	DPUSHS ("ProcessorCommandSystem: CodeAttachToStageMessageSlot begined.")
	ASSERT_C ( "ProcessorCommandSystem:CodeAttachToStageMessageSlot --- Checking for correct object type failed.", _self->gid ==  3307502136344893952ull )
	ASSERT_C ( "ProcessorCommandSystem:CodeAttachToStageMessageSlot --- Checking for correct parameter type failed at parameter _toDo.", _toDo->gid ==  2108332898258556672ull || _toDo == _nil )
	Object _stageName;
	_stageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _messageName;
	_messageName = ProcessorCommandSystem_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_AttachToStageMessageSlot((((ProcessorCommandSystem) (_self->entity))->_processor), _stageName, _messageName);
	Object toReturn = _self;
	DPOPS ("ProcessorCommandSystem: CodeAttachToStageMessageSlot ended.")
	return toReturn;
}
