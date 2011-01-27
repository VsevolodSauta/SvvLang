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
	Object_SetDeepCloner(toReturn, &Processor_DeepClone);
	((Processor) (toReturn->entity))->_contextObject = _nil;
	((Processor) (toReturn->entity))->_contextJobStage = _nil;
	((Processor) (toReturn->entity))->_contextJob = _nil;
	((Processor) (toReturn->entity))->_machine = _nil;
	((Processor) (toReturn->entity))->_localNamespaces = _nil;
	((Processor) (toReturn->entity))->_helperStack = _nil;
	((Processor) (toReturn->entity))->_processorCodes = _nil;
	toReturn = Processor_Init(toReturn);
	return toReturn;
}

Object Processor_Init(Object _self)
{
	(((Processor) (_self->entity))->_localNamespaces) = Stack_Create();
	(((Processor) (_self->entity))->_helperStack) = Stack_Create();
	(((Processor) (_self->entity))->_processorCodes) = ListMap_Create();
	return _self;
}

Object Processor_Clone(Object _self)
{
	return Processor_Create();
}

Object Processor_DeepClone(Object _self)
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
	_candidate = ListMap_ObjectAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
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
	_candidate = ListMap_SynonimAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)), _objectName);
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
	DPUSHS( "Processor: Sending message." ) 
	Object _uid;
	_uid = ListMap_ListAt(_message, StringFactory_FromUTF8(_stringFactory, "Получатель", 20));
	Object _receiver;
	_receiver = Machine_ObjectByUID((((Processor) (_self->entity))->_machine), _uid);
	Object _messageList;
	_messageList = ListMap_ListAt(_receiver, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18));
	List_PushBack(_messageList, _message);
	Machine_Schedule((((Processor) (_self->entity))->_machine), _uid);
	DPOPS( "Processor: Message sent." ) 
	return _self;
}

Object Processor_DoHelper(Object _self, Object _toDo)
{
	DPUSHS( "Processor: DOHelper." ) 
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
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_value, _nil) == _equal)) != _false)
		{
			_value = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		Processor_Do(_self, _value);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Разрешить имя", 25)) == _equal)) != _false)
	{
		Object _name;
		_name = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя", 6));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
		{
			_name = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		Stack_Push((((Processor) (_self->entity))->_helperStack), Processor_ResolveName(_self, _name));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Взять объект из синонима", 45)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
		{
			_synonim = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		}
		Stack_Push((((Processor) (_self->entity))->_helperStack), Synonim_Object(_synonim));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить текущий объект в вершину", 62)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextObject));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить текущую работу в вершину", 62)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJob));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить текущую стадию в вершину", 62)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), (((Processor) (_self->entity))->_contextJobStage));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить список в вершину", 47)) == _equal)) != _false)
	{
		Object _list;
		_list = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Список", 12));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_list, _nil) == _equal)) != _false)
		{
			_list = List_Create();
			Object_Autorelease(_list);
		}
		Stack_Push((((Processor) (_self->entity))->_helperStack), _list);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить отображение в вершину", 57)) == _equal)) != _false)
	{
		Object _listMap;
		_listMap = ListMap_ObjectAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Отображение", 22));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_listMap, _nil) == _equal)) != _false)
		{
			_listMap = ListMap_Create();
			Object_Autorelease(_listMap);
		}
		Stack_Push((((Processor) (_self->entity))->_helperStack), _listMap);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Удалить вершину", 29)) == _equal)) != _false)
	{
		Stack_Pop((((Processor) (_self->entity))->_helperStack));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить элемент в отображение", 57)) == _equal)) != _false)
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
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Добавить элемент в список", 47)) == _equal)) != _false)
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
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Дублировать вершину", 37)) == _equal)) != _false)
	{
		Stack_Push((((Processor) (_self->entity))->_helperStack), Stack_Peek((((Processor) (_self->entity))->_helperStack)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Поменять местами вершинные элементы", 67)) == _equal)) != _false)
	{
		Object _a;
		_a = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		Object _b;
		_b = Stack_Pop((((Processor) (_self->entity))->_helperStack));
		Stack_Push((((Processor) (_self->entity))->_helperStack), _a);
		Stack_Push((((Processor) (_self->entity))->_helperStack), _b);
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
	DPOPS( "Processor: DONEHelper." ) 
	return _self;
}

Object Processor_Do(Object _self, Object _toDo)
{
	DPUSHS( "Processor: DO." ) 
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
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Вызвать метод", 25)) == _equal)) != _false)
	{
		Processor_InvokeMethod(_self, ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Параметры", 18)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Определить метод", 31)) == _equal)) != _false)
	{
		ListMap_Add(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Метод", 10)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Удалить метод", 25)) == _equal)) != _false)
	{
		ListMap_Remove(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя метода", 19)));
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать ТВА", 21)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
		{
			Object _name;
			_name = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Существующее имя поля", 40));
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
			{
				Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректные параметры для действия \\\"Создать ТВА\\\".", 94));
				DPOPS( "Processor: DONE." ) 
				return _self;
			}
			_synonim = Processor_ResolveName(_self, _name);
		}
		Object _reference;
		_reference = ListMap_Create();
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), Stack_Peek((((Processor) (_self->entity))->_localNamespaces)));
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Synonim_AddReference(_synonim, _reference);
		Object_Release(_reference);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать поле работы", 36)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
		{
			Object _name;
			_name = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Существующее имя поля", 40));
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
			{
				Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректные параметры для действия \\\"Создать поле работы\\\".", 109));
				DPOPS( "Processor: DONE." ) 
				return _self;
			}
			_synonim = Processor_ResolveName(_self, _name);
		}
		Object _reference;
		_reference = ListMap_Create();
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), ListMap_ListMapAt((((Processor) (_self->entity))->_contextJob), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Synonim_AddReference(_synonim, _reference);
		Object_Release(_reference);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать поле объекта", 38)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
		{
			Object _name;
			_name = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Существующее имя поля", 40));
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
			{
				Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректные параметры для действия \\\"Создать поле объекта\\\".", 111));
				DPOPS( "Processor: DONE." ) 
				return _self;
			}
			_synonim = Processor_ResolveName(_self, _name);
		}
		Object _reference;
		_reference = ListMap_Create();
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Поля", 8)));
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Synonim_AddReference(_synonim, _reference);
		Object_Release(_reference);
	}
	else if((LogicFactory_FromLong(_logicFactory, Object_Compare(_action, StringFactory_FromUTF8(_stringFactory, "Создать глобальное поле", 44)) == _equal)) != _false)
	{
		Object _synonim;
		_synonim = ListMap_SynonimAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Синоним", 14));
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_synonim, _nil) == _equal)) != _false)
		{
			Object _name;
			_name = ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Существующее имя поля", 40));
			if((LogicFactory_FromLong(_logicFactory, Object_Compare(_name, _nil) == _equal)) != _false)
			{
				Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректные параметры для действия \\\"Создать глобальное поле\\\".", 117));
				DPOPS( "Processor: DONE." ) 
				return _self;
			}
			_synonim = Processor_ResolveName(_self, _name);
		}
		Object _reference;
		_reference = ListMap_Create();
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Пространство имен", 33), (((Machine) ((((Processor) (_self->entity))->_machine)->entity))->_globalContext));
		ListMap_Add(_reference, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15), ListMap_ListAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Имя поля", 15)));
		Synonim_AddReference(_synonim, _reference);
		Object_Release(_reference);
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
			DPOPS( "Processor: DONE." ) 
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
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Завершение работы", 33));
		List_RemoveFirst(ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Работы", 12)), ListMap_ListMapAt(_toDo, StringFactory_FromUTF8(_stringFactory, "Работа", 12)));
	}
	else
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Некорректное toDo: неизвестное действие.", 71));
	}
	DPOPS( "Processor: DONE." ) 
	return _self;
}

Object Processor_InvokeMethod(Object _self, Object _methodName, Object _parameters)
{
	DPUSHS( "Processor: Invoking method." ) 
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _method;
	_method = ListMap_ListMapAt(ListMap_ListMapAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Методы", 12)), _methodName);
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_method, _nil) == _equal)) != _false)
	{
		Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Ошибка! Вызов несуществующего метода.", 69));
		AutoreleasePool_PopFrame(_autoreleasePool);
		DPOPS( "Processor: Method processed." ) 
		return _self;
	}
	if((ListMap_LogicAt(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14))) != _false)
	{
		Object _adressConstant;
		_adressConstant = StringFactory_FromUTF8(_stringFactory, "Адрес", 10);
		Object _externalObjectEntity;
		_externalObjectEntity = ListMap_ObjectAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Сущность", 16));
		Object _object;
		_object = (((Processor) (_self->entity))->_contextObject);
		( ( BasicMethod ) ListMap_ObjectAt ( _method, _adressConstant ) ) ( _externalObjectEntity, _object, _parameters ) ; 
	}
	else
	{
		Object _namespace;
		_namespace = ListMap_Create();
		Stack_Push((((Processor) (_self->entity))->_localNamespaces), _namespace);
		ListMap_AddListMap(_namespace, _parameters);
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
	DPOPS( "Processor: Method processed." ) 
	return _self;
}

Object Processor_MessageConfirmsToParameter(Object _self, Object _message, Object _parameter)
{
	Object _checkingMethod;
	_checkingMethod = ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27));
	if((LogicFactory_FromLong(_logicFactory, Object_Compare(_checkingMethod, StringFactory_FromUTF8(_stringFactory, "Совпадение", 20)) == _equal)) != _false)
	{
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(ListMap_ObjectAt(_message, ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Ключ", 8))), ListMap_ObjectAt(_parameter, StringFactory_FromUTF8(_stringFactory, "Значение", 16))) == _equal)) != _false)
		{
			return _true;
		}
	}
	return _false;
}

Object Processor_TryLinkMessageWithJobStage(Object _self, Object _jobStage, Object _message)
{
	DPUSHS( "Processor: Trying to link message with a job." ) 
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
	DPOPS( "Processor: Message linking ended." ) 
	return _self;
}

Object Processor_ProcessOneMessage(Object _self)
{
	DPUSHS( "Processor: Processing message." ) 
	Object _messageList;
	_messageList = ListMap_ListAt((((Processor) (_self->entity))->_contextObject), StringFactory_FromUTF8(_stringFactory, "Сообщения", 18));
	if((Logic_Not(List_Empty(_messageList))) != _false)
	{
		Object _message;
		_message = List_PopFront(_messageList);
		if((LogicFactory_FromLong(_logicFactory, Object_Compare(_message, _nil) != _equal)) != _false)
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
					Processor_TryLinkMessageWithJobStage(_self, _message, ListIterator_ListMapData(_jobStagesIterator));
					ListIterator_Next(_jobStagesIterator);
				}
				ListIterator_Next(_jobsIterator);
			}
		}
	}
	DPOPS( "Processor: Message processed." ) 
	return _self;
}

Object Processor_ProcessOneJobIfAny(Object _self)
{
	DPUSHS( "Processor: Processing job." ) 
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
				Processor_InvokeMethod(_self, ListMap_ListAt(_jobStage, StringFactory_FromUTF8(_stringFactory, "Метод", 10)), _emptyParameters);
				Object_Release(_emptyParameters);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJobStage), _nil);
				Object_SetRetaining(&(((Processor) (_self->entity))->_contextJob), _nil);
				DPOPS( "Processor: Job processed." ) 
				return _self;
			}
			ListIterator_Next(_jobStagesIterator);
		}
		ListIterator_Next(_jobsIterator);
	}
	DPOPS( "Processor: Job processed." ) 
	return _self;
}

Object Processor_ProcessObject(Object _self, Object _uid)
{
	DPUSHS( "Processor: Processing object." ) 
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _object;
	_object = Machine_ObjectByUID((((Processor) (_self->entity))->_machine), _uid);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _object);
	Processor_ProcessOneMessage(_self);
	Processor_ProcessOneJobIfAny(_self);
	Object_SetRetaining(&(((Processor) (_self->entity))->_contextObject), _nil);
	AutoreleasePool_PopFrame(_autoreleasePool);
	DPOPS( "Processor: Object processed." ) 
	return _self;
}
