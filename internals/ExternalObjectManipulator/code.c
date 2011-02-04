#include "internals/basics.h"
#include "internals/ExternalObjectManipulator/imports.h"


Object ExternalObjectManipulator_Create(void)
{
	Object _self = Object_Create();
	DPUSHS ("ExternalObjectManipulator: Create begined.")
	_self->entity = Allocator_New(_allocator, sizeof(struct ExternalObjectManipulator));
	_self->gid =  8518571086308177920ull;
	Object_SetComparator(_self, &ExternalObjectManipulator_Compare);
	Object_SetDestructor(_self, &ExternalObjectManipulator_Destroy);
	Object_SetCloner(_self, &ExternalObjectManipulator_Clone);
	Object_SetDeepCloner(_self, &ExternalObjectManipulator_DeepClone);
	((ExternalObjectManipulator) (_self->entity))->_machine = _nil;
	((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy = _nil;
	_self = ExternalObjectManipulator_Init(_self);
	DPOPS ("ExternalObjectManipulator: Create ended.")
	return _self;
}

Object ExternalObjectManipulator_Init(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Init begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Init ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Clone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Clone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_DeepClone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: DeepClone begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: DeepClone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Destroy begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object_Release((((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy));
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalObjectManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Compare(Object _self, Object _manipulator)
{
	DPUSHS ("ExternalObjectManipulator: Compare begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object toReturn = _equal;
	DPOPS ("ExternalObjectManipulator: Compare ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalObjectManipulator: SetMachine begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	(((ExternalObjectManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CreateUIDObject(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: CreateUIDObject begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	AutoreleasePool_PushFrame(_autoreleasePool);
	Object _uid;
	_uid = Machine_ImportUID((((ExternalObjectManipulator) (_self->entity))->_machine), StringFactory_FromUTF8(_stringFactory, "Объект", 12));
	ExternalObjectManipulator_SetBasicMethodWithNameForUID(_self, MethodFactory_FromPointer(_methodFactory, &ExternalObjectManipulator_CloneUIDObjectBasicMethod), StringFactory_FromUTF8(_stringFactory, "Клонировать", 22), _uid);
	(((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy) = Object_DeepClone(Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid));
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _uid;
	DPOPS ("ExternalObjectManipulator: CreateUIDObject ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetBasicMethodWithNameForUID(Object _self, Object _method, Object _name, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: SetBasicMethodWithNameForUID begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый метод", 25), _method);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _true);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetBasicMethodWithNameForUID ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMethodWithNameForUID(Object _self, Object _methodBody, Object _name, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: SetMethodWithNameForUID begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8), _methodBody);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMethodWithNameForUID ended.")
	return toReturn;
}

Object ExternalObjectManipulator_CloneUIDObjectBasicMethod(Object _self, Object _uid, Object _parameters, Object _processor)
{
	DPUSHS ("ExternalObjectManipulator: CloneUIDObjectBasicMethod begined.")
	ASSERT_C ( "Checking for correct object type", _self->gid ==  8518571086308177920ulll )
	Object _object;
	_object = Machine_UIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GenerateUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	Object _objectToReturn;
	_objectToReturn = Object_DeepClone((((ExternalObjectManipulator) (_self->entity))->_objectMasterCopy));
	ListMap_Add(_objectToReturn, StringFactory_FromUTF8(_stringFactory, "Методы", 12), Object_TempDeepClone(ListMap_ObjectAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12))));
	ListMap_Add(_objectToReturn, StringFactory_FromUTF8(_stringFactory, "Поля", 8), Object_TempDeepClone(ListMap_ObjectAt(_object, StringFactory_FromUTF8(_stringFactory, "Поля", 8))));
	Object _list;
	_list = List_Create();
	ListMap_Add(ListMap_ListMapAt(_objectToReturn, StringFactory_FromUTF8(_stringFactory, "Свойства", 16)), StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28), _list);
	Object_Release(_list);
	Machine_SetUIDToObject((((ExternalObjectManipulator) (_self->entity))->_machine), _uidToReturn, _objectToReturn);
	Object_Release(_objectToReturn);
	Object _receiver;
	_receiver = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Сообщение на клонирование", 48), StringFactory_FromUTF8(_stringFactory, "Получатель", 20));
	Object _sender;
	_sender = Processor_EntityFromNamedMessageField(_processor, StringFactory_FromUTF8(_stringFactory, "Сообщение на клонирование", 48), StringFactory_FromUTF8(_stringFactory, "Отправитель", 22));
	Object _message;
	_message = ListMap_Create();
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Отправитель", 22), _receiver);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Получатель", 20), _sender);
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Тип", 6), StringFactory_FromUTF8(_stringFactory, "Ответ", 10));
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Ответ", 10), StringFactory_FromUTF8(_stringFactory, "Успех", 10));
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Запрос", 12), StringFactory_FromUTF8(_stringFactory, "Клонировать", 22));
	ListMap_Add(_message, StringFactory_FromUTF8(_stringFactory, "Клон", 8), _uidToReturn);
	Processor_SendMessage(_processor, _message);
	Object_Release(_message);
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Сообщение послано. Ура!", 42));
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: CloneUIDObjectBasicMethod ended.")
	return toReturn;
}
