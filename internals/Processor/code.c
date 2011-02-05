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
	Object toReturn = _equal;
	DPOPS ("Processor: Compare ended.")
	return toReturn;
}

Object Processor_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("Processor: SetMachine begined.")
	ASSERT_C ( "Processor:SetMachine --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Выполнить", 18), MethodFactory_FromPointer(_methodFactory, &Processor_DoCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Сущность поля сообщения", 44), MethodFactory_FromPointer(_methodFactory, &Processor_EntityFromMessageFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Идентификатор поля", 35), MethodFactory_FromPointer(_methodFactory, &Processor_UIDFromFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущий объект", 27), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentUIDToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая работа", 27), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentJobToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Текущая стадия", 27), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentJobStageToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Список", 12), MethodFactory_FromPointer(_methodFactory, &Processor_AddListToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Отображение", 22), MethodFactory_FromPointer(_methodFactory, &Processor_AddListMapToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveFromStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в отображение", 59), MethodFactory_FromPointer(_methodFactory, &Processor_AddEntityToListMapCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по ключу", 75), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveEntityFromListMapByKeyCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из отображения по значению", 81), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveEntityFromListMapByValueCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в список", 49), MethodFactory_FromPointer(_methodFactory, &Processor_AddEntityToListCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка на позиции", 69), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveEntityFromListByPositionCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить сущность из списка по значению", 71), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveEntityFromListByValueCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить сущность в вершину", 51), MethodFactory_FromPointer(_methodFactory, &Processor_AddEntityToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Дублировать вершину", 37), MethodFactory_FromPointer(_methodFactory, &Processor_DuplicateTopInStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Поменять местами вершинные элементы", 67), MethodFactory_FromPointer(_methodFactory, &Processor_SwapTopInStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту с идентификатором", 82), MethodFactory_FromPointer(_methodFactory, &Processor_SendMessageToUIDCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение объекту из поля", 62), MethodFactory_FromPointer(_methodFactory, &Processor_SendMessageToFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать ответ на сообщение", 49), MethodFactory_FromPointer(_methodFactory, &Processor_SendReplyForMessageCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Вызвать метод с параметрами", 51), MethodFactory_FromPointer(_methodFactory, &Processor_InvokeMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Определить метод", 31), MethodFactory_FromPointer(_methodFactory, &Processor_DefineMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить метод с именем", 41), MethodFactory_FromPointer(_methodFactory, &Processor_UnDefineMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить ТВА", 27), MethodFactory_FromPointer(_methodFactory, &Processor_DefineLocalFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле работы", 42), MethodFactory_FromPointer(_methodFactory, &Processor_DefineJobFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить поле объекта", 44), MethodFactory_FromPointer(_methodFactory, &Processor_DefineObjectFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить глобальное поле", 50), MethodFactory_FromPointer(_methodFactory, &Processor_DefineGlobalFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Присвоить полю идентификатор", 54), MethodFactory_FromPointer(_methodFactory, &Processor_SetFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Перемежить поле прибытия с полем отправления", 83), MethodFactory_FromPointer(_methodFactory, &Processor_UniteFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить поле", 23), MethodFactory_FromPointer(_methodFactory, &Processor_UnDefineFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить работу", 29), MethodFactory_FromPointer(_methodFactory, &Processor_AddJobCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить стадию", 29), MethodFactory_FromPointer(_methodFactory, &Processor_AddJobStageCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить стадию", 27), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveJobStageCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии", 29), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveAllJobStagesCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить ожидаемые сообщения", 54), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveAllMessageSlotsCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии и ожидаемые сообщения", 70), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveAllJobStagesAndMessageSlotsCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить ожидаемое сообщение", 54), MethodFactory_FromPointer(_methodFactory, &Processor_AddMessageSlotCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить ожидаемое сообщение", 52), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveMessageSlotCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Установить стадии ожидаемое сообщение", 71), MethodFactory_FromPointer(_methodFactory, &Processor_AttachToStageMessageSlotCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученное сообщение", 54), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveMessageInSlotCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить полученные сообщения", 54), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveAllReceivedMessagesCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Завершить текущую работу", 46), MethodFactory_FromPointer(_methodFactory, &Processor_FinishThisJobCode));
	Object toReturn = _self;
	DPOPS ("Processor: Init ended.")
	return toReturn;
}

Object Processor_Do(Object _self, Object _toDo)
{
	DPUSHS ("Processor: Do begined.")
	ASSERT_C ( "Processor:Do --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Console_WriteLnString(_console, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	Object _method;
	_method = ListMap_MethodAt((((Processor) (_self->entity))->_processorCodes), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: Действие не задано либо отсутствует в системе комманд.", 131));
	}
	Method_Invoke(_method, _self, _toDo);
	Object toReturn = _self;
	DPOPS ("Processor: Do ended.")
	return toReturn;
}

Object Processor_GetNamedEntityFromToDoOrStack(Object _self, Object _entityName, Object _toDo)
{
	DPUSHS ("Processor: GetNamedEntityFromToDoOrStack begined.")
	ASSERT_C ( "Processor:GetNamedEntityFromToDoOrStack --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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

Object Processor_DoCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DoCode begined.")
	ASSERT_C ( "Processor:DoCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _action;
	_action = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Действие", 16), _toDo);
	Processor_Do(_self, _action);
	Object toReturn = _self;
	DPOPS ("Processor: DoCode ended.")
	return toReturn;
}

Object Processor_EntityFromMessageFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: EntityFromMessageFieldCode begined.")
	ASSERT_C ( "Processor:EntityFromMessageFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((Processor) (_self->entity))->_helperStack), ListMap_JobFieldInMessageSlot(Processor_ContextJob(_self), _fieldName, _messageSlotName));
	Object toReturn = _self;
	DPOPS ("Processor: EntityFromMessageFieldCode ended.")
	return toReturn;
}

Object Processor_UIDFromFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UIDFromFieldCode begined.")
	ASSERT_C ( "Processor:UIDFromFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Stack_Push((((Processor) (_self->entity))->_helperStack), Processor_FieldNameToUID(_self, _fieldName));
	Object toReturn = _self;
	DPOPS ("Processor: UIDFromFieldCode ended.")
	return toReturn;
}

Object Processor_AddCurrentUIDToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentUIDToStackCode begined.")
	ASSERT_C ( "Processor:AddCurrentUIDToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextUID));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentUIDToStackCode ended.")
	return toReturn;
}

Object Processor_AddCurrentJobToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentJobToStackCode begined.")
	ASSERT_C ( "Processor:AddCurrentJobToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentJobToStackCode ended.")
	return toReturn;
}

Object Processor_AddCurrentJobStageToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentJobStageToStackCode begined.")
	ASSERT_C ( "Processor:AddCurrentJobStageToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobStageName));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentJobStageToStackCode ended.")
	return toReturn;
}

Object Processor_AddListToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddListToStackCode begined.")
	ASSERT_C ( "Processor:AddListToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _list;
	_list = List_Create();
	Stack_Push((((Processor) (_self->entity))->_helperStack), _list);
	Object_Release(_list);
	Object toReturn = _self;
	DPOPS ("Processor: AddListToStackCode ended.")
	return toReturn;
}

Object Processor_AddListMapToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddListMapToStackCode begined.")
	ASSERT_C ( "Processor:AddListMapToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _listMap;
	_listMap = ListMap_Create();
	Stack_Push((((Processor) (_self->entity))->_helperStack), _listMap);
	Object_Release(_listMap);
	Object toReturn = _self;
	DPOPS ("Processor: AddListMapToStackCode ended.")
	return toReturn;
}

Object Processor_RemoveFromStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveFromStackCode begined.")
	ASSERT_C ( "Processor:RemoveFromStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Remove((((Processor) (_self->entity))->_helperStack));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveFromStackCode ended.")
	return toReturn;
}

Object Processor_AddEntityToListMapCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddEntityToListMapCode begined.")
	ASSERT_C ( "Processor:AddEntityToListMapCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	Object _key;
	_key = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Add(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key, _value);
	Object toReturn = _self;
	DPOPS ("Processor: AddEntityToListMapCode ended.")
	return toReturn;
}

Object Processor_RemoveEntityFromListMapByKeyCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveEntityFromListMapByKeyCode begined.")
	ASSERT_C ( "Processor:RemoveEntityFromListMapByKeyCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _key;
	_key = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _toDo);
	ListMap_Remove(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveEntityFromListMapByKeyCode ended.")
	return toReturn;
}

Object Processor_RemoveEntityFromListMapByValueCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveEntityFromListMapByValueCode begined.")
	ASSERT_C ( "Processor:RemoveEntityFromListMapByValueCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	DPOPS ("Processor: RemoveEntityFromListMapByValueCode ended.")
	return toReturn;
}

Object Processor_AddEntityToListCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddEntityToListCode begined.")
	ASSERT_C ( "Processor:AddEntityToListCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	DPOPS ("Processor: AddEntityToListCode ended.")
	return toReturn;
}

Object Processor_RemoveEntityFromListByPositionCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveEntityFromListByPositionCode begined.")
	ASSERT_C ( "Processor:RemoveEntityFromListByPositionCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _position;
	_position = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Позиция", 14), _toDo);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_position, _nil) != _equal)) != _false)
	{
		List_RemoveObjectAtPosition(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _position);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveEntityFromListByPositionCode ended.")
	return toReturn;
}

Object Processor_RemoveEntityFromListByValueCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveEntityFromListByValueCode begined.")
	ASSERT_C ( "Processor:RemoveEntityFromListByValueCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _value;
	_value = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Значение", 16), _toDo);
	List_RemoveFirst(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _value);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveEntityFromListByValueCode ended.")
	return toReturn;
}

Object Processor_AddEntityToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddEntityToStackCode begined.")
	ASSERT_C ( "Processor:AddEntityToStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Push((((Processor) (_self->entity))->_helperStack), Object_TempClone(ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16))));
	Object toReturn = _self;
	DPOPS ("Processor: AddEntityToStackCode ended.")
	return toReturn;
}

Object Processor_DuplicateTopInStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DuplicateTopInStackCode begined.")
	ASSERT_C ( "Processor:DuplicateTopInStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Stack_Push((((Processor) (_self->entity))->_helperStack), Object_TempClone(Stack_Peek((((Processor) (_self->entity))->_helperStack))));
	Object toReturn = _self;
	DPOPS ("Processor: DuplicateTopInStackCode ended.")
	return toReturn;
}

Object Processor_SwapTopInStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SwapTopInStackCode begined.")
	ASSERT_C ( "Processor:SwapTopInStackCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _a;
	_a = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	Object _b;
	_b = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	Stack_Push((((Processor) (_self->entity))->_helperStack), _a);
	Stack_Push((((Processor) (_self->entity))->_helperStack), _b);
	Object toReturn = _self;
	DPOPS ("Processor: SwapTopInStackCode ended.")
	return toReturn;
}

Object Processor_SendMessageToUIDCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SendMessageToUIDCode begined.")
	ASSERT_C ( "Processor:SendMessageToUIDCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _message;
	_message = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	Object _receiver;
	_receiver = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Получатель", 20), _toDo);
	ListMap_MessageSetSender(_message, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_message, _receiver);
	Processor_SendMessage(_self, _message);
	Object toReturn = _self;
	DPOPS ("Processor: SendMessageToUIDCode ended.")
	return toReturn;
}

Object Processor_SendMessageToFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SendMessageToFieldCode begined.")
	ASSERT_C ( "Processor:SendMessageToFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	DPOPS ("Processor: SendMessageToFieldCode ended.")
	return toReturn;
}

Object Processor_SendReplyForMessageCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SendReplyForMessageCode begined.")
	ASSERT_C ( "Processor:SendReplyForMessageCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _reply;
	_reply = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), _toDo);
	Object _messageName;
	_messageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _message;
	_message = ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageName);
	Object _receiver;
	_receiver = ListMap_MessageSender(_message);
	Object _reqest;
	_reqest = ListMap_MessageRequest(_message);
	_reply = Object_TempDeepClone(_reply);
	ListMap_MessageSetSender(_reply, (((Processor) (_self->entity))->_contextUID));
	ListMap_MessageSetReceiver(_reply, _receiver);
	ListMap_MessageSetRequest(_reply, _reqest);
	ListMap_MessageSetType(_reply, StringFactory_FromUTF8(_stringFactory, "Ответ", 10));
	Processor_SendMessage(_self, _reply);
	Object toReturn = _self;
	DPOPS ("Processor: SendReplyForMessageCode ended.")
	return toReturn;
}

Object Processor_InvokeMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: InvokeMethodCode begined.")
	ASSERT_C ( "Processor:InvokeMethodCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _methodName;
	_methodName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _parameters;
	_parameters = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Параметры", 18), _toDo);
	Processor_InvokeMethodWithParameters(_self, _methodName, _parameters);
	Object toReturn = _self;
	DPOPS ("Processor: InvokeMethodCode ended.")
	return toReturn;
}

Object Processor_DefineMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineMethodCode begined.")
	ASSERT_C ( "Processor:DefineMethodCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _methodName;
	_methodName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	Object _method;
	_method = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Метод", 10), _toDo);
	ListMap_ObjectSetMethod(Processor_ContextObject(_self), _method, _methodName);
	Object toReturn = _self;
	DPOPS ("Processor: DefineMethodCode ended.")
	return toReturn;
}

Object Processor_UnDefineMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UnDefineMethodCode begined.")
	ASSERT_C ( "Processor:UnDefineMethodCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _methodName;
	_methodName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19), _toDo);
	ListMap_ObjectRemoveMethod(Processor_ContextObject(_self), _methodName);
	Object toReturn = _self;
	DPOPS ("Processor: UnDefineMethodCode ended.")
	return toReturn;
}

Object Processor_DefineLocalFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineLocalFieldCode begined.")
	ASSERT_C ( "Processor:DefineLocalFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, Stack_Peek((((Processor) (_self->entity))->_localNamespaces)));
	DPOPS ("Processor: DefineLocalFieldCode ended.")
	return toReturn;
}

Object Processor_DefineJobFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineJobFieldCode begined.")
	ASSERT_C ( "Processor:DefineJobFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ObjectFields(Processor_ContextJob(_self)));
	DPOPS ("Processor: DefineJobFieldCode ended.")
	return toReturn;
}

Object Processor_DefineObjectFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineObjectFieldCode begined.")
	ASSERT_C ( "Processor:DefineObjectFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ObjectFields(Processor_ContextObject(_self)));
	DPOPS ("Processor: DefineObjectFieldCode ended.")
	return toReturn;
}

Object Processor_DefineGlobalFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineGlobalFieldCode begined.")
	ASSERT_C ( "Processor:DefineGlobalFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext));
	DPOPS ("Processor: DefineGlobalFieldCode ended.")
	return toReturn;
}

Object Processor_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace)
{
	DPUSHS ("Processor: DefineFieldHelper begined.")
	ASSERT_C ( "Processor:DefineFieldHelper --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _uid;
	_uid = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _synonim;
	_synonim = Synonim_Create();
	Synonim_SetUID(_synonim, _uid);
	Object _reference;
	_reference = ListMap_Create();
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), _nameSpace);
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _fieldName);
	Synonim_AddReference(_synonim, _reference);
	Object_Release(_reference);
	Object_Release(_synonim);
	Object toReturn = _self;
	DPOPS ("Processor: DefineFieldHelper ended.")
	return toReturn;
}

Object Processor_SetFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SetFieldCode begined.")
	ASSERT_C ( "Processor:SetFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _uid;
	_uid = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26), _toDo);
	Synonim_SetUID(Processor_FieldNameToSynonim(_self, _fieldName), _uid);
	Object toReturn = _self;
	DPOPS ("Processor: SetFieldCode ended.")
	return toReturn;
}

Object Processor_UniteFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UniteFieldCode begined.")
	ASSERT_C ( "Processor:UniteFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _destinationFieldName;
	_destinationFieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля прибытия", 32), _toDo);
	Object _sourceFieldName;
	_sourceFieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля отправления", 38), _toDo);
	Synonim_Unite(Processor_FieldNameToSynonim(_self, _destinationFieldName), Processor_FieldNameToSynonim(_self, _sourceFieldName));
	Object toReturn = _self;
	DPOPS ("Processor: UniteFieldCode ended.")
	return toReturn;
}

Object Processor_UnDefineFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UnDefineFieldCode begined.")
	ASSERT_C ( "Processor:UnDefineFieldCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _fieldName;
	_fieldName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), _toDo);
	Object _locationType;
	_locationType = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33));
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
	DPOPS ("Processor: UnDefineFieldCode ended.")
	return toReturn;
}

Object Processor_AddJobCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddJobCode begined.")
	ASSERT_C ( "Processor:AddJobCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _jobName;
	_jobName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя работы", 19), _toDo);
	Object _job;
	_job = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Работа", 12), _toDo);
	ListMap_ObjectSetJob(Processor_ContextObject(_self), _job, _jobName);
	Object toReturn = _self;
	DPOPS ("Processor: AddJobCode ended.")
	return toReturn;
}

Object Processor_AddJobStageCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddJobStageCode begined.")
	ASSERT_C ( "Processor:AddJobStageCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _jobStageName;
	_jobStageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _jobStage;
	_jobStage = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Стадия", 12), _toDo);
	ListMap_JobSetStage(Processor_ContextJob(_self), _jobStage, _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: AddJobStageCode ended.")
	return toReturn;
}

Object Processor_AddMessageSlotCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddMessageSlotCode begined.")
	ASSERT_C ( "Processor:AddMessageSlotCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _messageName;
	_messageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _message;
	_message = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _toDo);
	ListMap_JobSetMessageSlot(Processor_ContextJob(_self), _message, _messageName);
	Object toReturn = _self;
	DPOPS ("Processor: AddMessageSlotCode ended.")
	return toReturn;
}

Object Processor_RemoveJobStageCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveJobStageCode begined.")
	ASSERT_C ( "Processor:RemoveJobStageCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _jobStageName;
	_jobStageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _iterator;
	_iterator = ListMap_JobMessageSlotsIterator(Processor_ContextJob(_self));
	while((Logic_Not(ListMapIterator_ThisEnd(_iterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMapIterator_ThisValue(_iterator);
		Object _stages;
		_stages = ListMap_MessageSlotStages(_messageSlot);
		List_RemoveFirst(_stages, _jobStageName);
		ListMapIterator_Next(_iterator);
	}
	ListMap_JobRemoveStage(Processor_ContextJob(_self), _jobStageName);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveJobStageCode ended.")
	return toReturn;
}

Object Processor_RemoveMessageSlotCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveMessageSlotCode begined.")
	ASSERT_C ( "Processor:RemoveMessageSlotCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageSlotName), _nil) != _equal)) != _false)
	{
		Object _stagesIterator;
		_stagesIterator = ListMap_JobStagesIterator(Processor_ContextJob(_self));
		while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
		{
			Object _stage;
			_stage = ListMapIterator_ListMapData(_stagesIterator);
			if((List_RemoveFirstWithConfirmation(ListMap_StageMessageSlots(_stage), _messageSlotName)) != _false)
			{
				ListMap_StageDecrementMessagesCounter(_stage);
			}
			ListMapIterator_Next(_stagesIterator);
		}
	}
	else
	{
		Object _stagesIterator;
		_stagesIterator = ListMap_JobStagesIterator(Processor_ContextJob(_self));
		while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
		{
			Object _stage;
			_stage = ListMapIterator_ListMapData(_stagesIterator);
			List_RemoveFirst(ListMap_StageMessageSlots(_stage), _messageSlotName);
			ListMapIterator_Next(_stagesIterator);
		}
	}
	ListMap_JobRemoveMessageSlot(Processor_ContextJob(_self), _messageSlotName);
	Object toReturn = _self;
	DPOPS ("Processor: RemoveMessageSlotCode ended.")
	return toReturn;
}

Object Processor_RemoveMessageInSlotCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveMessageInSlotCode begined.")
	ASSERT_C ( "Processor:RemoveMessageInSlotCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _messageSlotName;
	_messageSlotName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Object _messageSlot;
	_messageSlot = ListMap_JobMessageSlot(Processor_ContextJob(_self), _messageSlotName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_MessageSlotMessage(_messageSlot), _nil) != _equal)) != _false)
	{
		ListMap_MessageSlotSetMessage(_messageSlot, _nil);
		Object _stagesIterator;
		_stagesIterator = ListMap_JobStagesIterator(Processor_ContextJob(_self));
		while((Logic_Not(ListMapIterator_ThisEnd(_stagesIterator))) != _false)
		{
			Object _stage;
			_stage = ListMapIterator_ListMapData(_stagesIterator);
			if((ListMap_StageContainsMessageSlot(_stage, _messageSlotName)) != _false)
			{
				ListMap_StageDecrementMessagesCounter(_stage);
			}
			ListMapIterator_Next(_stagesIterator);
		}
	}
	Object toReturn = _nil;
	DPOPS ("Processor: RemoveMessageInSlotCode ended.")
	return toReturn;
}

Object Processor_RemoveAllReceivedMessagesCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveAllReceivedMessagesCode begined.")
	ASSERT_C ( "Processor:RemoveAllReceivedMessagesCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_JobMessageSlotsIterator(Processor_ContextJob(_self));
	Object _stagesIterator;
	_stagesIterator = ListMap_JobStagesIterator(Processor_ContextJob(_self));
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
		ListMap_MessageSlotSetMessage(_messageSlot, _nil);
		ListMapIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllReceivedMessagesCode ended.")
	return toReturn;
}

Object Processor_RemoveAllJobStagesCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveAllJobStagesCode begined.")
	ASSERT_C ( "Processor:RemoveAllJobStagesCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ListMap_JobRemoveAllStages(Processor_ContextJob(_self));
	Object _messageSlotsIterator;
	_messageSlotsIterator = ListMap_JobMessageSlotsIterator(Processor_ContextJob(_self));
	while((Logic_Not(ListMapIterator_ThisEnd(_messageSlotsIterator))) != _false)
	{
		Object _messageSlot;
		_messageSlot = ListMapIterator_ListMapData(_messageSlotsIterator);
		List_Clean(ListMap_MessageSlotStages(_messageSlot));
		ListMapIterator_Next(_messageSlotsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllJobStagesCode ended.")
	return toReturn;
}

Object Processor_RemoveAllMessageSlotsCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveAllMessageSlotsCode begined.")
	ASSERT_C ( "Processor:RemoveAllMessageSlotsCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ListMap_JobRemoveAllMessageSlots(Processor_ContextJob(_self));
	Object _jobStagesIterator;
	_jobStagesIterator = ListMap_JobStagesIterator(Processor_ContextJob(_self));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobStagesIterator))) != _false)
	{
		Object _jobStage;
		_jobStage = ListMapIterator_ThisValue(_jobStagesIterator);
		List_Clean(ListMap_StageMessageSlots(_jobStage));
		ListMap_StageSetMessagesCounter(_jobStage, NumberFactory_FromLong(_numberFactory, 0));
		ListMapIterator_Next(_jobStagesIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllMessageSlotsCode ended.")
	return toReturn;
}

Object Processor_RemoveAllJobStagesAndMessageSlotsCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveAllJobStagesAndMessageSlotsCode begined.")
	ASSERT_C ( "Processor:RemoveAllJobStagesAndMessageSlotsCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ListMap_JobRemoveAllStages(Processor_ContextJob(_self));
	ListMap_JobRemoveAllMessageSlots(Processor_ContextJob(_self));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllJobStagesAndMessageSlotsCode ended.")
	return toReturn;
}

Object Processor_AttachToStageMessageSlotCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AttachToStageMessageSlotCode begined.")
	ASSERT_C ( "Processor:AttachToStageMessageSlotCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _stageName;
	_stageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя стадии", 19), _toDo);
	Object _messageName;
	_messageName = Processor_GetNamedEntityFromToDoOrStack(_self, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25), _toDo);
	Processor_AttachToStageMessageSlot(_self, _stageName, _messageName);
	Object toReturn = _self;
	DPOPS ("Processor: AttachToStageMessageSlotCode ended.")
	return toReturn;
}

Object Processor_FinishThisJobCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: FinishThisJobCode begined.")
	ASSERT_C ( "Processor:FinishThisJobCode --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	ListMap_ObjectRemoveJob(Processor_ContextObject(_self), (((Processor) (_self->entity))->_contextJobName));
	Object toReturn = _self;
	DPOPS ("Processor: FinishThisJobCode ended.")
	return toReturn;
}

Object Processor_AttachToStageMessageSlot(Object _self, Object _stageName, Object _messageName)
{
	DPUSHS ("Processor: AttachToStageMessageSlot begined.")
	ASSERT_C ( "Processor:AttachToStageMessageSlot --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _stage;
	_stage = ListMap_JobStage(Processor_ContextJob(_self), _stageName);
	Object _stagesInMessageSlot;
	_stagesInMessageSlot = ListMap_MessageSlotStages(ListMap_JobMessageSlot(Processor_ContextJob(_self), _messageName));
	if((Logic_Not(List_Contains(_stagesInMessageSlot, _stageName))) != _false)
	{
		Object _messageSlotsInStage;
		_messageSlotsInStage = ListMap_StageMessageSlots(_stage);
		List_PushBack(_stagesInMessageSlot, _stageName);
		List_PushBack(_messageSlotsInStage, _messageName);
		ListMap_StageIncrementMessagesCounter(_stage);
	}
	Object toReturn = _self;
	DPOPS ("Processor: AttachToStageMessageSlot ended.")
	return toReturn;
}

Object Processor_EntityFromNamedMessageField(Object _self, Object _messageName, Object _fieldName)
{
	DPUSHS ("Processor: EntityFromNamedMessageField begined.")
	ASSERT_C ( "Processor:EntityFromNamedMessageField --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = ListMap_ObjectAt(ListMap_JobMessageInMessageSlot(Processor_ContextJob(_self), _messageName), _fieldName);
	DPOPS ("Processor: EntityFromNamedMessageField ended.")
	return toReturn;
}

Object Processor_NamespaceNameToNamespace(Object _self, Object _locationType)
{
	DPUSHS ("Processor: NamespaceNameToNamespace begined.")
	ASSERT_C ( "Processor:NamespaceNameToNamespace --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Взятие отсутствующего поля", 50));
	Object toReturn = _nil;
	DPOPS ("Processor: FieldNameToSynonim ended.")
	return toReturn;
}

Object Processor_FieldNameToUID(Object _self, Object _fieldName)
{
	DPUSHS ("Processor: FieldNameToUID begined.")
	ASSERT_C ( "Processor:FieldNameToUID --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object toReturn = Synonim_GetUID(Processor_FieldNameToSynonim(_self, _fieldName));
	DPOPS ("Processor: FieldNameToUID ended.")
	return toReturn;
}

Object Processor_SendMessage(Object _self, Object _message)
{
	DPUSHS ("Processor: SendMessage begined.")
	ASSERT_C ( "Processor:SendMessage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _uid;
	_uid = ListMap_MessageSender(_message);
	Object _receiver;
	_receiver = Machine_UIDToObject((((Processor) (_self->entity))->_machine), _uid);
	Processor_ProcessMessageForObject(_self, _message, _receiver);
	Machine_ScheduleUID((((Processor) (_self->entity))->_machine), _uid);
	Object toReturn = _self;
	DPOPS ("Processor: SendMessage ended.")
	return toReturn;
}

Object Processor_SendReplyForMessage(Object _self, Object _replyMessage, Object _messageSlotName)
{
	DPUSHS ("Processor: SendReplyForMessage begined.")
	ASSERT_C ( "Processor:SendReplyForMessage --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
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
	ListMap_MessageSetType(_replyMessage, StringFactory_FromUTF8(_stringFactory, "Ответ", 10));
	Processor_SendMessage(_self, _message);
	Object toReturn = _self;
	DPOPS ("Processor: SendReplyForMessage ended.")
	return toReturn;
}

Object Processor_InvokeMethodWithParameters(Object _self, Object _methodName, Object _parameters)
{
	DPUSHS ("Processor: InvokeMethodWithParameters begined.")
	ASSERT_C ( "Processor:InvokeMethodWithParameters --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _method;
	_method = ListMap_ObjectMethod(Processor_ContextObject(_self), _methodName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ошибка! Вызов несуществующего метода.", 69));
	}
	else
	{
		if((ListMap_LogicAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14))) != _false)
		{
			Object _basicMethod;
			_basicMethod = ListMap_MethodAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый метод", 25));
			Object _objectEntity;
			_objectEntity = ListMap_ObjectAt(_method, StringFactory_FromUTF8(_stringFactory, "Сущность", 16));
			Method_Invoke(_basicMethod, _objectEntity, _parameters, _self);
		}
		else
		{
			Object _namespace;
			_namespace = ListMap_Create();
			Stack_Push((((Processor) (_self->entity))->_localNamespaces), _namespace);
			ListMap_AddListMap(_namespace, _parameters);
			Object_Release(_namespace);
			Object _methodBody;
			_methodBody = ListMap_ListAt(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8));
			Object _iterator;
			_iterator = List_First(_methodBody);
			while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
			{
				Processor_Do(_self, ListIterator_ListMapData(_iterator));
				ListIterator_Next(_iterator);
			}
			Stack_Pop((((Processor) (_self->entity))->_localNamespaces));
		}
	}
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _self;
	DPOPS ("Processor: InvokeMethodWithParameters ended.")
	return toReturn;
}

Object Processor_MessageConfirmsToParameter(Object _self, Object _message, Object _parameter)
{
	DPUSHS ("Processor: MessageConfirmsToParameter begined.")
	ASSERT_C ( "Processor:MessageConfirmsToParameter --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _checkingMethod;
	_checkingMethod = ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Совпадение", 20)) == _equal)) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Ключ", 8))), ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Значение", 16))) == _equal)) != _false)
		{
			Object toReturn = _true;
			DPOPS ("Processor: MessageConfirmsToParameter ended.")
			return toReturn;
		}
	}
	Object toReturn = _false;
	DPOPS ("Processor: MessageConfirmsToParameter ended.")
	return toReturn;
}

Object Processor_TryLinkMessageWithMessageSlotAndJob(Object _self, Object _message, Object _messageSlot, Object _job)
{
	DPUSHS ("Processor: TryLinkMessageWithMessageSlotAndJob begined.")
	ASSERT_C ( "Processor:TryLinkMessageWithMessageSlotAndJob --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _confirms;
	_confirms = _true;
	Object _parametersIterator;
	_parametersIterator = List_First(ListMap_ListAt(_messageSlot, StringFactory_FromUTF8(_stringFactory, "Метод идентификации", 37)));
	while((Logic_Not(ListIterator_ThisEnd(_parametersIterator))) != _false)
	{
		Object _parameter;
		_parameter = ListIterator_ListMapData(_parametersIterator);
		if((Logic_Not(Processor_MessageConfirmsToParameter(_self, _message, _parameter))) != _false)
		{
			_confirms = _false;
			break;
		}
		ListIterator_Next(_parametersIterator);
	}
	if((_confirms) != _false)
	{
		ListMap_MessageSlotSetMessage(_messageSlot, _message);
		Object _waitingStageNamesIterator;
		_waitingStageNamesIterator = List_First(ListMap_MessageSlotStages(_messageSlot));
		while((Logic_Not(ListIterator_ThisEnd(_waitingStageNamesIterator))) != _false)
		{
			Object _jobStage;
			_jobStage = ListMap_ListMapAt(ListMap_JobStages(_job), ListIterator_ListData(_waitingStageNamesIterator));
			ListMap_StageDecrementMessagesCounter(_jobStage);
			ListIterator_Next(_waitingStageNamesIterator);
		}
	}
	Object toReturn = _self;
	DPOPS ("Processor: TryLinkMessageWithMessageSlotAndJob ended.")
	return toReturn;
}

Object Processor_ProcessMessageForObject(Object _self, Object _message, Object _object)
{
	DPUSHS ("Processor: ProcessMessageForObject begined.")
	ASSERT_C ( "Processor:ProcessMessageForObject --- Checking for correct object type failed.", _self->gid ==  8708543990322460672ull )
	Object _jobsIterator;
	_jobsIterator = ListMap_First(ListMap_ObjectJobs(_object));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobsIterator))) != _false)
	{
		Object _job;
		_job = ListMapIterator_ListMapData(_jobsIterator);
		Object _messageSlotsIterator;
		_messageSlotsIterator = ListMap_JobMessageSlotsIterator(_job);
		while((Logic_Not(ListMapIterator_ThisEnd(_messageSlotsIterator))) != _false)
		{
			Processor_TryLinkMessageWithMessageSlotAndJob(_self, _message, ListMapIterator_ListMapData(_messageSlotsIterator), _job);
			ListMapIterator_Next(_messageSlotsIterator);
		}
		ListMapIterator_Next(_jobsIterator);
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
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_StageMessagesCounter(_jobStage), NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
			{
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStageName), ListMapIterator_ThisKey(_jobStagesIterator));
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobName), ListMapIterator_ThisKey(_jobsIterator));
				Object _emptyParameters;
				_emptyParameters = ListMap_Create();
				Processor_InvokeMethodWithParameters(_self, ListMap_StageMethod(_jobStage), _emptyParameters);
				Object_Release(_emptyParameters);
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
