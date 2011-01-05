#include "internals/basics.h"
#include "internals/Processor/imports.h"


Object Processor_Create(void)
{
	Object toReturn = Object_Create();
	toReturn->entity = Allocator_New(_allocator, sizeof(struct Processor));
	toReturn->gid =  8708543990322460672ull;
	Object_SetComparator(toReturn, &Processor_Compare);
	Object_SetDestructor(toReturn, &Processor_Destroy);
	Object_SetCloner(toReturn, &Processor_Clone);
	((Processor) (toReturn->entity))->_contextObject = _nil;
	((Processor) (toReturn->entity))->_contextJobStage = _nil;
	((Processor) (toReturn->entity))->_machine = _nil;
	((Processor) (toReturn->entity))->_localNamespaces = _nil;
	((Processor) (toReturn->entity))->_helperStack = _nil;
	toReturn = Processor_Init(toReturn);
	return toReturn;
}

Object Processor_Init(Object _self)
{
	(((Processor) (_self->entity))->_localNamespaces) = Stack_Create();
	(((Processor) (_self->entity))->_helperStack) = Stack_Create();
	return _self;
}

Object Processor_Clone(Object _self)
{
	return Processor_Create();
}

Object Processor_Destroy(Object _self)
{
	Object_Release((((Processor) (_self->entity))->_contextObject));
	Object_Release((((Processor) (_self->entity))->_contextJobStage));
	Object_Release((((Processor) (_self->entity))->_helperStack));
	Object_Release((((Processor) (_self->entity))->_localNamespaces));
	return Object_Destroy(_self);
}

Object Processor_Compare(Object _self, Object _processor)
{
	return _equal;
}

Object Processor_SetMachine(Object _self, Object _machine)
{
	(((Processor) (_self->entity))->_machine) = _machine;
	return _self;
}

Object Processor_LocationType(Object _self, Object _objectName)
{
	Object _candidate;
	_candidate = ListMap_ObjectAt(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27);
	}
	_candidate = ListMap_ObjectAt(ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJobStage), StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return StringFactory_FromUTF8(_stringFactory, "Поле работы", 21);
	}
	_candidate = ListMap_ObjectAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23);
	}
	_candidate = ListMap_ObjectAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return StringFactory_FromUTF8(_stringFactory, "Глобальное поле", 29);
	}
	else
	{
		return StringFactory_FromUTF8(_stringFactory, "Нет такого поля", 28);
	}
}

Object Processor_ResolveName(Object _self, Object _objectName)
{
	Object _candidate;
	_candidate = ListMap_SynonimAt(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return _candidate;
	}
	_candidate = ListMap_SynonimAt(ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJobStage), StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return _candidate;
	}
	_candidate = ListMap_SynonimAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_candidate, _nil) != _equal)) != _false)
	{
		return _candidate;
	}
	_candidate = ListMap_SynonimAt((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), _objectName);
	return _candidate;
}

Object Processor_SendMessage(Object _self, Object _message)
{
	Object _receiver;
	_receiver = Machine_ObjectByUID((((Processor) (_self->entity))->_machine), ListMap_ListAt(_message, StringFactory_FromUTF8(_stringFactory, "Получатель", 20)));
	Object _messageQueue;
	_messageQueue = ListMap_QueueAt(_receiver, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18));
	Queue_Push(_messageQueue, _message);
	Machine_Schedule((((Processor) (_self->entity))->_machine), _receiver);
	return _self;
}

Object Processor_DoHelper(Object _self, Object _toDo)
{
	Object _action;
	_action = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: отсутствует действие.", 71));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Вызвать Do", 17)) == _equal)) != _false)
	{
		Object _value;
		_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
		if((_value = _nil) != _false)
		{
			_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		Processor_Do(_self, _value);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать список", 27)) == _equal)) != _false)
	{
		Object _list;
		_list = List_Create();
		Stack_Push((((Processor) (_self->entity))->_helperStack), _list);
		Object_Release(_list);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать отображение", 37)) == _equal)) != _false)
	{
		Object _listMap;
		_listMap = ListMap_Create();
		Stack_Push((((Processor) (_self->entity))->_helperStack), _listMap);
		Object_Release(_listMap);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29)) == _equal)) != _false)
	{
		Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить в отображение элемент", 57)) == _equal)) != _false)
	{
		Object _key;
		_key = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Ключ", 8));
		Object _value;
		_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
		if((_value = _nil) != _false)
		{
			_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_key, _nil) == _equal)) != _false)
		{
			_key = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		ListMap_Add(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _key, _value);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить в список элемент", 47)) == _equal)) != _false)
	{
		Object _value;
		_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16));
		if((_value = _nil) != _false)
		{
			_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		List_PushBack(Stack_Peek((((Processor) (_self->entity))->_helperStack)), _value);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить в стек", 28)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Значение", 16)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Дублировать", 22)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), Stack_Peek((((Processor) (_self->entity))->_helperStack)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Вызвать DoHelper", 23)) == _equal)) != _false)
	{
		Object _value;
		_value = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Аргумент", 16));
		if((_value = _nil) != _false)
		{
			_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		Processor_DoHelper(_self, _value);
	}
	else
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: неизвестное действие.", 71));
	}
	return _self;
}

Object Processor_Do(Object _self, Object _toDo)
{
	Object _action;
	_action = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Действие", 16));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: отсутствует действие.", 71));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Послать сообщение", 33)) == _equal)) != _false)
	{
		Processor_SendMessage(_self, ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Сообщение", 18)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Определить метод", 31)) == _equal)) != _false)
	{
		Object _methodEntity;
		_methodEntity = ListMap_Create();
		ListMap_Add(_methodEntity, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), ListMap_LogicAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Базовый", 14)));
		ListMap_Add(_methodEntity, StringFactory_FromUTF8(_stringFactory, "Тело", 8), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Тело метода", 21)));
		ListMap_Add(_methodEntity, StringFactory_FromUTF8(_stringFactory, "Адрес", 10), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Адрес", 10)));
		Object_Release(_methodEntity);
		ListMap_Add(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Метод", 10)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Вызвать метод", 25)) == _equal)) != _false)
	{
		Processor_InvokeMethod(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Параметры", 18)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Удалить метод", 25)) == _equal)) != _false)
	{
		ListMap_Remove(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать ТВА", 21)) == _equal)) != _false)
	{
		ListMap_Add(Stack_Peek((((Processor) (_self->entity))->_localNamespaces)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать поле работы", 36)) == _equal)) != _false)
	{
		ListMap_Add(ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJobStage), StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать поле объекта", 38)) == _equal)) != _false)
	{
		ListMap_Add(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать глобальное поле", 44)) == _equal)) != _false)
	{
		ListMap_Add((((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)), ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Присвоить", 18)) == _equal)) != _false)
	{
		Synonim_SetObject(Processor_ResolveName(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15))), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Идентификатор", 26)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Перемежить", 20)) == _equal)) != _false)
	{
		Synonim_Unite(Processor_ResolveName(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15))), Processor_ResolveName(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя прибытия", 23))));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Удалить поле", 23)) == _equal)) != _false)
	{
		Object _locationType;
		_locationType = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, _nil) == _equal)) != _false)
		{
			_locationType = Processor_LocationType(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		}
		Object _place;
		_place = ListMap_Create();
		ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Имя", 6), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Локальное поле", 27)) == _equal)) != _false)
		{
			ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), Stack_Peek((((Processor) (_self->entity))->_localNamespaces)));
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле работы", 21)) == _equal)) != _false)
		{
			ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJobStage), StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Поле объекта", 23)) == _equal)) != _false)
		{
			ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
		}
		else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_locationType, StringFactory_FromUTF8(_stringFactory, "Глобальное поле", 29)) == _equal)) != _false)
		{
			ListMap_Add(_place, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext));
		}
		else
		{
			Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Попытка удалить несуществующее поле.", 68));
			Object_Release(_place);
			return _self;
		}
		Object _synonim;
		_synonim = Processor_ResolveName(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Synonim_RemoveReference(_synonim, _place);
		Object_Release(_place);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить работу", 29)) == _equal)) != _false)
	{
		List_PushBack(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить следующую стадию", 48)) == _equal)) != _false)
	{
		List_PushBack(ListMap_ListAt(ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Стадии", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Стадия", 12)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить условие входа на стадию", 60)) == _equal)) != _false)
	{
		Object _stage;
		_stage = ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Стадия", 12));
		List_PushBack(ListMap_ListAt(_stage, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Условие", 14)));
		Number_Inc(ListMap_NumberAt(_stage, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Очистить стадии", 29)) == _equal)) != _false)
	{
		List_Clean(ListMap_ListAt(ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)), StringFactory_FromUTF8(_stringFactory, "Стадии", 12)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Завершить работу", 31)) == _equal)) != _false)
	{
		List_RemoveFirst(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)));
	}
	else
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: неизвестное действие.", 71));
	}
	return _self;
}

Object Processor_InvokeMethod(Object _self, Object _methodName, Object _parameters)
{
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _method;
	_method = ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), _methodName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ошибка! Вызов несуществующего метода.", 69));
		AutoreleasePool_PopFrame(_autoreleasePool);
		return _self;
	}
	if((ListMap_LogicAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14))) != _false)
	{
		Object _adressConstant;
		_adressConstant = StringFactory_FromUTF8(_stringFactory, "Адрес", 10);
		Object _object;
		_object = (((Processor) (_self->entity))->_contextObject);
		( ( BasicMethod ) ListMap_ObjectAt( _method, _adressConstant ) )( _object, _parameters ); 
	}
	else
	{
		Object _namespace;
		_namespace = ListMap_Create();
		Stack_Push((((Processor) (_self->entity))->_localNamespaces), _namespace);
		Object_Release(_namespace);
		Object _methodBody;
		_methodBody = ListMap_ObjectAt(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8));
		Object _iterator;
		_iterator = List_First(_methodBody);
		while((Logic_Not(ListIterator_ThisEnd(_iterator))) != _false)
		{
			Processor_DoHelper(_self, ListIterator_ListMapData(_iterator));
			ListIterator_Next(_iterator);
		}
		Stack_Pop((((Processor) (_self->entity))->_localNamespaces));
	}
	AutoreleasePool_PopFrame(_autoreleasePool);
	return _self;
}

Object Processor_MessageConfirmsToParameter(Object _self, Object _message, Object _parameter)
{
	Object _checkingMethod;
	_checkingMethod = ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Совпадение", 20)) == _equal)) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Тип", 6))), ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Значение", 16))) == _equal)) != _false)
		{
			return _true;
		}
	}
	return _false;
}

Object Processor_TryLinkMessageWithJobStage(Object _self, Object _jobStage, Object _message)
{
	Object _messagesIterator;
	_messagesIterator = List_First(ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37)));
	while((Logic_Not(ListIterator_ThisEnd(_messagesIterator))) != _false)
	{
		Object _parametersIterator;
		_parametersIterator = List_First(ListIterator_ListData(_messagesIterator));
		Object _confirms;
		_confirms = _true;
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
			ListMap_Add(ListIterator_ListMapData(_messagesIterator), StringFactory_FromUTF8(_stringFactory, "Сообщение", 18), _message);
			Object _msgNeeded;
			_msgNeeded = ListMap_NumberAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39));
			Number_Dec(_msgNeeded);
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_msgNeeded, NumberFactory_FromLong(_numberFactory, 0)) == _equal)) != _false)
			{
				ListMap_Add(_jobStage, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Готовность", 20));
			}
		}
		ListIterator_Next(_messagesIterator);
	}
	return _self;
}

Object Processor_ProcessOneMessage(Object _self)
{
	Object _message;
	_message = Queue_Pop(ListMap_QueueAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Сообщения", 18)));
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
			Processor_TryLinkMessageWithJobStage(_self, _message, ListIterator_ListMapData(_jobStagesIterator));
			ListIterator_Next(_jobStagesIterator);
		}
		ListIterator_Next(_jobsIterator);
	}
	return _self;
}

Object Processor_ProcessOneJobIfAny(Object _self)
{
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
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Cостояние", 17)), StringFactory_FromUTF8(_stringFactory, "Готовность", 20)) == _equal)) != _false)
			{
				ListIterator_Hide(_jobsIterator);
				ListIterator_Hide(_jobStagesIterator);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStage), _jobStage);
				Object _emptyParameters;
				_emptyParameters = ListMap_Create();
				Processor_InvokeMethod(_self, ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Метод", 10)), _emptyParameters);
				Object_Release(_emptyParameters);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStage), _nil);
				return _self;
			}
			ListIterator_Next(_jobStagesIterator);
		}
		ListIterator_Next(_jobsIterator);
	}
	return _self;
}

Object Processor_ProcessObject(Object _self, Object _object)
{
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _object);
	Processor_ProcessOneMessage(_self);
	Processor_ProcessOneJobIfAny(_self);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _nil);
	AutoreleasePool_PopFrame(_autoreleasePool);
	return _self;
}
