#include "internals/basics.h"
#include "internals/ExternalEntitiesFactory/imports.h"


Object ExternalEntitiesFactory_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalEntitiesFactory: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalEntitiesFactory));
	_self->gid =  4514905638553083904ull;
	Object_SetComparator(_self, &ExternalEntitiesFactory_Compare);
	Object_SetDestructor(_self, &ExternalEntitiesFactory_Destroy);
	Object_SetCloner(_self, &ExternalEntitiesFactory_Clone);
	Object_SetDeepCloner(_self, &ExternalEntitiesFactory_DeepClone);
	((ExternalEntitiesFactory) (_self->entity))->_placeHolder = _nil;
	DPOPS ("ExternalEntitiesFactory: Create ended.")
	return _self;
}

Object ExternalEntitiesFactory_Clone(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: Clone begined.")
	ASSERT_C ( "ExternalEntitiesFactory:Clone --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalEntitiesFactory: Clone ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_DeepClone(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: DeepClone begined.")
	ASSERT_C ( "ExternalEntitiesFactory:DeepClone --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = Object_Retain(_self);
	DPOPS ("ExternalEntitiesFactory: DeepClone ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_Destroy(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: Destroy begined.")
	ASSERT_C ( "ExternalEntitiesFactory:Destroy --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalEntitiesFactory: Destroy ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_Compare(Object _self, Object _entitiesFactory)
{
	DPUSHS ("ExternalEntitiesFactory: Compare begined.")
	ASSERT_C ( "ExternalEntitiesFactory:Compare --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	ASSERT_C ( "ExternalEntitiesFactory:Compare --- Checking for correct parameter type failed at parameter _entitiesFactory.", _entitiesFactory->gid ==  4514905638553083904ull || _entitiesFactory == _nil )
	Object toReturn = _equal;
	DPOPS ("ExternalEntitiesFactory: Compare ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyListMap(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyListMap begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyListMap --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ListMap_Create();
	Object toReturn = Object_Autorelease(_toReturn);
	DPOPS ("ExternalEntitiesFactory: CreateEmptyListMap ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyList(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyList begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyList --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = List_Create();
	Object toReturn = Object_Autorelease(_toReturn);
	DPOPS ("ExternalEntitiesFactory: CreateEmptyList ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyJob(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyJob begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyJob --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Поля", 8), ExternalEntitiesFactory_CreateEmptyListMap(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37), ExternalEntitiesFactory_CreateEmptyListMap(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Стадии", 12), ExternalEntitiesFactory_CreateEmptyListMap(_self));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyJob ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyMethod(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyMethod begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyMethod --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Тело", 8), ExternalEntitiesFactory_CreateEmptyList(_self));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyMethod ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyJobStage(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyJobStage begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyJobStage --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Метод", 10), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Необходимо сообщений", 39), NumberFactory_FromLong(_numberFactory, 0));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Готово", 12));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyJobStage ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateConditionPresence(Object _self, Object _key)
{
	DPUSHS ("ExternalEntitiesFactory: CreateConditionPresence begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateConditionPresence --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	ASSERT_C ( "ExternalEntitiesFactory:CreateConditionPresence --- Checking for correct parameter type failed at parameter _key.", _key->gid ==  3732711262168886272ull || _key == _nil )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27), StringFactory_FromUTF8(_stringFactory, "Наличие", 14));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), _key);
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateConditionPresence ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateConditionEquality(Object _self, Object _key, Object _value)
{
	DPUSHS ("ExternalEntitiesFactory: CreateConditionEquality begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateConditionEquality --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	ASSERT_C ( "ExternalEntitiesFactory:CreateConditionEquality --- Checking for correct parameter type failed at parameter _key.", _key->gid ==  3732711262168886272ull || _key == _nil )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Метод проверки", 27), StringFactory_FromUTF8(_stringFactory, "Совпадение", 20));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Ключ", 8), Object_TempClone(_key));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Значение", 16), Object_TempClone(_value));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateConditionEquality ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyMessageSlot(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyMessageSlot begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyMessageSlot --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Метод идентификации", 37), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Стадии", 12), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Состояние", 18), StringFactory_FromUTF8(_stringFactory, "Открыто", 14));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), ExternalEntitiesFactory_CreateEmptyList(_self));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyMessageSlot ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateRequestMessageSlot(Object _self, Object _request)
{
	DPUSHS ("ExternalEntitiesFactory: CreateRequestMessageSlot begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateRequestMessageSlot --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	ASSERT_C ( "ExternalEntitiesFactory:CreateRequestMessageSlot --- Checking for correct parameter type failed at parameter _request.", _request->gid ==  3732711262168886272ull || _request == _nil )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyMessageSlot(_self);
	ListMap_MessageSlotSetCondition(_toReturn, ExternalEntitiesFactory_CreateConditionEquality(_self, StringFactory_FromUTF8(_stringFactory, "Тип", 6), StringFactory_FromUTF8(_stringFactory, "Запрос", 12)));
	ListMap_MessageSlotSetCondition(_toReturn, ExternalEntitiesFactory_CreateConditionEquality(_self, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), _request));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateRequestMessageSlot ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateReplyMessageSlot(Object _self, Object _request)
{
	DPUSHS ("ExternalEntitiesFactory: CreateReplyMessageSlot begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateReplyMessageSlot --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	ASSERT_C ( "ExternalEntitiesFactory:CreateReplyMessageSlot --- Checking for correct parameter type failed at parameter _request.", _request->gid ==  3732711262168886272ull || _request == _nil )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyMessageSlot(_self);
	ListMap_MessageSlotSetCondition(_toReturn, ExternalEntitiesFactory_CreateConditionEquality(_self, StringFactory_FromUTF8(_stringFactory, "Тип", 6), StringFactory_FromUTF8(_stringFactory, "Ответ", 10)));
	ListMap_MessageSlotSetCondition(_toReturn, ExternalEntitiesFactory_CreateConditionEquality(_self, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), _request));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateReplyMessageSlot ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateObject(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateObject begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateObject --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Методы", 12), ExternalEntitiesFactory_CreateEmptyMethods(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Поля", 8), ExternalEntitiesFactory_CreateEmptyFields(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Свойства", 16), ExternalEntitiesFactory_CreateEmptyProperties(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Работы", 12), ExternalEntitiesFactory_CreateEmptyJobs(_self));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateObject ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyMessage(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyMessage begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyMessage --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	Object _attribs;
	_attribs = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_attribs, StringFactory_FromUTF8(_stringFactory, "Ожидаемые сообщения", 37), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Атрибуты", 16), _attribs);
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyMessage ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyFields(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyFields begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyFields --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	DPOPS ("ExternalEntitiesFactory: CreateEmptyFields ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyMethods(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyMethods begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyMethods --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	DPOPS ("ExternalEntitiesFactory: CreateEmptyMethods ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyJobs(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyJobs begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyJobs --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	DPOPS ("ExternalEntitiesFactory: CreateEmptyJobs ended.")
	return toReturn;
}

Object ExternalEntitiesFactory_CreateEmptyProperties(Object _self)
{
	DPUSHS ("ExternalEntitiesFactory: CreateEmptyProperties begined.")
	ASSERT_C ( "ExternalEntitiesFactory:CreateEmptyProperties --- Checking for correct object type failed.", _self->gid ==  4514905638553083904ull )
	Object _toReturn;
	_toReturn = ExternalEntitiesFactory_CreateEmptyListMap(_self);
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28), ExternalEntitiesFactory_CreateEmptyList(_self));
	ListMap_Add(_toReturn, StringFactory_FromUTF8(_stringFactory, "Имя", 6), ExternalEntitiesFactory_CreateEmptyList(_self));
	Object toReturn = _toReturn;
	DPOPS ("ExternalEntitiesFactory: CreateEmptyProperties ended.")
	return toReturn;
}
