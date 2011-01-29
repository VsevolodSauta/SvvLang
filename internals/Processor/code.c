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
	((Processor) (_self->entity))->_contextObject = _nil;
	((Processor) (_self->entity))->_contextJobStage = _nil;
	((Processor) (_self->entity))->_contextJob = _nil;
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
	Object toReturn = Processor_Create();
	DPOPS ("Processor: Clone ended.")
	return toReturn;
}

Object Processor_DeepClone(Object _self)
{
	DPUSHS ("Processor: DeepClone begined.")
	Object toReturn = Processor_Create();
	DPOPS ("Processor: DeepClone ended.")
	return toReturn;
}

Object Processor_Destroy(Object _self)
{
	DPUSHS ("Processor: Destroy begined.")
	Object_Release((((Processor) (_self->entity))->_contextObject));
	Object_Release((((Processor) (_self->entity))->_contextJobStage));
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
	Object toReturn = _equal;
	DPOPS ("Processor: Compare ended.")
	return toReturn;
}

Object Processor_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("Processor: SetMachine begined.")
	(((Processor) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("Processor: SetMachine ended.")
	return toReturn;
}

Object Processor_Init(Object _self)
{
	DPUSHS ("Processor: Init begined.")
	(((Processor) (_self->entity))->_localNamespaces) = Stack_Create();
	(((Processor) (_self->entity))->_helperStack) = Stack_Create();
	(((Processor) (_self->entity))->_processorCodes) = ListMap_Create();
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Выполнить", 18), MethodFactory_FromPointer(_methodFactory, &Processor_DoCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Взять сообщение из имени", 45), MethodFactory_FromPointer(_methodFactory, &Processor_MessageFromMessageNameCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Взять сущность из поля сообщения", 60), MethodFactory_FromPointer(_methodFactory, &Processor_ObjectFromMessagesFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Взять синоним из поля", 39), MethodFactory_FromPointer(_methodFactory, &Processor_FieldNameToSynonimCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Взять объект из синонима", 45), MethodFactory_FromPointer(_methodFactory, &Processor_SynonimToUIDCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить текущий объект в вершину", 62), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentObjectToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить текущую работу в вершину", 62), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentJobToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить текущую стадию в вершину", 62), MethodFactory_FromPointer(_methodFactory, &Processor_AddCurrentJobStageToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить список в вершину", 47), MethodFactory_FromPointer(_methodFactory, &Processor_AddListToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить отображение в вершину", 57), MethodFactory_FromPointer(_methodFactory, &Processor_AddListMapToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29), MethodFactory_FromPointer(_methodFactory, &Processor_PopFromStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить элемент в отображение", 57), MethodFactory_FromPointer(_methodFactory, &Processor_AddObjectToListMapCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить элемент в список", 47), MethodFactory_FromPointer(_methodFactory, &Processor_AddObjectToListCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить в стек", 28), MethodFactory_FromPointer(_methodFactory, &Processor_AddObjectToStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Дублировать вершину", 37), MethodFactory_FromPointer(_methodFactory, &Processor_DuplicateTopInStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Поменять местами вершинные элементы", 67), MethodFactory_FromPointer(_methodFactory, &Processor_SwapTopInStackCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Послать сообщение", 33), MethodFactory_FromPointer(_methodFactory, &Processor_SendMessageCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Вызвать метод", 25), MethodFactory_FromPointer(_methodFactory, &Processor_InvokeMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Определить метод", 31), MethodFactory_FromPointer(_methodFactory, &Processor_DefineMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить метод", 25), MethodFactory_FromPointer(_methodFactory, &Processor_UnDefineMethodCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Создать ТВА", 21), MethodFactory_FromPointer(_methodFactory, &Processor_DefineLocalFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Создать поле работы", 36), MethodFactory_FromPointer(_methodFactory, &Processor_DefineJobFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Создать поле объекта", 38), MethodFactory_FromPointer(_methodFactory, &Processor_DefineObjectFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Создать глобальное поле", 44), MethodFactory_FromPointer(_methodFactory, &Processor_DefineGlobalFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Присвоить", 18), MethodFactory_FromPointer(_methodFactory, &Processor_SetFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Перемежить", 20), MethodFactory_FromPointer(_methodFactory, &Processor_UniteFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Удалить поле", 23), MethodFactory_FromPointer(_methodFactory, &Processor_UnDefineFieldCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить работу", 29), MethodFactory_FromPointer(_methodFactory, &Processor_AddJobToObjectCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить следующую стадию", 48), MethodFactory_FromPointer(_methodFactory, &Processor_AddStageToJobCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Добавить условие входа на стадию", 60), MethodFactory_FromPointer(_methodFactory, &Processor_AddConditionToStageCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Очистить стадии", 29), MethodFactory_FromPointer(_methodFactory, &Processor_RemoveAllStagesCode));
	ListMap_Add((((Processor) (_self->entity))->_processorCodes), StringFactory_FromUTF8(_stringFactory, "Завершить работу", 31), MethodFactory_FromPointer(_methodFactory, &Processor_FinishJobCode));
	Object toReturn = _self;
	DPOPS ("Processor: Init ended.")
	return toReturn;
}

Object Processor_Do(Object _self, Object _toDo)
{
	DPUSHS ("Processor: Do begined.")
	Console_WriteLnString(_console, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	Object _method;
	_method = ListMap_MethodAt((((Processor) (_self->entity))->_processorCodes), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16)));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: Действие не существует либо отсутствует в системе комманд.", 139));
	}
	Method_Invoke(_method, _self, _toDo);
	Object toReturn = _self;
	DPOPS ("Processor: Do ended.")
	return toReturn;
}

Object Processor_DoCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DoCode begined.")
	Object _value;
	_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
	{
		_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Processor_Do(_self, _value);
	Object toReturn = _self;
	DPOPS ("Processor: DoCode ended.")
	return toReturn;
}

Object Processor_MessageFromMessageNameCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: MessageFromMessageNameCode begined.")
	Object _name;
	_name = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя сообщения", 25));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
	{
		_name = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Object _message;
	_message = ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)), _name);
	Stack_Push((((Processor) (_self->entity))->_helperStack), _message);
	Object toReturn = _self;
	DPOPS ("Processor: MessageFromMessageNameCode ended.")
	return toReturn;
}

Object Processor_ObjectFromMessagesFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: ObjectFromMessagesFieldCode begined.")
	Object _name;
	_name = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
	{
		_name = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Object _message;
	_message = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_message, _nil) == _equal)) != _false)
	{
		_message = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Stack_Push((((Processor) (_self->entity))->_helperStack), ListMap_ObjectAt(_message, _name));
	Object toReturn = _self;
	DPOPS ("Processor: ObjectFromMessagesFieldCode ended.")
	return toReturn;
}

Object Processor_FieldNameToSynonimCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: FieldNameToSynonimCode begined.")
	Object _name;
	_name = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя", 6));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
	{
		_name = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Stack_Push((((Processor) (_self->entity))->_helperStack), Processor_FieldNameToSynonim(_self, _name));
	Object toReturn = _self;
	DPOPS ("Processor: FieldNameToSynonimCode ended.")
	return toReturn;
}

Object Processor_SynonimToUIDCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SynonimToUIDCode begined.")
	Object _synonim;
	_synonim = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
	{
		_synonim = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	Stack_Push((((Processor) (_self->entity))->_helperStack), Synonim_GetUID(_synonim));
	Object toReturn = _self;
	DPOPS ("Processor: SynonimToUIDCode ended.")
	return toReturn;
}

Object Processor_AddCurrentObjectToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentObjectToStackCode begined.")
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextObject));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentObjectToStackCode ended.")
	return toReturn;
}

Object Processor_AddCurrentJobToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentJobToStackCode begined.")
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJob));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentJobToStackCode ended.")
	return toReturn;
}

Object Processor_AddCurrentJobStageToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddCurrentJobStageToStackCode begined.")
	Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobStage));
	Object toReturn = _self;
	DPOPS ("Processor: AddCurrentJobStageToStackCode ended.")
	return toReturn;
}

Object Processor_AddListToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddListToStackCode begined.")
	Object _list;
	_list = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Список", 12));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_list, _nil) == _equal)) != _false)
	{
		_list = List_Create();
		Object_Autorelease(_list);
	}
	Stack_Push((((Processor) (_self->entity))->_helperStack), _list);
	Object toReturn = _self;
	DPOPS ("Processor: AddListToStackCode ended.")
	return toReturn;
}

Object Processor_AddListMapToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddListMapToStackCode begined.")
	Object _listMap;
	_listMap = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Отображение", 22));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_listMap, _nil) == _equal)) != _false)
	{
		_listMap = ListMap_Create();
		Object_Autorelease(_listMap);
	}
	Stack_Push((((Processor) (_self->entity))->_helperStack), _listMap);
	Object toReturn = _self;
	DPOPS ("Processor: AddListMapToStackCode ended.")
	return toReturn;
}

Object Processor_PopFromStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: PopFromStackCode begined.")
	Stack_Pop((((Processor) (_self->entity))->_helperStack));
	Object toReturn = _self;
	DPOPS ("Processor: PopFromStackCode ended.")
	return toReturn;
}

Object Processor_AddObjectToListMapCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddObjectToListMapCode begined.")
	Object _key;
	_key = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Ключ", 8));
	Object _value;
	_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
	{
		_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_key, _nil) == _equal)) != _false)
	{
		_key = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	ListMap_Add(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key, _value);
	Object toReturn = _self;
	DPOPS ("Processor: AddObjectToListMapCode ended.")
	return toReturn;
}

Object Processor_AddObjectToListCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddObjectToListCode begined.")
	Object _value;
	_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
	{
		_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	List_PushBack(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _value);
	Object toReturn = _self;
	DPOPS ("Processor: AddObjectToListCode ended.")
	return toReturn;
}

Object Processor_AddObjectToStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddObjectToStackCode begined.")
	Stack_Push((((Processor) (_self->entity))->_helperStack), ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	Object toReturn = _self;
	DPOPS ("Processor: AddObjectToStackCode ended.")
	return toReturn;
}

Object Processor_DuplicateTopInStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DuplicateTopInStackCode begined.")
	Stack_Push((((Processor) (_self->entity))->_helperStack), Object_TempClone(Stack_Peek((((Processor) (_self->entity))->_helperStack))));
	Object toReturn = _self;
	DPOPS ("Processor: DuplicateTopInStackCode ended.")
	return toReturn;
}

Object Processor_SwapTopInStackCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SwapTopInStackCode begined.")
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

Object Processor_SendMessageCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SendMessageCode begined.")
	Processor_SendMessage(_self, ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	Object toReturn = _self;
	DPOPS ("Processor: SendMessageCode ended.")
	return toReturn;
}

Object Processor_InvokeMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: InvokeMethodCode begined.")
	Processor_InvokeMethodWithParameters(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Параметры", 18)));
	Object toReturn = _self;
	DPOPS ("Processor: InvokeMethodCode ended.")
	return toReturn;
}

Object Processor_DefineMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineMethodCode begined.")
	ListMap_Add(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Метод", 10)));
	Object toReturn = _self;
	DPOPS ("Processor: DefineMethodCode ended.")
	return toReturn;
}

Object Processor_UnDefineMethodCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UnDefineMethodCode begined.")
	ListMap_Remove(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)));
	Object toReturn = _self;
	DPOPS ("Processor: UnDefineMethodCode ended.")
	return toReturn;
}

Object Processor_DefineLocalFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineLocalFieldCode begined.")
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, Stack_Peek((((Processor) (_self->entity))->_localNamespaces)));
	DPOPS ("Processor: DefineLocalFieldCode ended.")
	return toReturn;
}

Object Processor_DefineJobFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineJobFieldCode begined.")
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
	DPOPS ("Processor: DefineJobFieldCode ended.")
	return toReturn;
}

Object Processor_DefineObjectFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineObjectFieldCode begined.")
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
	DPOPS ("Processor: DefineObjectFieldCode ended.")
	return toReturn;
}

Object Processor_DefineGlobalFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: DefineGlobalFieldCode begined.")
	Object toReturn = Processor_DefineFieldHelper(_self, _toDo, (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext));
	DPOPS ("Processor: DefineGlobalFieldCode ended.")
	return toReturn;
}

Object Processor_DefineFieldHelper(Object _self, Object _toDo, Object _nameSpace)
{
	DPUSHS ("Processor: DefineFieldHelper begined.")
	Object _synonim;
	_synonim = ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
	{
		Object _name;
		_name = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Существующее имя поля", 40));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
		{
			Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректные параметры для \\\"Создать поле\\\".", 79));
			Object toReturn = _self;
			DPOPS ("Processor: DefineFieldHelper ended.")
			return toReturn;
		}
		_synonim = Processor_FieldNameToSynonim(_self, _name);
	}
	Object _reference;
	_reference = ListMap_Create();
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), _nameSpace);
	ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
	Synonim_AddReference(_synonim, _reference);
	Object_Release(_reference);
	Object toReturn = _self;
	DPOPS ("Processor: DefineFieldHelper ended.")
	return toReturn;
}

Object Processor_SetFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: SetFieldCode begined.")
	Synonim_SetUID(Processor_FieldNameToSynonim(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15))), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26)));
	Object toReturn = _self;
	DPOPS ("Processor: SetFieldCode ended.")
	return toReturn;
}

Object Processor_UniteFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UniteFieldCode begined.")
	Synonim_Unite(Processor_FieldNameToSynonim(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя прибытия", 23))), Processor_FieldNameToSynonim(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15))));
	Object toReturn = _self;
	DPOPS ("Processor: UniteFieldCode ended.")
	return toReturn;
}

Object Processor_UnDefineFieldCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: UnDefineFieldCode begined.")
	Object _locationType;
	_locationType = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, _nil) == _equal)) != _false)
	{
		_locationType = Processor_FieldNameToNamespaceName(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
	}
	Object _place;
	_place = ListMap_Create();
	ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Имя", 6), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
	ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), Processor_NamespaceNameToNamespace(_self, _locationType));
	Object _synonim;
	_synonim = Processor_FieldNameToSynonim(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
	Synonim_RemoveReference(_synonim, _place);
	Object_Release(_place);
	Object toReturn = _self;
	DPOPS ("Processor: UnDefineFieldCode ended.")
	return toReturn;
}

Object Processor_AddJobToObjectCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddJobToObjectCode begined.")
	List_PushBack(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)));
	Object toReturn = _self;
	DPOPS ("Processor: AddJobToObjectCode ended.")
	return toReturn;
}

Object Processor_AddStageToJobCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddStageToJobCode begined.")
	List_PushBack(ListMap_ListAt(ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Стадии", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Стадия", 12)));
	Object toReturn = _self;
	DPOPS ("Processor: AddStageToJobCode ended.")
	return toReturn;
}

Object Processor_AddConditionToStageCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: AddConditionToStageCode begined.")
	Object _stage;
	_stage = ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Стадия", 12));
	List_PushBack(ListMap_ListAt(_stage, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Условие", 14)));
	Number_Inc(ListMap_NumberAt(_stage, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39)));
	Object toReturn = _self;
	DPOPS ("Processor: AddConditionToStageCode ended.")
	return toReturn;
}

Object Processor_RemoveAllStagesCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: RemoveAllStagesCode begined.")
	List_Clean(ListMap_ListAt(ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Стадии", 12)));
	Object toReturn = _self;
	DPOPS ("Processor: RemoveAllStagesCode ended.")
	return toReturn;
}

Object Processor_FinishJobCode(Object _self, Object _toDo)
{
	DPUSHS ("Processor: FinishJobCode begined.")
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Завершение работы", 33));
	List_RemoveFirst(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)));
	Object toReturn = _self;
	DPOPS ("Processor: FinishJobCode ended.")
	return toReturn;
}

Object Processor_NamespaceNameToNamespace(Object _self, Object _locationType)
{
	DPUSHS ("Processor: NamespaceNameToNamespace begined.")
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Глобальное поле", 29)) == _equal)) != _false)
	{
		Object toReturn = (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext);
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23)) == _equal)) != _false)
	{
		Object toReturn = ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле работы", 21)) == _equal)) != _false)
	{
		Object toReturn = ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27)) == _equal)) != _false)
	{
		Object toReturn = Stack_Peek((((Processor) (_self->entity))->_localNamespaces));
		DPOPS ("Processor: NamespaceNameToNamespace ended.")
		return toReturn;
	}
	Object toReturn = _nil;
	DPOPS ("Processor: NamespaceNameToNamespace ended.")
	return toReturn;
}

Object Processor_FieldNameToNamespaceName(Object _self, Object _objectName)
{
	DPUSHS ("Processor: FieldNameToNamespaceName begined.")
	Object _candidate;
	_candidate = ListMap_ObjectAt(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	_candidate = ListMap_ObjectAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Поле работы", 21);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	_candidate = ListMap_ObjectAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23);
		DPOPS ("Processor: FieldNameToNamespaceName ended.")
		return toReturn;
	}
	_candidate = ListMap_ObjectAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
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

Object Processor_FieldNameToSynonim(Object _self, Object _objectName)
{
	DPUSHS ("Processor: FieldNameToSynonim begined.")
	Object _candidate;
	_candidate = ListMap_SynonimAt(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		Object toReturn = _candidate;
		DPOPS ("Processor: FieldNameToSynonim ended.")
		return toReturn;
	}
	_candidate = ListMap_SynonimAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _objectName);
	Object toReturn = _candidate;
	DPOPS ("Processor: FieldNameToSynonim ended.")
	return toReturn;
}

Object Processor_SendMessage(Object _self, Object _message)
{
	DPUSHS ("Processor: SendMessage begined.")
	Object _uid;
	_uid = ListMap_ListAt(_message, StringFactory_FromUTF8(_stringFactory, "Получатель", 20));
	Object _receiver;
	_receiver = Machine_UIDToObject((((Processor) (_self->entity))->_machine), _uid);
	Processor_ProcessMessageForObject(_self, _message, _receiver);
	Machine_ScheduleUID((((Processor) (_self->entity))->_machine), _uid);
	Object toReturn = _self;
	DPOPS ("Processor: SendMessage ended.")
	return toReturn;
}

Object Processor_InvokeMethodWithParameters(Object _self, Object _methodName, Object _parameters)
{
	DPUSHS ("Processor: InvokeMethodWithParameters begined.")
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _method;
	_method = ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), _methodName);
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
			_objectEntity = ListMap_ObjectAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Свойства", 16)), StringFactory_FromUTF8(_stringFactory, "Сущность", 16));
			Method_Invoke(_basicMethod, _objectEntity, (((Processor) (_self->entity))->_contextObject), _parameters);
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
		ListMap_Add(_messageSlot, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _message);
		Object _waitingStageNamesIterator;
		_waitingStageNamesIterator = List_First(ListMap_ListAt(_messageSlot, StringFactory_FromUTF8(_stringFactory, "Ожидающие стадии", 31)));
		while((Logic_Not(ListIterator_ThisEnd(_waitingStageNamesIterator))) != _false)
		{
			Object _jobStage;
			_jobStage = ListMap_ListMapAt(ListMap_ListMapAt(_job, StringFactory_FromUTF8(_stringFactory, "Стадии", 12)), ListIterator_ListData(_waitingStageNamesIterator));
			Object _msgNeeded;
			_msgNeeded = ListMap_NumberAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39));
			Number_Dec(_msgNeeded);
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_msgNeeded, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
			{
				ListMap_Add(_jobStage, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Готовность", 20));
			}
		}
	}
	Object toReturn = _self;
	DPOPS ("Processor: TryLinkMessageWithMessageSlotAndJob ended.")
	return toReturn;
}

Object Processor_ProcessMessageForObject(Object _self, Object _message, Object _object)
{
	DPUSHS ("Processor: ProcessMessageForObject begined.")
	Object _jobsIterator;
	_jobsIterator = ListMap_First(ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Работы", 12)));
	while((Logic_Not(ListMapIterator_ThisEnd(_jobsIterator))) != _false)
	{
		Object _job;
		_job = ListMapIterator_ListMapData(_jobsIterator);
		Object _messageSlotsIterator;
		_messageSlotsIterator = ListMap_First(ListMap_ListMapAt(_job, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)));
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
	Object _jobsIterator;
	_jobsIterator = List_First(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)));
	while((Logic_Not(ListIterator_ThisEnd(_jobsIterator))) != _false)
	{
		Object _job;
		_job = ListIterator_ListMapData(_jobsIterator);
		Object _jobStagesIterator;
		_jobStagesIterator = List_First(ListMap_ListAt(_job, StringFactory_FromUTF8(_stringFactory, "Стадии", 12)));
		while((Logic_Not(ListIterator_ThisEnd(_jobStagesIterator))) != _false)
		{
			Object _jobStage;
			_jobStage = ListIterator_ListMapData(_jobStagesIterator);
			Console_WriteLnString(_console, ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)));
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Состояние", 18)), StringFactory_FromUTF8(_stringFactory, "Готовность", 20)) == _equal)) != _false)
			{
				ListIterator_Hide(_jobsIterator);
				ListIterator_Hide(_jobStagesIterator);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStage), _jobStage);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJob), _job);
				Object _emptyParameters;
				_emptyParameters = ListMap_Create();
				Processor_InvokeMethodWithParameters(_self, ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Метод", 10)), _emptyParameters);
				Object_Release(_emptyParameters);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStage), _nil);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJob), _nil);
				Object toReturn = _self;
				DPOPS ("Processor: ProcessOneJobIfAny ended.")
				return toReturn;
			}
			ListIterator_Next(_jobStagesIterator);
		}
		ListIterator_Next(_jobsIterator);
	}
	Object toReturn = _self;
	DPOPS ("Processor: ProcessOneJobIfAny ended.")
	return toReturn;
}

Object Processor_ProcessUID(Object _self, Object _uid)
{
	DPUSHS ("Processor: ProcessUID begined.")
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _object;
	_object = Machine_UIDToObject((((Processor) (_self->entity))->_machine), _uid);
	Stack_Clean((((Processor) (_self->entity))->_helperStack));
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _object);
	Processor_ProcessOneJobIfAny(_self);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _nil);
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _self;
	DPOPS ("Processor: ProcessUID ended.")
	return toReturn;
}
