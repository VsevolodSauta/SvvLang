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
	_self = ExternalObjectManipulator_Init(_self);
	DPOPS ("ExternalObjectManipulator: Create ended.")
	return _self;
}

Object ExternalObjectManipulator_Init(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Init begined.")
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Init ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Clone(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Clone begined.")
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: Clone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Destroy(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Destroy begined.")
	Object toReturn = Object_Destroy(_self);
	DPOPS ("ExternalObjectManipulator: Destroy ended.")
	return toReturn;
}

Object ExternalObjectManipulator_Compare(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: Compare begined.")
	Object toReturn = _equal;
	DPOPS ("ExternalObjectManipulator: Compare ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMachine(Object _self, Object _machine)
{
	DPUSHS ("ExternalObjectManipulator: SetMachine begined.")
	(((ExternalObjectManipulator) (_self->entity))->_machine) = _machine;
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMachine ended.")
	return toReturn;
}

Object ExternalObjectManipulator_ObjectCreate(Object _self)
{
	DPUSHS ("ExternalObjectManipulator: ObjectCreate begined.")
	AutoreleasePool_PushFrame(_autoreleasePool);
	Console_WriteLnString(_console, StringFactory_FromUTF8(_stringFactory, "Создаем объект.", 28));
	Object _object;
	_object = ListMap_Create();
	Object _messageList;
	_messageList = List_Create();
	Object _methods;
	_methods = ListMap_Create();
	Object _fields;
	_fields = ListMap_Create();
	Object _jobs;
	_jobs = List_Create();
	Object _properties;
	_properties = ListMap_Create();
	Object _uids;
	_uids = List_Create();
	Object _uid;
	_uid = Machine_GetUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	List_PushBack(_uids, _uid);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12), _methods);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Поля", 8), _fields);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Свойства", 16), _properties);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Работы", 12), _jobs);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Сообщения", 18), _messageList);
	ListMap_Add(_object, StringFactory_FromUTF8(_stringFactory, "Идентификаторы", 28), _uids);
	Machine_SetObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid, _object);
	Object_Release(_object);
	Object_Release(_jobs);
	Object_Release(_fields);
	Object_Release(_properties);
	Object_Release(_methods);
	Object_Release(_messageList);
	Object_Release(_uids);
	AutoreleasePool_PopFrame(_autoreleasePool);
	Object toReturn = _uid;
	DPOPS ("ExternalObjectManipulator: ObjectCreate ended.")
	return toReturn;
}

Object ExternalObjectManipulator_ObjectClone(Object _self, Object _uid)
{
	DPUSHS ("ExternalObjectManipulator: ObjectClone begined.")
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _uidToReturn;
	_uidToReturn = Machine_GetUID((((ExternalObjectManipulator) (_self->entity))->_machine));
	Object _objectToReturn;
	_objectToReturn = Object_DeepClone(_object);
	Machine_SetObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uidToReturn, _objectToReturn);
	Object_Release(_objectToReturn);
	Object toReturn = _uidToReturn;
	DPOPS ("ExternalObjectManipulator: ObjectClone ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetBasicMethodForObjectWithName(Object _self, Object _methodAdress, Object _uid, Object _name)
{
	DPUSHS ("ExternalObjectManipulator: SetBasicMethodForObjectWithName begined.")
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Адрес", 10), _methodAdress);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _true);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetBasicMethodForObjectWithName ended.")
	return toReturn;
}

Object ExternalObjectManipulator_SetMethodForObjectWithName(Object _self, Object _methodBody, Object _uid, Object _name)
{
	DPUSHS ("ExternalObjectManipulator: SetMethodForObjectWithName begined.")
	Object _object;
	_object = Machine_ObjectByUID((((ExternalObjectManipulator) (_self->entity))->_machine), _uid);
	Object _methods;
	_methods = ListMap_ListMapAt(_object, StringFactory_FromUTF8(_stringFactory, "Методы", 12));
	Object _method;
	_method = ListMap_Create();
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Тело", 8), _methodBody);
	ListMap_Add(_method, StringFactory_FromUTF8(_stringFactory, "Базовый", 14), _false);
	ListMap_Add(_methods, _name, _method);
	Object_Release(_method);
	Object toReturn = _self;
	DPOPS ("ExternalObjectManipulator: SetMethodForObjectWithName ended.")
	return toReturn;
}
